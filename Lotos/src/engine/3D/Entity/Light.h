#include "glm.hpp"
#include "Shader.h"
#include "sstream"

class Light 
{
protected:
	float intensity;
	glm::vec3 color;
public:
	Light(float intensity, glm::vec3 color)
	{
		this->intensity = intensity;
		this->color = color;
	}

	virtual void sendToShader(Shader& program) = 0;

	~Light() 
	{

	}
};

class PointLight : public Light
{
protected:
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;
public:
	PointLight(glm::vec3 position, float intensity = 1.f, glm::vec3 color = glm::vec3(1.f), 
		float constant = 1.f, float linear = 0.045f, float quadratic = 0.0075f) : Light(intensity, color)
	{
		this->position = position;
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}

	void setPosition(const glm::vec3 position)
	{
		this->position = position;
	}

	void sendToShader(Shader& program)
	{
		program.setVec3("pointlight.position", this->position);
		program.setFloat("pointlight.intensity", this->intensity);
		program.setVec3("pointlight.color", this->color);
		program.setFloat("pointlight.constant", this->constant);
		program.setFloat("pointlight.linear", this->linear);
		program.setFloat("pointlight.quadratic", this->quadratic);
	} 

	~PointLight()
	{

	}
};
