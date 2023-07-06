// Ash Engine Main

// ===========================================================================
// INCLUDES
// ===========================================================================

#include "GlobalIncludes.hpp"

// ===========================================================================
// HELPER FUNCTIONS AND CLASSES
// ===========================================================================

#include "Application.cpp"

// ===========================================================================
// MAIN
// ===========================================================================


int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Init();
	delete app;

	return 0;
}

