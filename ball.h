#ifndef BALL_H
#define BALL_H

#define GL_SILENCE_DEPRECATION
#define GRAVITATIONAL_CONSTANT -9.8
#define LINE_WIDTH 2
#include <GLFW/glfw3.h>
#include <math.h>

typedef struct Ball {
    float x;
    float y;
    float rad;
    int num_segments;
    float velocity;
    float mass;
    double last_updated_timestamp;
} Ball;

void draw_ball(Ball ball);

void init_ball(Ball *ball, float x, float y, float rad, int num_segments, float mass);

void update_ball_pos(Ball *ball, GLFWwindow *window);

#endif // BALL_H