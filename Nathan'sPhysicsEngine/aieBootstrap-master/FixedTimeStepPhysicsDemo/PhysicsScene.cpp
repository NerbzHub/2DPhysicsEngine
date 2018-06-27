#include "PhysicsScene.h"

//-------------------------------------------------------------------------------------------------
// Class:
//		PhysicsScene: The Physics scene covers all of the collision detection code, gravity and
//					most of what happens during the scene.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Default Constructor for the physics scene.
//-------------------------------------------------------------------------------------------------
PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
	delete m_actors.back();
}

void PhysicsScene::update(float dt)
{
	static std::list<PhysicsObject*> dirty;

	// update physics at a fixed time step
	static float accumulatedTime = 0.0f;
	accumulatedTime += dt;
	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		accumulatedTime -= m_timeStep;
		checkForCollision();
		// check for collisions (ideally you'd want to have some sort of
		// scene management in place)
		/*for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{*/


			//if (pActor == pOther)
				//continue;
			//if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
				//std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
				//continue;

			/*RigidBody* pRigid = dynamic_cast<RigidBody*>(pActor);
			if (pRigid->checkCollision(pOther) == true)
			{
				pRigid->applyForceToActor(dynamic_cast<RigidBody*>(pOther),
					pRigid->getVelocity() * pRigid->getMass());
				dirty.push_back(pRigid);
				dirty.push_back(pOther);
			}*/


			/*	}
			}
			dirty.clear();*/

	}
}

//-------------------------------------------------------------------------------------------------
// updateGizmos: Update gizmos is an update function for the gizmos. 
//-------------------------------------------------------------------------------------------------
void PhysicsScene::updateGizmos()
{
	// Re-creates every gizmo on the screen every frame.
	for (auto pActor : m_actors)
	{
		pActor->makeGizmo();
	}
}

//-------------------------------------------------------------------------------------------------
// addActor: This function is used to add an actor to the physics scene.
//
//		params:
//			actor: Actor is the physicsObject that is being added to the physics scene.
//-------------------------------------------------------------------------------------------------
void PhysicsScene::addActor(PhysicsObject* actor)
{
	// Add an actor to the scene.
	m_actors.push_back(actor);
}

//-------------------------------------------------------------------------------------------------
// removeActor: This function is used to remove an actor from the physics scene.
//
//		params:
//			actor: Actor is the physicsObject that is being removed from the physics scene.
//-------------------------------------------------------------------------------------------------
void PhysicsScene::removeActor(PhysicsObject* actor)
{
}

//-------------------------------------------------------------------------------------------------
// debugScene: This function is used for debugging.
//-------------------------------------------------------------------------------------------------
void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		std::cout << count << " : ";
		pActor->debug();
		count++;
	}
}

// function pointer array for doing our collisions 
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

//-------------------------------------------------------------------------------------------------
// CollisionFunctionArray: This array checks which collision is occurring if there is a collision.
//-------------------------------------------------------------------------------------------------
static fn collisionFunctionArray[] = {
	PhysicsScene::plane2Plane, PhysicsScene::plane2Sphere, PhysicsScene::plane2aabb, PhysicsScene::plane2Box,
	PhysicsScene::sphere2Plane, PhysicsScene::sphere2Sphere, PhysicsScene::sphere2aabb, PhysicsScene::sphere2Box,
	PhysicsScene::aabb2Plane, PhysicsScene::aabb2Sphere, PhysicsScene::aabb2aabb, PhysicsScene::aabb2Box,
	PhysicsScene::box2Plane, PhysicsScene::box2Sphere, PhysicsScene::box2aabb, PhysicsScene::box2Box };

//-------------------------------------------------------------------------------------------------
// checkForCollision: The check for collision function checks whether there are any collisions
//					occurring.
//-------------------------------------------------------------------------------------------------
void PhysicsScene::checkForCollision() {
	// Stores the size of actors in the scene.
	int actorCount = m_actors.size();
	// Need to check for collisions against all objects except this one. 
	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeId1 = object1->getShapeID();
			int shapeId2 = object2->getShapeID();
			// Using function pointers.
			int functionIdx = (shapeId1 * SHAPE_COUNT) + shapeId2;
			fn collisionFunctionPtr = collisionFunctionArray[functionIdx];
			if (collisionFunctionPtr != nullptr)
			{
				// Did a collision occur? 
				collisionFunctionPtr(object1, object2);
			}
		}
	}
}

