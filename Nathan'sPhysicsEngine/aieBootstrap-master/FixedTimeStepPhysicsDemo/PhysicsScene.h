#pragma once
#include <glm\vec2.hpp>
#include <glm\ext.hpp>
#include <vector>
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "AABB.h"
#include <iostream>

//-------------------------------------------------------------------------------------------------
// Forward declaration
//-------------------------------------------------------------------------------------------------
class PhysicsObject;

//-------------------------------------------------------------------------------------------------
// Class:
//		PhysicsScene: The Physics scene covers all of the collision detection code, gravity and
//					most of what happens during the scene.
//-------------------------------------------------------------------------------------------------
class PhysicsScene
{
public:
	//-------------------------------------------------------------------------------------------------
	// Default Constructor for the physics scene.
	//-------------------------------------------------------------------------------------------------
	PhysicsScene();

	//-------------------------------------------------------------------------------------------------
	// Default Deconstructor for the physics scene. 
	//-------------------------------------------------------------------------------------------------
	~PhysicsScene();

	//-------------------------------------------------------------------------------------------------
	// update: Update runs every frame. Anything that needs to be done in the scene that isn't 
	//		physics calculations. 
	//		
	//		params: 
	//			dt: dt stands for deltaTime which is the frame rate.
	//-------------------------------------------------------------------------------------------------
	void update(float dt);

	//-------------------------------------------------------------------------------------------------
	// updateGizmos: Update gizmos is an update function for the gizmos. 
	//-------------------------------------------------------------------------------------------------
	void updateGizmos();

	//-------------------------------------------------------------------------------------------------
	// addActor: This function is used to add an actor to the physics scene.
	//
	//		params:
	//			actor: Actor is the physicsObject that is being added to the physics scene.
	//-------------------------------------------------------------------------------------------------
	void addActor(PhysicsObject* actor);

	//-------------------------------------------------------------------------------------------------
	// removeActor: This function is used to remove an actor from the physics scene.
	//
	//		params:
	//			actor: Actor is the physicsObject that is being removed from the physics scene.
	//-------------------------------------------------------------------------------------------------
	void removeActor(PhysicsObject* actor);

	//-------------------------------------------------------------------------------------------------
	// debugScene: This function is used for debugging.
	//-------------------------------------------------------------------------------------------------
	void debugScene();
	
	//-------------------------------------------------------------------------------------------------
	// checkForCollision: The check for collision function checks whether there are any collisions
	//					occurring.
	//-------------------------------------------------------------------------------------------------
	void checkForCollision();



	//-------------------------------------------------------------------------------------------------
	// setGravity: setGravity sets the value for the gravitational force. 
	//		
	//		params: 
	//			gravity: a vector 2 of the gravitational force to be set for the scene.
	//-------------------------------------------------------------------------------------------------
	void setGravity(const glm::vec2 gravity) { m_gravity = gravity; }

	//-------------------------------------------------------------------------------------------------
	// getGravity: getGravity returns the current gravity value of the scene.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getGravity() const { return m_gravity; }

	//-------------------------------------------------------------------------------------------------
	// setTimeStep: This function sets the tick count of the fixed update.
	//
	//		params:
	//			timeStep: A floating point number for the tick rate.
	//-------------------------------------------------------------------------------------------------
	void setTimeStep(const float timeStep) { m_timeStep = timeStep; }

	//-------------------------------------------------------------------------------------------------
	// getTimeStep: This function returns the current timeStep rate.
	//-------------------------------------------------------------------------------------------------
	float getTimeStep() const { return m_timeStep; }

	//-------------------------------------------------------------------------------------------------
	// These functions are all the collision code for the various types of shape collision.
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	//												Plane
	//
	// Plane to Plane
	static bool plane2Plane(PhysicsObject*, PhysicsObject*);
	// Plane to Sphere
	static bool plane2Sphere(PhysicsObject*, PhysicsObject*);
	// Plane to AABB
	static bool plane2aabb(PhysicsObject*, PhysicsObject*);
	// Plane to Box
	static bool plane2Box(PhysicsObject*, PhysicsObject*);
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	//												Sphere
	//
	// Sphere to Plane
	static bool sphere2Plane(PhysicsObject*, PhysicsObject*);
	// Sphere to Sphere
	static bool sphere2Sphere(PhysicsObject*, PhysicsObject*);
	// Sphere to AABB
	static bool sphere2aabb(PhysicsObject*, PhysicsObject*);
	// Sphere to Box
	static bool sphere2Box(PhysicsObject*, PhysicsObject*);
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	//												AABB
	//
	// AABB to Plane
	static bool aabb2Plane(PhysicsObject*, PhysicsObject*);
	// AABB to Sphere
	static bool aabb2Sphere(PhysicsObject*, PhysicsObject*);
	// AABB to AABB
	static bool aabb2aabb(PhysicsObject*, PhysicsObject*);
	// AABB to Box
	static bool aabb2Box(PhysicsObject*, PhysicsObject*);
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	//												Box
	//
	// Box to Plane
	static bool box2Plane(PhysicsObject * obj1, PhysicsObject * obj2);
	// Box to Sphere
	static bool box2Sphere(PhysicsObject*, PhysicsObject*);
	// Box to AABB
	static bool box2aabb(PhysicsObject*, PhysicsObject*);
	// Box to Box
	static bool box2Box(PhysicsObject*, PhysicsObject*);
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	// distanceBetweenSpheres is a vector 2 that stores the mid point between the two spheres.
	//-------------------------------------------------------------------------------------------------
	static glm::vec2 distanceBetweenSpheres;

protected:
	//-------------------------------------------------------------------------------------------------
	// m_actors is a vector of physicsObject pointers that is used to see which two shapes collide.
	// After it sorts out which shapes are colliding then it chooses the appropriate function to call.
	//-------------------------------------------------------------------------------------------------
	std::vector<PhysicsObject*> m_actors;

	//-------------------------------------------------------------------------------------------------
	// m_gravity is a vector 2 to store the current gravitational force of the scene.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_gravity;

	//-------------------------------------------------------------------------------------------------
	// m_timeStep is a float that stores the current tick rate of the fixed update.
	//-------------------------------------------------------------------------------------------------
	float m_timeStep;
};


