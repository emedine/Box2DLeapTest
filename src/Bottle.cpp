#include "Bottle.h"
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"

#include <string.h>
#include <iostream>

using namespace bottles;
Bottle::Bottle() {
    
  
}

Bottle::~Bottle() {
	//body->GetWorld()->DestroyBody( body );  // this ruins everything
}

///// should pass in standard sizes for this
void Bottle::setup(b2World *tw, Vec2f boxSize, Vec2f mousePos, int bT, int imgId) {
	// std::cout << "working 1" <<std::endl;
    
    /*
   rectPaths
squarePaths
    rectSmPaths[]
     */
    
    boxType = bT;
	size = boxSize/2;
	m_contacting = false;
    
	tworld = tw;
	/// world = &world;
    
    /// load an image
    
    switch (boxType){
            
        case 0:
           theImage = loadImage( cinder::app::loadAsset(squarePaths[imgId]));
            break;
            
        case 1:
            theImage = loadImage( cinder::app::loadAsset(rectPaths[imgId]));
            break;
            
        case 2:
           theImage = loadImage( cinder::app::loadAsset(rectSmPaths[imgId]));
            break;
            
            
        case 3:
           theImage = loadImage( cinder::app::loadAsset(rectPaths[imgId]));
            break;
            
            
        default:
            
            break;
            
    }


	// create a dynamic body
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(Conversions::toPhysics(mousePos.x), Conversions::toPhysics(mousePos.y));

	// instead of just creating body...
	// b2Body* body = world->CreateBody(&bodyDef);
	// do the following to create it with a circular reference to it's corresponding particle
	bodyDef.userData = this;
	body = tworld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	

	dynamicBox.SetAsBox(Conversions::toPhysics(size.x), Conversions::toPhysics(size.y));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.8f; // bounce

	body->CreateFixture(&fixtureDef);

    /*
	if (global::COLOR_SCHEME == 0)
		color = ci::ColorA(1, ci::Rand::randFloat(0,.8), .5, 1);  // red to yellow
	else
		color = ci::ColorA(ci::Rand::randFloat(0,.8), .5, 1, 1);  // blue to violet
    
    */
}

void Bottle::update() {

}

void Bottle::draw() {
    /*
	glColor4f(color);
     */
	Vec2f pos = Conversions::toScreen( body->GetPosition() );
	float t = Conversions::radiansToDegrees( body->GetAngle() );

	glPushMatrix();
	gl::translate( pos );
	gl::rotate( t );

    /*
	Rectf rect(-size.x, -size.y, size.x, size.y);
	gl::drawSolidRect(rect);
    */
    ///// image
    if( theImage )
		gl::draw( theImage, Vec2f(-size.x, -size.y ) );

	glPopMatrix();
}

//// collision params
//Ball class functions
void Bottle::startContact() {
	m_contacting = true;
}
void Bottle::endContact() {
	m_contacting = false;
}


