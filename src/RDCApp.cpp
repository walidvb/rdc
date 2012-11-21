#ifndef RDC_APP_h
#define RDC_APP_h

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

#include "RDC.h"
#include "Camera.h"
#include "Camera_A.h"
using namespace std;

class RDCApp : public cinder::app::AppBasic {
  public:
	void setup();
	void mouseDown( cinder::app::MouseEvent event );	
	void update();
	void draw();
    void quit();
    
private:
    Camera_A* cam;
    RDC* rdc;
};

void RDCApp::setup()
{
    cam = new Camera(20,10);
    cam->init();
    rdc = new RDC(cam);
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
}

void RDCApp::quit()
{
    delete cam;
    delete rdc;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif