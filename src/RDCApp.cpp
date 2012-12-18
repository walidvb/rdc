#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"

#include "RDC.h"
#include "Camera.h"
#include "Camera_A.h"
#include "Renderer_A.h"
#include "Renderer_Cinder.h"

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
    Camera_A* cam;
    RDC* rdc;
    Renderer_A* gfx;
    
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
    
    cam = new Cam(20,10);
    cam->init();
    gfx = new Renderer_Cinder(width, height);
    rdc = new RDC(cam, gfx);
    rdc->calibrate();
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
    rdc->calibrate();

}

void RDCApp::quit()
{
    delete cam;
    delete rdc;
    delete gfx;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif