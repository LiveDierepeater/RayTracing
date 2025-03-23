#include "Renderer.h"

#include "Walnut/Random.h"

namespace Utils {
	static uint32_t ConvertToRGBA(const glm::vec4& color)
	{
		uint8_t r = (uint8_t)(color.r * 255.0f);
		uint8_t g = (uint8_t)(color.g * 255.0f);
		uint8_t b = (uint8_t)(color.b * 255.0f);
		uint8_t a = (uint8_t)(color.a * 255.0f);

		uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
		return result;
	}
}

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		// No resize necessary
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render(const Camera& camera)
{
	const glm::vec3& rayOrigin = camera.GetPosition();

	Ray ray;
	ray.Origin = camera.GetPosition();

	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			ray.Direction = camera.GetRayDirections()[x + y * m_FinalImage->GetWidth()];
			glm::vec4 color = TraceRay(ray);
			color = glm::clamp(color, glm::vec4(0.0f), glm::vec4(1.0f));
			m_ImageData[x + y * m_FinalImage->GetWidth()] = Utils::ConvertToRGBA(color);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

glm::vec4 Renderer::TraceRay(const Ray& ray)
{
	float radius = 0.5f;
	//rayDirection = glm::normalize(rayDirection);

	// (bx^2 + by^2 + bz^2)t^2 + (2(axbx + ayby + azbz))t + (ax^2 + ay^2 + az^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance

	float a = glm::dot(ray.Direction, ray.Direction);
	float b = 2.0f * glm::dot(ray.Origin, ray.Direction);
	float c = glm::dot(ray.Origin, ray.Origin) - radius * radius;

	// Quadratic formula discriminant:
	// b^2 - 4ac

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return glm::vec4(0, 0, 0, 1);
	
	// (-b +- sqrt(discriminant)) / 2a
	float t0 = (-b + glm::sqrt(discriminant)) / (2.0f * a);
	float closestT = (-b - glm::sqrt(discriminant)) / (2.0f * a);

	glm::vec3 hitPoint = ray.Origin + ray.Direction * closestT;
	glm::vec3 hitNormal = glm::normalize(hitPoint);

	glm::vec3 lightDir = glm::normalize(m_LightDirection);

	auto lightIntensity = glm::max(glm::dot(hitNormal , -lightDir), 0.0f);

	auto sphereColor = m_SphereColor;
	//sphereColor = hitNormal * 0.5f + 0.5f;
	sphereColor *= lightIntensity;
	return glm::vec4(sphereColor, 1.0f);
}

// calculate hit distances/point
// calculate normal of hit point
// apply some shading to the sphere
// implement aspect ratio
// be able to move sphere


// ===== S E L F    M A D E    C O D E  ===== //
// =====          22.03.2025            ===== //
/*float t = -b - std::sqrt(discriminant);

if (t > 0)
{
	t = t / (2.0f * a);
	glm::vec3 hitPoint = rayOrigin + rayDirection * t;
	glm::vec3 hitNormal = glm::normalize(hitPoint - sphereOrigin);

	auto lightIntensity = glm::dot(-rayDirection, hitNormal);
	lightIntensity = glm::clamp(lightIntensity, 0.0f, 1.0f);

	auto brightness = (uint8_t)(255.0f * lightIntensity);
	//return 0xff000000 | (brightness << 16) | (brightness << 8) | brightness;
	return glm::vec4(lightIntensity, lightIntensity, lightIntensity, 1);
}

return glm::vec4(1, 0, 1, 1);*/