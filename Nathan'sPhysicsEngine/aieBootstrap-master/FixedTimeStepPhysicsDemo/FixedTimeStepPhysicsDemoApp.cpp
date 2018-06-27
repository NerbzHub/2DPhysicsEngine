#include "FixedTimeStepPhysicsDemoApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "PhysicsScene.h"
#include <Gizmos.h>
#include <glm\ext.hpp>
#include <glm\glm.hpp>
#include <glm\vec2.hpp>
#include "Sphere.h"
#include "Plane.h"
#include "AABB.h"
#include "gl_core_4_4.h" // this is for imgui for glClear()

// A #define for pi.
#define M_PI 3.1415926

//-------------------------------------------------------------------------------------------------
// Class:
//		FixedTimeStepPhysicsDemoApp: This class is used to set up a certain scene demonstrating 
//									certain shapes.
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Default FixedTimeStepPhysicsDemoApp constructor
//-------------------------------------------------------------------------------------------------
FixedTimeStepPhysicsDemoApp::FixedTimeStepPhysicsDemoApp()
{

}

//-------------------------------------------------------------------------------------------------
// Default FixedTimeStepPhysicsDemoApp deconstructor
//-------------------------------------------------------------------------------------------------
FixedTimeStepPhysicsDemoApp::~FixedTimeStepPhysicsDemoApp()
{
}