//-------------------------------------------------------------------------------------------------
// These functions are all the collision code for the various types of shape collision.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//												Plane
//
bool PhysicsScene::plane2Plane(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::plane2Sphere(PhysicsObject *obj1, PhysicsObject *obj2)
{
	return sphere2Plane(obj2, obj1);
}

bool PhysicsScene::plane2aabb(PhysicsObject *obj1, PhysicsObject *obj2)
{
	return aabb2Plane(obj2, obj1);

}

bool PhysicsScene::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return box2Plane(obj2, obj1);
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//												Sphere
//
bool PhysicsScene::sphere2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	//if we are successful then test for collision 
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->getNormal();
		//only for rotation
		glm::vec2 contact = sphere->getPosition() + (collisionNormal * -sphere->getRadius());
		float sphereToPlane = glm::dot(sphere->getPosition(), plane->getNormal()) - plane->getDistance();
		// if we are behind plane then we flip the normal 
		if (sphereToPlane < 0)
		{
			collisionNormal *= -1;
			sphereToPlane *= -1;
		}
		float intersection = sphere->getRadius() - sphereToPlane;
		if (intersection > 0)
		{
			glm::vec2 nullVec2(0, 0);

			//set sphere velocity to zero here 
			//sphere->setVelocity(nullVec2);
			plane->resolveCollision(sphere, contact);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//try to cast objects to sphere and sphere 
	Sphere *sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere *sphere2 = dynamic_cast<Sphere*>(obj2);


	//if we are successful then test for collision 

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		glm::vec2 contact = 0.5f * (sphere1->getPosition() + sphere2->getPosition());

		glm::vec2 displacement = sphere1->getPosition() - sphere2->getPosition();

		glm::vec2 collNormal = normalize(displacement);

		float deltaXSquared;
		float deltaYSquared;
		float sumRadiiSquared;

		deltaXSquared = sphere1->getPosition().x - sphere2->getPosition().x;
		deltaXSquared *= deltaXSquared;

		deltaYSquared = sphere1->getPosition().y - sphere2->getPosition().y;
		deltaYSquared *= deltaYSquared;

		sumRadiiSquared = sphere1->getRadius() + sphere2->getRadius();
		sumRadiiSquared *= sumRadiiSquared;

		if (deltaXSquared + deltaYSquared <= sumRadiiSquared)
		{
			glm::vec2 nullVec2(0, 0);
			//Collision
			//sphere1->setVelocity(nullVec2);
			//sphere2->setVelocity(nullVec2);
			sphere1->resolveCollision(sphere2, contact, &collNormal);
			return true;
		}









		//this is where the collision detection happens 
		//you need code which sets the velocity of the two spheres to zero 
		//if they are overlapping 



		// get distance between 2 spheres 
		//distanceBetweenSpheres = sphere2->getPosition() - sphere1->getPosition();

		// if distance is less than the combined radius of 
		// both spheres, then a collision occurred so set the 
		// velocity of both spheres to 0 (we will add collision resolution later)
		//if (distanceBetweenSpheres < )
		//{
		//	//velocity = 0
		//}
	}

	return false;
}

// A is centre clamped

