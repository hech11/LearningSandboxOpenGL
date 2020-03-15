
#include "pch.h"
#include "OrthographicCamera.h"

#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "GLFW/glfw3.h"

#include "Input.h"
#include <math.h>
namespace LSO {
	///////////////////////////// OrthographicCamera ///////////////////////////// 

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near /*= 0.0f*/, float far /*= 1.0f*/)
		: m_Position({ 0.0f, 0.0f, 0.0f }), m_RotAxis(1.0f),
		m_Scale({ 1.0f, 1.0f, 1.0f, }), m_Angle(0.0f), m_ViewMatrix(glm::mat4(1.0f)), 
		m_ProjectionMatrix(glm::ortho(left, right, bottom, top, near, far)), m_ProjViewMatrix(glm::mat4(1.0f))
	{
		m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}


	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float near /*= 0.0f*/, float far /*= 1.0f*/) {
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
		m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;

	}

	void OrthographicCamera::SetPosition(const glm::vec3& position) {
		m_Position = position;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::SetRotation(float angle, float zAxis) {
		m_RotAxis = zAxis;
		m_Angle = angle;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::SetScale(const glm::vec3& scale) {
		m_Scale = scale;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::Move(const glm::vec3& offset) {
		m_Position += offset;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::Rotate(float offset)
	{
		m_Angle += offset;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::Enlarge(const glm::vec3& offset)
	{
		m_Scale += offset;
		RecalculateProjViewMatrix();
	}

	void OrthographicCamera::RecalculateProjViewMatrix() {
		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::rotate(glm::mat4(1.0f), glm::radians(m_Angle), { 0.0f, 0.0f, m_RotAxis }) *
			glm::scale(glm::mat4(1.0f), m_Scale);

		m_ViewMatrix = glm::inverse(m_ViewMatrix);
		m_ProjViewMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}




	///////////////////////////// OrthographicCameraController ///////////////////////////// 
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool canRotate /*= false*/) 
		: m_AspectRatio(aspectRatio), m_ZoomLevel(1.0f), m_ZoomSpeed(1.0f),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel)
	{
		if (!canRotate)
			SetRotateSpeed(0.0f);

	}

	void OrthographicCameraController::SetMoveSpeed(float speed) {
		m_MoveSpeed = speed;
	}

	void OrthographicCameraController::SetRotateSpeed(float speed) {
		m_RotateSpeed = speed;
	}

	void OrthographicCameraController::SetZoomSpeed(float speed) {
		m_ZoomSpeed = speed;
	}

	void OrthographicCameraController::OnUpdate(const Timestep& ts) {
		if (Input::GetKey(GLFW_KEY_D)) {
			m_Camera.Move({ m_MoveSpeed * ts * -m_ZoomLevel, 0.0f, 0.0f });
		}
		else if (Input::GetKey(GLFW_KEY_A)) {
			m_Camera.Move({ -m_MoveSpeed * ts * -m_ZoomLevel, 0.0f, 0.0f });
		}
		if (Input::GetKey(GLFW_KEY_W)) {
			m_Camera.Move({ 0.0f, m_MoveSpeed * ts * -m_ZoomLevel, 0.0f });
		}
		else if (Input::GetKey(GLFW_KEY_S)) {
			m_Camera.Move({ 0.0f, -m_MoveSpeed * ts * -m_ZoomLevel, 0.0f });
		}


		if (Input::GetKey(GLFW_KEY_Q)) {
			m_Camera.Rotate(-m_RotateSpeed * ts);
		}
		else if (Input::GetKey(GLFW_KEY_E)) {
			m_Camera.Rotate(m_RotateSpeed*ts);
		}
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowRezize, this, std::placeholders::_1));

	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_ZoomLevel -= e.GetYScroll()*m_ZoomSpeed;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowRezize(WindowResizeEvent& e)
	{
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
		return false;
	}

}


