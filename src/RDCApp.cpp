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
	void mouseDown( cinder::app::MouseEvent event );
    void keyDown( cinder::app::KeyEvent event );
	void update();
	void draw();
    void quit();
    void prepareSettings(Settings *settings);
    
private:
    Controller* controller;
    int width, height;
    Image img;
    bool isCalibrated;
    bool isGrabOk;
    ci::gl::Texture myImg;
    //give surface to texture
    bool isImgProcessed;
    bool isFullScreen;
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
    
    controller = new Controller();
    controller->init(width, height);
    
    isCalibrated = false;
    isGrabOk = false;
    isImgProcessed = false;
    img.load("/Users/Gaston/dev/RDC/resources/goccia.jpg");
    isFullScreen = false;
}

void RDCApp::mouseDown( cinder::app::MouseEvent event )
{
}

void RDCApp::keyDown( cinder::app::KeyEvent event )
{
    char command = event.getChar();
    controller->sendCommand(command);
    if(command == 'f')
    {
        isFullScreen = !isFullScreen;
        setFullScreen(isFullScreen);
    }
}
void RDCApp::update()
{
    if(isFullScreen)
    {
        if(controller->isRDCCalibrated && !isImgProcessed)
        {
            controller->process(img);
            int w = img.getWidth();
            int h = img.getHeight();
            
            //conversion from Image (cv::Mat) to ci::surface
            ci::Surface8u surface(w, h, false);
            for(int i = 0; i < w; i+=1)
            {
                for (int j = 0; j<h; j+=1)
                {
                    cv::Vec3b pixel = img.pixelAt(i,j);
                    unsigned char b = pixel[0];
                    unsigned char g = pixel[1];
                    unsigned char r = pixel[2];
                    cinder::Vec2i pos(i,j);
                    ci::ColorT<unsigned char> color(r,g,b);
                    surface.setPixel(pos, color);
                }
            }
            myImg = ci::gl::Texture(surface);
            isImgProcessed = true;
        }
    }

}

void RDCApp::draw()
{
    if(isFullScreen)
    {
        if(!controller->isRDCCalibrated)
        {
            ci::gl::clear( ci::Color( 0, 0, 0 ) );
            controller->calibrate();
        }
        else
        {
            ci::gl::clear( ci::Color( 0, 0, 0 ) );
            //drawing code here
            ci::gl::draw(myImg);
        }
    }
    else
    {
        ci::gl::clear( ci::Color( 15, 0, 0 ) );
    }
}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif