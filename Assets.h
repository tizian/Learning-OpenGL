#pragma once

#include "ModelAsset.h"
#include "Shader.h"

namespace Assets {

	Shader shader;

	ModelAsset cube;
	ModelAsset sphere;
	ModelAsset bunny;
	ModelAsset suzanne;

	void init() {
		shader = Shader("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");

		cube = ModelAsset(&shader, "Models/cube.dae");

		sphere= ModelAsset(&shader, "Models/sphere.dae");

		bunny = ModelAsset(&shader, "Models/bunny.dae");

		suzanne = ModelAsset(&shader, "Models/suzanne.dae");
	}

	void destroy() {
		shader.destroy();
		cube.destroy();
		sphere.destroy();
		bunny.destroy();
		suzanne.destroy();
	}
};