// A = clamp(C, min, max)
//
// V = A - C
//
// result = (V * V) < radius^2
bool PhysicsScene::sphere2aabb(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Sphere *sphere = dynamic_cast<Sphere*>(obj1);
	AABB *aabb = dynamic_cast<AABB*>(obj2);

	// Just create the variables first.
	glm::vec2 tl = aabb->getPosition() + glm::vec2(-aabb->getExtents().x, -aabb->getExtents().y);
	glm::vec2 tr = aabb->getPosition() + glm::vec2(aabb->getExtents().x, aabb->getExtents().y);
	glm::vec2 br = aabb->getPosition() + glm::vec2(aabb->getExtents().x, aabb->getExtents().y);
	glm::vec2 bl = aabb->getPosition() + glm::vec2(-aabb->getExtents().x, -aabb->getExtents().y);

	float radius = sphere->getRadius();
	glm::vec2 centreOfSphere = sphere->getPosition();

	glm::vec2 A = glm::clamp(centreOfSphere, bl, tr);
	glm::vec2 V = A - centreOfSphere;

	if (radius > glm::length(V))
	{
		sphere->resolveCollision(aabb, A);
		return true;
	}
	else
	{
		return false;
	}

}

bool PhysicsScene::sphere2Box(PhysicsObject *obj1, PhysicsObject *obj2)
{
	return box2Sphere(obj2, obj1);
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//												AABB
//
bool PhysicsScene::aabb2Plane(PhysicsObject *obj1, PhysicsObject *obj2)
{
	AABB *aabb = dynamic_cast<AABB*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);

	if (aabb != nullptr && plane != nullptr)
	{

		glm::vec2 collisionNormal = glm::normalize(plane->getNormal());
		//glm::vec2 contact = glm::vec2(0, 0);
		//
		//glm::vec2 diagonals = glm::vec2(aabb->getPosition().x - aabb->getExtents().x, aabb->getPosition().y + aabb->getExtents().y);
		//// Top right
		//float c1 = glm::dot(aabb->getPosition() + 0.5f * aabb->getExtents(), plane->getNormal()) - plane->getDistance();
		//// Top left
		//float c2 = glm::dot(aabb->getPosition() - 0.5f * aabb->getExtents(), plane->getNormal()) - plane->getDistance();
		//// Bottom right
		//float c3 = glm::dot(+diagonals, plane->getNormal()) - plane->getDistance();
		//// Bottom left
		//// If c4 is the same as c3 then it works fine or if i put a - before plane->GetNormal() then it works.
		//float c4 = glm::dot(-diagonals, -plane->getNormal()) - plane->getDistance();
		//
		//if (c1 < 0 || c2 < 0 || c3 < 0 || c4 < 0)
		//{
		//	plane->resolveCollision(aabb, contact);
		//	return true;
		//}

		glm::vec2 tl = aabb->getPosition() + glm::vec2(-aabb->getExtents().x, -aabb->getExtents().y);
		glm::vec2 tr = aabb->getPosition() + glm::vec2(aabb->getExtents().x, aabb->getExtents().y);
		glm::vec2 br = aabb->getPosition() + glm::vec2(aabb->getExtents().x, -aabb->getExtents().y);
		glm::vec2 bl = aabb->getPosition() + glm::vec2(-aabb->getExtents().x, -aabb->getExtents().y);

		float tl_depth = glm::dot(collisionNormal, tl) - plane->getDistance();
		float tr_depth = glm::dot(collisionNormal, tr) - plane->getDistance();
		float bl_depth = glm::dot(collisionNormal, bl) - plane->getDistance();
		float br_depth = glm::dot(collisionNormal, br) - plane->getDistance();

		float smallest = tl_depth;
		if (tr_depth < smallest) smallest = tr_depth;
		if (bl_depth < smallest) smallest = bl_depth;
		if (br_depth < smallest) smallest = br_depth;

		if (smallest < 0)
		{
			aabb->setPosition(aabb->getPosition() + plane->getNormal() * -smallest);
			plane->resolveCollision(aabb, glm::vec2(0, 0));
			return true;
		}


	}
	return false;
}


bool PhysicsScene::aabb2Sphere(PhysicsObject *obj1, PhysicsObject *obj2)
{
	sphere2aabb(obj2, obj1);
	return true;
}

