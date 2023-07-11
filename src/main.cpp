// Ash Engine Main


#include "GlobalIncludes.hpp"
#include "Application.hpp"

// TODO: add AABB collision
// TODO: add physics
// TODO: add texture quad
	// Setup a basic render pipeline
	// setup textures
// TODO: setup cameras 
	// Let me change camera types dynamically
// TODO: imgui
// TODO: mesh loader
// TODO: Figure file structure
// TODO FUTURE: compute shader
// TODO: Make it so window resize works properly

int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}

