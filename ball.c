#include <stdio.h>
#include "ball.h"

/**
 * Draws the broder of a circle by repeatedly drawing line segments between 
 * two consecutive points which lie along the edge of the circle.
 * @param ball Ball which will be drawn inside the window.
 */
void draw_ball(Ball ball) 
{
    float theta = (M_PI * 2) / (float)ball.num_segments;
    float tangential_factor = tanf(theta), radial_factor = cosf(theta);
    float dx = ball.rad, dy = 0;
    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < ball.num_segments; i++)
    {
        glVertex2f(dx + ball.x, dy + ball.y);

        float tx = -dy;
        float ty = dx;

        dx += tx * tangential_factor;
        dy += ty * tangential_factor;

        dx *= radial_factor;
        dy *= radial_factor;
    }
    glEnd();
}

void init_ball(Ball *ball, float x, float y, float rad, int num_segments, float mass) {
    ball->x = x;
    ball->y = y;
    ball->rad = rad;
    ball->num_segments = num_segments;
    ball->velocity = 0.0;
    ball->mass = mass;
    ball->last_updated_timestamp = glfwGetTime();
}

void update_ball_pos(Ball *ball, GLFWwindow *window) {    
    int win_width, win_height;
    double timestamp = glfwGetTime();
    double dt = timestamp - ball->last_updated_timestamp;
    ball->last_updated_timestamp = timestamp;

    glfwGetWindowSize(window, &win_width, &win_height);
    float lower_bound = ball->rad + LINE_WIDTH;
    float acceleration = GRAVITATIONAL_CONSTANT * ball->mass;

    if (ball->y < lower_bound) {
        ball->y = lower_bound;
        ball->velocity *= -1;
    } else {
        ball->velocity += (acceleration * dt);
    }
    ball->y += ball->velocity * dt;
}