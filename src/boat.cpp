#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y,float z, color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->speed = glm::vec3(0,0,0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

    GLfloat vertex_buffer_data_left[] =   {
        //left
            -1,1,-1,
            -0.5,0.5,-0.5,
            -0.5,0.5,0.5,
            -1,1,-1,
            -1,1,1,
            -0.5,0.5,0.5,};
    GLfloat vertex_buffer_data_right[] =   {
            //right
            0.5,0.5,0.5,
            1,1,1,
            1,1,-1,
            0.5,0.5,0.5,
            0.5,0.5,-0.5,
            1,1,-1,};
    GLfloat vertex_buffer_data_front[] =   {
            //front
            -1,1,-1,
            -0.5,0.5,-0.5,
            0.5,0.5,-0.5,
            -1,1,-1,
            1,1,-1,
            0.5,0.5,-0.5,
    };
    GLfloat vertex_buffer_data_behind[] =   {
            //back
            0.5,0.5,0.5,
            1,1,1,
            -1,1,1,
            0.5,0.5,0.5,
            -0.5,0.5,0.5,
            -1,1,1,};
    GLfloat vertex_buffer_data_down[] =   {
            //bottom
            -0.5,0.5,0.5,
            -0.5,0.5,-0.5,
            0.5,0.5,-0.5,
            -0.5,0.5,0.5,
            0.5,0.5,0.5,
            0.5,0.5,-0.5,};

    for(int i=0;i<2*3*3;i++)
    {
        vertex_buffer_data_left[i]*= 2;
        vertex_buffer_data_right[i]*= 2;
        vertex_buffer_data_down[i]*= 2;
        vertex_buffer_data_behind[i]*= 2;
        vertex_buffer_data_front[i]*= 2;
    }
        //    static GLfloat vertex_buffer_data[200];

//    vertex_buffer_data[0] = -0.5;
//    vertex_buffer_data[1] = 0.5;
//    vertex_buffer_data[2] = 0.5;
//    vertex_buffer_data[3] = -0.5;
//    vertex_buffer_data[4] = 0.5;
//    vertex_buffer_data[5] = -0.5;
//    vertex_buffer_data[6] = 0.5;
//    vertex_buffer_data[7] = 0.5;
//    vertex_buffer_data[8] = -0.5;

//    vertex_buffer_data[9] =  -0.5;
//    vertex_buffer_data[10] = 0.5;
//    vertex_buffer_data[11] = 0.5;
//    vertex_buffer_data[12] = 0.5;
//    vertex_buffer_data[13] = 0.5;
//    vertex_buffer_data[14] = 0.5;
//    vertex_buffer_data[15] = 0.5;
//    vertex_buffer_data[16] = 0.5;
//    vertex_buffer_data[17] = -0.5;


//    vertex_buffer_data[18] = 1;
//    vertex_buffer_data[19] = 1;
//    vertex_buffer_data[20] = 1;
//    vertex_buffer_data[21] = 1;
//    vertex_buffer_data[22] = 1;
//    vertex_buffer_data[23] = -1;
//    vertex_buffer_data[24] = -1;
//    vertex_buffer_data[25] = 1;
//    vertex_buffer_data[26] = -1;

//    vertex_buffer_data[27] = 1;
//    vertex_buffer_data[28] = 1;
//    vertex_buffer_data[29] = 1;
//    vertex_buffer_data[30] = 1;
//    vertex_buffer_data[31] = 1;
//    vertex_buffer_data[32] = -1;
//    vertex_buffer_data[33] = -1;
//    vertex_buffer_data[34] = 1;
//    vertex_buffer_data[35] = -1;

//       // //front
//       //  -1,1,-1,
//       //  -0.5,0.5,-0.5,
//       //  0.5,0.5,-0.5,
//       //  -1,1,-1,
//       //  1,1,-1,
//        // 0.5,0.5,-0.5,

//    vertex_buffer_data[36] = -1;
//    vertex_buffer_data[37] = 1;
//    vertex_buffer_data[38] = -1;
//    vertex_buffer_data[39] = -0.5;
//    vertex_buffer_data[40] = 0.5;
//    vertex_buffer_data[41] = -0.5;
//    vertex_buffer_data[42] = 0.5;
//    vertex_buffer_data[43] = 0.5;
//    vertex_buffer_data[44] = -0.5;

//    vertex_buffer_data[45] = -1;
//    vertex_buffer_data[46] = 1;
//    vertex_buffer_data[47] = -1;
//    vertex_buffer_data[48] = 1;
//    vertex_buffer_data[49] = 1;
//    vertex_buffer_data[50] = -1;
//    vertex_buffer_data[51] = 0.5;
//    vertex_buffer_data[52] = 0.5;
//    vertex_buffer_data[53] = -0.5;

