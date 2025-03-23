#pragma once

#include "Walnut/Image.h"

#include "Camera.h"
#include "Ray.h"

#include <memory>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Camera& camera);

	inline void SetSphereColor(glm::vec3 color) { m_SphereColor = color; }
	inline void SetLightDirection(glm::vec3 lightDirection) { m_LightDirection = lightDirection; }

	inline std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
	
private:
	glm::vec4 TraceRay(const Ray& ray);

private:
	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;

	glm::vec3 m_SphereColor{ 1.0f, 0.0f, 1.0f };
	glm::vec3 m_LightDirection{ -1.0f, -1.0f, -1.0f };
};
