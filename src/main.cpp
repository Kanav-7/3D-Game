#include "main.h"
#include "timer.h"
#include "cuboid.h"
#include "boat.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int view = 0;
float camera_x = 0;
float camera_y = 75;
float camera_z = 20;
float target_x = 0;
float target_y = 75;
float target_z = 0;
Cuboid water,cannon;
Cuboid boss;
Boat boat;
Cuboid rocks[1000000];
Cuboid monster[1000000];
Cuboid fireball;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int num_rocks = 200,num_monster = 200,num_kill = 0;
float acc = 0.3f,upsped = 3.0f,acc2 = 0.3f;
Timer t60(1.0 / 60);
int flagw = 1,fireflag = 1;
int monsflag = 1, monstick = 0;
float random(float a,float b)
{
   return (a + (((float) rand()) / (float) RAND_MAX)*(b-a));
}

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
//    glm::vec3 eye (boat.position.x, boat.position.y + 5,boat.position.z +  20 );
//    glm::vec3 eye ( 1, 5,0 );
      glm::vec3 eye(camera_x,camera_y,camera_z);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0, 10, 10);
//    glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
      glm::vec3 target (target_x,target_y,target_z);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    cannon.draw(VP);
    for(int i=0;i<num_rocks;i++)
        rocks[i].draw(VP);
    for(int i=0;i<num_monster;i++)
        monster[i].draw(VP);
    boss.draw(VP);
    boat.draw(VP);
    water.draw(VP);
    fireball.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int f = glfwGetKey(window, GLFW_KEY_F);


    if (left) {
//        boat.set_position(boat.position.x + 0.1,boat.position.y,boat.position.z);
        boat.rotation-=1;
    }
    if (right) {
//        boat.set_position(boat.position.x - 0.1,boat.position.y,boat.position.z);
        boat.rotation+=1;

    }
    if (up) {
        int doin = 1;
        for(int i=0;i<num_rocks;i++)
        {
            if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
            {
                 doin = 0;
                 boat.set_position(boat.position.x,boat.position.y,boat.position.z + 2);
                 cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
                 break;
            }
        }
        if(doin)
        {
            boat.set_position(boat.position.x + 0.5*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z + 0.5*cos(boat.rotation*M_PI/180));
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        }

    }
    if (down) {
        int doin = 1;
        for(int i=0;i<num_rocks;i++)
        {
            if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
            {
                 doin = 0;
                 break;
            }
        }
        if(doin)
        {
            boat.set_position(boat.position.x - 0.5*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z - 0.5*cos(boat.rotation*M_PI/180));
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);

        }

    }
    if (space && boat.position.y <=0) {
        boat.speed.y = upsped;
        cannon.speed.y = upsped;
    }
    if(d)
    {
        cannon.rotation+=5;
    }

    if(f && fireflag)
    {
        fireball.position = cannon.position;
//        fireball.speed.x = 1.0*sin()
        fireball.speed.y = 2.0f;
        fireball.speed.x = 0.5*sin(boat.rotation*M_PI/180);
        fireball.speed.z = 0.5*cos(boat.rotation*M_PI/180);
        fireflag = 0;
    }
}

