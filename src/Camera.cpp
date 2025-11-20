#include <Camera.h>

Camera::Camera(float x)
    : x(x) {}

void Camera::setX(float newX) {
    if (newX < -LOGICAL_WIDTH) newX = -LOGICAL_WIDTH;
    if (newX > LOGICAL_WIDTH * 2) newX = LOGICAL_WIDTH * 2;
    x = newX;
}

void Camera::moveX(float dx) {
    setX(x + dx);
}

float Camera::getX() const { return x; }
