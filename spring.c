#include "raylib.h"
#include <stdio.h>
#include <math.h>

#define FPS 100
#define WIDTH 900
#define HEIGHT 600
#define THICK 5

// Constantes e variáveis úteis modificáveis na simulação
#define FLOOR_Y (HEIGHT*0.6) // Local do chão

#define MASS_SIDE 100 // tamanho do quadrado de massa
#define NUM_SPRING_ELEMENTS 15 // numero de elementos da mola
#define SPRING_ELEM_LENGHT 50 // tamanho dos elementos da mola
#define X_REST (WIDTH/3) // local de descanso da mola
#define K 200 // constante elastica
#define FRICTION 2 // constante de atrito

float x_mass = WIDTH*0.7; // local inicial da massa
float velocity = 20; // velocidade inicial da massa

void draw_floor()
{
    Vector2 start = {0,FLOOR_Y};
    Vector2 end = {WIDTH, FLOOR_Y};
    DrawLineEx(start, end, THICK, GRAY);
}

void draw_spring()
{
    Vector2 points[NUM_SPRING_ELEMENTS+1];
    float x_max = x_mass / NUM_SPRING_ELEMENTS; //Tamanho máximo dos elementos no eixo 'X' 
    for(int i = 0; i <= NUM_SPRING_ELEMENTS; i++)
    {
        if(i%2 == 0)
        {
            points[i].x = i * x_max;
            points[i].y = FLOOR_Y - MASS_SIDE/2 + SPRING_ELEM_LENGHT/2;
        }
        else
        {
            points[i].x = i * x_max;
            points[i].y = FLOOR_Y - MASS_SIDE/2 - SPRING_ELEM_LENGHT/2;
        }
    }
    DrawLineStrip(points, NUM_SPRING_ELEMENTS+1, GRAY);
}

void draw_mass()
{
    Rectangle rect = {x_mass, FLOOR_Y-MASS_SIDE-THICK/2, MASS_SIDE, MASS_SIDE};
    DrawRectangleRec(rect, BLUE);
}

// se o mouse estiver fora da posição da massa retorna 0, se não retorna 1
int is_mouse_on_mass()
{
    Vector2 mouse_position = GetMousePosition();

    if(mouse_position.x < x_mass || mouse_position.x > x_mass+MASS_SIDE)
    {
        return 0;
    }
    else if(mouse_position.y < FLOOR_Y-MASS_SIDE-THICK/2 || mouse_position.y > (FLOOR_Y-MASS_SIDE-(THICK/2) + MASS_SIDE))
    {
        return 0;
    }
    else
        return 1;
}

void control_mass_xPosition()
{
    Vector2 mouse_position = GetMousePosition();

    int new_x = mouse_position.x - MASS_SIDE/2;

    x_mass = new_x;

    draw_mass();
    draw_spring();
    EndDrawing();
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Simulação sistema massa em mola");
    SetTargetFPS(FPS);

    float delta_t;
    float aceleration;
    float current_friction;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            //DrawFPS(10, 10);
            // delta de tempo para calcular com base no FPS da simulação
            delta_t = GetFrameTime();
            //DrawText("Simulação massa em mola", WIDTH*0.37, HEIGHT*0.1, 20, BLUE);
            draw_floor();

            // desenha com base no mouse se clicar na massa
            if(is_mouse_on_mass() == 1)
            {
                if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    control_mass_xPosition();
                    continue;
                }
            }

            // fricção no momento com base na velocidade
            current_friction = velocity*FRICTION;
            //aceleração: equação sistema massa mola, com fricção
            aceleration = - K * (x_mass - X_REST) - current_friction;
            // atualiza velocidade com base na aceleração, e contando o FPS da simulação
            velocity += aceleration * delta_t;
            // atualiza a posição da massa com base na velocidade, e contando o FPS da simulação
            x_mass += velocity * delta_t;
            draw_mass();
            draw_spring();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}