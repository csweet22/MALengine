// Cole Sweet | 251179642
// CS3388b
// April 2023
// Assignment 6

#ifndef PLANEMESH_HPP
#define PLANEMESH_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>


#include "GameObject.hpp"
#include "GlobalIncludes.hpp"
#include "Camera.hpp"

// Class that creates Texture Objects, VBOs, VAO, for a single ply and single bmp file.
// This also provides a draw() method for the main draw-loop to call.
class PlaneMesh : public GameObject
{

private:
    GLuint vaoID;           // ID of the VAO
    GLuint positionsID;     // ID of the VBO that stores all vertex position
    GLuint eboID;           // ID of the VBO that stores all vertex position
    GLuint texCoordID;      // ID of the VBO that stores all texture coordinates
    GLuint normalsID;       // ID of the VBO that stores all texture coordinates
    GLuint textureID;       // ID of the texture
    GLuint shaderID;        // ID of the shader program
    GLuint waterTextureID;  // ID of the water diffuse texture       
    GLuint displaceTextureID;   // ID of the height displacement texture
	std::vector<float> verts;   // List of all vertices in the plane mesh
	std::vector<float> normals; // List of all normals in the plane mesh
	std::vector<float> uvs;     // List of all UVs in the plane mesh
	std::vector<int> indices;   // List of all indices in the plane mesh

	float min;  // Minimum value of the plane coordinate
	float max;  // Maximum value of the plane coordinate
	int numVerts;   // Number of vertices in the mesh
	int numIndices; // Number of indices in the mesh

public:
    PlaneMesh(float min = -2.0f, float max = 2.0f, float stepsize = 0.2f);
    void setupTexture();
    void setupVBOs();
    void setupVAO();
    void setShaderID(GLuint programID);
    float remap(float input, float iLow, float iHigh, float gLow, float gHigh);
	void planeMeshQuads(float min, float max, float stepsize);
    void Draw();
    void Update();
    Camera* cam;
};

#endif