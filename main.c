#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "ball.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define MAX_BALLS 20

Ball *arr = NULL;
int num_balls = 0;
float radius = 10;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        if (num_balls < MAX_BALLS) {
            double x, y;
            glfwGetCursorPos(window, &x, &y);
            y = WINDOW_HEIGHT - y;

            init_ball(&arr[num_balls], num_balls, x, y, radius, 360, 10);
            num_balls++;
        }
    }
}

int main(void)
{
    GLFWwindow* window;

    // Allocate memory for balls
    arr = malloc(sizeof(Ball) * MAX_BALLS);
    if (!arr) {
        fprintf(stderr, "Failed to allocate memory for balls\n");
        return -1;
    }

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        free(arr);
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Set up orthographic projection to match window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0, 0.5, 0.5);
        for (int i = 0; i < num_balls; i++) {
            update_ball_pos(&arr[i], window);
            check_collisions(&arr[i], &arr); // pass arr, not &arr
            draw_ball(arr[i]);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    free(arr);
    return 0;
}