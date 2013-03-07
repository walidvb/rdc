#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "Controller.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Image.h"
#include "Renderer_A.h"
#include "cinder/gl/Texture.h"
using namespace std;

class RDCApp : public cinder::app::AppBasic {
public:
	void setup();
    void keyDown( cinder::app::KeyEvent event );
	void update();
	void draw();
    void quit();
    void prepareSettings(Settings *settings);
    
private:
    Controller* controller;
    int width, height;
    Image imgProcessed;
    Image imgSource;
    bool isCalibrated;
    bool isGrabOk;
    ci::gl::Texture textProcessed;
    ci::gl::Texture textSource;

    //give surface to texture
    bool isImgProcessed;
    bool isFullScreen;
    bool compensate;
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
    compensate = false;
    controller = new Controller();
    controller->init(width, height);
    
    isCalibrated = false;
    isGrabOk = false;
    isImgProcessed = false;
    isFullScreen = false;
    
    //Get source image in a format Cinder can draw
    imgSource.load("/Users/Gaston/dev/RDC/resources/testPic.jpg");
    int w = imgSource.getWidth();
    int h = imgSource.getHeight();
    
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
    textSource = ci::gl::Texture(surface);
    
}

void RDCApp::keyDown( cinder::app::KeyEvent event )
{
    char command = event.getChar();
    switch(command)
    {
        case 'f':
            isFullScreen = !isFullScreen;
            setFullScreen(isFullScreen);
            break;
        case 'c':
            compensate = !compensate;
            break;
        default:
            controller->sendCommand(command);
            break;
    }
    
   
    
}
void RDCApp::update()
{
    if(isFullScreen)
    {
        if(controller->isRDCCalibrated && !isImgProcessed)
        {
            controller->process(imgSource);
            int w = imgSource.getWidth();
            int h = imgSource.getHeight();
            
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
            textProcessed = ci::gl::Texture(surface);
            isImgProcessed = true;
        }
    }
    
}

void RDCApp::draw()
{
        if(!controller->isRDCCalibrated && isFullScreen)
        {
            ci::gl::clear( ci::Color( 0, 0, 0 ) );
            controller->calibrate();
        }
        else
        {
            ci::gl::clear( ci::Color( 0, 0, 0 ) );
            //drawing code here
            if(compensate && isImgProcessed)
            {
                ci::gl::draw(textProcessed);
            }
            else
            {
                ci::gl::draw(textSource);
            }
        }

}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif