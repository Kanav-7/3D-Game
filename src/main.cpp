#include "main.h"
#include "timer.h"
#include "cuboid.h"
#include "boat.h"
#include "ball.h"
#include "diamond.h"
#include "wave.h"
using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

int score=0,health=100,life=3;
int view = 0;
float xcam = 0;
float ycam = 75;
float zcam = 20;
float xtar = 0;
float ytar = 75;
float ztar = 0;
Cuboid water,cannon;
Cuboid island;
Cuboid boss;
Boat boat;
Wave wav[1000];
int num_wave = 100;
Cuboid rocks[10000];
Cuboid monster[10000];
int mon_stat[10000];
Cuboid barrel[10000];
Diamond gifts[10000];
Cuboid boost;
Cuboid fireball;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
int num_rocks = 200,num_monster = 200,num_kill = 0;
float acc = 0.6f,upsped = 5.0f,acc2 = 0.3f;
Timer t60(1.0 / 60);
int flagw = 1,fireflag = 1, windflag = 1;
float windx,windz;
int monsflag = 1, monstick = 0, windtick = 0;
int boost_flag = 0;
int num_coins = 100;
int boss_shoot = 0;
Ball coins[10000];
int boosttick = 0;

char outsc[1000000];
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
      glm::vec3 eye(xcam,ycam,zcam);
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
//    glm::vec3 target (0, 10, 10);
//    glm::vec3 target (boat.position.x,boat.position.y,boat.position.z);
      glm::vec3 target (xtar,ytar,ztar);
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
    {
        monster[i].draw(VP);
        gifts[i].draw(VP);
    }
