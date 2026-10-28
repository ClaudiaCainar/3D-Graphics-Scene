#include "Camera.hpp"

namespace gps {

    //Camera constructor
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget, glm::vec3 cameraUp) {
        //TODO
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraUpDirection = cameraUp;
        
    }

    //return the view matrix, using the glm::lookAt() function
    glm::mat4 Camera::getViewMatrix() {
        //TODO

        return glm::lookAt(cameraPosition, cameraTarget, this->cameraUpDirection);
    }

    //update the camera internal parameters following a camera move event
    void Camera::move(MOVE_DIRECTION direction, float speed) {
        //TODO
        glm::vec3 cameraFront = glm::normalize(cameraTarget - cameraPosition);
        glm::vec3 cameraRight = glm::normalize(glm::cross(cameraUpDirection, cameraFront));

        switch (direction) {
        case MOVE_FORWARD:
            cameraPosition += cameraFront * speed;
            cameraTarget += cameraFront * speed;
            break;
        case MOVE_BACKWARD:
            cameraPosition -= cameraFront * speed;
            cameraTarget -= cameraFront * speed;
            break;
        case MOVE_LEFT:
            cameraPosition += cameraRight * speed;
            cameraTarget += cameraRight * speed;
            break;
        case MOVE_RIGHT:
            cameraPosition -= cameraRight * speed;
            cameraTarget -= cameraRight * speed;
            break;
            // Add more cases if needed for other directions
        }
    }

    //update the camera internal parameters following a camera rotate event
    //yaw - camera rotation around the y axis
    //pitch - camera rotation around the x axis
    void Camera::rotate(float pitch, float yaw) {
        //TODO
        glm::mat4 rotationMatrix = glm::mat4(1.0f);

        // Apply yaw (rotation around the y-axis)
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));

        // Apply pitch (rotation around the x-axis)
        rotationMatrix = glm::rotate(rotationMatrix, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));

        // Update the camera's target position
        glm::vec4 updatedTarget = rotationMatrix * glm::vec4(cameraTarget - cameraPosition, 1.0f);
        cameraTarget = cameraPosition + glm::vec3(updatedTarget);
    }
}