//  // //back
//  //       0.5,0.5,0.5,
//  //       1,1,1,
//  //       -1,1,1,
//  //       0.5,0.5,0.5,
//  //       -0.5,0.5,0.5,
//  //       -1,1,1,

//    vertex_buffer_data[54] = 0.5;
//    vertex_buffer_data[55] = 0.5;
//    vertex_buffer_data[56] = 0.5;
//    vertex_buffer_data[57] = 1;
//    vertex_buffer_data[58] = 1;
//    vertex_buffer_data[59] = 1;
//    vertex_buffer_data[60] = -1;
//    vertex_buffer_data[61] = 1;
//    vertex_buffer_data[62] = 1;

//    vertex_buffer_data[63] = 0.5;
//    vertex_buffer_data[64] = 0.5;
//    vertex_buffer_data[65] = 0.5;
//    vertex_buffer_data[66] = -0.5;
//    vertex_buffer_data[67] = 0.5;
//    vertex_buffer_data[68] = 0.5;
//    vertex_buffer_data[69] = -1;
//    vertex_buffer_data[70] = 1;
//    vertex_buffer_data[71] = 1;

//    // //left
//    //     -1,1,-1,
//    //     -0.5,0.5,-0.5,
//    //     -0.5,0.5,0.5,
//    //     -1,1,-1,
//    //     -1,1,1,
//    //     -0.5,0.5,0.5,
//    vertex_buffer_data[72] = -1;
//    vertex_buffer_data[73] = 1;
//    vertex_buffer_data[74] = -1;
//    vertex_buffer_data[75] = -0.5;
//    vertex_buffer_data[76] = 0.5;
//    vertex_buffer_data[77] = -0.5;
//    vertex_buffer_data[78] = -0.5;
//    vertex_buffer_data[79] = 0.5;
//    vertex_buffer_data[80] = 0.5;

//    vertex_buffer_data[81] = -1;
//    vertex_buffer_data[82] = 1;
//    vertex_buffer_data[83] = -1;
//    vertex_buffer_data[84] = -1;
//    vertex_buffer_data[85] = 1;
//    vertex_buffer_data[86] = 1;
//    vertex_buffer_data[87] = -0.5;
//    vertex_buffer_data[88] = 0.5;
//    vertex_buffer_data[89] = 0.5;


//        // //right
//        // 0.5,0.5,0.5,
//        // 1,1,1,
//        // 1,1,-1,
//        // 0.5,0.5,0.5,
//        // 0.5,0.5,-0.5,
//        // 1,1,-1,
//    vertex_buffer_data[90] = 0.5;
//    vertex_buffer_data[91] = 0.5;
//    vertex_buffer_data[92] = 0.5;
//    vertex_buffer_data[93] = 1;
//    vertex_buffer_data[94] = 1;
//    vertex_buffer_data[95] = 1;
//    vertex_buffer_data[96] = 1;
//    vertex_buffer_data[97] = 1;
//    vertex_buffer_data[98] = -1;

//    vertex_buffer_data[99]  = 0.5;
//    vertex_buffer_data[100] = 0.5;
//    vertex_buffer_data[101] = 0.5;
//    vertex_buffer_data[102] = 0.5;
//    vertex_buffer_data[103] = 0.5;
//    vertex_buffer_data[104] = -0.5;
//    vertex_buffer_data[105] = 1;
//    vertex_buffer_data[106] = 1;
//    vertex_buffer_data[107] = -1;

//    color_t a[] = {color,COLOR_BLACK};
    this->object1 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_left, ICOLOR_ORANGE, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_right, ICOLOR_RED, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_behind, ICOLOR_GREEN, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_front, COLOR_BLACK, GL_FILL);
    this->object5 = create3DObject(GL_TRIANGLES, 2*3, vertex_buffer_data_down, ICOLOR_INDIGO, GL_FILL);
}

void Boat::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
    draw3DObject(this->object5);
}

void Boat::set_speed(double vx, double vy,double vz) {
    this->speed = glm::vec3(vx,vy,vz);
}

void Boat::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Boat::tick() {
//    this->rotation += speed;
    this->position.x += this->speed.x;
    this->position.y += this->speed.y;
    this->position.z += this->speed.z;
    // this->position.y -= speed;
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x;
    float y = this->position.y;
    float z = this->position.z;
    float h = 2;
    float b = 4;
    float l = 4;
    bounding_box_t bbox = { x, y, z, l,b,h };
    return bbox;
}
