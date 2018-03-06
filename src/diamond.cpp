#include "diamond.h"
#include "main.h"

Diamond::Diamond(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->col = color;
    int n = 360;
    int mag = 2;
    GLfloat vertex_buffer_data[] = {

        0.5f,0.0f,0.0f,
        -0.5f,0.0f,0.0f,
        0.0f,1.0f,0.0f,

        0.5f,0.0f,0.0f,
        -0.5f,0.0f,0.0f,
        0.0f,-1.0f,0.0f,

    };

    for(int i=0;i<2*3*3;i++)
        vertex_buffer_data[i]*=mag;

     this->object = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
}

void Diamond::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Diamond::set_position(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}



void Diamond::move(float x,float y) {
    this->position.x += x;
     this->position.y += y;
}

bounding_box_t Diamond::bounding_box() {
    int mag = 2;
    float x = this->position.x, y = this->position.y, z = this->position.z ;
    bounding_box_t bbox = { x, y, z, mag,mag,mag };
    return bbox;
}
