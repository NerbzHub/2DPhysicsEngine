#include "AABB.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		AABB: Inherited from RigidBody, the AABB class is to create an aabb box with correct 
//			 collision that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------

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
AABB::AABB(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour) 
	: RigidBody(ENUMAABB, position, velocity, 0, mass)
{
	// Setting the new extents from the constructor as the current extents.
	m_extents = extents;
	// Setting the new colour from the constructor as the current colour.
	m_colour = colour;
}

//-------------------------------------------------------------------------------------------------
// AABB Default Destructor.
//-------------------------------------------------------------------------------------------------
AABB::~AABB()
{
}

//-------------------------------------------------------------------------------------------------
// makeGizmo is a function that creates what will be rendered on the screen.
//-------------------------------------------------------------------------------------------------
void AABB::makeGizmo()
{
	// Creates the AABB gizmo that will be rendered.
	aie::Gizmos::add2DAABBFilled(m_position, m_extents, m_colour);
}

//-------------------------------------------------------------------------------------------------
// getExtents is a function that returns a vector 2 that are the current extents of the box.
//-------------------------------------------------------------------------------------------------
glm::vec2 AABB::getExtents()
{
	// Returns the current extents value.
	return m_extents;
}

//-------------------------------------------------------------------------------------------------
// getMinExtents is a function that returns the minimum extents of this box.
//-------------------------------------------------------------------------------------------------
glm::vec2 AABB::getMinExtents()
{
	// Returns the position - the extents.
	return m_position - m_extents;
}

//-------------------------------------------------------------------------------------------------
// getMaxExtents is a function that returns the maximum extents of this box.
//-------------------------------------------------------------------------------------------------
glm::vec2 AABB::getMaxExtents()
{
	// Returns the position + the extents.
	return m_position + m_extents;
}