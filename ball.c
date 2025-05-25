#include <stdio.h>
#include "ball.h"

/**
 * Check for collisions between a subject ball and any ball within an array of 
 * balls.
 * @param ball Subject ball to check for collisions.
 * @param ballArr Array of balls to check for collisions against subject ball.
 */
void check_collisions(Ball *ball, Ball **ballArr) {
    int len = sizeof(ballArr) / sizeof(ballArr[0]);
    printf("%d", len);
    for (int i = 0; i < len; i++) {
        // d < r1 + r2 indicates a collision between the two balls
        if (ball->id != ballArr[i]->id) { // ignore the same ball
            float dist = distance(*ball, *ballArr[i]);
            if (dist < (ball->rad + ballArr[i]->rad)) {
                printf("Collision!!!!\n");
                fflush(stdout);
            }
        }
    } 
}

/**
 * Draws the border of a circle by repeatedly drawing line segments between 
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

/**
 * Calculates the euclidean distances between the center of two balls.
 * @param b1 First ball to use in distance calculation. 
 * @param b2 Second ball to use in distance calculation.
 */
float distance(Ball b1, Ball b2) {
    // d = sqrt((x2 - x1)^2 + (y2 - y1)^2)
    float dx = b2.x - b1.x;
    float dy = b2.y - b1.y;

    return sqrtf((dx * dx) + (dy * dy));
}

/**
 * Initializes a given ball with the given properties.
 */
void init_ball(Ball *ball, int id, float x, float y, float rad, int num_segments, float mass) {
    ball->id = id;
    ball->x = x;
    ball->y = y;
    ball->rad = rad;
    ball->num_segments = num_segments;
    ball->velocity = 0.0;
    ball->mass = mass;
    ball->last_updated_timestamp = glfwGetTime();
}

/**
 * Update the position of a given ball for the current time.
 * @param ball Ball to update position. 
 * @param window GLFW window containing the ball.
 */
void update_ball_pos(Ball *ball, GLFWwindow *window) {    
    int win_width, win_height;
    double timestamp = glfwGetTime();
    double dt = timestamp - ball->last_updated_timestamp;
    ball->last_updated_timestamp = timestamp;

    glfwGetWindowSize(window, &win_width, &win_height);
    float lower_bound = ball->rad + LINE_WIDTH;
    float acceleration = GRAVITATIONAL_CONSTANT * ball->mass; // a = G * m

    if (ball->y < lower_bound) {
        ball->y = lower_bound;
        ball->velocity *= -1;
    } else {
        ball->velocity += (acceleration * dt); // v = v0 + (a * delta(t))
    }
    ball->y += ball->velocity * dt;
}