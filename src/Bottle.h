#pragma once
#include "cinder/Color.h"
#include <Box2D/Box2d.h>
#include "Globals.h"
#include "cinder/Rand.h"
#include "cinder/gl/Texture.h"
#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "Conversions.h"
using namespace ci;
namespace bottles {
	
    class Bottle {
	public:
		Bottle();
		~Bottle();
		
		// pass in a pointer to the bottle
        // reference to world, x, y, mouse position ;
		void setup(b2World *tw, ci::Vec2f boxSize, ci::Vec2f mousePos, int bt, int imgId);
		void update();
		void draw();

		// store a pointer to the bottle in the physics world from the main app
		b2Body* body;
		ci::Color color;
		ci::Vec2f size;
        int boxType;
        int imgId;
        gl::Texture theImage;
        
        private:
        // store a pointer to the world from the main app
        //b2World &tworld;
		b2World *tworld;
		bool m_contacting;
		void startContact();
		void endContact();
        //
        std::string squarePaths[4] = {"boxes/rect_boxSq1.jpg","boxes/rect_boxSq2.jpg","boxes/rect_boxSq3.jpg","boxes/rect_boxSq4.jpg"};
        std::string rectPaths[4] = {"boxes/rect_boxLg1.jpg","boxes/rect_boxLg2.jpg","boxes/rect_boxLg3.jpg","boxes/rect_boxLg4.jpg"};
        std::string rectSmPaths[4]= {"boxes/rect_boxSm1.jpg","boxes/rect_boxSm2.jpg","boxes/rect_boxSm3.jpg","boxes/rect_boxSm4.jpg"};
	};
	
}

