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
       
        /// get the box type
        int boxType = Rand::randInt(3);
        /// get the image id
        int imgId = Rand::randInt(3);
        int boxW;
        int boxH;
        
        
        //// do a "switch" to set the box2d body params
        switch (boxType){
                
            case 0:
                boxW = 70;
                boxH = 70;
                // theImage = loadImage(cinder::app::loadAsset("boxes/rect_boxSq1.jpg" ));
                break;
                
            case 1:
                boxW = 123;
                boxH = 70;
                // theImage = loadImage( cinder::app::loadAsset("boxes/rect_boxLg1.jpg"));
                break;
                
            case 2:
                boxW = 93;
                boxH = 70;
                // theImage = loadImage( cinder::app::loadAsset("boxes/rect_boxSm1.jpg" ));
                break;
                
                
            case 3:
                boxW = 123;
                boxH = 70;
                // theImage = loadImage(  cinder::app::loadAsset("boxes/rect_boxLg1.jpg" ));
                break;
                
                
            default:
                
                break;
                
        }

        
        /*
        
        float boxSizeX = Rand::randFloat(global::BOX_X_MIN, global::BOX_X_MAX);
        float boxSizeY = Rand::randFloat(global::BOX_Y_MIN, global::BOX_Y_MAX);
         */
        // rest of initialization particle can do for itself
        p.setup(world, Vec2f(boxW, boxH), Vec2f(mousePos), boxType, imgId);
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