bool PhysicsScene::aabb2aabb(PhysicsObject *obj1, PhysicsObject *obj2)
{
	AABB *aabb1 = dynamic_cast<AABB*>(obj1);
	AABB *aabb2 = dynamic_cast<AABB*>(obj2);

	// AABB 1
	glm::vec2 tl1 = aabb1->getPosition() + glm::vec2(-aabb1->getExtents().x, aabb1->getExtents().y);
	glm::vec2 tr1 = aabb1->getPosition() + glm::vec2(aabb1->getExtents().x, aabb1->getExtents().y);
	glm::vec2 br1 = aabb1->getPosition() + glm::vec2(aabb1->getExtents().x, -aabb1->getExtents().y);
	glm::vec2 bl1 = aabb1->getPosition() + glm::vec2(-aabb1->getExtents().x, -aabb1->getExtents().y);

	// AABB 2
	glm::vec2 tl2 = aabb2->getPosition() + glm::vec2(-aabb2->getExtents().x, aabb2->getExtents().y);
	glm::vec2 tr2 = aabb2->getPosition() + glm::vec2(aabb2->getExtents().x, aabb2->getExtents().y);
	glm::vec2 br2 = aabb2->getPosition() + glm::vec2(aabb2->getExtents().x, -aabb2->getExtents().y);
	glm::vec2 bl2 = aabb2->getPosition() + glm::vec2(-aabb2->getExtents().x, -aabb2->getExtents().y);

	if (tr1.x < bl2.x || tr2.x < bl1.x || tr1.y < bl2.y || tr2.y < bl1.y)
	{
		return false;
	}
	else
	{
		// 
		aabb1->resolveCollision(aabb2, glm::vec2(0,0));
		return true;
	}
}

bool PhysicsScene::aabb2Box(PhysicsObject *, PhysicsObject *)
{
	return false;
}
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//												Box
//
bool PhysicsScene::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box *box = dynamic_cast<Box*>(obj1);
	Plane *plane = dynamic_cast<Plane*>(obj2);
	//if we are successful then test for collision
	if (box != nullptr && plane != nullptr)
	{
		int numContacts = 0;
		glm::vec2 contact(0, 0);
		float contactV = 0;
		float radius = 0.5f * std::fminf(box->getWidth(), box->getHeight());
		// which side is the centre of mass on?
		glm::vec2 planeOrigin = plane->getNormal() * plane->getDistance();
		float comFromPlane = glm::dot(box->getPosition() - planeOrigin, plane->getNormal());
		// check all four corners to see if we've hit the plane
		for (float x = -box->getExtents().x;
			x < box->getWidth();
			x += box->getWidth())
		{
			for (float y = -box->getExtents().y; y < box->getHeight(); y += box->getHeight())
			{
				// get the position of the corner in world space
				glm::vec2 p = box->getPosition() + x * box->getLocalX() + y * box->getLocalY();
				float distFromPlane = glm::dot(p - planeOrigin, plane->getNormal());
				// this is the total velocity of the point
				float velocityIntoPlane = glm::dot(box->getVelocity() + box->getRotation() *
					(-y * box->getLocalX() + x * box->getLocalY()), plane->getNormal());
				// if this corner is on the opposite side from the COM,
				// and moving further in, we need to resolve the collision
				if ((distFromPlane > 0 && comFromPlane < 0 && velocityIntoPlane > 0) ||
					(distFromPlane < 0 && comFromPlane > 0 && velocityIntoPlane < 0))
				{
					numContacts++;
					contact += p;
					contactV += velocityIntoPlane;
				}
			}
		}

		// we've had a hit - typically only two corners can contact
		if (numContacts > 0)
		{
			// get the average collision velocity into the plane
			// (covers linear and rotational velocity of all corners involved)
			float collisionV = contactV / (float)numContacts;
			// get the acceleration required to stop (restitution = 0) or reverse
			// (restitution = 1) the average velocity into the plane
			glm::vec2 acceleration = -plane->getNormal() * ((1.0f + box->getElasticity()) * collisionV);
			// and the average position at which we'll apply the force
			// (corner or edge centre) 
			glm::vec2 localContact = (contact / (float)numContacts) - box->getPosition();
			// this is the perpendicular distance we apply the force at relative to
			// the COM, so Torque = F*r
			float r = glm::dot(localContact, glm::vec2(plane->getNormal().y, -plane->getNormal().x));
			// work out the "effective mass" - this is a combination of moment of
			// inertia and mass, and tells us how much the contact point velocity
			// will change with the force we're applying
			float mass0 = 1.0f / (1.0f / box->getMass() + (r*r) / box->getMoment());
			// and apply the force 
			box->applyForce(acceleration * mass0, localContact);
		}
	}
	return false;
}

