#ifndef GLOBALINCLUDES_HPP
#define GLOBALINCLUDES_HPP

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include "InputSystem.hpp"

// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>

static int nextGUID = 0;

#define DEBUG_LOG(x) std::cout << x << std::endl
#define DEBUG_INIT(x) std::cout << "[INIT]: " << x << std::endl
#define DEBUG_INFO(x) std::cout << "[INFO]: " << x << std::endl
#define DEBUG_ERROR(x) std::cout << "\t\t[ERROR]: " << x << std::endl

#endif