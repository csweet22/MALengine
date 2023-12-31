#include "SphereMesh.hpp"

void loadARGB_BMP2(const char *imagepath, unsigned char **data, unsigned int *width, unsigned int *height)
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

GLuint LoadShaders2(const char * vertex_file_path,const char * fragment_file_path){

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }


    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    
glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

SphereMesh::SphereMesh(float min, float max, float stepsize)
{
    GLuint shader = LoadShaders2("./shaders/default.vs", "./shaders/default.fs");

    setShaderID(shader);

    this->min = min;
    this->max = max;

    GenerateMesh(min, max, stepsize);
    numVerts = verts.size()/3;
    numIndices = indices.size();

    setupTexture();
    setupVBOs();
    setupVAO();
    DEBUG_INFO("Created Camera");
}

void SphereMesh::Draw()
{   
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    // glColor3f(1.0, 1.0, 0.0);
    // glPointSize(2.0f);
    // glBegin(GL_POINTS);
    // for (int i = 0; i < verts.size(); i += 3)
    // {
    //     std::string msg = std::to_string(verts.at(i)) + " " + std::to_string(verts.at(i+1)) + " " + std::to_string(verts.at(i+2));
    //     glVertex3f(verts.at(i), verts.at(i+1), verts.at(i+2));
    //     // DEBUG_INFO(msg);
    // }
    // glEnd();

    glUseProgram(shaderID);
    
    GLuint MVPID = glGetUniformLocation(shaderID, "MVP");
    glUniformMatrix4fv(MVPID, 1, GL_FALSE, &(cam->GetMVP())[0][0]);
    
    GLuint timeID = glGetUniformLocation(shaderID, "time");
    glUniform1f(timeID, Time::getInstance().GetTime());

    glBindVertexArray(vaoID);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (void*)0);
    
    glBindVertexArray(0);
    glDisableVertexAttribArray(0); // Deactivate vertex position
    glDisableVertexAttribArray(1); // Deactivate vertex position
    glUseProgram(0);                 // Deactivate the current shader program

}

void SphereMesh::Update(){
    if (!CheckEnabled()) {return;}

    this->Draw();
}

void SphereMesh::setupTexture(){
    // unsigned char *DiffuseData; // Texture data in unsigned bytes
    // unsigned int DiffuseWidth;  // Width of the texture
    // unsigned int DiffuseHeight; // Height of the texture

    // // Load the data and dimensions from file.
    // loadARGB_BMP2("Assets/water.bmp", &DiffuseData, &DiffuseWidth, &DiffuseHeight);

    // glGenTextures(1, &waterTextureID);            // Generate 1 serverside texture object
    // glBindTexture(GL_TEXTURE_2D, waterTextureID); // Bind the texture obj to GL_TEXTURE_2D
    // // Store data from client data to server buffer:
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DiffuseWidth, DiffuseHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, DiffuseData);

    // glGenerateMipmap(GL_TEXTURE_2D); // Generate the mipmaps for the texture
    
    // glBindTexture(GL_TEXTURE_2D, 0); // Bind the texture obj to GL_TEXTURE_2D
    
    // unsigned char *DisplaceData; // Texture data in unsigned bytes
    // unsigned int DisplaceWidth;  // Width of the texture
    // unsigned int DisplaceHeight; // Height of the texture

    // // Load the data and dimensions from file.
    // loadARGB_BMP2("Assets/displacement-map1.bmp", &DisplaceData, &DisplaceWidth, &DisplaceHeight);

    // glGenTextures(1, &displaceTextureID);            // Generate 1 serverside texture object
    // glBindTexture(GL_TEXTURE_2D, displaceTextureID); // Bind the texture obj to GL_TEXTURE_2D
    // // Store data from client data to server buffer:
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, DisplaceWidth, DisplaceHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, DisplaceData);

    // glGenerateMipmap(GL_TEXTURE_2D); // Generate the mipmaps for the texture

    
    // glBindTexture(GL_TEXTURE_2D, 0); // Bind the texture obj to GL_TEXTURE_2D
}

void SphereMesh::setupVBOs(){
    GLfloat vertex_buffer_data[verts.size()];
    for (int i = 0; i < verts.size(); i++)
    {
        vertex_buffer_data[i] = verts.at(i);
    }

    
    GLfloat uv_buffer_data[uvs.size()];
    for (int i = 0; i < uvs.size(); i++)
    {
        uv_buffer_data[i] = uvs.at(i);
    }

    GLuint index_buffer_data[indices.size()];
    for (int i = 0; i < indices.size(); i++)
    {
        index_buffer_data[i] = indices.at(i);
    }

    glGenBuffers(1, &positionsID);             
    glBindBuffer(GL_ARRAY_BUFFER, positionsID); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer_data), vertex_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &texCoordID);             
    glBindBuffer(GL_ARRAY_BUFFER, texCoordID); 
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv_buffer_data), uv_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &eboID);                   
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID); 
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_buffer_data), index_buffer_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void SphereMesh::setupVAO(){
    glGenVertexArrays(1, &vaoID); 
    glBindVertexArray(vaoID);     

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

    glBindBuffer(GL_ARRAY_BUFFER, positionsID);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, (GLvoid *)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, texCoordID);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, false, 0, (GLvoid *)0);

    glBindVertexArray(0);            
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
}

void SphereMesh::setShaderID(GLuint programID){
    this->shaderID = programID;
}

float SphereMesh::remap(float input, float iLow, float iHigh, float gLow, float gHigh){
    return gLow + (input-iLow)*(gHigh-gLow)/(iHigh-iLow);
}

void SphereMesh::GenerateMesh(int radius, int latitudes, int longitudes) {

    if(longitudes < 3)
        longitudes = 3;
    if(latitudes < 2)
        latitudes = 2;

    float nx, ny, nz, lengthInv = 1.0f / radius;    
    
    struct Vertex
    {
        float x, y, z, s, t; // Postion and Texcoords
    };

    float deltaLatitude = M_PI / latitudes;
    float deltaLongitude = 2 * M_PI / longitudes;
    float latitudeAngle;
    float longitudeAngle;

    for (int i = 0; i <= latitudes; ++i)
    {
        latitudeAngle = M_PI / 2 - i * deltaLatitude; 
        float xy = radius * cosf(latitudeAngle);      
        float z = radius * sinf(latitudeAngle);       
        
        for (int j = 0; j <= longitudes; ++j)
        {
            longitudeAngle = j * deltaLongitude;

            Vertex vertex;
            vertex.x = xy * cosf(longitudeAngle);      
            vertex.y = xy * sinf(longitudeAngle);      
            vertex.z = z;                              
            vertex.s = (float)j/longitudes;            
            vertex.t = (float)i/latitudes;             
            verts.emplace_back(vertex.x);
            verts.emplace_back(vertex.y);
            verts.emplace_back(vertex.z);
            uvs.emplace_back(vertex.s);
            uvs.emplace_back(vertex.t);
        }
    }

    unsigned int k1, k2;
    for(int i = 0; i < latitudes; ++i){
        k1 = i * (longitudes + 1);
        k2 = k1 + longitudes + 1;
        // 2 Triangles per latitude block excluding the first and last longitudes blocks
        for(int j = 0; j < longitudes; ++j, ++k1, ++k2){
            if (i != 0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (latitudes - 1)){
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }

}

