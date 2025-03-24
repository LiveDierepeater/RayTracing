#pragma once

#include "Walnut/Image.h"

#include "Scene.h"
#include "Camera.h"
#include "Ray.h"

#include <memory>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t width, uint32_t height);
	void Render(const Scene& scene, const Camera& camera);

	inline void SetSphereColor(glm::vec3 color) { m_SphereColor = color; }
	inline void SetLightDirection(glm::vec3 lightDirection) { m_LightDirection = lightDirection; }

	inline std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
	
private:
	struct HitPayload
	{
		float HitDistance;
		glm::vec3 WorldPosition;
		glm::vec3 WorldNormal;

		int ObjectIndex;
	};

	glm::vec4 PerPixel(uint32_t x, uint32_t y); // RayGen

	HitPayload TraceRay(const Ray& ray);
	HitPayload ClosestHit(const Ray& ray, float hitDistance, int objectIndex);
	HitPayload Miss(const Ray& ray);

private:
	std::shared_ptr<Walnut::Image> m_FinalImage;

	const Scene* m_ActiveScene = nullptr;
	const Camera* m_ActiveCamera = nullptr;

	uint32_t* m_ImageData = nullptr;

	glm::vec3 m_SphereColor{ 1.0f, 0.0f, 1.0f };
	glm::vec3 m_LightDirection{ -1.0f, -1.0f, -1.0f };
};
