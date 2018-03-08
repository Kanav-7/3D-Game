#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y,float z, float l,float b, float h, color_t color);
    glm::vec3 position;
    float rotation;
    float rotationx;
    float length;
    float breadth;
    float height;
    float size;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void set_speed(double vx, double vy,double vz);
    bounding_box_t bounding_box();
    void tick();
    glm::vec3 speed;
private:
    VAO *object;
};


#endif // BALL_H
