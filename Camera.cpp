#include"Camera.h"

static float horizontalAngle = 3.14f;
static float verticalAngle = 0.0f;
void Camera::update() {
	// deltaTime
	static double lastTime = glfwGetTime();
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	lastTime = currentTime;
	switch (ctr) {
	case CAM_CONTROL_TYPE::FIRST_PERSON: {
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		glfwSetCursorPos(window, WINDOW_WIDTH / 2, WINDOW_HEIGHT/ 2);

		// Compute new orientation
		horizontalAngle += rotate_speed * float(WINDOW_WIDTH / 2 - xpos);
		verticalAngle += rotate_speed * float(WINDOW_HEIGHT / 2 - ypos);

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
		);

		// Up vector
		glm::vec3 up = glm::cross(right, direction);

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			posi += direction * deltaTime * move_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			posi -= direction * deltaTime * move_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			posi += right * deltaTime * move_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			posi -= right * deltaTime * move_speed;
		}

		P = glm::perspective(glm::radians(FOV), aspect, near, far);
		V = glm::lookAt(
			posi,           
			posi + direction, 
			up               
			);
		break;
		}
	}
}

