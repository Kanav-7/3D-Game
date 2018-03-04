#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y,float z,float l,float b,float h, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static GLfloat vertex_buffer_data[200];

    vertex_buffer_data[0] = l/2.0f;
    vertex_buffer_data[1] = h/2.0f;
    vertex_buffer_data[2] = -b/2.0f;
    vertex_buffer_data[3] = l/2.0f;
    vertex_buffer_data[4] = -h/2.0f;
    vertex_buffer_data[5] = -b/2.0f;
    vertex_buffer_data[6] = -l/2.0f;
    vertex_buffer_data[7] = -h/2.0f;
    vertex_buffer_data[8] = -b/2.0f;

    vertex_buffer_data[9] = l/2.0f;
    vertex_buffer_data[10] = h/2.0f;
    vertex_buffer_data[11] = -b/2.0f;
    vertex_buffer_data[12] = -l/2.0f;
    vertex_buffer_data[13] = h/2.0f;
    vertex_buffer_data[14] = -b/2.0f;
    vertex_buffer_data[15] = -l/2.0f;
    vertex_buffer_data[16] = -h/2.0f;
    vertex_buffer_data[17] = -b/2.0f;



    vertex_buffer_data[18] = -l/2.0f;
    vertex_buffer_data[19] = h/2.0f;
    vertex_buffer_data[20] = -b/2.0f;
    vertex_buffer_data[21] = -l/2.0f;
    vertex_buffer_data[22] = h/2.0f;
    vertex_buffer_data[23] = b/2.0f;
    vertex_buffer_data[24] = -l/2.0f;
    vertex_buffer_data[25] = -h/2.0f;
    vertex_buffer_data[26] = b/2.0f;

    vertex_buffer_data[27] = -l/2.0f;
    vertex_buffer_data[28] = h/2.0f;
    vertex_buffer_data[29] = -b/2.0f;
    vertex_buffer_data[30] = -l/2.0f;
    vertex_buffer_data[31] = -h/2.0f;
    vertex_buffer_data[32] = -b/2.0f;
    vertex_buffer_data[33] = -l/2.0f;
    vertex_buffer_data[34] = -h/2.0f;
    vertex_buffer_data[35] = b/2.0f;



    vertex_buffer_data[36] = l/2.0f;
    vertex_buffer_data[37] = h/2.0f;
    vertex_buffer_data[38] = -b/2.0f;
    vertex_buffer_data[39] = l/2.0f;
    vertex_buffer_data[40] = h/2.0f;
    vertex_buffer_data[41] = b/2.0f;
    vertex_buffer_data[42] = l/2.0f;
    vertex_buffer_data[43] = -h/2.0f;
    vertex_buffer_data[44] = b/2.0f;

    vertex_buffer_data[45] = l/2.0f;
    vertex_buffer_data[46] = h/2.0f;
    vertex_buffer_data[47] = -b/2.0f;
    vertex_buffer_data[48] = l/2.0f;
    vertex_buffer_data[49] = -h/2.0f;
    vertex_buffer_data[50] = -b/2.0f;
    vertex_buffer_data[51] = l/2.0f;
    vertex_buffer_data[52] = -h/2.0f;
    vertex_buffer_data[53] = b/2.0f;

    vertex_buffer_data[54] = l/2.0f;
    vertex_buffer_data[55] = h/2.0f;
    vertex_buffer_data[56] = -b/2.0f;
    vertex_buffer_data[57] = -l/2.0f;
    vertex_buffer_data[58] = h/2.0f;
    vertex_buffer_data[59] = -b/2.0f;
    vertex_buffer_data[60] = l/2.0f;
    vertex_buffer_data[61] = h/2.0f;
    vertex_buffer_data[62] = b/2.0f;

    vertex_buffer_data[63] = -l/2.0f;
    vertex_buffer_data[64] = h/2.0f;
    vertex_buffer_data[65] = b/2.0f;
    vertex_buffer_data[66] = -l/2.0f;
    vertex_buffer_data[67] = h/2.0f;
    vertex_buffer_data[68] = b/2.0f;
    vertex_buffer_data[69] = l/2.0f;
    vertex_buffer_data[70] = h/2.0f;
    vertex_buffer_data[71] = b/2.0f;


    vertex_buffer_data[72] = l/2.0f;
    vertex_buffer_data[73] = -h/2.0f;
    vertex_buffer_data[74] = -b/2.0f;
    vertex_buffer_data[75] = -l/2.0f;
    vertex_buffer_data[76] = -h/2.0f;
    vertex_buffer_data[77] = -b/2.0f;
    vertex_buffer_data[78] = l/2.0f;
    vertex_buffer_data[79] = -h/2.0f;
    vertex_buffer_data[80] = b/2.0f;

    vertex_buffer_data[81] = -l/2.0f;
    vertex_buffer_data[82] = -h/2.0f;
    vertex_buffer_data[83] = b/2.0f;
    vertex_buffer_data[84] = -l/2.0f;
    vertex_buffer_data[85] = -h/2.0f;
    vertex_buffer_data[86] = -b/2.0f;
    vertex_buffer_data[87] = l/2.0f;
    vertex_buffer_data[88] = -h/2.0f;
    vertex_buffer_data[89] = b/2.0f;

    vertex_buffer_data[90] = l/2.0f;
    vertex_buffer_data[91] = h/2.0f;
    vertex_buffer_data[92] = b/2.0f;
    vertex_buffer_data[93] = l/2.0f;
    vertex_buffer_data[94] = -h/2.0f;
    vertex_buffer_data[95] = b/2.0f;
    vertex_buffer_data[96] = -l/2.0f;
    vertex_buffer_data[97] = -h/2.0f;
    vertex_buffer_data[98] = b/2.0f;

    vertex_buffer_data[99] = l/2.0f;
    vertex_buffer_data[100] = h/2.0f;
    vertex_buffer_data[101] = b/2.0f;
    vertex_buffer_data[102] = -l/2.0f;
    vertex_buffer_data[103] = h/2.0f;
    vertex_buffer_data[104] = b/2.0f;
    vertex_buffer_data[105] = -l/2.0f;
    vertex_buffer_data[106] = -h/2.0f;
    vertex_buffer_data[107] = b/2.0f;

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cuboid::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cuboid::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

