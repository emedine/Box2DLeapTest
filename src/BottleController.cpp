#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Vector.h"
#include "BottleController.h"
#include "Globals.h"
#include "Conversions.h"

using namespace ci;
using std::list;


namespace bottles {
    
    b2World *world;
    BottleController::BottleController()
    {
    }
    
    void BottleController::setup(b2World &w)
    {
        world = &w;
       
    }
    
    void BottleController::update()
    {
        for( list<Bottle>::iterator p = bottles.begin(); p != bottles.end(); p++) {
            p->update();
        }
    }
    
    void BottleController::draw()
    {
        for( list<Bottle>::iterator p = bottles.begin(); p != bottles.end(); p++ ){
            p->draw();
        }
    }
    
    void BottleController::addBottle(const Vec2i &mousePos)
    {
        Bottle p = Bottle();
        /*
        // create a dynamic body
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(Conversions::toPhysics(mousePos.x), Conversions::toPhysics(mousePos.y));
        
        // instead of just creating body...
        // b2Body* body = world->CreateBody(&bodyDef);
        // do the following to create it with a circular reference to it's corresponding particle
        bodyDef.userData = &p;
        p.body = world->CreateBody(&bodyDef);
        
        b2PolygonShape dynamicBox;
        float boxSizeX = Rand::randFloat(global::BOX_X_MIN, global::BOX_X_MAX);
        float boxSizeY = Rand::randFloat(global::BOX_Y_MIN, global::BOX_Y_MAX);
        
        dynamicBox.SetAsBox(Conversions::toPhysics(boxSizeX), Conversions::toPhysics(boxSizeY));
        
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;
        fixtureDef.restitution = 0.8f; // bounce
        
        p.body->CreateFixture(&fixtureDef);
        */
        
        /// clean this
        float boxSizeX = Rand::randFloat(global::BOX_X_MIN, global::BOX_X_MAX);
        float boxSizeY = Rand::randFloat(global::BOX_Y_MIN, global::BOX_Y_MAX);
        // rest of initialization particle can do for itself
        p.setup(world, Vec2f(boxSizeX, boxSizeY), Vec2f(mousePos));
        bottles.push_back(p);
        
    }
    
    void BottleController::removeAll()
    {
        // not the right way, but an alternative
        /*
         b2Body* body = world->GetBodyList();
         while( body != NULL )
         {
         
         body = body->GetNext();
         }
         */
        
        // right way
        for( list<Bottle>::iterator p = bottles.begin(); p != bottles.end(); p++) {
            world->DestroyBody(p->body);
        }
        
        /// killl the bottles array
        bottles.clear();
        
        if (global::COLOR_SCHEME == 0)
            global::COLOR_SCHEME++;
        else
            global::COLOR_SCHEME--;
    }
    
} /// end namespace