//-------------------------------------------------------------------------------------------------
// startup: The first function to be called in the demo.
//-------------------------------------------------------------------------------------------------
bool FixedTimeStepPhysicsDemoApp::startup()
{
	// Increase the 2d line count to maximize the number of objects that can be drawn.
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	// Assigning a new Renderer 2D to the m_2dRenderer.
	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	// Assign new PhysicsScene.
	m_physicsScene = new PhysicsScene();
	// Set the tick rate of the scene.
	m_physicsScene->setTimeStep(0.01f);
	// Set the gravity of the scene.
	m_physicsScene->setGravity(glm::vec2(0.0f, -10.0f));

	// Set the radius.
	float radius = 1.0f;
	// Set the speed.
	float speed = 30;
	// Set the starting position.
	glm::vec2 startPos(-40, 0);
	// Set the inclination.
	float inclination = (float)M_PI / 4.0f;

	//setupContinuousDemo(startPos, inclination, speed, -10);

	//m_physicsScene->addActor(new Sphere(startPos, inclination, speed, 1, radius, glm::vec4(1, 0, 0, 1)));

	/*Sphere* ball;
	Sphere* ball1;*/

	/*ball = new Sphere(glm::vec2(10, 50), glm::vec2(0, 0), 10.0f, 1, glm::vec4(1, 0, 0, 1));
	m_physicsScene->addActor(ball);
	ball1 = new Sphere(glm::vec2(-10, 50), glm::vec2(0, 0), 10.0f, 1, glm::vec4(0, 1, 0, 1));
	m_physicsScene->addActor(ball1);*/
	//ball->applyForceToActor(ball1, glm::vec2(20, 20));

//-------------------------------------------------------------------------------------------------
// Creating the shapes:
//
//Balls
	redBall = new Sphere(glm::vec2(-70, 20), glm::vec2(0, 0), 1.0f, 6, glm::vec4(1, 0, 0, 1));
	redBall1 = new Sphere(glm::vec2(-30, 20), glm::vec2(0, 0), 1.0f, 6, glm::vec4(1, 0, 0, 1));
	redBall2 = new Sphere(glm::vec2(-90, 20), glm::vec2(0, 0), 1.0f, 6, glm::vec4(1, 0, 0, 1));

	ball1 = new Sphere(glm::vec2(40, 40), glm::vec2(0, 0), 1.0f, 4, glm::vec4(0, 1, 0, 1));
	ball2 = new Sphere(glm::vec2(20, 40), glm::vec2(0, 0), 1.0f, 4, glm::vec4(0, 1, 0, 1));
	ball3 = new Sphere(glm::vec2(10, 40), glm::vec2(0, 0), 1.0f, 4, glm::vec4(0, 1, 0, 1));
	ball4 = new Sphere(glm::vec2(60, 40), glm::vec2(0, 0), 1.0f, 4, glm::vec4(0, 1, 0, 1));


	//Planes
	plane = new Plane(glm::vec2(0, 1), (-10));
	plane1 = new Plane(glm::normalize(glm::vec2(3, 2)), (0));
	planeTop = new Plane(glm::vec2(0, -1), (-50));
	planeBottom = new Plane(glm::vec2(0, 1), (-50));
	planeLeft = new Plane(glm::vec2(1, 0), (-99));
	planeRight = new Plane(glm::vec2(-1, 0), (-99));

	//AABBs
	aabb = new AABB(glm::vec2(40, 10), glm::vec2(5, 5), glm::vec2(0, 0), 1.0f, glm::vec4(1, 0, 1, 1));
	aabb1 = new AABB(glm::vec2(60, 20), glm::vec2(5, 5), glm::vec2(0, 0), 1, glm::vec4(1, 0, 1, 1));
	/*aabb2 = new AABB(glm::vec2(-60, 20), glm::vec2(5, 5), glm::vec2(0, 0), 1, glm::vec4(1, 0, 1, 1));
	aabb3 = new AABB(glm::vec2(-40, 20), glm::vec2(5, 5), glm::vec2(0, 0), 1, glm::vec4(1, 0, 1, 1));
	aabb4 = new AABB(glm::vec2(-100, 20), glm::vec2(5, 5), glm::vec2(0, 0), 1, glm::vec4(1, 0, 1, 1));
*/


	//Boxes
	//box = new Box(glm::vec2(20, 25), glm::vec2(3, 3), glm::vec2(0, 0), 1.0f, glm::vec4(0, 1, 0, 1));
	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	// Applying forces to shapes:
	//
	redBall->applyForce(glm::vec2(100, 0), glm::vec2(0, 0));
	redBall->applyForce(glm::vec2(50, 0), glm::vec2(0, 0));
	redBall->applyForce(glm::vec2(50, 30), glm::vec2(0, 0));

	ball1->applyForce(glm::vec2(0, 0), glm::vec2(0, 0));
	aabb->applyForce(glm::vec2(-50, -30), glm::vec2(0, 0));
	aabb1->applyForce(glm::vec2(0, 0), glm::vec2(0, 0));
	

	//-------------------------------------------------------------------------------------------------

	//-------------------------------------------------------------------------------------------------
	// Adding shapes to PhysiscsScene:
	//
	// Sphere
	m_physicsScene->addActor(redBall);
	m_physicsScene->addActor(redBall1);
	m_physicsScene->addActor(redBall2);

	m_physicsScene->addActor(ball1);
	m_physicsScene->addActor(ball2);
	m_physicsScene->addActor(ball3);
	m_physicsScene->addActor(ball4);


	// Plane
	//m_physicsScene->addActor(plane);
	m_physicsScene->addActor(plane1);
	m_physicsScene->addActor(planeTop);
	m_physicsScene->addActor(planeBottom);
	m_physicsScene->addActor(planeLeft);
	m_physicsScene->addActor(planeRight);

	// AABB
	m_physicsScene->addActor(aabb);
	m_physicsScene->addActor(aabb1);


	//-------------------------------------------------------------------------------------------------
	return true;
}

//-------------------------------------------------------------------------------------------------
// shutdown: The function that gets called at the end of the demo.
//-------------------------------------------------------------------------------------------------
void FixedTimeStepPhysicsDemoApp::shutdown()
{
	// for every mouse click that happens, delete mouseball
	// Delete anything that needs deleting to prevent memory leaks.
	delete m_font;
	delete m_2dRenderer;
	delete plane;
	delete plane1;
	delete planeTop;
	delete planeBottom;
	delete planeLeft;
	delete planeRight;
	delete redBall;
	delete redBall1;
	delete redBall2;
	delete ball1;
	delete ball2;
	delete ball3;
	delete ball4;
	delete aabb;
	delete aabb1;
}

