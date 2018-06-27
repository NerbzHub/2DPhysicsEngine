#include "Box.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		Box: Inherited from RigidBody, the Box class is to create a box using OBB collision
//			that can be rendered in 2D.
//-------------------------------------------------------------------------------------------------

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
Box::Box(glm::vec2 position, glm::vec2 extents, glm::vec2 velocity, float mass, glm::vec4 colour) 
	: RigidBody(BOX, position, velocity, 0, mass)
{
	// Assigning the new values into the member values of the Boxes.
	m_colour = colour;
	m_extents = extents;
	m_moment = 1.0f / 12.0f * mass * extents.x * extents.y;
	m_position = position;

	//store the local axes 
	/*float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cs, sn));
	m_localY = glm::normalize(glm::vec2(-sn, cs));*/
}

//-------------------------------------------------------------------------------------------------
// Default Deconstructor for the Box class.
//-------------------------------------------------------------------------------------------------
Box::~Box()
{
}

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
void Box::fixedUpdate(glm::vec2 gravity, float timeStep)
{
	// Call the rigidBody fixedUpdate.
	RigidBody::fixedUpdate(gravity, timeStep);

	// Store the local axes.
	float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cs, sn));
	m_localY = glm::normalize(glm::vec2(-sn, cs));
}

//-------------------------------------------------------------------------------------------------
// makeGizmo: Make gizmo is a function used to create a gizmo to be rendered on the screen.
//-------------------------------------------------------------------------------------------------
void Box::makeGizmo()
{	
	// Draw using local axes.
	glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;
	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}

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
bool Box::checkBoxCorners(Box* box, glm::vec2& contact, int& numContacts, glm::vec2& edgeNormal, glm::vec2& contactForce)
{
	// Calculating the Box height and width.
	float boxW = box->getExtents().x * 2;
	float boxH = box->getExtents().y * 2;

	// Calculating the penetration value.
	float penetration = 0; for (float x = -box->getExtents().x; x < boxW; x += boxW)
	{
		for (float y = -box->getExtents().y; y < boxH; y += boxH)
		{
			// pos in worldspace
			glm::vec2 p = box->m_position + x * box->m_localX + y * box->m_localY;
			// position in our box's space 
			glm::vec2 p0(glm::dot(p - m_position, m_localX), glm::dot(p - m_position, m_localY));
			float w2 = m_extents.x, h2 = m_extents.y;
			if (p0.y < h2 && p0.y > -h2)
			{
				if (p0.x > 0 && p0.x < w2)
				{
					numContacts++;
					contact += m_position + w2 * m_localX + p0.y * m_localY;
					edgeNormal = m_localX;
					penetration = w2 - p0.x;
				}
				if (p0.x < 0 && p0.x > -w2)
				{
					numContacts++;
					contact += m_position - w2 * m_localX + p0.y * m_localY;
					edgeNormal = -m_localX;
					penetration = w2 + p0.x;
				}
			}
			if (p0.x < w2 && p0.x > -w2)
			{
				if (p0.y > 0 && p0.y < h2)
				{
					numContacts++;
					contact += m_position + p0.x * m_localX + h2 * m_localY;
					float pen0 = h2 - p0.y;
					if (pen0 < penetration || penetration == 0)
					{
						penetration = pen0;
						edgeNormal = m_localY;
					}
				}

				if (p0.y < 0 && p0.y > -h2)
				{
					numContacts++;
					contact += m_position + p0.x * m_localX - h2 * m_localY;
					float pen0 = h2 + p0.y;
					if (pen0 < penetration || penetration == 0)
					{
						penetration = pen0;
						edgeNormal = -m_localY;
					}
				}
			}
		}
	}
	// Calculate the contact force.
	contactForce = penetration * edgeNormal;

	// Return true if a penetration has occurred.
	return (penetration != 0);
}
