#pragma once
#include "RigidBody.h"
#include "Gizmos.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		Sphere: Inherited from RigidBody, the Sphere class is to create a sphere that can be 
//				rendered in 2D.
//-------------------------------------------------------------------------------------------------
class Sphere : public RigidBody
{
public:
	//-------------------------------------------------------------------------------------------------
	// Sphere constructor:
	//
	//		params:
	//			position: A vector 2 to allocate where the sphere will be created.
	//			velocity: A vector 2 to set the starting velocity of the sphere.
	//			mass: A float to set the mass of the sphere on creation.
	//			radius: A float that sets the rotation of the sphere in radians.
	//			colour: A vector 4 that sets the colour of the sphere in RGBA.
	//-------------------------------------------------------------------------------------------------
	Sphere(glm::vec2 position, glm::vec2 velocity, float mass, float radius, glm::vec4 colour);

	//-------------------------------------------------------------------------------------------------
	// Sphere Secondary constructor:
	//
	//		params:
	//			position: A vecotr 2 to set the starting position of the sphere.
	//			inclination: A float to set the starting inclination of the sphere.
	//			speed: A float to set te starting speed of the sphere.
	//			mass: A float to set the starting mass of the sphere.
	//			radius A float to set the starting radius of the sphere.
	//			colour: A vector 4 to set the colour of the sphere in RGBA.
	//-------------------------------------------------------------------------------------------------
	Sphere(glm::vec2 position, float inclination, float speed, float mass, float radius, glm::vec4 colour);

	//-------------------------------------------------------------------------------------------------
	// Default Sphere deconstructor
	//-------------------------------------------------------------------------------------------------
	~Sphere();

	//-------------------------------------------------------------------------------------------------
	// makeGizmo: This function creates the gizmo of the sphere to be rendered in 2D.
	//-------------------------------------------------------------------------------------------------
	virtual void makeGizmo();

	//-------------------------------------------------------------------------------------------------
	// checkCollision: This function checks whether there is anything colliding with this sphere.
	//
	//		params: 
	//			pOther: A PhysicsObject pointer of whatever object is colliding with the sphere.
	//-------------------------------------------------------------------------------------------------
	virtual bool checkCollision(PhysicsObject* pOther);

	//-------------------------------------------------------------------------------------------------
	// getRadius: Returns the current radius of the sphere.
	//-------------------------------------------------------------------------------------------------
	float getRadius() { return m_radius; }

	//-------------------------------------------------------------------------------------------------
	// getColour: Returns the current colour of the sphere.
	//-------------------------------------------------------------------------------------------------
	glm::vec4 getColour() { return m_colour; }

protected:
	//-------------------------------------------------------------------------------------------------
	// m_radius is a float value that is the current radius of the sphere.
	//-------------------------------------------------------------------------------------------------
	float m_radius;

	//-------------------------------------------------------------------------------------------------
	// m_colour is a vector 4 that stores the RGBA value of the colour of the sphere.
	//-------------------------------------------------------------------------------------------------
	glm::vec4 m_colour;
};

