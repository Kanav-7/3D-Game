#include "main.h"

#ifndef WAVE_H
#define WAVE_H


class Wave {
public:
    Wave() {}
    Wave(float x, float y,float z,color_t color);
    glm::   vec3 position;
    float rotation;
    color_t col;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void tick();
    void move(float x,float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
