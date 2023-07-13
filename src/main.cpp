// Ash Engine Main


#include "GlobalIncludes.hpp"
#include "Application.hpp"

// TODO: add physics
	// TODO: add AABB collision
// Setup a basic render pipeline
	// TODO: mesh loader (assimp)
	// TODO: add primitives
	// TODO: add texture quad
	// TODO: add LYGIA shader library
	// setup textures (SAIL image library)
	// TODO FUTURE: compute shader
// TODO: imgui abstract it (create DockSpace imgui docking branch)
// TODO: make imgui scene hierarchy show parents and children
// TODO: enabled is broken for children
// TODO: able to select objects

int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}

