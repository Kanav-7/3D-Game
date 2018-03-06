#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float z,float r,color_t color);
    glm::   vec3 position;
    float rotation;
    float radius;
    color_t col;
    void draw(glm::mat4 VP);
    void set_position(float x, float y, float z);
    void set_radius(float r);
    void set_speed(double vx,double vy);
    void tick();
    void move(float x,float y);
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BALL_H
