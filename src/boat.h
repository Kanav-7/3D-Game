#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, float z,color_t color);
    glm::vec3 position;
    glm::vec3 speed;
    bounding_box_t bounding_box();

    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void set_speed(double vx, double vy,double vz);
    void tick();
private:
    VAO *object1;
    VAO *object2;
    VAO *object3;
    VAO *object4;
    VAO *object5;
    VAO *object6;

};

#endif // BALL_H
