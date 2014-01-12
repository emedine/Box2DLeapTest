#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Triangulate.h"
#include "cinder/Rand.h"

#include "Conversions.h"
#include "ParticleController.h"
#include "BottleController.h"
#include "SparkController.h"
///#include <cinder/KeyEvent.h>
/// box 2d
//#include "suBox2D.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace particles;
using namespace bottles;

b2Vec2 gravity(0.0f, 10.0f);
b2World world(gravity);




class Box2dLeapTestApp : public AppBasic {

  BottleController bottleController;
    ParticleController particleController;
  SparkController sparkController;
  public:
    void prepareSettings( Settings *settings );
    void setup();
    virtual void doMouseDown(MouseEvent event);
    virtual void doMouseUp(MouseEvent event);
    virtual void mouseMove(MouseEvent event);
    virtual void mouseDrag(MouseEvent event);
    virtual void keyDown(KeyEvent event);
    void update();
    void draw();
    
    
    
private:
    float width;
    float height;
    bool mousePressed;
    Vec2f mousePos;
    Vec2f mouseVel;
    
};


void Box2dLeapTestApp::prepareSettings( Settings *settings )
{
    settings->setWindowSize( 1024, 768 );
}

void Box2dLeapTestApp::setup()
{
    mousePressed = false;
    
    /////// SET ALL BOX2D OBJECTS /////////
    // first define a ground box (no mass)
    // 1. define a body
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(Conversions::toPhysics(app::getWindowWidth()/2), Conversions::toPhysics(app::getWindowHeight())); // pos of ground
    
    // 2. use world to create body
    b2Body* groundBody = world.CreateBody(&groundBodyDef);
    
    // 3. define fixture
    b2PolygonShape groundBox;
    groundBox.SetAsBox(Conversions::toPhysics(app::getWindowWidth()/2), Conversions::toPhysics(1.0f)); // size the ground
    
    // 4. create fixture on body
    groundBody->CreateFixture(&groundBox, 0.0f);
    
    // pass world to ParticleController and bottles
    particleController.setup(world);
    bottleController.setup(world);

   
}


//////// INPUT FUNCTIONS ////////////////////////////
void Box2dLeapTestApp::keyDown( KeyEvent event )
{
    
    switch ( event.getChar() )
    {
        case 'b':
            sparkController.addSparks(125, mousePos, mouseVel);
            bottleController.addBottle(mousePos);
            break;
            
        case 'c':
            sparkController.addSparks(125, mousePos, mouseVel);
            particleController.addParticle(mousePos);
            break;
            
        case 'r':
            particleController.removeAll();
            break;
        case 's':
            sparkController.addSparks(250, mousePos, mouseVel);
            
            break;
            
        case 'j':
            sparkController.addSparks(125, mousePos, mouseVel);
            bottleController.addBottle(mousePos);
            break;

            
        default:
            
            break;
    }
}

void Box2dLeapTestApp::doMouseDown( MouseEvent event )
{
    mousePressed = true;
}


void Box2dLeapTestApp::doMouseUp( MouseEvent event )
{
    mousePressed = false;
}




void Box2dLeapTestApp::mouseMove( MouseEvent event )
{
    
    mouseVel = ( event.getPos() - mousePos );
    mousePos = event.getPos();
            
}
void Box2dLeapTestApp::mouseDrag( MouseEvent event )
{
    mouseMove( event );
}


//// end input functions //////

void Box2dLeapTestApp::update()
{
    /*
    if (mousePressed){
        particleController.addParticle(mousePos);
    }
     */
    particleController.update();
    bottleController.update();
    
    // step physics world
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;
    world.Step(timeStep, velocityIterations, positionIterations);
    
    sparkController.update();
   
}

void Box2dLeapTestApp::draw()
{
    // clear out the window with black
    gl::clear( Color( 0, 0, 0 ) );
    particleController.draw();
    bottleController.draw();
    sparkController.draw();
}

CINDER_APP_NATIVE( Box2dLeapTestApp, RendererGl )