//-------------------------------------------------------------------------------------------------
// update: Update runs every frame. Anything that needs to be done in the scene that isn't 
//		physics calculations. 
//		
//		params: 
//			deltaTime: deltaTime is a float which is the frame rate.
//-------------------------------------------------------------------------------------------------
void FixedTimeStepPhysicsDemoApp::update(float deltaTime) {

	// Input.
	aie::Input* input = aie::Input::getInstance();

	// Clears the screen of any old positions of the shapes.
	aie::Gizmos::clear();
	// Physics scene update to happen every frame.
	m_physicsScene->update(deltaTime);
	// Physics scene update for the gizmos.
	m_physicsScene->updateGizmos();

	// Exit the application if escape is pressed.
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

//-------------------------------------------------------------------------------------------------
// draw: This function draws all of the objects that will be rendered in the scene.
//-------------------------------------------------------------------------------------------------
void FixedTimeStepPhysicsDemoApp::draw() {

	// Wipe the screen to the background colour.
	clearScreen();

	// Begin drawing sprites.
	m_2dRenderer->begin();

	// Draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// Output some text, uses the last used colour.
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// Done drawing sprites.
	m_2dRenderer->end();
}

//-------------------------------------------------------------------------------------------------
// getMouseInWorldSpace: This function gets the current mouse position as a vector 2.
//
//		params:
//			pos: A vector 2 that is the mouse's position.
//-------------------------------------------------------------------------------------------------
glm::vec2 FixedTimeStepPhysicsDemoApp::getMouseInWorldSpace(glm::vec2 pos)
{
	// Gets the aspect ratio.
	auto aspectRatio = (float)getWindowHeight() / getWindowWidth();
	// Gets the ortho matrix value.
	auto orthoMatrix = glm::ortho<float>(
		-100, 100, -100 * aspectRatio, 100 * aspectRatio, -1, 1);

	// Clips the position to the window.
	auto clipPos = glm::vec2{ pos.x / getWindowWidth(), pos.y / getWindowHeight() };
	clipPos *= 2.0f;
	clipPos -= glm::vec2{ 1, 1 };

	// Gets the world posittion value.
	auto worldPos = glm::inverse(orthoMatrix) * glm::vec4{ clipPos, 0, 1 };

	// Returns the world pos as a vector 2.
	return glm::vec2{ worldPos.x, worldPos.y };

	// Matt Dodd assisted me with this.
}

//-------------------------------------------------------------------------------------------------
//  setupContinuousDemo: This function sets up a preset scene.
//		
//		params:
//			startPos: A vector 2 that is the starting position.
//			inclination: A float that gets assigned as the inclination value.
//			speed: A float that sets the stating speed.
//			gravity: A float that sets the starting gravitational force of the scene.
//-------------------------------------------------------------------------------------------------
void FixedTimeStepPhysicsDemoApp::setupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	// Setting up the timeStep.
	float t = 0;
	float tStep = 0.5f;
	// Setting the radius.
	float radius = 1.0f;
	// Setting the segments.
	int segments = 12;
	// Setting the colour.
	glm::vec4 colour = glm::vec4(1, 1, 0, 1);

	while (t <= 5)
	{
		//calculate the x, y position of the projectile at time t
		glm::vec2 incl = glm::vec2(sin(inclination), cos(inclination));

		float x = startPos.x + (incl.x * speed * t);
		float y = startPos.y + (incl.y * speed * t) + ((gravity * t*t) / 2.0f);

		aie::Gizmos::add2DCircle(glm::vec2(x, y), radius, segments, colour);
		t += tStep;
	}
}




