#pragma once
#include "cinder/Color.h"
#include <Box2D/Box2d.h>

namespace bottles {
	
    class Bottle {
	public:
		Bottle();
		~Bottle();
		
		// pass in a pointer to the bottle
        // reference to self, x, y, mouse position ;
		void setup(b2World *world, ci::Vec2f boxSize, ci::Vec2f mousePos);
		void update();
		void draw();
		
        //private:
        // store a pointer to the world from the main app
        b2World* tWorld;
		// store a pointer to the bottle in the physics world from the main app
		b2Body* body;
		ci::Color color;
		ci::Vec2f size;
	};
	
}

