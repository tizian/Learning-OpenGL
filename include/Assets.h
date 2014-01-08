#pragma once

#include "ModelAsset.h"
#include "Shader.h"

namespace Assets {

	Shader phongShader;

	ModelAsset cube;
	ModelAsset sphere;
	ModelAsset bunny;
	ModelAsset suzanne;

	void init() {
		phongShader = Shader("Shaders/phong_vertex.glsl", "Shaders/phong_fragment.glsl");

		cube = ModelAsset(&phongShader, "Models/cube.dae");

		sphere= ModelAsset(&phongShader, "Models/sphere.dae");

		bunny = ModelAsset(&phongShader, "Models/bunny.dae");

		suzanne = ModelAsset(&phongShader, "Models/suzanne.dae");
	}

	void destroy() {
		phongShader.destroy();
		cube.destroy();
		sphere.destroy();
		bunny.destroy();
		suzanne.destroy();
	}
};