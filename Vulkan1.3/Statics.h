#pragma once

#ifndef _STATICS_H
#define _STATICS_H

// GLFW
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

// GLM
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// I/O Stream
#include <iostream>
#include <fstream>

// Misc
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>
#include <array>
#include <map>

// Local
#include "Utility.h"

using KEYMAP = std::map<int, bool>;

class Statics
{
public:
	static void UpdateDeltaTime();

	static class Window* MainWindow;
	static class SceneManager* SceneManager;
	static class MeshManager* MeshManager;
	static class CameraComponent* ActiveCamera;
	static KEYMAP Keymap;
	static float DeltaTime;

private:
	static double LastTime;
};
#endif
