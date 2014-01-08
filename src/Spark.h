#pragma once
#include "cinder/Channel.h"
#include "cinder/Vector.h"

#include <vector>

class Spark {
public:
	Spark();
	Spark( ci::Vec2i , ci::Vec2f);
	void update();
	void draw();
	
	ci::Vec2f	mLoc;
	
	bool        isDead;
    float		mRadius;
    
private:
    ci::Vec2f	mDir;
    ci::Vec2f   mGrav;
};