#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "Controller.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Image.h"
#include "Renderer_A.h"
using namespace std;

class RDCApp : public cinder::app::AppBasic {
  public:
	void setup();
	void mouseDown( cinder::app::MouseEvent event );	
	void update();
	void draw();
    void quit();
    void prepareSettings(Settings *settings);
    
private:
    Controller* controller;
    int width, height;
    Image img;
    bool isCalibrated;
};

void RDCApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 640, 480 );
    settings->setFrameRate( 60.0f );
    setFullScreen( true );
}

void RDCApp::setup()
{
    width = getWindowWidth();
    height = getWindowHeight();
    
    controller = new Controller();
    controller->init(width, height);

    isCalibrated = false;
    img.load("/Users/Gaston/dev/RDC/resources/cucu.jpg");
}

void RDCApp::mouseDown( cinder::app::MouseEvent event )
{
}

void RDCApp::update()
{
}

void RDCApp::draw()
{
    ci::gl::clear( ci::Color( 0, 0, 0 ) );

    if(!isCalibrated)
    {
        controller->calibrate();
        controller->process(img);
        isCalibrated = true;
    }

	//clear out the window with black
    controller->getRenderer()->drawImg(&img);

}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif