#pragma once
#include "PhysicsObject.h"
#include "Gizmos.h"

//-------------------------------------------------------------------------------------------------
// The minimum Linear and Rotation Threshold.
//-------------------------------------------------------------------------------------------------
#define MIN_LINEAR_THRESHOLD 0.010f
#define MIN_ROTATION_THRESHOLD 0.01f

//-------------------------------------------------------------------------------------------------
// Class: 
//		RigidBody: Inherited from PhysicsObject, the RigidBody class is for the physics objects
//				in the scene to inherit from. The rigidbody is what the physics interacts with.
//-------------------------------------------------------------------------------------------------
class RigidBody : public PhysicsObject {

public:
	//-------------------------------------------------------------------------------------------------
	// RigidBody constructor:
	//			
	//		params:
	//			shapeID: The shape type of the shape this rigidBody is being added to.
	//			position: A vector 2 for the position that the rigidBody will be created at.
	//			velocity: A vector 2 for the starting velocity of the rigidBody.
	//			rotation: A float for the starting rotation in radians.
	//			mass: A float for the starting mass value.
	//-------------------------------------------------------------------------------------------------
	RigidBody(ShapeType shapeID, glm::vec2 position, glm::vec2 velocity, float rotation, float mass); 

	//-------------------------------------------------------------------------------------------------
	// Default deconstructor.
	//-------------------------------------------------------------------------------------------------
	~RigidBody();

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
	virtual void fixedUpdate(glm::vec2 gravity, float timeStep);

	//-------------------------------------------------------------------------------------------------
	// debug: Debug is used for debugging purposes.
	//-------------------------------------------------------------------------------------------------
	virtual void debug() {};

	//-------------------------------------------------------------------------------------------------
	// applyForce: This function applies a force to the rigidBody.
	//
	//		params: 
	//			force: A vector 2 for the strength of force applied.
	//			pos: A vector 2 that represents the direction of where the force is being applied.
	//-------------------------------------------------------------------------------------------------
	void applyForce(glm::vec2 force, glm::vec2 pos);

	//-------------------------------------------------------------------------------------------------
	// checkCollision: Checks whether anything has collided with it or not, if it has, it takes in 
	//				the other object as pOther.
	//
	//		params:
	//			pOther: A physics object pointer of whatever shape collides with it.
	//-------------------------------------------------------------------------------------------------
	virtual bool checkCollision(PhysicsObject* pOther) = 0;

	//-------------------------------------------------------------------------------------------------
	// resolveCollision: resolveCollision is what happens when something collides with it.
	// 
	//			params:
	//				actor2: A rigidbody pointer that is whatever object is colliding with this object.
	//				contact: A vector 2 that is the point where the object collided with the object.
	//				collisionNormal: A vector 2 that is the normal of the collision.
	//-------------------------------------------------------------------------------------------------
	void resolveCollision(RigidBody* actor2, glm::vec2 contact, glm::vec2* collisionNormal=nullptr);

	//-------------------------------------------------------------------------------------------------
	// getPosition: A function that returns the current position of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getPosition() { return m_position; }

	//-------------------------------------------------------------------------------------------------
	// setPosition: A function to set the position of the rigidBody to a new position.
	//
	//		params:
	//			newPos: A vector 2 with the new position for the rigidBody.
	//-------------------------------------------------------------------------------------------------
	void setPosition(glm::vec2 newPos) { m_position = newPos; }

	//-------------------------------------------------------------------------------------------------
	// getPosition: A function that returns the current position of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float getRotation() { return m_rotation; }

	//-------------------------------------------------------------------------------------------------
	// getMass: A function that returns the current mass of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float getMass() { return m_mass; }

	//-------------------------------------------------------------------------------------------------
	// getVelocity: A function that returns the current velocity of the rigidBody as a vector 2.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getVelocity() { return m_velocity; }

	//-------------------------------------------------------------------------------------------------
	// setVelocity: A function that takes in a vector 2 as a velocity and applies it to the rigidBody.
	//
	//		params:
	//			newVel: A vector 2 that is to be applied as velocity to the rigidBody.
	//-------------------------------------------------------------------------------------------------
	void setVelocity(glm::vec2 newVel) { m_velocity = newVel; }

	//-------------------------------------------------------------------------------------------------
	// getLinearDrag: This function returns the current linearDrag of this rigidBody.
	//-------------------------------------------------------------------------------------------------
	float getLinearDrag() { return m_linearDrag; };

	//-------------------------------------------------------------------------------------------------
	// setLinearDrag: This function sets the linear drag of the rigidBody.
	//
	//		params: 
	//			newLinDrag: A float that is applied as the new linearDrag value.
	//-------------------------------------------------------------------------------------------------
	void setLinearDrag(float newLinDrag) { m_linearDrag = newLinDrag; }

	//-------------------------------------------------------------------------------------------------
	// getAngularDrag: A function that returns the rigidBody's current angularDrag.
	//-------------------------------------------------------------------------------------------------
	float getAngularDrag() { return m_angularDrag; }

	//-------------------------------------------------------------------------------------------------
	// setAngularDrag: This function sets the current rigidBody's angular drag to a new value.
	//
	//		params:
	//			newAngDrag: A float that is the new angular drag to be set to.
	//-------------------------------------------------------------------------------------------------
	void setAngularDrag(float newAngDrag) { m_angularDrag = newAngDrag; }

	//-------------------------------------------------------------------------------------------------
	// getElasticity: This function returns the current elasticity of this rigidBody.
	//-------------------------------------------------------------------------------------------------
	float getElasticity() { return m_elasticity; }

	//-------------------------------------------------------------------------------------------------
	// setElasticity: This function assigns the new float taken in as the current elasticity.
	//
	//		params:
	//			newElasticity: This is a float that is assigned as the new elasticity of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	void setElasticity(float newElasticity) { m_elasticity = newElasticity; }
	
protected:
	//-------------------------------------------------------------------------------------------------
	// m_position is a vector 2 that stores the current position of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_position;
	//-------------------------------------------------------------------------------------------------
	// m_velocity is a vector 2 that stores the current velocity of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 m_velocity;
	//-------------------------------------------------------------------------------------------------
	// m_mass is a float that stores the current mass of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_mass;
	//-------------------------------------------------------------------------------------------------
	// m_rotation is a float that stores the current rotation of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_rotation;
	//-------------------------------------------------------------------------------------------------
	// m_moment is a float that stores the current moment of inertia of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_moment;
	//-------------------------------------------------------------------------------------------------
	// m_linearDrag is a float that stores the current linear drag of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_linearDrag;
	//-------------------------------------------------------------------------------------------------
	// m_angularDrag is a float that stores the current angular drag of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_angularDrag;
	//-------------------------------------------------------------------------------------------------
	// m_elasticity is a float that stores the current elasticity of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_elasticity;
	//-------------------------------------------------------------------------------------------------
	// m_angularVelocity is a float that stores the current angular velocity of the rigidBody.
	//-------------------------------------------------------------------------------------------------
	float m_angularVelocity;
};

