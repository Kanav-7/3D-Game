#include "ball.h"
#include "main.h"

Ball::Ball(float x, float y,float z, float r,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->radius = r;
    this->rotation = 0;
    this->col = color;
    int n = 360;
    static GLfloat vertex_buffer_data[360*9];
    float pi = M_PI*2;
    float xs = r , ys = 0 , cs = cos(pi/n),sn = sin(pi/n);

    for(int i=0;i<360*9;)
    {
//        printf("%f\n",xs);
        float x1 = xs*cs - ys*sn;
        float y1 = xs*sn  + ys*cs;
        vertex_buffer_data[i++] = 0;
        vertex_buffer_data[i++] = 0;
        vertex_buffer_data[i++] = 0.0f;
        vertex_buffer_data[i++] = xs  ;
        vertex_buffer_data[i++] = ys ;
        vertex_buffer_data[i++] = 0.0f;
        vertex_buffer_data[i++] = x1 ;
        vertex_buffer_data[i++] = y1 ;
        vertex_buffer_data[i++] = 0.0f;
        xs=x1,ys=y1;
    }

        this->object = create3DObject(GL_TRIANGLES, 3*n, vertex_buffer_data, color, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Ball::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Ball::set_radius(float r) {
    this->radius = r;
}


void Ball::move(float x,float y) {
    this->position.x += x;
     this->position.y += y;
}

bounding_box_t Ball::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z ,r = this->radius;
    bounding_box_t bbox = { x, y, z,2*r,2*r,2*r };
    return bbox;
}
