#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "Controller.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "Image.h"
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
};

void RDCApp::prepareSettings( Settings *settings ){
    settings->setWindowSize( 1082, 887 );
    settings->setFrameRate( 60.0f );
}

void RDCApp::setup()
{
    width = getWindowWidth();
    height = getWindowHeight();
    
    controller = new Controller();
    controller->init(width, height);
    controller->calibrate();
    //TODO open image
    //convert to Image
    Image img;
    img.load("/Users/Gaston/dev/RDC/resources/cucu.jpg");
    controller->process(img);
}

void RDCApp::mouseDown( cinder::app::MouseEvent event )
{
}

void RDCApp::update()
{
}

void RDCApp::draw()
{
	//clear out the window with black
    ci::gl::clear( ci::Color( 0, 0, 0 ) );
    //ci::gl::drawSolidCircle( ci::Vec2f( 30, 30 ), 50.0f );

}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif