#pragma once
#include "Spark.h"
#include <list>

class SparkController {
public:
    SparkController();
    void update();
    void draw();
    void addSparks( int amt );
    void removeSparks( int amt );
    
    std::list<Spark> sparks;
};
