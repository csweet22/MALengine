// Ash Engine Main


#include "GlobalIncludes.hpp"
#include "Application.hpp"

// TODO: add physics
	// TODO: add AABB collision
// Setup a basic render pipeline
	// TODO: mesh loader
	// TODO: add primitives
	// TODO: add texture quad
	// setup textures
	// TODO FUTURE: compute shader
// TODO: imgui abstract it
// TODO: make imgui scene hierarchy show parents and children

int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}

