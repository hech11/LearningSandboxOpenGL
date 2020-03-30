#pragma once



#include "pch.h"
#include "glm/glm.hpp"

#include "Event.h"
#include "Timestep.h"

namespace LSO {


	struct OrthographicCameraBounds {
		float Left, Right;
		float Bottom, Top;

		float GetWidth() { return Right - Left; }
		float GetHeight() { return Top - Bottom; }
	};

	class OrthographicCamera {
		public :
			OrthographicCamera(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);


			void SetProjection(float left, float right, float bottom, float top, float near = -1.0f, float far = 1.0f);

			void SetPosition(const glm::vec3& position);
			void SetRotation(float angle, float zAxis);
			void SetScale(const glm::vec3& scale);

			void Move(const glm::vec3& offset);
			// This only offsets the angle and not the zAxis, this could change in the future!
			void Rotate(float offset);
			void Enlarge(const glm::vec3& offset);



			const glm::vec3& GetPosition() const { return m_Position; }

			void RecalculateProjViewMatrix();

			inline const glm::mat4& GetProjView() const { return m_ProjViewMatrix; }


		private :
			float m_Angle, m_RotAxis;
			glm::vec3 m_Position, m_Scale;
			glm::mat4 m_ViewMatrix, m_ProjectionMatrix, m_ProjViewMatrix;
	};



	class OrthographicCameraController {

		public :
			OrthographicCameraController(float aspectRatio, bool canRotate = false);

			void SetMoveSpeed(float speed);
			// If the camera is set to not be able to rotate, this will enable rotation.
			void SetRotateSpeed(float speed);
			void SetZoomSpeed(float speed);

			void OnUpdate(const Timestep& ts);
			void OnEvent(Event& e);

			bool OnMouseScrolled(MouseScrolledEvent& e);
			bool OnWindowRezize(WindowResizeEvent& e);

			OrthographicCamera& GetCamera() { return m_Camera; }
			const OrthographicCameraBounds& GetBounds() const { return m_Bounds; }

		private :

			float m_ZoomLevel;
			float m_AspectRatio;

			float m_MoveSpeed = 1.0f, m_RotateSpeed = 100.0f, m_ZoomSpeed = 1.0f;
			glm::vec3 m_CameraPos;

			OrthographicCamera m_Camera;
			OrthographicCameraBounds m_Bounds;
	};

}