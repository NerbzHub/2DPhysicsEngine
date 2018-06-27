#pragma once
#include "Rigidbody.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		AABB: Inherited from RigidBody, the AABB class is to create an aabb box with correct 
//			 collision that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------
class AABB : public RigidBody
{
public:
	//-------------------------------------------------------------------------------------------------
	// AABB constructor:
	//
	//		params: 
	//			position: A vector 2 to store the position of the aabb.
	//			extents: A vector 2 to store the extents of the aabb box.
	//			velocity: A vector2 to store the velocity of the aabb box.
	//			mass: A floating point number to store the mass of the aabb box.
	//			colour: A vector 4 to store the RGBA value for the colour of the aabb box.
	//-------------------------------------------------------------------------------------------------
	AABB(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour);

	//-------------------------------------------------------------------------------------------------
	// AABB Default Destructor.
	//-------------------------------------------------------------------------------------------------
	~AABB();

	//-------------------------------------------------------------------------------------------------
	// makeGizmo is a function that creates what will be rendered on the screen.
	//-------------------------------------------------------------------------------------------------
	virtual void makeGizmo();

	//-------------------------------------------------------------------------------------------------
	// getColour is a function that returns the current colour of this box.
	//-------------------------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

	//-------------------------------------------------------------------------------------------------
	// getExtents is a function that returns a vector 2 that are the current extents of the box.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getExtents();

	//-------------------------------------------------------------------------------------------------
	// getMinExtents is a function that returns the minimum extents of this box.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getMinExtents();

	//-------------------------------------------------------------------------------------------------
	// getMaxExtents is a function that returns the maximum extents of this box.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getMaxExtents();

	//-------------------------------------------------------------------------------------------------
	// checkCollision is a function that checks whether there is a collision occurring with this box.
	//
	//		param: 
	//			pOther: Is a PhysicsObject pointer that represents the object that the box is
	//					colliding with.
	//-------------------------------------------------------------------------------------------------
	virtual bool checkCollision(PhysicsObject* pOther) { return false; };

protected:
	//-------------------------------------------------------------------------------------------------
	// m_extents is a vector 2 to store the extents of the box.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_extents;

	//-------------------------------------------------------------------------------------------------
	// m_colour is a vector 4 to store the RGBA value that the box will be rendered at.
	//-------------------------------------------------------------------------------------------------
	glm::vec4 m_colour;
};