void tick_elements() {
    monstick++;
    if(monstick == 5000)
    {
        monstick = 0;
        monsflag = 1;
    }
    speed_camera();

    boat.tick();
    fireball.tick();
    cannon.tick();
//    camera_rotation_angle += 1;

    if(flagw)
    {
        water.position.y+=0.007;
        if(water.position.y + 9.5f > 0.3f)
            flagw = 0;
    }
    else
    {
        water.position.y-=0.007;
        if(water.position.y + 9.5f < 0.0f)
            flagw = 1;
    }

    for(int i=0;i<num_monster;i++)
    {
        if(detect_collision(fireball.bounding_box(),monster[i].bounding_box()))
        {
            monster[i].set_position(random(-500,500),2,random(-500,500));
            fireball.set_position(10000,10000,10000);
            fireflag = 1;
        }

        if(detect_collision(boat.bounding_box(),monster[i].bounding_box()))
        {
            monster[i].set_position(random(-500,500),2,random(-500,500));

            boat.set_position(boat.position.x,boat.position.y,boat.position.z + 2);
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        }
        if(monsflag)
        {
        monster[i].speed.x = random(-0.15,0.15);
        monster[i].speed.z = random(-0.15,0.15);
        if(i == num_monster -1)
            monsflag = 0;
        }
        monster[i].tick();
    }


    if(fireball.speed.y > 0){
        fireball.speed.y-=acc2;
    }
    if(fireball.position.y < 0)
    {
        fireball.position.y = 10000;
        fireball.position.x = 10000;
        fireball.position.z = 10000;
        fireball.speed.y = 0;
        fireball.speed.z = 0;
        fireball.speed.x = 0;
        fireflag = 1;
    }
    if(boat.speed.y > 0){
        cout << boat.speed.y << endl;
        boat.speed.y-=acc;
        cannon.speed.y-=acc;
    }
    if(boat.position.y < 0)
    {
        cannon.position.y = 2.5;
        cannon.speed.y = 0;
        boat.position.y = 0;
        boat.speed.y = 0;
    }
//    cout << fireball.position.x << " " << fireball.position.y << " " << fireball.position.z << " " << endl;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models

    water = Cuboid(0,-9,0,2000,2000,20,COLOR_BLUE);

    cannon = Cuboid(0,2.5,0,0.2,0.2,3,COLOR_RED);

    fireball = Cuboid(10000,10000,10000,0.2,0.2,0.2,COLOR_BLACK);
    cannon.rotationx = 40;
//    cannon.rotation = 140;

    boat = Boat(0,0,0,COLOR_GREEN);

    for(int i=0;i<num_rocks;i++)
        rocks[i] = Cuboid(random(-500,500),2,random(-500,500),random(4,8),random(4,8),random(4,8),COLOR_RED);

    for(int i=0;i<num_monster;i++)
        monster[i] = Cuboid(random(-500,500),2,random(-500,500),random(4,8),random(4,8),random(4,8),COLOR_GREY);

    boss = Cuboid(random(-10,10),5,random(-10,10),10,10,10,ICOLOR_YELLOW);

    // Create and comM_PIle our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.l + b.l)) &&
           (abs(a.z - b.z) * 2 < (a.b + b.b));
}

void reset_screen() {
    /*float top    = screen_center_y + 5 / screen_zoom;
    float bottom = screen_center_y - 5 / screen_zoom;
    float left   = screen_center_x - 5 / screen_zoom;
    float right  = screen_center_x + 5 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);*/
    Matrices.projection = glm::perspective(45.0f, 1.0f, 10.0f, 500.0f);
}

void change_camera(){
    view++;
    view = view%5;
}

void speed_camera()
{
//    cout << view << endl;
    if(view==1){

        camera_x = boat.position.x;
        camera_y = boat.position.y + 5;
        camera_z = boat.position.z -  20;
        target_x = boat.position.x;
        target_y = boat.position.y;
        target_z = boat.position.z;

    }
    else if(view==0)
    {
        // follow
        double theta = (boat.rotation)*(M_PI/180);

        camera_x = boat.position.x+3*sin(theta);
        camera_y = boat.position.y+5;
        camera_z = boat.position.z+3*cos(theta);

        target_x = boat.position.x+10*sin(theta);
        target_y = boat.position.y+5;
        target_z = boat.position.z+10*cos(theta);

    }
    else if(view==2)
    {
        // tower view
        camera_y = 30;
//        camera_z+=5;
        target_y = 30;
    }
    else if(view==3)
    {
        // top view
        camera_x = boat.position.x;
        camera_y = 200;
        camera_z = boat.position.z;

        target_x = boat.position.x+1;
        target_y = boat.position.y;
        target_z = boat.position.z;
//        printf("cx=%f cy=%f cz=%f\n", camera_x, camera_y, camera_z);
//        printf("tx=%f ty=%f tz=%f\n", target_x, target_y, target_z);
    }
    else if(view==4)
    {
        // helicopter
        camera_x = boat.position.x+90;
        camera_y = 90;
        camera_z = boat.position.z;

        target_x = boat.position.x;
        target_y = boat.position.y;
        target_z = boat.position.z;
    }

}

void heli_camera(float x, float y)
{
    if(view==2)
    {
        target_x = boat.position.x+(x-300);
        if(y<=300)
        {
            target_y = boat.position.y+(300-y)/2;
        }
    }
}

void zoom_camera(int type)
{
    if(view==2)
    {
        double l = target_x-camera_x;
        double m = target_y-camera_y;
        double n = target_z-camera_z;
        if(type==1)
        {
            if(camera_z-10>target_z)
                camera_z-=10;
        }
        else if(type==-1)
        {
            camera_z+=10;
        }
        camera_x = l*(camera_z-target_z)/n+target_x;
        camera_y = m*(camera_z-target_z)/n+target_y;
    }
}
