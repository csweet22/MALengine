// Cole Sweet | 251179642
// CS3388b
// April 2023
// Assignment 6

#ifndef PLANEMESH_HPP
#define PLANEMESH_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>
#include "shader.hpp"

void loadARGB_BMP(const char *imagepath, unsigned char **data, unsigned int *width, unsigned int *height)
{

    printf("Reading image %s\n", imagepath);

    // Data read from the header of the BMP file
    unsigned char header[54];
    unsigned int dataPos;
    unsigned int imageSize;
    // Actual RGBA data

    // Open the file
    FILE *file = fopen(imagepath, "rb");
    if (!file)
    {
        printf("%s could not be opened. Are you in the right directory?\n", imagepath);
        getchar();
        return;
    }

    // Read the header, i.e. the 54 first bytes

    // If less than 54 bytes are read, problem
    if (fread(header, 1, 54, file) != 54)
    {
        printf("Not a correct BMP file1\n");
        fclose(file);
        return;
    }

    // Read the information about the image
    dataPos = *(int *)&(header[0x0A]);
    imageSize = *(int *)&(header[0x22]);
    *width = *(int *)&(header[0x12]);
    *height = *(int *)&(header[0x16]);
    // A BMP files always begins with "BM"
    if (header[0] != 'B' || header[1] != 'M')
    {
        printf("Not a correct BMP file2\n");
        fclose(file);
        return;
    }
    // Make sure this is a 32bpp file
    // if (*(int *)&(header[0x1E]) != 3)
    // {
    //     printf("Not a correct BMP file3\n");
    //     fclose(file);
    //     return;
    // }
    // fprintf(stderr, "header[0x1c]: %d\n", *(int*)&(header[0x1c]));
    // if ( *(int*)&(header[0x1C])!=32 ) {
    //     printf("Not a correct BMP file4\n");
    //     fclose(file);
    //     return;
    // }

    // Some BMP files are misformatted, guess missing information
    if (imageSize == 0)
        imageSize = (*width) * (*height) * 4; // 4 : one byte for each Red, Green, Blue, Alpha component
    if (dataPos == 0)
        dataPos = 54; // The BMP header is done that way

    // Create a buffer
    *data = new unsigned char[imageSize];

    if (dataPos != 54)
    {
        fread(header, 1, dataPos - 54, file);
    }

    // Read the actual data from the file into the buffer
    fread(*data, 1, imageSize, file);

    // Everything is in memory now, the file can be closed.
    fclose(file);
}