//    for(int i=0;i<num_wave;i++)
//    {
//        wav[i].draw(VP);
//    }

    for(int i=0;i<num_coins;i++){
        coins[i].draw(VP);
        barrel[i].draw(VP);
    }
    island.draw(VP);
    boost.draw(VP);
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
        float fact = 0.5;
        if(boost_flag)
            fact = 1;
        boat.set_position(boat.position.x + fact*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z + fact*cos(boat.rotation*M_PI/180));
        cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);

        int doin = 0;
        for(int i=0;i<num_rocks;i++)
        {
            if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
            {
                health-=1;
                 doin = 1;
//                 boat.set_position(boat.position.x,boat.position.y,boat.position.z + 2);
//                 cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
                 break;
            }
        }
        if(doin)
        {
            boat.set_position(boat.position.x - fact*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z - fact*cos(boat.rotation*M_PI/180));
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        }

    }
    if (down) {
        float fact = 0.5;
        if(boost_flag)
            fact = 1;
        boat.set_position(boat.position.x - fact*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z - fact*cos(boat.rotation*M_PI/180));
        cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        int doin = 0;
        for(int i=0;i<num_rocks;i++)
        {
            if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
            {
                 doin = 1;
                 health-=1;
                 break;
            }
        }
        if(doin)
        {
            boat.set_position(boat.position.x + fact*sin(boat.rotation*M_PI/180),boat.position.y,boat.position.z + fact*cos(boat.rotation*M_PI/180));
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

    if(health <= 0)
    {
        life--;
        health = 100;
    }
    if(life == 0)
        quit(window);

    cout << life << " " << health << " " << score << endl;
    if(boost_flag)
        boosttick++;

    if(boosttick == 700)
    {
        boost_flag = 0;
    }

    windtick++;

    if(windtick == 1000)
    {
//        cout << "check" << endl;
        boat.speed.x-=windx;
        boat.speed.z-=windz;
        cannon.speed.x-=windx;
        cannon.speed.z-=windz;
    }

    if(windtick == 3000)
    {
        windtick = 0;
        windflag = 1;
    }
    if(windflag)
    {
        windx = random(-0.2,0.2);
        windz = random(-0.2,0.2);
        windflag = 0;
        boat.speed.x+=windx;
        boat.speed.z+=windz;
        cannon.speed.x+=windx;
        cannon.speed.z+=windz;
    }
    monstick++;
    if(monstick == 2000)
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

    for(int i=0;i<num_rocks;i++)
    {
        if(detect_collision(boat.bounding_box(),rocks[i].bounding_box()))
        {
            health-=1;
            boat.set_position(boat.position.x,boat.position.y,boat.position.z + 2);
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        }
    }

    for(int i=0;i<num_coins;i++)
    {
        if(detect_collision(boat.bounding_box(),barrel[i].bounding_box()))
        {
//            health-=1;
            boat.set_position(boat.position.x,boat.position.y,boat.position.z + 1);
            cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
        }
    }

    for(int i=0;i<num_monster;i++)
    {
        gifts[i].rotation+=3;
        if(detect_collision(fireball.bounding_box(),monster[i].bounding_box()))
        {
            score+=20;
            num_kill++;
            if(num_kill == 3)
                boss.set_position(random(-100,100),5,random(-100,100));
            gifts[i].set_position(monster[i].position.x,3,monster[i].position.z);
            monster[i].set_position(random(-500,500),2,random(-500,500));
            fireball.set_position(10000,10000,10000);
            fireflag = 1;
        }

        if(detect_collision(boat.bounding_box(),monster[i].bounding_box()))
        {
            health-=20;
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

        if(detect_collision(boat.bounding_box(),gifts[i].bounding_box()))
        {
            health+=10 + rand()%10;
            gifts[i].set_position(10000,10000,10000);
        }
        monster[i].tick();
    }

    if(detect_collision(fireball.bounding_box(),boss.bounding_box()) && boss_shoot == 3)
    {
        score+=100;
        boost.set_position(boss.position.x,3,boss.position.z);
        boss.set_position(20000,20000,20000);
        fireball.set_position(10000,10000,10000);
        fireflag = 1;
    }
    if(detect_collision(fireball.bounding_box(),boss.bounding_box()) && boss_shoot < 3)
    {
//        cout << "YO" << endl;
        boss_shoot++;
        fireball.set_position(10000,10000,10000);
        fireflag = 1;
    }

    if(detect_collision(boat.bounding_box(),boost.bounding_box()))
    {
        score+=10;
        health+=20;
        boost.set_position(11000,11000,11000);
        boost_flag = 1;
        boosttick = 0;
//        boat.speed.x = 1.5*boat.speed.x;
//        boat.speed.z = 1.5*boat.speed.z;
    }
//    cout << boss_shoot;

    if(detect_collision(boat.bounding_box(),boss.bounding_box()))
    {
//        boss.set_position(random(-500,500),5,random(-500,500));
//        boss.set_position(20000,20000,20000);
        life-=1;
        health = 100;
        boat.set_position(boat.position.x,boat.position.y,boat.position.z + 2);
        cannon.set_position(boat.position.x,boat.position.y + 2.5f,boat.position.z);
    }

    for(int i=0;i<num_coins;i++)
    {
        if(detect_collision(boat.bounding_box(),coins[i].bounding_box()))
        {
            score+=5 + rand()%10;
            coins[i].set_position(random(-500,500),7,random(-500,500));
        }
        coins[i].rotation+=3;
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
//        cout << boat.speed.y << endl;
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
    island = Cuboid(100,1,100,100,100,0.6,ICOLOR_ORANGE);
    boat = Boat(0,0,0,COLOR_GREEN);
    boost = Cuboid(11000,11000,11000,4,4,4,ICOLOR_ORANGE);
    for(int i=0;i<num_rocks;i++)
        rocks[i] = Cuboid(random(-500,500),2,random(-500,500),random(4,8),random(4,8),random(4,8),COLOR_RED);

    for(int i=0;i<num_monster;i++)
    {
        monster[i] = Cuboid(random(-500,500),2,random(-500,500),random(4,8),random(4,8),random(4,8),COLOR_GREY);
        gifts[i] = Diamond(10000,10000,10000,COLOR_CYAN);
        //3
    }

//    int p = -1000;
//    for(int i=0;i<num_wave;i++)
//    {
//        wav[i] = Wave();
//    }

    for(int i=0;i<num_coins;i++)
    {
        float xr = random(-500,500);
        float zr = random(-500,500);
        coins[i] = Ball(xr,7,zr,2,ICOLOR_YELLOW);
        barrel[i] = Cuboid(xr,1,zr,6,6,0.8,COLOR_BROWN);
    }

//    boss = Cuboid(random(-100,100),5,random(-100,100),10,10,10,ICOLOR_YELLOW);
    boss = Cuboid(20000,20000,20000,10,10,10,ICOLOR_YELLOW);
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
            sprintf(outsc,"3D Zelda | Score: %d | Health: %d | Lives: %d",score,health,life);
            glfwSetWindowTitle(window,outsc);
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 <= (a.l + b.l)) &&
           (abs(a.z - b.z) * 2 <= (a.b + b.b)) &&
            (abs(a.y - b.y) * 2 <= (a.h + b.h));
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
    view = view%6;
}

void speed_camera()
{
    if(view==1)
    {

        xcam = boat.position.x;
        ycam = boat.position.y + 5;
        zcam = boat.position.z -  20;
        xtar = boat.position.x;
        ytar = boat.position.y;
        ztar = boat.position.z;

    }

    if(view==0)
    {
        double theta = (boat.rotation)*(M_PI/180);

        xcam = boat.position.x+3*sin(theta);
        ycam = boat.position.y+2;
        zcam = boat.position.z+3*cos(theta);

        xtar = boat.position.x+10*sin(theta);
        ytar = boat.position.y+2;
        ztar = boat.position.z+10*cos(theta);

    }

    if(view==2)
    {
        ycam = 30;
        ytar = 30;
    }

    if(view==3)
    {
        // top view
        xcam = boat.position.x;
        ycam = 200;
        zcam = boat.position.z;

        xtar = boat.position.x+1;
        ytar = boat.position.y;
        ztar = boat.position.z;
    }

    if(view==4)
    {
        // helicopter
        xcam = boat.position.x+90;
        ycam = 90;
        zcam = boat.position.z;

        xtar = boat.position.x;
        ytar = boat.position.y;
        ztar = boat.position.z;
    }

    if(view == 5)
    {
        xcam = boat.position.x+60*sin(boat.rotation*M_PI/180.0f);;
        ycam= 30;
        zcam = boat.position.z+60*cos(boat.rotation*M_PI/180.0f);
        xtar = boat.position.x;
        ytar = boat.position.y;
        ztar = boat.position.z;
    }

}

