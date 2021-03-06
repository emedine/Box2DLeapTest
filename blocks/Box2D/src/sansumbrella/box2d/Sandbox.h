/*
 * Copyright (c) 2010—2013, David Wicks, sansumbrella.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or
 * without modification, are permitted provided that the following
 * conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once
#include "Common.h"
#include "Renderer.h"

namespace cinder
{ // forward declaration
  class TriMesh2d;
}

namespace box2d
{
  /**
   Sandbox is a convenient way to manage a b2World.
   It keeps track of the world and the variables needed to step it in time.
   It also enables debug drawing of the physics world.

   The lifetime of objects created through the Sandbox interface are managed by
   smart pointers, which scope the lifetime of the associated objects. The b2body
   or b2joint will be destroyed when the smart pointer falls out of scope. Given
   how Box2D manages memory, this requires a custom deleter, which Sandbox sets
   up for your automatically.

   All bodies are created using Box2D kg/m/s units, so use a scale factor when
   converting to/from screen space. See Box2DScale for a convenient solution
   to managing the scale factor and conversion methods.
   */

  class Sandbox
  {
  public:
    Sandbox();
    ~Sandbox() = default;
    //! Run the Box2D physics timestep
    void step();
    //! have a look at what's in the physics system (scaled up to screen space)
    void debugDraw( float points_per_meter );

    //! Create a boundary rectangle in screen coordinates; uses a b2ChainShape
    void createBoundaryRect( ci::Rectf screen_bounds );
    //! Destroy the boundary rectangle
    void destroyBoundaryRect() { mBoundaryBody.reset(); }
    //! Create a box using world coordinates
    unique_body_ptr createBox( const ci::Vec2f &pos, const ci::Vec2f &size );
    //! Create a circle using world coordinates
    unique_body_ptr createCircle( const ci::Vec2f &pos, float radius );
    //! Create a shape from a TriMesh2d, as could be generated by ci::Triangulator
    unique_body_ptr createShape( const ci::Vec2f &centroid, const ci::TriMesh2d &mesh, float scale=1.0f );
    //! Performs simple triangulation of \a hull_vertices to create a hull around \a centroid
    //! pass the outside vertices like you would to a TRIANGLE_FAN, using world coordinates
    unique_body_ptr createFanShape( const ci::Vec2f &pos, const std::vector<b2Vec2> &hull_vertices );
    //! Create a box2d body with multiple fixtures from the given definitions
    unique_body_ptr createBody( const b2BodyDef &body_def, const std::vector<b2FixtureDef> &fixture_defs );
    //! Create a box2d body from the given definitions
    unique_body_ptr createBody( const b2BodyDef &body_def, const b2FixtureDef &fixture_def );
    //! Create a box2d body without fixtures
    unique_body_ptr createBody( const b2BodyDef &body_def );

    unique_joint_ptr createJoint( const b2JointDef &joint_def );

    //! Direct access to the box2d world
    b2World& getWorld()
    { return mWorld; }

    // Convenience methods for some b2world functions

    //! Returns the number of bodies being simulated
    inline int32    getBodyCount()
    { return mWorld.GetBodyCount(); }
    //! Returns the number of contacts generated between bodies
    inline int32    getContactCount()
    { return mWorld.GetContactCount(); }
    //! Returns the Box2D body list (a b2Body linked-list)
    inline b2Body*  getBodyList()
    { return mWorld.GetBodyList(); }

    //! Set the world gravity, default=(0, 10)
    inline void setGravity( const b2Vec2 &gravity ){ mWorld.SetGravity( gravity ); }
    //! Set number of velocity iterations used per step(), default=8
    inline void setVelocityIterations( int vi ){ mVelocityIterations = vi; }
    //! Set number of position iterations used per step(), default=3
    inline void setPositionIterations( int pi ){ mPositionIterations = pi; }
    //! Set how much time elapses with each physics simulation step
    inline void setTimeStep( float hz ){ mTimeStep = hz; }

    //! set the filter function for collisions (see box2d docs)
    void setContactFilter( const b2ContactFilter &filter );
  private:
    int     mVelocityIterations = 8;
    int     mPositionIterations = 3;
    float   mTimeStep = 1.0f / 60.0f;
    // the box2d world
    b2World         mWorld = b2World( b2Vec2( 0, 10.0f ) );
    // related objects
    b2ContactFilter   mContactFilter;
    Renderer          mDebugRenderer;
    unique_body_ptr   mBoundaryBody;

    //! Manage the lifetime of a b2Body with a unique_ptr and a custom deleter
    inline auto manage( b2Body *body ) -> unique_body_ptr
    { return { body, [this](b2Body *b){ mWorld.DestroyBody( b ); } }; }
    //! Manage the lifetime of a b2Joint with a unique_ptr and a custom deleter
    inline auto manage( b2Joint *joint ) -> unique_joint_ptr
    { return { joint, [this](b2Joint *j){ mWorld.DestroyJoint( j ); } }; }
  };
}