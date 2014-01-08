#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "SparkController.h"

using namespace ci;
using std::list;

SparkController::SparkController()
{
}

void SparkController::update()
{
    //// NOTICE THE DIFFERENT ITERATION STYLE-- WE ONLY WANT TO ITERATE IF SPARK IS NOT DEAD ///////
	for( list<Spark>::iterator p = sparks.begin(); p != sparks.end();){
        
        if( p->isDead ) {
            p = sparks.erase( p );
        }
        else {
            p->update();
            ++p;
        }
        

	}
}

void SparkController::draw()
{
	for( list<Spark>::iterator p = sparks.begin(); p != sparks.end(); ++p ){
		p->draw();
	}
}

void SparkController::addSparks( int amt, const Vec2i &mousePos , const Vec2f &mouseVel)
{
	for( int i=0; i<amt; i++ )
	{
        /* for random position
		float x = Rand::randFloat( app::getWindowWidth() );
		float y = Rand::randFloat( app::getWindowHeight() );
        Vec2f vel = mouseVel;
         sparks.push_back( Spark( Vec2f( x, y ), vel ) );
         */
        
        /* for mouse   */
        Vec2f loc = mousePos + Rand::randVec2f() * 10.0f;
        Vec2f vel = mouseVel; //  * 0.25f;
        

		sparks.push_back( Spark( loc, vel));
        
	}
}

void SparkController::removeSparks( int amt )
{
	for( int i=0; i<amt; i++ )
	{
		sparks.pop_back();
	}
}

