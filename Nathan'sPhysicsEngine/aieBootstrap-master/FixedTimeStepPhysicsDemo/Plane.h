#pragma once
#include "PhysicsObject.h"
#include "RigidBody.h"
#include "Sphere.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		Plane: Inherited from PhysicsObject, the Plane class is used to create planes in the scene
//			that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------
class Plane : public PhysicsObject
{
public:
	//-------------------------------------------------------------------------------------------------
	// Plane constructor
	//-------------------------------------------------------------------------------------------------
	Plane();

	//-------------------------------------------------------------------------------------------------
	// Plane constructor:
	//
	//	param:
	//		m_normal: A vector 2 that is used to set which way the normal is facing.
	//		distance: A float that is the distance of offset from 0, 0.
	//-------------------------------------------------------------------------------------------------
	Plane(glm::vec2 m_normal, float distance);

	//-------------------------------------------------------------------------------------------------
	// Default Plane deconstructor
	//-------------------------------------------------------------------------------------------------
	~Plane();

	//-------------------------------------------------------------------------------------------------
	// fixedUpdate: This is an update function specifically for physics calculations. It runs 
	//				seperately to the regular update function. It does not run every frame but using
	//				real time so that if the frame rate drops, the physics are not effected.
	//		param:
	//			gravity: Gravity is a vector 2 that takes in the current gravitational force of the
	//					application.
	//			timeStep: Time step is a floating point number that is the number of physics ticks
	//					per second. 
	//-------------------------------------------------------------------------------------------------
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	//-------------------------------------------------------------------------------------------------
	// debug: Debug is used for debugging purposes.
	//-------------------------------------------------------------------------------------------------
	virtual void debug() {}

	//-------------------------------------------------------------------------------------------------
	// makeGizmo: Make gizmo is a function used to create a gizmo to be rendered on the screen.
	//-------------------------------------------------------------------------------------------------
	virtual void makeGizmo();

	//-------------------------------------------------------------------------------------------------
	// resetPosition: This function resets the position of the plane to its' original position.
	//-------------------------------------------------------------------------------------------------
	virtual void resetPosition();

	//-------------------------------------------------------------------------------------------------
	// resolveCollision: resolveCollision is what happens when something collides with it.
	// 
	//			params:
	//				actor2: A rigidbody pointer that is whatever object is colliding with this plane.
	//				contact: A vector 2 that is the point where the object collided with the plane.
	//-------------------------------------------------------------------------------------------------
	void resolveCollision(RigidBody * actor2, glm::vec2 contact);

	//-------------------------------------------------------------------------------------------------
	// getNormal: This function returns the vector 2 that the plane's current normal is.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getNormal() { return m_normal;  }

	//-------------------------------------------------------------------------------------------------
	// getDistance: This function returns the current distance between this plane and the origin point
	//				as a float.
	//-------------------------------------------------------------------------------------------------
	float getDistance() { return m_distanceToOrigin; }

protected:
	//-------------------------------------------------------------------------------------------------
	// m_normal is a vector 2 that stores the current normal of the plane.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_normal;

	//-------------------------------------------------------------------------------------------------
	// m_centrePoint is a vector 2 that stores the centrePoint of the plane.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_centrePoint;

	//-------------------------------------------------------------------------------------------------
	// m_distanceToOrigin is a float that stores the current distance from the origin of this plane.
	//-------------------------------------------------------------------------------------------------
	float m_distanceToOrigin;

};
