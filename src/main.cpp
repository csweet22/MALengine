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
	// TODO: setup textures (SAIL image library)
	// TODO: abstract shaders somehow so that you can create instances of them and edit uniforms.
	// TODO FUTURE: compute shader
	// TODO: Frustrum culling
// TODO: imgui abstract it (create DockSpace imgui docking branch)
// TODO: able to select objects, create a gameobject inspector
// TODO: add a gameobject destroy() method, cleans up any parents and child pointers, frees data, removes from scene list.
// TODO: try to setup raymarching SDFs

int main( int argc, char* argv[])
{
	
	Application* app = new Application();
	app->Run();
	delete app;

	return 0;
}

