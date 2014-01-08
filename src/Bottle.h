#pragma once
#include "cinder/Color.h"
#include <Box2D/Box2d.h>

namespace bottles {
	
    class Bottle {
	public:
		Bottle();
		~Bottle();
		
		// pass in a pointer to the bottle
        // reference to world, x, y, mouse position ;
		void setup(b2World &tw, ci::Vec2f boxSize, ci::Vec2f mousePos);
		void update();
		void draw();

		// store a pointer to the bottle in the physics world from the main app
		b2Body* body;
		ci::Color color;
		ci::Vec2f size;
        
        private:
        // store a pointer to the world from the main app
        b2World &tworld;
	};
	
}

