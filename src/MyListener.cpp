//
//  MyListener.cpp
//  Box2dLeapTest
//
//  Created by Eric Medine on 2/1/14.
//
//
#include "Bottle.h"
// #include "Bottle.cpp"
#include "MyListener.h"

#include <Box2D/Box2d.h>
//
//  MyListener.cpp
//  Box2dLeapTest
//
//  Created by Eric Medine on 2/1/14.
//
//

class MyListener : public b2ContactListener {
    /*
     virtual void Add (b2ContactPoint *point);
     virtual void Persist (b2ContactPoint *point);
     virtual void Remove (b2ContactPoint *point);
     virtual void Result (b2ContactPoint *point);
     */

    void BeginContact(b2Contact* contact) {
        
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if ( bodyUserData ){
            printf(" Hit ");
            
            static_cast<bottles::Bottle*>( bodyUserData )->startContact();
           
        } else {
            
            printf(" wall hit ");
        }
        
        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyUserData ){
            printf(" hit ");
            
            
        } else {
            
            printf(" wall hit ");
        }
    }
    
    void EndContact(b2Contact* contact) {
        
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if ( bodyUserData ){
            // contact->GetFixtureA()->GetBody()->startContact();
            /// static_cast<Bottle>( bodyUserData )->startContact();
            
        }
        
        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if ( bodyUserData ) {
            /// static_cast<Ball*>( bodyUserData )->endContact();
            
        }
        
    }
};
