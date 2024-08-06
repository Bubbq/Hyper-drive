#include <stdio.h>
#include "headers/raylib.h"
#include "headers/raymath.h"

const float SCRSIZE = 750;
const Vector2 CENTER = { (SCRSIZE / 2.0f), (SCRSIZE / 2.0f) };

const int FPS = 60;
const int STAR_COUNT = 1000;

const float INIT_VEL = 1.0f;
const float FINAL_VEL = 15.0f;
const float DV = (FINAL_VEL / (SCRSIZE / 2));

const float DL = (15.0f/ (SCRSIZE / 2));

typedef struct
{
    Vector2 direction;
    Vector2 position;
    float velocity;
    Color color;
} Star;

void init_stars(Star stars[STAR_COUNT])
{
    for(int i = 0; i < STAR_COUNT; i++)
    {
        Star star;

        star.position = (Vector2){ GetRandomValue(0, SCRSIZE), GetRandomValue(0, SCRSIZE) };
        star.direction = Vector2Normalize(Vector2Subtract(star.position, CENTER));
        star.velocity = INIT_VEL;
        star.color = RAYWHITE;

        stars[i] = star;
    }
}

void handle_border_collision(Star *star)
{
    const int SPAWN_RADIUS = 25;
    
    if((star->position.x < 0 || star->position.x > SCRSIZE) || (star->position.y < 0 || star->position.y > SCRSIZE))
    {
        star->position = (Vector2){ GetRandomValue(CENTER.x - SPAWN_RADIUS, CENTER.x + SPAWN_RADIUS), GetRandomValue(CENTER.y - SPAWN_RADIUS, CENTER.y + SPAWN_RADIUS) };
        star->direction = Vector2Normalize(Vector2Subtract(star->position, CENTER));
    }
}

void move_star(Star *star)
{
    star->position = Vector2Add(star->position, Vector2Scale(star->direction, star->velocity));
}

void update_stars(Star stars[STAR_COUNT])
{
    for(int i = 0; i < STAR_COUNT; i++)
    {
        move_star(stars + i);
        handle_border_collision(stars + i);

        // stars move faster as it gets closer to screen border 
        stars[i].velocity = (Vector2Distance(stars[i].position, CENTER) * DV);
    }
}

void draw_stars(Star stars[STAR_COUNT])
{
    for(int i = 0; i < STAR_COUNT; i++)
    {
        Vector2 line = Vector2Scale(stars[i].direction, Vector2Distance(stars[i].position, CENTER) * DL * -1);

        DrawLineV(stars[i].position, Vector2Add(stars[i].position, line), RAYWHITE);
    }
}

int main()
{
    Star stars [STAR_COUNT];
    
    SetTargetFPS(FPS);
    SetTraceLogLevel(LOG_ERROR);
    InitWindow(SCRSIZE, SCRSIZE, "Hyperdrive Demo");

    init_stars(stars);

    while(!WindowShouldClose())
    {
        update_stars(stars);
        BeginDrawing();
            draw_stars(stars);
            DrawFPS(0, 0);
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}