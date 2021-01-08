#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <iostream>
#include "Shader.h"
#include "../../../../Camera.h"
#include "../../panda-engine-windows/Lotos/stb_image.h"

class Skybox
{
private:
	unsigned int textureID;
	std::vector<std::string> skies;
	std::vector<float>skyVerticies;
	unsigned int VAO, VBO;
public:
	Skybox(std::vector<std::string> path);
	Skybox(std::vector<std::string> path, float size);
	bool loadCube();
	void buildSkybox();
	void renderSkybox();
	unsigned int getTextureID();
	float* getVerticies();
	~Skybox();
};