#pragma once
#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include <Gizmos.h>
#include <list>

//-------------------------------------------------------------------------------------------------
// These enums represent the various types of shapes to be used in the simulation.
//
// It is used for the function array.
//
//-------------------------------------------------------------------------------------------------
enum ShapeType {
	PLANE = 0,
	SPHERE,
	ENUMAABB,
	BOX,
	SHAPE_COUNT,
};

//-------------------------------------------------------------------------------------------------
// PhysicsObject: The physics object class is used for every object in the simulation using 
//				physics.
//-------------------------------------------------------------------------------------------------
class PhysicsObject
{
public:
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
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep) = 0;

	//-------------------------------------------------------------------------------------------------
	// makeGizmo: Make gizmo is a function used to create a gizmo to be rendered on the screen.
	//-------------------------------------------------------------------------------------------------
	virtual void makeGizmo() = 0;

	virtual void debug() = 0;

	//-------------------------------------------------------------------------------------------------
	// resetPosition sets the position of the object back to its' original position.
	//-------------------------------------------------------------------------------------------------
	virtual void resetPosition() {};

	//-------------------------------------------------------------------------------------------------
	// getShapeID returns the shape type of this object.
	//-------------------------------------------------------------------------------------------------
	virtual ShapeType getShapeID() {return m_shapeID;}


protected:
	PhysicsObject(ShapeType a_ShapeID) : m_shapeID(a_ShapeID) {}
	ShapeType m_shapeID;
};

