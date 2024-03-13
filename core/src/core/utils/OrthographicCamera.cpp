#include "corepch.h"

#include "core/utils/OrthographicCamera.h"

core::utils::OrthographicCamera::OrthographicCamera(int controlMouseBtn)
	: m_controlMouseButton(controlMouseBtn)
{
}

void core::utils::OrthographicCamera::OnEvent(event::Event& event)
{
	event::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<event::MouseButtonPressedEvent>(
		[this](const event::MouseButtonPressedEvent& e) {
			if (e.GetMouseButton() == m_controlMouseButton)
				m_controlMouseButtonPressed = true;
			return false;
		});

	dispatcher.Dispatch<event::MouseButtonReleasedEvent>(
		[this](const event::MouseButtonReleasedEvent& e) {
			if (e.GetMouseButton() == m_controlMouseButton)
				m_controlMouseButtonPressed = false;
			return false;
		});

	dispatcher.Dispatch<event::MouseMovedEvent>(
		std::bind(&OrthographicCamera::OnMouseMoved, this, std::placeholders::_1));

	dispatcher.Dispatch<event::MouseScrolledEvent>(
		std::bind(&OrthographicCamera::OnMouseScrolled, this, std::placeholders::_1));
}

sigslot::connection core::utils::OrthographicCamera::SubscribeOnViewMatrixChange(const std::function<void(const glm::mat4&)>& slot)
{
	return m_viewMatrixSignal.connect(slot);
}

void core::utils::OrthographicCamera::TransformScreenCoords(float& x, float& y) const
{
	(x -= m_position.x) /= m_zoomLevel;
	(y -= m_position.y) /= m_zoomLevel;
}

bool core::utils::OrthographicCamera::OnMouseMoved(const event::MouseMovedEvent& e)
{
	glm::vec2 cursorPos(e.GetX(), e.GetY());

	if (m_controlMouseButtonPressed)
	{
		m_position += (cursorPos - m_lastCursorPos) * (m_zoomLevel * 2);
		m_viewMatrixSignal(GetViewMatrix());
	}

	m_lastCursorPos = cursorPos;

	return false;
}

bool core::utils::OrthographicCamera::OnMouseScrolled(const event::MouseScrolledEvent& e)
{
	m_zoomLevel += e.GetYOffset() * 0.02f;
	m_zoomLevel = std::max(0.05f, m_zoomLevel);
	m_viewMatrixSignal(GetViewMatrix());

	return false;
}

glm::mat4 core::utils::OrthographicCamera::GetViewMatrix()
{
	auto mat = glm::translate(glm::mat4(1.0f), glm::vec3(m_position, 0.0f));
	mat = glm::scale(mat, glm::vec3(m_zoomLevel, m_zoomLevel, 1.0f));
	return mat;
}
