
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include <iostream>
#include <fstream>
#include <string>

#include "Assets.h"
#include "Camera.h"
#include "Shader.h"
#include "ModelAsset.h"
#include "ModelInstance.h"
#include "Color.h"
#include "PointLight.h"
#include "Material.h"

using namespace std;

void glfwWindowResizeCallback(GLFWwindow *window, int width, int height);

void setupContext();
void destroyContext();

ModelInstance randomModelInstance();
float randomFloat(float a, float b);

static int width = 640;
static int height = 480;

float camSpeed = 8.0f;
float camRotSpeed = 100.0f;

GLFWwindow *window;
Camera camera;

Material testMaterial;

int main()
{
	setupContext();
	Assets::init();


	// DEPTH TESTING
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	// CULLING
	glEnable (GL_CULL_FACE); // cull face
	glCullFace (GL_BACK); // cull back face
	glFrontFace (GL_CCW); // GL_CCW for counter clock-wise

	Assets::shader.use();

	camera.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	camera.setAspectRatio((float)width/height);
	GLint cameraPosLoc = Assets::shader.getUniformLocation("cameraPosition");

	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(camera.getPosition()));

	GLint modelLoc = Assets::shader.getUniformLocation("model");
	GLint viewLoc = Assets::shader.getUniformLocation("view");
	GLint projLoc = Assets::shader.getUniformLocation("proj");

	glm::mat4 model = glm::mat4();
	glm::mat4 view = glm::mat4();
	glm::mat4 proj = glm::mat4();

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.projection()));

	PointLight testLight;
	testLight.setDiffuseColor(glm::vec3(0.7, 0.7, 0.7));
	testLight.setAmbientColor(glm::vec3(0.3, 0.3, 0.3));
	testLight.setAttenuationFactor(0.0005f);
	testLight.setUniforms(Assets::shader);
	
	testMaterial.setDiffuseFactor(glm::vec3(1, 0.5, 0));
	testMaterial.setShininess(50);
	testMaterial.setUniforms(Assets::shader);

	srand ((unsigned int) time(NULL));
	ModelInstance cubes[100];
	for (int i = 0; i < 100; i++) {
		cubes[i] = randomModelInstance();
	}

	bool lightFollowsCamera = false;

	while (!glfwWindowShouldClose(window)) {
		// Timer
		static double previous = glfwGetTime ();
		double current = glfwGetTime ();
		float deltaTime = (float) current - (float) previous;
		previous = current;


		// clear drawing surface
		//glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width, height);

		for (int i = 0; i < 100; i++) {
			cubes[i].render(Assets::shader);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, 1);
		}

		bool camMoved = false;
		glm::vec3 camOffset = glm::vec3(0,0,0);

		glm::vec3 forward = glm::vec3(0,0,1);
		glm::vec3 right = glm::vec3(1,0,0);
		glm::vec3 up = glm::vec3(0,1,0);

		float deltaTheta = camRotSpeed * deltaTime;

		if (glfwGetKey(window, GLFW_KEY_A)) {
			camera.moveLeftRight(camSpeed * deltaTime);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_D)) {
			camera.moveLeftRight(-camSpeed * deltaTime);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_SPACE)) {
			camera.moveUpDown(-camSpeed * deltaTime);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)) {
			camera.moveUpDown(camSpeed * deltaTime);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_W)) {
			camera.moveForwardBackward(camSpeed * deltaTime);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_S)) {
			camera.moveForwardBackward(-camSpeed * deltaTime);
			camMoved = true;
		}

		if (glfwGetKey(window, GLFW_KEY_UP)) {
			camera.pitch(-deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN)) {
			camera.pitch(deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT)) {
			camera.yaw(-deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
			camera.yaw(deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_Q)) {
			camera.roll(-deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_E)) {
			camera.roll(deltaTheta);
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_0)) {
			camera.setPosition(glm::vec3());
			camMoved = true;
		}
		if (glfwGetKey(window, GLFW_KEY_L)) {
			if (lightFollowsCamera) {
				lightFollowsCamera = false;
			}
			else {
				lightFollowsCamera = true;
			}
		}
		if (lightFollowsCamera) {
				testLight.setPosition(camera.getPosition());
				testLight.setUniforms(Assets::shader);
			}

		if (camMoved) {
			camera.move(camOffset);
			
			Assets::shader.use();
			glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera.view()));
			glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera.projection()));
			glUniform3fv(cameraPosLoc, 1, glm::value_ptr(camera.getPosition()));
			
		}
	}

	Assets::destroy();
	destroyContext();

	return 0;
}

void setupContext() {
	// start GL context
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 4);

	window = glfwCreateWindow(640, 480, "OpenGL Project", NULL, NULL);

	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	glfwSetWindowSizeCallback(window, glfwWindowResizeCallback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte *renderer = glGetString(GL_RENDERER);	// get renderer string
	const GLubyte *version = glGetString(GL_VERSION);	// get version string
	std::cout << "Renderer: " << renderer << std::endl;
	std::cout << "OpenGL version: " << version << std::endl;
}

void destroyContext() {
	// close GL context and any other GLFW resources

	glfwDestroyWindow(window);

	glfwTerminate();
}

void glfwWindowResizeCallback(GLFWwindow *window, int w, int h) {
		width = w;
		height = h;

		camera.setAspectRatio((float)width/height);
}

ModelInstance randomModelInstance() {
	float r[12];
	for (int i = 0; i < 6; i++) {
		r[i] = randomFloat(-20, 20);
	}
	for (int i = 6; i < 9; i++) {
		r[i] = randomFloat(0, 1);
	}
	for (int i = 9; i < 12; i++) {
		r[i] = randomFloat(0.3f, 3.0f);
	}

	glm::vec3 pos(r[0], r[1], r[2]);
	glm::fquat orient(1, r[3], r[4], r[5]);
	glm::vec4 col(r[6], r[7], r[8], 1);
	glm::vec3 scale(r[9], r[9], r[9]);

	ModelInstance m =  ModelInstance(pos, glm::normalize(orient), scale);
	m.setMaterial(testMaterial);
	return m;
}

float randomFloat(float a, float b) {
	float random = ((float) rand()) / (float) RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}