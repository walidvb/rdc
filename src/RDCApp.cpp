#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "Controller.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Image.h"
#include "Renderer_A.h"
#include "Sensor.h"
#include "cinder/gl/Texture.h"
using namespace std;

class RDCApp : public cinder::app::AppBasic {
public:
	void setup();
    void keyDown( cinder::app::KeyEvent event );
    void mouseUp( ci::app::MouseEvent event);
    void mouseDown( ci::app::MouseEvent event);
    void mouseDrag(ci::app::MouseEvent event);
    void mouseMove(ci::app::MouseEvent event);
	void update();
	void draw();
    void quit();
    void prepareSettings(Settings *settings);
    
    void loadFiles();
private:
    Controller* controller;
    int width, height;
    Image imgProcessed;
    Image imgSource;
    Sensor movie;
    bool watchingMovie;
    bool isCalibrated;
    bool isGrabOk;
    ci::gl::Texture textureProcessed;
    ci::gl::Texture textureSource;
    ci::Vec2f rectStart;    //<! the rectangle to be drawn when selecting an area
    ci::Vec2f rectEnd;
    bool rectDraw;
    
    bool isImgProcessed;
    bool isFullScreen;
    bool displayCompensated;
    bool newProcessReq;
    bool isReady;               //<! set to true when ready to scan+process
    vector<string> sources;
    int sourceID;
};

void RDCApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
    settings->enableSecondaryDisplayBlanking();
}

void RDCApp::setup()
{
    width = getWindowWidth();
    height = getWindowHeight();
    displayCompensated = true;
    controller = new Controller();
    controller->init(width, height);
    
    isCalibrated = false;
    isGrabOk = false;
    isImgProcessed = false;
    isFullScreen = false;
    newProcessReq = false;
    isReady = false;
    rectDraw = false;
    watchingMovie = true;
    loadFiles();
    int w = imgSource.getWidth();
    int h = imgSource.getHeight();
    cout << "[RDCApp]: Source size: " << w << " " << h << endl;
    //conversion from Image (cv::Mat) to ci::surface
    ci::Surface8u surface(w, h, false);
    for(int i = 0; i < w; i+=1)
    {
        for (int j = 0; j<h; j+=1)
        {
            cv::Vec3b pixel = imgSource.pixelAt(i,j);
            unsigned char b = pixel[0];
            unsigned char g = pixel[1];
            unsigned char r = pixel[2];
            cinder::Vec2i pos(i,j);
            ci::ColorT<unsigned char> color(r,g,b);
            surface.setPixel(pos, color);
        }
    }
    textureSource = ci::gl::Texture(surface);
}

void RDCApp::loadFiles()
{
    if(!watchingMovie)
    {
        //Get source image in a format Cinder can draw
        sources.push_back("lena.jpg");
        sources.push_back("testPic.jpg");
        sources.push_back("goccia.jpg");
        sources.push_back("ba.jpg");
        sources.push_back("manaus.jpg");
        sources.push_back("rio.jpg");
        sources.push_back("cucu.jpg");
        sourceID = 0;
        imgSource.load("/Users/Gaston/dev/RDC/resources/" + sources[sourceID]);
    }
    else
    {
        movie.init("/Users/Gaston/dev/RDC/resources/dbz.mpg");
    }

}

void RDCApp::update()
{
    if(isReady)
    {
        if(controller->isRDCCalibrated && (!isImgProcessed || newProcessReq))
        {
            
            if(!watchingMovie)
            {
                imgSource.load("/Users/Gaston/dev/RDC/resources/" + sources[sourceID]);
                newProcessReq = false;
            }
            else
            {
                imgSource = movie.grabFrame();
                imgSource.resize(800, 600);
                newProcessReq = true;
            }
            int w = imgSource.getWidth();
            int h = imgSource.getHeight();
            if(displayCompensated || !watchingMovie)
            {

                //conversion from Image (cv::Mat) to ci::surface
                ci::Surface8u surfacesrc(w, h, false);
                for(int i = 0; i < w; i+=1)
                {
                    for (int j = 0; j<h; j+=1)
                    {
                        cv::Vec3b pixel = imgSource.pixelAt(i,j);
                        unsigned char b = pixel[0];
                        unsigned char g = pixel[1];
                        unsigned char r = pixel[2];
                        cinder::Vec2i pos(i,j);
                        ci::ColorT<unsigned char> color(r,g,b);
                        surfacesrc.setPixel(pos, color);
                    }
                }
                textureSource = ci::gl::Texture(surfacesrc);
            }
            
            controller->process(imgSource);
            //conversion from Image (cv::Mat) to ci::surface
            ci::Surface8u surface(w, h, false);
            for(int i = 0; i < w; i+=1)
            {
                for (int j = 0; j<h; j+=1)
                {
                    cv::Vec3b pixel = imgSource.pixelAt(i,j);
                    unsigned char b = pixel[0];
                    unsigned char g = pixel[1];
                    unsigned char r = pixel[2];
                    cinder::Vec2i pos(i,j);
                    ci::ColorT<unsigned char> color(r,g,b);
                    surface.setPixel(pos, color);
                }
            }
            textureProcessed = ci::gl::Texture(surface);
            isImgProcessed = true;
            //cout << "[RDCApp]: image processed!" << endl;
        }
        
    }
}

void RDCApp::draw()
{
    if(!controller->isRDCCalibrated && isReady)
    {
        ci::gl::clear( ci::Color( 0, 0, 0 ) );
        controller->calibrate();
    }
    else
    {
        ci::gl::clear( ci::Color( 0, 0, 0 ) );
        //drawing code here
        if(displayCompensated && isImgProcessed)
        {
            ci::gl::draw(textureProcessed);
        }
        else
        {
            ci::gl::draw(textureSource);
        }
    }
    if(rectDraw)
    {
        ci::Rectf rect(rectStart, rectEnd);
        cinder::gl::drawStrokedRect(rect);
    }
}

void RDCApp::keyDown( cinder::app::KeyEvent event )
{
    if( event.getCode() == cinder::app::KeyEvent::KEY_RETURN )
    {
        isReady = !isReady;
        return;
    }
    char command = event.getChar();
    switch(command)
    {
        case 'f':
            isFullScreen = !isFullScreen;
            setFullScreen(isFullScreen);
            break;
        case 'c':
            displayCompensated = !displayCompensated;
            break;
        case 'p':
            newProcessReq = true;
            break;
        case 'o':
            sourceID = (sourceID+1)%sources.size();
            newProcessReq = true;
            break;
        case 'v':
            watchingMovie = !watchingMovie;
            loadFiles();
            break;
        case 'q':
            exit(0);
            break;
        default:
            controller->sendCommand(command);
            break;
    }
}

void RDCApp::mouseMove( ci::app::MouseEvent event )
{
    event.getPos();
}

void RDCApp::mouseDrag( ci::app::MouseEvent event ) {
    mouseMove( event );
    int x = min(max(0,event.getX()), width);
    int y = min(max(0,event.getY()), height);
    rectEnd = ci::Vec2f(x, y);
}

void RDCApp::mouseDown( ci::app::MouseEvent event)
{
    int x = min(max(0,event.getX()), width);
    int y = min(max(0,event.getY()), height);
    controller->mouseDown(x, y);
    rectDraw = true;
    rectStart = ci::Vec2f(x, y);
    rectEnd = rectStart;
}

void RDCApp::mouseUp( ci::app::MouseEvent event)
{
    int x = min(max(0,event.getX()), width);
    int y = min(max(0,event.getY()), height);
    controller->mouseUp(x, y);
    rectDraw = false;
}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif