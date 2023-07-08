// Ash Engine Main


#include "GlobalIncludes.hpp"
#include "Application.cpp"

// TODO: add AABB collision
// TODO: add physics
// TODO: add texture quad
	// Setup a basic render pipeline
	// setup shaders
	// setup textures
// TODO: setup cameras
// TODO: imgui

int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}

