#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "Controller.h"

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
    settings->setWindowSize( 800, 600 );
    settings->setFrameRate( 60.0f );
}

void RDCApp::setup()
{
    width = getWindowWidth();
    height = getWindowHeight();
    
    controller = new Controller();
    controller->init(width, height);
    controller->process();
}

void RDCApp::mouseDown( cinder::app::MouseEvent event )
{
}

void RDCApp::update()
{
}

void RDCApp::draw()
{
	// clear out the window with black
    ci::gl::clear( ci::Color( 0, 0, 0 ) );
}

void RDCApp::quit()
{
    delete controller;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif