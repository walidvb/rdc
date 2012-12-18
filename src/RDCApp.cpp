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
    
private:
    Camera_A* cam;
    RDC* rdc;
    Renderer_A* gfx;
};

void RDCApp::setup()
{
    cam = new Cam(20,10);
    cam->init();
    gfx = new Renderer_Cinder();
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
    delete gfx;
}

CINDER_APP_BASIC( RDCApp, cinder::app::RendererGl )
#endif