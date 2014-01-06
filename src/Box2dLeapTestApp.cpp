#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Box2dLeapTestApp : public AppNative {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void Box2dLeapTestApp::setup()
{
}

void Box2dLeapTestApp::mouseDown( MouseEvent event )
{
}

void Box2dLeapTestApp::update()
{
}

void Box2dLeapTestApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_NATIVE( Box2dLeapTestApp, RendererGl )
