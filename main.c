#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <stdio.h>
#include "ball.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        printf("clicked");
        fflush(stdout);
}

int main(void)
{
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
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

    float origin_x = WINDOW_WIDTH / 2, origin_y = WINDOW_HEIGHT / 2;
    float x = origin_x, y = origin_y;
    float radius = 10;

    Ball b;
    init_ball(&b, x, y, radius, 360, 10);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0, 0.5, 0.5);

        update_ball_pos(&b, window);
        draw_ball(b);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}