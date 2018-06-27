#include "Plane.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		Plane: Inherited from PhysicsObject, the Plane class is used to create planes in the scene
//			that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Plane constructor
//-------------------------------------------------------------------------------------------------
Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	// Set the distance to origin to 0.
	m_distanceToOrigin = 0;
	// Set the normal to 0, 0.
	m_normal = glm::vec2(0, 0);
	// The centre of the plane is the normal vector * the distance to origin.
	m_centrePoint = m_normal * m_distanceToOrigin;
}

//-------------------------------------------------------------------------------------------------
// Plane constructor:
//
//	param:
//		m_normal: A vector 2 that is used to set which way the normal is facing.
//		distance: A float that is the distance of offset from 0, 0.
//-------------------------------------------------------------------------------------------------
Plane::Plane(glm::vec2 a_normal, float distance) : PhysicsObject(ShapeType::PLANE)
{
	// Assigning the normal to the constructor normal.
	m_normal = a_normal;
	// Assigning the distance to the constructor distance.
	m_distanceToOrigin = distance;
}

//-------------------------------------------------------------------------------------------------
// Default Plane deconstructor
//-------------------------------------------------------------------------------------------------
Plane::~Plane()
{
}

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
void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{
}

//-------------------------------------------------------------------------------------------------
// makeGizmo: Make gizmo is a function used to create a gizmo to be rendered on the screen.
//-------------------------------------------------------------------------------------------------
void Plane::makeGizmo()
{
	// Setting the line segment.
	float lineSegmentLength = 300;
	// Setting the centrepoint.
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	// easy to rotate normal through 90 degrees around z.
	glm::vec2 parallel(m_normal.y, -m_normal.x); 
	// Set the colour.
	glm::vec4 colour(1, 0, 1, 1);
	// Setting the start.
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	// Setting the end
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	// Creating the gizmo to be rendered.
	aie::Gizmos::add2DLine(start, end, colour);
}

//-------------------------------------------------------------------------------------------------
// resetPosition: This function resets the position of the plane to its' original position.
//-------------------------------------------------------------------------------------------------
void Plane::resetPosition()
{
}

//-------------------------------------------------------------------------------------------------
// resolveCollision: resolveCollision is what happens when something collides with it.
// 
//			params:
//				actor2: A rigidbody pointer that is whatever object is colliding with this plane.
//				contact: A vector 2 that is the point where the object collided with the plane.
//-------------------------------------------------------------------------------------------------
void Plane::resolveCollision(RigidBody* actor2, glm::vec2 contact)
{
	// Assign a new vector 2 as a normal.
	glm::vec2 normal = m_normal;
	// Get the relative velocity.
	glm::vec2 relativeVelocity = actor2->getVelocity();
	// Set the elasticity to 1.
	float elasticity = 1;
	// Calculating j.
	float j = -(1 + elasticity) * glm::dot(relativeVelocity, normal) /
		glm::dot(normal, normal) * ((1 / actor2->getMass()));

	// The force is the normal * j.
	glm::vec2 force = normal * j;

	// Apply the calculated force to the other actor.
	actor2->applyForce(force, contact - actor2->getPosition());
}
