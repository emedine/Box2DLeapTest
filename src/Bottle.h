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
        int imageId;
        gl::Texture theImage;
        
        /// set some attributes
        // these are not used yet
        b2Vec2 m_position;
        float m_angle; /// maybe we won't use this because it's not a circle?
        b2Vec2 m_linearVelocity;
        
        private:
        // store a pointer to the world from the main app
		b2World *tworld;
        bool hasHit;
		bool m_contacting = false;
        bool done(); // checks to see if the object has left the bounds
		void startContact();
		void endContact();
        void showImpact();
        // these are the paths to the images
        std::string squarePaths[4] = {"boxes/rect_boxSq1.jpg","boxes/rect_boxSq2.jpg","boxes/rect_boxSq3.jpg","boxes/rect_boxSq4.jpg"};
        std::string rectPaths[4] = {"boxes/rect_boxLg1.jpg","boxes/rect_boxLg2.jpg","boxes/rect_boxLg3.jpg","boxes/rect_boxLg4.jpg"};
        std::string rectSmPaths[4]= {"boxes/rect_boxSm1.jpg","boxes/rect_boxSm2.jpg","boxes/rect_boxSm3.jpg","boxes/rect_boxSm4.jpg"};
        
        /// paths to the post-impact images
        std::string squarePathsR[4] = {"boxes/rect_boxSq1r.jpg","boxes/rect_boxSq2r.jpg","boxes/rect_boxSq3r.jpg","boxes/rect_boxSq4r.jpg"};
        std::string rectPathsR[4] = {"boxes/rect_boxLg1r.jpg","boxes/rect_boxLg2r.jpg","boxes/rect_boxLg3r.jpg","boxes/rect_boxLg4r.jpg"};
        std::string rectSmPathsR[4]= {"boxes/rect_boxSm1r.jpg","boxes/rect_boxSm2r.jpg","boxes/rect_boxSm3r.jpg","boxes/rect_boxSm4r.jpg"};
	};
	
}

