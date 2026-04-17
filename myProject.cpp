#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"


using namespace std;

Vector3 oldpos,deltapos;
float theta=0;  //initial vector direction
Vector3 forward={0,0,1.0f}; //initial forward


//----------------------------------------------------------------------------------------
Vector3 delta(Vector3 origpos, Vector3 newpos)
{
    Vector3 diff;

    diff={(origpos.x-newpos.x),(origpos.y-newpos.y),(origpos.z-newpos.z)};

    return diff;


}
//----------------------------------------------------------------------------------------
Vector3 newforward(Vector3 &first, float angle)
{

    first.x=sin(angle);
    first.z=cos(angle);

    return first;


}
//----------------------------------------------------------------------------------------
void miniMap()
{
    DrawRectangleLines(650,100,300,300,GREEN);

    DrawLine(650+150,100,650+150,100+300,GREEN);
    DrawLine(650,100+150,650+300,100+150,GREEN);




}
//----------------------------------------------------------------------------------------



int main()
{
    InitWindow(1000,1000,"3D-Attempt");
    SetTargetFPS(60);

    Camera3D camera = { 0 };

    camera.position = (Vector3){ 0.0f, 10.0f, 1.0f }; // Position (where the camera is in the world)
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f }; // Target (what the camera is looking at)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Up vector (usually just "up" in the world)
    camera.fovy = 60.0f; // Field of view (in degrees)
    camera.projection = CAMERA_PERSPECTIVE; // Projection type

    oldpos=camera.position; //start with initial pos
    Vector3 forward={0,0,1.0f};
    Vector3 right={1.0f,0,0};
    

    while(!WindowShouldClose())
    {
        BeginDrawing();

            //======================================
            //      front and back movement

            float joy1=GetGamepadAxisMovement(2,1);

            if(joy1<(-.1))
                {
                    camera.position=Vector3Add(camera.position,forward);
                    



                    
                    
                }
            if(joy1>(.1))
                {
                    
                    
                }

            //======================================
            //      lateral joy---> rotation of view


            float joy_LR=GetGamepadAxisMovement(2,0);

            if(joy_LR<-0.1)
                {
                    if(theta>2*PI) theta=0;
                    
                    theta+=PI/180.0f;       //add 1 degree
                    newforward(camera.target, theta);
                    forward=camera.target;          //set the addition vector to the place you are looking

                    
                }
            if(joy_LR>0.1)
                {
                    if(theta<-2*PI) theta=0;
                   
                    theta-=PI/180.0f;       //subtract 1 degree
                    newforward(camera.target, theta);   //by reference changes target according to angle
                    forward=camera.target;


                    
                }
            //======================================
            system("clear");
            cout<<"X: "<<camera.position.x<<" Y: "<<camera.position.y<<" Z: "<<camera.position.z<<endl;
            cout<<"X: "<<forward.x<<" Y: "<<forward.y<<" Z: "<<forward.z<<endl;
            cout<<theta<<"  radians\n";

            UpdateCamera(&camera, CAMERA_FREE);

                        // Lock height
            camera.position.y = 2.0f;
            camera.target.y   = 2.0f;

            // Keep inside world
            float limit = 10.0f;

            //camera.position.x = std::clamp(camera.position.x, -limit, limit);
            //camera.position.z = std::clamp(camera.position.z, -limit, limit);



            ClearBackground(BLACK);
            DrawText("  3D \n\n\nWorld",350,80,50,WHITE);

            BeginMode3D(camera);

                //DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 20.0f, 20.0f }, GRAY);
                DrawGrid(100, 1.0f);
                DrawCube((Vector3){ 50.0f, 2.0f, 50.0f }, 1.0f, 4.0f, 1.0f, GREEN);
                DrawCube((Vector3){ 50.0f, 2.0f, -50.0f }, 1.0f, 4.0f, 1.0f, BLUE);
                DrawCube((Vector3){ -50.0f, 2.0f, 50.0f }, 1.0f, 4.0f, 1.0f, RED);
                DrawCube((Vector3){ -50.0f, 2.0f, -50.0f }, 1.0f, 4.0f, 1.0f, ORANGE);

                //DrawSphere((Vector3){0,10,0},5,BLUE);

              

            EndMode3D();
                
                miniMap();

        EndDrawing();



    }

    return 0;
    
}

/*
            if (IsKeyDown(KEY_W)) camera.position.z -= 0.1f;
            if (IsKeyDown(KEY_S)) camera.position.z += 0.1f;
            if (IsKeyDown(KEY_A)) camera.position.x -= 0.1f;
            if (IsKeyDown(KEY_D)) camera.position.x += 0.1f;
*/