#pragma once
#include "glm\glm.hpp"
#include "glm\vec2.hpp"
#include "Application.h"
#include "Renderer2D.h"

//-------------------------------------------------------------------------------------------------
// Forward Declarations
//
class PhysicsScene;
class Plane;
class Sphere;
class AABB;
class Box;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Screen window dimentions in pixels
static int screenX = 1280;
static int screenY = 720;
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Class:
//		FixedTimeStepPhysicsDemoApp: This class is used to set up a certain scene demonstrating 
//									certain shapes.
//-------------------------------------------------------------------------------------------------
class FixedTimeStepPhysicsDemoApp : public aie::Application {
public:
	//-------------------------------------------------------------------------------------------------
	// Default FixedTimeStepPhysicsDemoApp constructor
	//-------------------------------------------------------------------------------------------------
	FixedTimeStepPhysicsDemoApp();

	//-------------------------------------------------------------------------------------------------
	// Default FixedTimeStepPhysicsDemoApp deconstructor
	//-------------------------------------------------------------------------------------------------
	virtual ~FixedTimeStepPhysicsDemoApp();

	//-------------------------------------------------------------------------------------------------
	// startup: The first function to be called in the demo.
	//-------------------------------------------------------------------------------------------------
	virtual bool startup();

	//-------------------------------------------------------------------------------------------------
	// shutdown: The function that gets called at the end of the demo.
	//-------------------------------------------------------------------------------------------------
	virtual void shutdown();

	//-------------------------------------------------------------------------------------------------
	// update: Update runs every frame. Anything that needs to be done in the scene that isn't 
	//		physics calculations. 
	//		
	//		params: 
	//			deltaTime: deltaTime is a float which is the frame rate.
	//-------------------------------------------------------------------------------------------------
	virtual void update(float deltaTime);

	//-------------------------------------------------------------------------------------------------
	// draw: This function draws all of the objects that will be rendered in the scene.
	//-------------------------------------------------------------------------------------------------
	virtual void draw();

	//-------------------------------------------------------------------------------------------------
	// m_physicsScene is a PhysicsScene pointer to create a physics scene.
	//-------------------------------------------------------------------------------------------------
	PhysicsScene* m_physicsScene;


	//-------------------------------------------------------------------------------------------------
	// createSphere: This function is used to create a sphere at the position of the mouse when the 
	//				left mouse button is clicked.
	//
	//		params:
	//			mousePos: This is a vector 2 that takes in the mouse's position to create a sphere 
	//					there.
	//-------------------------------------------------------------------------------------------------
	void createSphere(glm::vec2 mousePos);

	//-------------------------------------------------------------------------------------------------
	// getMouseInWorldSpace: This function gets the current mouse position as a vector 2.
	//
	//		params:
	//			pos: A vector 2 that is the mouse's position.
	//-------------------------------------------------------------------------------------------------
	glm::vec2 getMouseInWorldSpace(glm::vec2 pos);

	//-------------------------------------------------------------------------------------------------
	//  setupContinuousDemo: This function sets up a preset scene.
	//		
	//		params:
	//			startPos: A vector 2 that is the starting position.
	//			inclination: A float that gets assigned as the inclination value.
	//			speed: A float that sets the stating speed.
	//			gravity: A float that sets the starting gravitational force of the scene.
	//-------------------------------------------------------------------------------------------------
	virtual void setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);

protected:

	// m_2dRenderer is a Renderer2D pointer to store the renderer
	aie::Renderer2D*	m_2dRenderer;
	// m_font is a Font pointer that store the current font.
	aie::Font*			m_font;
	//-------------------------------------------------------------------------------------------------
	// Creating the objects to be added to the scene.
	//
	Plane* plane;
	Plane* plane1;
	Plane* planeTop;
	Plane* planeBottom;
	Plane* planeLeft;
	Plane* planeRight;
	Sphere* redBall;
	Sphere* redBall1;
	Sphere* redBall2;

	Sphere* ball1;
	Sphere* ball2;
	Sphere* ball3;
	Sphere* ball4;

	AABB* aabb;
	AABB* aabb1;
	//-------------------------------------------------------------------------------------------------

	// Mouse click counter
	int mouseClickCount = 0;
};