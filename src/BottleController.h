#pragma once
#include "Bottle.h"
#include <Box2D/Box2d.h>
#include <list>

namespace bottles {
	
	class BottleController {
	public:
		BottleController();
		// pass the physics world from the main app by reference
		void setup(b2World &w);
		void update();
		void draw();
		void addBottle(const ci::Vec2i &mousePos);
		void removeAll();

	private:
        // store a pointer to the physics world from the main app
		b2World *world;
		std::list<Bottle>	bottles;
    };
    
}