#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <SDL3/SDL.h>

// Assume 16:10, otherwise black bars appear
#define LOGICAL_WIDTH 400
#define LOGICAL_HEIGHT 250

class Camera {
public:
    Camera(float x = 0.0f);

    void setX(float x);
    void moveX(float dx);

    float getX() const;

private:
    float x;
};

#endif // __CAMERA_H__
