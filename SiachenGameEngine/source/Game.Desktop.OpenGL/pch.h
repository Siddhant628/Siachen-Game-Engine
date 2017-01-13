#pragma once

#include <windows.h>
#include <exception>
#include <cassert>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "GL/gl3w.h"
#include "GLFW/glfw3.h"

// TODO Check why glm libraries are producing warnings
//#include "glm/glm.hpp"
//#include "glm/gtx/simd_mat4.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/matrix_inverse.hpp"
//#include "glm/gtc/type_ptr.hpp"

// TODO Check if this file is obsolete
//#include "glm/core/func_trigonometric.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL