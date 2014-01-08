#include "Spark.h"
#include "cinder/Rand.h"
#include "cinder/gl/gl.h"
#include "cinder/app/AppBasic.h"

int mAge;
int mLifespan;
bool isDead;

ci::ColorA mColor1; /// main color object
float col_1,col_2,col_3; // colors
ci::ColorA mColor2; /// main color object
float col_4,col_5,col_6; // colors

float sizeAdjust;

ci::Vec2f mDir; ///  private vars? how?
ci::Vec2f mGrav;

ci::Vec2f posAdjust;
float trans; /// transition number
float trans2; /// transparency number 2
ci::Vec2f newVel;
ci::Vec2f newLoc;
ci::Vec2f theGravity;

float stubNumX;
float stubNumY;

using namespace ci;

Spark::Spark()
{
}

Spark::Spark( Vec2i loc , Vec2f vel)
{

    
    newVel = vel;
    mLoc	= loc;
    newLoc = mLoc;
    
    // gah
    stubNumX = (rand() % 5)-2.5;
    stubNumY = (rand() % 2) -2;
    
    /*
    std::cout << "X ." << stubNumX << " Y = " << stubNumY;
    std::cout << ">>>>" <<std::endl;
     */
    //
    mDir = Vec2f(stubNumX, stubNumY); /// Rand::randVec2f();
    // mDir = Vec2f((rand() % 10 + -10), (rand() % 10 + -10)); /// Rand::randVec2f();
    sizeAdjust = Rand::randFloat( 2.15f );
    posAdjust = Rand::randVec2f();
    // theGravity = Vec2f(0, Rand::randFloat(7.5f));
    mGrav = Vec2f(1,  Rand::randFloat( 2.15f ));
    
    /// grav from java     velocity = new PVector(pApp.random(-1,1),pApp.random(-2,0));
    
     /// newVel	= Rand::randFloat( 5.0f );//  vel; //
    /*
	mLoc	= loc;
	mDir	= Rand::randVec2f();
	mVel	= Rand::randFloat( 5.0f );
     */
	mRadius	= 5.0f - sizeAdjust;
    
    //red
    trans = .6;
    col_1 = 1;
    col_2 = 0;
    col_3 = 0;
    // yellow
    trans2 = .45;
    col_4 = 1;
    col_5 = 1;
    col_6 = 1;
    
    mAge = 0;
    mLifespan = 10000;
    isDead = false;
}

void Spark::update()
{
    
    mAge++;
    trans -= 0.00001;
    trans2 -= 0.00001;
    mRadius -= 0.12;
    mColor1=ColorA(col_1,col_2,col_3,trans);
    if(mRadius <=.012){
        isDead = true;
        
    }
	/// mLoc += mDir * mVel;
    mLoc -= mDir * mGrav;
}

void Spark::draw()
{
	gl::enableAlphaBlending();
    mColor1 = ColorA(col_1,col_2,col_3, trans);
    gl::color( mColor1 );
    gl::drawSolidCircle( mLoc, mRadius + 1.2f);
    
    mColor2 = ColorA(col_4,col_5,col_6, trans2);
    gl::color( mColor2 );
    gl::drawSolidCircle( mLoc, mRadius );
    
    gl::disableAlphaBlending();
}
