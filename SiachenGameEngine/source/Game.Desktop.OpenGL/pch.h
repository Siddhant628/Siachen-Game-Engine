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

#define GLM_FORCE_CXX11
#include "glm/glm.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL