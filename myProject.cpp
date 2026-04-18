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
void miniMap(Vector3 pos,Vector3 target)
{
    //center point 800,250
    DrawRectangleLines(650,100,300,300,GREEN);

    DrawLine(650+150,100,650+150,100+300,GREEN);
    DrawLine(650,100+150,650+300,100+150,GREEN);


    DrawCircle(pos.x+800,pos.z+250,4,RED);
    DrawLine(pos.x+800,pos.z+250,(target.x*3)+800,(target.z*3)+250,BLUE);




}
//----------------------------------------------------------------------------------------



int main()
{
    InitWindow(1000,1000,"3D-Attempt");
    SetTargetFPS(60);

    Texture2D sky=LoadTexture("./resources/sky.png");

    Camera3D camera = { 0 };

    camera.position = (Vector3){ 0.0f, 10.0f, 1.0f }; // Position (where the camera is in the world)
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f }; // Target (what the camera is looking at)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f }; // Up vector (usually just "up" in the world)
    camera.fovy = 60.0f; // Field of view (in degrees)
    camera.projection = CAMERA_PERSPECTIVE; // Projection type

    oldpos=camera.position; //start with initial pos
    Vector3 forward={0,0,1.0f};
    Vector3 right={1.0f,0,0};

    float dx=0, dz=0;

    Mesh orb=GenMeshSphere(400,50,50);
    Model earth=LoadModelFromMesh(orb);
    earth.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture=sky;


    while(!WindowShouldClose())
    {
        BeginDrawing();

            //======================================
            //      front and back movement

            float joy1=GetGamepadAxisMovement(2,1);
        

            if(joy1<(-.1))
                {
                    dz=-1*joy1;
                    camera.position.z=camera.position.z+(cos(theta)*dz);
                    camera.position.x=camera.position.x+(sin(theta)*dz);

                }
                else
                    if(joy1>(.1))
                    {
                        dz=1*joy1;
                        camera.position.z=camera.position.z-(cos(theta)*dz);
                        camera.position.x=camera.position.x-(sin(theta)*dz);

                    }
                    else dz=0;  //no forward movement

            //======================================
            //      lateral joy---> rotation of view


            float joy_LR=GetGamepadAxisMovement(2,0);

            if(joy_LR<-0.1)
                {
                    if(theta>2*PI) theta=0;
                    
                    theta+=PI/180.0f;       //add 1 degree
                    

                    
                }
            if(joy_LR>0.1)
                {
                    if(theta<-2*PI) theta=0;
                   
                    theta-=PI/180.0f;       //subtract 1 degree
                    
   
                }
            //======================================
            

            
            
            
            camera.position.y=2;
            
            

            camera.target.x=camera.position.x+(sin(theta)*5);
            camera.target.z=camera.position.z+(cos(theta)*5);
            camera.target.y=2;





            

            UpdateCamera(&camera, CAMERA_FREE);

           

            

            // Keep inside world
            float limit = 10.0f;

            system("clear");
            cout<<"Position--->X: "<<camera.position.x<<" Y: "<<camera.position.y<<" Z: "<<camera.position.z<<endl;
            cout<<"View------->X: "<<camera.target.x<<" Y: "<<camera.target.y<<" Z: "<<camera.position.z<<endl;
            cout<<theta<<"  radians\n";



            ClearBackground(WHITE);
            DrawText("  3D \n\n\nWorld",350,80,50,WHITE);

            BeginMode3D(camera);

                DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 1000.0f, 1000.0f }, BLACK);
                //DrawGrid(1000, 1.0f);
                DrawCube((Vector3){ 50.0f, 2.0f, 50.0f }, 1.0f, 4.0f, 1.0f, GREEN);
                DrawCube((Vector3){ 50.0f, 2.0f, -50.0f }, 1.0f, 4.0f, 1.0f, BLUE);
                DrawCube((Vector3){ -50.0f, 2.0f, 50.0f }, 1.0f, 4.0f, 1.0f, RED);
                DrawCube((Vector3){ -50.0f, 2.0f, -50.0f }, 1.0f, 4.0f, 1.0f, ORANGE);


                rlDisableBackfaceCulling();
                    DrawModel(earth,{0,0,0},1.0f,WHITE);
                rlEnableBackfaceCulling();
                


              

            EndMode3D();
                
                miniMap(camera.position,camera.target);

        EndDrawing();



    }

    return 0;
    
}

