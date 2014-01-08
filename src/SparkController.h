#pragma once
#include "Spark.h"
#include <list>

class SparkController {
 public:
    SparkController();
    void update();
    void draw();
    void addSparks( int amt , const ci::Vec2i &mousePos, const ci::Vec2f &mouseVel);
    void removeSparks( int amt );
    
    std::list<Spark> sparks;
};