// Class that creates Texture Objects, VBOs, VAO, for a single ply and single bmp file.
// This also provides a draw() method for the main draw-loop to call.
class PlaneMesh
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
    // Sets up the serverside texture object
    void setupTexture(){
        unsigned char *DiffuseData; // Texture data in unsigned bytes
        unsigned int DiffuseWidth;  // Width of the texture
        unsigned int DiffuseHeight; // Height of the texture

        // Load the data and dimensions from file.
        loadARGB_BMP("Assets/water.bmp", &DiffuseData, &DiffuseWidth, &DiffuseHeight);

        glGenTextures(1, &waterTextureID);            // Generate 1 serverside texture object
        glBindTexture(GL_TEXTURE_2D, waterTextureID); // Bind the texture obj to GL_TEXTURE_2D
        // Store data from client data to server buffer:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DiffuseWidth, DiffuseHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, DiffuseData);

        glGenerateMipmap(GL_TEXTURE_2D); // Generate the mipmaps for the texture
        
        glBindTexture(GL_TEXTURE_2D, 0); // Bind the texture obj to GL_TEXTURE_2D
        
        unsigned char *DisplaceData; // Texture data in unsigned bytes
        unsigned int DisplaceWidth;  // Width of the texture
        unsigned int DisplaceHeight; // Height of the texture

        // Load the data and dimensions from file.
        loadARGB_BMP("Assets/displacement-map1.bmp", &DisplaceData, &DisplaceWidth, &DisplaceHeight);

        glGenTextures(1, &displaceTextureID);            // Generate 1 serverside texture object
        glBindTexture(GL_TEXTURE_2D, displaceTextureID); // Bind the texture obj to GL_TEXTURE_2D
        // Store data from client data to server buffer:
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DisplaceWidth, DisplaceHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, DisplaceData);

        glGenerateMipmap(GL_TEXTURE_2D); // Generate the mipmaps for the texture

        
        glBindTexture(GL_TEXTURE_2D, 0); // Bind the texture obj to GL_TEXTURE_2D
    }

    // This sets up the serverside position, normal, uv, and index buffers.
    void setupVBOs(){
        // ===================================================
        // PARSING THEN STORING VERTEX POSITIONS IN A 1D ARRAY
        // ===================================================
        GLfloat vertex_buffer_data[verts.size()];
        // [x1, y1, z1, x2, y2, z2, ...]

        for (int i = 0; i < verts.size(); i++)
        {
            vertex_buffer_data[i] = verts.at(i);
        }

        // =================================================
        // PARSING THEN STORING UV COORDINATES IN A 1D ARRAY
        // =================================================
        GLfloat uv_buffer_data[uvs.size()];
        // [u1, v1, u2, v2, ...]

        for (int i = 0; i < uvs.size(); i++)
        {
            uv_buffer_data[i] = uvs.at(i);
        }


        // ===================================================
        // PARSING THEN STORING VERTEX POSITIONS IN A 1D ARRAY
        // ===================================================
        GLfloat normals_buffer_data[normals.size()];
        // [x1, y1, z1, x2, y2, z2, ...]

        for (int i = 0; i < normals.size(); i++)
        {
            normals_buffer_data[i] = normals.at(i);
        }

        // ===================================================
        // PARSING THEN STORING TRIANGLE INDICES IN A 1D ARRAY
        // ===================================================
        GLuint index_buffer_data[indices.size()];
        // t => tri; v => vertex
        // [t1v1, t1v2, t1v3, t2v1, t2v2, t2v3, ...]

        for (int i = 0; i < indices.size(); i++)
        {
            index_buffer_data[i] = indices.at(i);
        }

        // ============================
        // CREATING VERTEX POSITION VBO
        // ============================
        glGenBuffers(1, &positionsID);              // Generate 1 serverside buffer object
        glBindBuffer(GL_ARRAY_BUFFER, positionsID); // Bind the object to GL_ARRAY_BUFFER
        // Store data from client data to server buffer:
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the current GL_ARRAY_BUFFER buffer

        // =====================
        // CREATING UV COORD VBO
        // =====================
        glGenBuffers(1, &texCoordID);              // Generate 1 serverside buffer object
        glBindBuffer(GL_ARRAY_BUFFER, texCoordID); // Bind the object to GL_ARRAY_BUFFER
        // Store data from client data to server buffer:
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the current GL_ARRAY_BUFFER buffer

        
        // ====================
        // CREATING NORMALS VBO
        // ====================
        glGenBuffers(1, &normalsID);              // Generate 1 serverside buffer object
        glBindBuffer(GL_ARRAY_BUFFER, normalsID); // Bind the object to GL_ARRAY_BUFFER
        // Store data from client data to server buffer:
        glBufferData(GL_ARRAY_BUFFER, sizeof(normals_buffer_data), normals_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the current GL_ARRAY_BUFFER buffer


        // ============
        // CREATING EBO
        // ============
        glGenBuffers(1, &eboID);                      // Generate 1 serverside buffer object
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID); // Bind the object to GL_ELEMENT_ARRAY_BUFFER
        // Store data from client data to server buffer:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // // Unbind the current GL_ELEMENT_ARRAY_BUFFER buffer
    }

    // Sets up the serverside VAO using the generated VBOs.
    // Must be called after setupVBO or else there will be no data in the VBOs.
    // (and no IDs will have been generated.)
    void setupVAO(){
        glGenVertexArrays(1, &vaoID); // Create 1 serverside VAO object
        glBindVertexArray(vaoID);     // Bind the current VAO object

        // Bind the EBO data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

        // Bind the position data VBO
        glBindBuffer(GL_ARRAY_BUFFER, positionsID);
        glEnableVertexAttribArray(0); // activate vertex position attribute position
        // Store the data stored in the currently bound VBO
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (GLvoid *)0);
        // You could unbind here for safety but is isn't necessary.


        // Bind the normal data VBO
        glBindBuffer(GL_ARRAY_BUFFER, normalsID);
        glEnableVertexAttribArray(1);
        // Store the data stored in the currently bound VBO
        glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, (GLvoid *)0);


        // Bind the uv data VBO
        glBindBuffer(GL_ARRAY_BUFFER, texCoordID);
        glEnableVertexAttribArray(2); // activate texture coords attribute position
        // Store the data stored in the currently bound VBO
        glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, (GLvoid *)0); // uv texture coordinates

        

        glBindVertexArray(0);             // Unbind the current VAO
        glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the current GL_ARRAY_BUFFER
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the current GL_ARRAY_BUFFER
    }

    // Sets the shader ID for the TexturedMesh.
    void setShaderID(GLuint programID){
        this->shaderID = programID;
    }

    // Basic float remap method. Used for getting UVs
        // Given a value in range [iLow, iHigh], remap to  [gLow, gHigh]
        // i => initial min and max
        // g => goal min and max
    float remap(float input, float iLow, float iHigh, float gLow, float gHigh){
        return gLow + (input-iLow)*(gHigh-gLow)/(iHigh-iLow);
    }

    // Plane vertices, uv, normal, and index creation method.
        // Credit to Alex Brandt.
        // Modified by Cole Sweet.
	void planeMeshQuads(float min, float max, float stepsize) {

		// The following coordinate system works as if (min, 0, min) is the origin
		// And then builds up the mesh from that origin down (in z)
		// and then to the right (in x).
		// So, one "row" of the mesh's vertices have a fixed x and increasing z

        // X axis is U
        // Z axis is V

		//manually create a first column of vertices
		float x = min;
		float y = 0;
		for (float z = min; z <= max; z += stepsize) {
			verts.push_back(x);
			verts.push_back(y);
			verts.push_back(z);
			normals.push_back(0);
			normals.push_back(1);
			normals.push_back(0);
            uvs.push_back(remap(x, min, max, 0, 1.0));
            uvs.push_back(remap(z, min, max, 0, 1.0));
		}

		for (float x = min+stepsize; x <= max; x += stepsize) {
			for (float z = min; z <= max; z += stepsize) {
				verts.push_back(x);
				verts.push_back(y);
				verts.push_back(z);
				normals.push_back(0);   // Default normals point up (Y) for a plane
				normals.push_back(1);
				normals.push_back(0);
                // Remap min to UVs based on vertex position.
				uvs.push_back(remap(x, min, max, 0, 1.0));
				uvs.push_back(remap(z, min, max, 0, 1.0));
			}
		}

		int nCols = (max-min)/stepsize + 1;
		int i = 0, j = 0;
		for (float x = min; x < max; x += stepsize) {
			j = 0;
			for (float z = min; z < max; z += stepsize) {
				indices.push_back(i*nCols + j);
				indices.push_back(i*nCols + j + 1);
				indices.push_back((i+1)*nCols + j + 1);
				indices.push_back((i+1)*nCols + j);
				++j;
			}
			++i;
		}
	}

    // Constructor
    // Sets up the Textures, VBOs, and VAO
    PlaneMesh(float min, float max, float stepsize)
    {
        GLuint shader = LoadShaders("../shaders/default.fs", "../shaders/default.vs");

        setShaderID(shader);

		this->min = min;
		this->max = max;

		planeMeshQuads(min, max, stepsize);
		numVerts = verts.size()/3;
		numIndices = indices.size();

        setupTexture();
        setupVBOs();
        setupVAO();
    }

    // Draws the Planemesh
    void draw(glm::mat4 MVP, glm::mat4 V, glm::mat4 M)
    {   
        // Get all shader uniforms
        // GLuint waterTextureLocationID = glGetUniformLocation(shaderID, "waterTexture");
        GLuint MVPID = glGetUniformLocation(shaderID, "MVP");

        // Use shader
        glUseProgram(shaderID);

        // Enable 2D textures
        glEnable(GL_TEXTURE_2D);
        
        // Access the water diffuse texture
		glActiveTexture(GL_TEXTURE0); // Texture unit 0
		glBindTexture(GL_TEXTURE_2D, waterTextureID);

        // Access the water height displacement texture
		glActiveTexture(GL_TEXTURE1); // Texture unit 1
		glBindTexture(GL_TEXTURE_2D, displaceTextureID);

        // Pass all the uniforms into the shader.
        glUniformMatrix4fv(MVPID, 1, GL_FALSE, &MVP[0][0]);
		// glUniform1i(waterTextureLocationID, 0);
		// glUniform3f(LightDirID, 4, 3.0, -10.0);


        // Bind the VAO to draw.
        glBindVertexArray(vaoID);
        // Draw the plane.
		glDrawElements(GL_PATCHES, numIndices, GL_UNSIGNED_INT, (void*)0);
        
        // Unbind the VAO
        glBindVertexArray(0);
        glDisableVertexAttribArray(0); // Deactivate vertex position
        glDisableVertexAttribArray(1); // Deactivate texture coords
        glDisableVertexAttribArray(2); // Deactivate normals

        glUseProgram(0);                 // Deactivate the current shader program
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the current texture.

    }
};

#endif