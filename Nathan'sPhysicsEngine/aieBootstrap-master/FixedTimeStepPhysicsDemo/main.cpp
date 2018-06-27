#include "FixedTimeStepPhysicsDemoApp.h"
#include <crtdbg.h>


int main() {

	// allocation
	auto app = new FixedTimeStepPhysicsDemoApp();

	// initialise and loop
	app->run("AIE", screenX, screenY, false);

	// deallocation
	delete app;

	// Check for memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	return 0;
}