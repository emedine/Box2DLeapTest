#include "Bottle.h"
#include "Globals.h"
#include "cinder/Rand.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Conversions.h"
#include <Box2D/Box2d.h>

namespace bottles {
    
    
    bool m_contacting;
	
	Bottle::Bottle() {
	}
	
	Bottle::~Bottle() {
		//body->GetWorld()->DestroyBody( body );  // this ruins everything
	}
    
	
	///// should pass in standard sizes for this
	void Bottle::setup(b2World &tw, Vec2f boxSize, Vec2f mousePos) {
        std::cout << "working 1" <<std::endl;


		size = boxSize;
        m_contacting = false;
        
        tworld = &tw;
        /// world = &world;
        
         std::cout << "working 2" <<std::endl;
        // create a dynamic body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(Conversions::toPhysics(mousePos.x), Conversions::toPhysics(mousePos.y));
        
        // instead of just creating body...
        // b2Body* body = world->CreateBody(&bodyDef);
        // do the following to create it with a circular reference to it's corresponding particle
        bodyDef.userData = this;
        body = tworld->CreateBody(&bodyDef);
        
         std::cout << "working 3" <<std::endl;
        b2PolygonShape dynamicBox;
        float boxSizeX = Rand::randFloat(global::BOX_X_MIN, global::BOX_X_MAX);
        float boxSizeY = Rand::randFloat(global::BOX_Y_MIN, global::BOX_Y_MAX);
        
        dynamicBox.SetAsBox(Conversions::toPhysics(boxSizeX), Conversions::toPhysics(boxSizeY));
        
         std::cout << "working 4" <<std::endl;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.8f; // bounce
        
        body->CreateFixture(&fixtureDef);
        
		if (global::COLOR_SCHEME == 0)
			color = ci::ColorA(1, ci::Rand::randFloat(0,.8), .5, 1);  // red to yellow
		else
			color = ci::ColorA(ci::Rand::randFloat(0,.8), .5, 1, 1);  // blue to violet
	}
	
	void Bottle::update() {
        
	}
    
	void Bottle::draw() {
        
		glColor4f(color);
        
		Vec2f pos = Conversions::toScreen( body->GetPosition() );
		float t = Conversions::radiansToDegrees( body->GetAngle() );
        
		glPushMatrix();
		gl::translate( pos );
		gl::rotate( t );
        
		Rectf rect(-size.x, -size.y, size.x, size.y);
		gl::drawSolidRect(rect);
        
		glPopMatrix();
	}
    
    //// collision params
    //Ball class functions
    void startContact() {
        m_contacting = true;
    }
    void endContact() {
        m_contacting = false;
    }
    
}