bool PhysicsScene::box2Sphere(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Box* box = dynamic_cast<Box*>(obj1); Sphere* sphere = dynamic_cast<Sphere*>(obj2); if (box != nullptr && sphere != nullptr) {
		glm::vec2 circlePos = sphere->getPosition() - box->getPosition();
		float w2 = box->getWidth() / 2, h2 = box->getHeight() / 2;

		int numContacts = 0;
		glm::vec2 contact(0, 0);
		// contact is in our box coordinates
		// check the four corners to see if any of them are inside the circle 
		for (float x = -w2; x <= w2; x += box->getWidth())
		{
			for (float y = -h2; y <= h2; y += box->getHeight())
			{
				glm::vec2 p = x * box->getLocalX() + y * box->getLocalY();
				glm::vec2 dp = p - circlePos;
				if (dp.x*dp.x + dp.y*dp.y < sphere->getRadius()*sphere->getRadius())
				{
					numContacts++;
					contact += glm::vec2(x, y);
				}
			}

		}

		glm::vec2* direction = nullptr;

		// get the local position of the circle centre 
		glm::vec2 localPos(glm::dot(box->getLocalX(), circlePos), glm::dot(box->getLocalY(), circlePos));
		if (localPos.y < h2 && localPos.y > -h2)
		{
			if (localPos.x > 0 && localPos.x < w2 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec2(w2, localPos.y);
				direction = new glm::vec2(box->getLocalX());
			}
			if (localPos.x < 0 && localPos.x > -(w2 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec2(-w2, localPos.y);
				direction = new glm::vec2(-box->getLocalX());
			}
		}

		if (localPos.x < w2 && localPos.x > -w2)
		{
			if (localPos.y > 0 && localPos.y < h2 + sphere->getRadius())
			{
				numContacts++;
				contact += glm::vec2(localPos.x, h2);
				direction = new glm::vec2(box->getLocalY());
			}

			if (localPos.y < 0 && localPos.y > -(h2 + sphere->getRadius()))
			{
				numContacts++;
				contact += glm::vec2(localPos.x, -h2);
				direction = new glm::vec2(-box->getLocalY());
			}
		}
		if (numContacts > 0)
		{
			// average, and convert back into world coords
			contact = box->getPosition() + (1.0f / numContacts) *
				(box->getLocalX() *contact.x + box->getLocalY()*contact.y);
			box->resolveCollision(sphere, contact, direction);
		}
		delete direction;
	}
	return false;
}


bool PhysicsScene::box2aabb(PhysicsObject *, PhysicsObject *)
{
	return false;
}

bool PhysicsScene::box2Box(PhysicsObject *obj1, PhysicsObject *obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{

		glm::vec2 boxPos = box2->getPosition() - box1->getPosition();
		glm::vec2 normal;
		glm::vec2 contactForce1, contactForce2;
		glm::vec2 contact(0, 0);

		int numContacts = 0; box1->checkBoxCorners(box2, contact, numContacts, normal, contactForce1);
		if (box2->checkBoxCorners(box1, contact, numContacts, normal, contactForce2))
		{
			normal = -normal;
		}

		if (numContacts > 0)
		{
			glm::vec2 contactForce = 0.5f * (contactForce1 - contactForce2);

			box1->setPosition(box1->getPosition() - contactForce);
			box2->setPosition(box2->getPosition() + contactForce);
			box1->resolveCollision(box2, contact / float(numContacts), &normal);
			return true;
		}
	}
	return false;
}
//-------------------------------------------------------------------------------------------------

// this helped me with the aabb https://www.gamasutra.com/view/feature/3015/pool_hall_lessons_fast_accurate_.php