#pragma once
#include "RigidBody.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		Box: Inherited from RigidBody, the Box class is to create a box using OBB collision
//			that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------
class Box : public RigidBody
{
public:
	//-------------------------------------------------------------------------------------------------
	// Box constructor:
	//
	//		params:
	//			position: A vector 2 to store the position of the aabb.
	// 			extents: A vector 2 to store the extents of the aabb box.
	// 			velocity: A vector2 to store the velocity of the aabb box.
	// 			mass: A floating point number to store the mass of the aabb box.
	// 			colour: A vector 4 to store the RGBA value for the colour of the aabb box.
	//-------------------------------------------------------------------------------------------------
	Box(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour);
	
	//-------------------------------------------------------------------------------------------------
	// Default Deconstructor for the Box class.
	//-------------------------------------------------------------------------------------------------
	~Box();

	//-------------------------------------------------------------------------------------------------
	// fixedUpdate: This is an update function specifically for physics calculations. It runs 
	//				seperately to the regular update function. It does not run every frame but using
	//				real time so that if the frame rate drops, the physics are not effected.
	//		params:
	//			gravity: Gravity is a vector 2 that takes in the current gravitational force of the
	//					application.
	//			timeStep: Time step is a floating point number that is the number of physics ticks
	//					per second. 
	//-------------------------------------------------------------------------------------------------
	void fixedUpdate(glm::vec2 gravity, float timeStep);

	//-------------------------------------------------------------------------------------------------
	// makeGizmo: Make gizmo is a function used to create a gizmo to be rendered on the screen.
	//-------------------------------------------------------------------------------------------------
	void makeGizmo();

	//-------------------------------------------------------------------------------------------------
	// checkBoxCorners: The CheckBoxCorners function checks whether anything has collided with the box.
	//
	//		params:
	//			box: A box pointer of which box to check for.
	//			contact: A vector 2 that is the memory address of the contact between two colliding
	//					objects.
	//			numContacts: An int to store the number of contacts occurring.
	//			edgeNormal: A vector 2 that stores which way the normal is facing.
	//			contactForce: A vector 2 of the force of the contact.
	//-------------------------------------------------------------------------------------------------
	bool checkBoxCorners(Box * box, glm::vec2 & contact, int & numContacts, glm::vec2 & edgeNormal, glm::vec2 & contactForce);
	
	//-------------------------------------------------------------------------------------------------
	// getWidth: This function returns the current width of this box as a float.
	//-------------------------------------------------------------------------------------------------
	float getWidth() { return m_extents.x; };

	//-------------------------------------------------------------------------------------------------
	// getHeight: This function returns the current height of this box as a float.
	//-------------------------------------------------------------------------------------------------
	float getHeight() { return m_extents.y; };

	//-------------------------------------------------------------------------------------------------
	// getMoment: This function returns the current moment of inertia of this box as a float.
	//-------------------------------------------------------------------------------------------------
	float getMoment() { return m_moment; };

	//-------------------------------------------------------------------------------------------------
	// getExtents: This function returns the current extents of this box as a vector 2.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getExtents() { return m_extents; };

	//-------------------------------------------------------------------------------------------------
	// getPosition: This function returns the current position of this box as a vector 2.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getPosition() { return m_position; };

	//-------------------------------------------------------------------------------------------------
	// getLocalX: This function returns the current local X of this box as a vector 2.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getLocalX() { return m_localX; };

	//-------------------------------------------------------------------------------------------------
	// getLocalY: This function returns the current local Y of this box as a vector 2.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getLocalY() { return m_localY; };

	//-------------------------------------------------------------------------------------------------
	// checkCollision: This function is needed because it inherits from rigidBody.
	//
	//			params:
	//				pOther: A physics object pointer that takes in the other object that is colliding
	//						with this box.
	//-------------------------------------------------------------------------------------------------
	bool checkCollision(PhysicsObject* pOther) { return false; };

protected:

	//-------------------------------------------------------------------------------------------------
	// m_extents is a vector 2 that stores the halfway length of the box.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_extents; 

	//-------------------------------------------------------------------------------------------------
	// m_colour is a vector 4 that stores the RGBA value for the box's colour.
	//-------------------------------------------------------------------------------------------------
	glm::vec4 m_colour;

	//-------------------------------------------------------------------------------------------------
	// m_localX stores the local x axis of the box based on its angle of rotation.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_localX;

	//-------------------------------------------------------------------------------------------------
	// m_localY stores the local y axis of the box based on its angle of rotation.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_localY;
};

