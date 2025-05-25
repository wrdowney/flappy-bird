#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

#define LINE_WIDTH 2
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

/*
Draws a circle by repeatedly drawing line segments between two points which are 
lie along the edge of the circle.
*/
void drawCircle(float x, float y, float rad, int numSegments)
{
    float theta = (M_PI * 2) / (float)numSegments;
    float tangentialFactor = tanf(theta), radialFactor = cosf(theta);
    float dx = rad, dy = 0;

    glLineWidth(LINE_WIDTH);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++)
    {
        glVertex2f(dx + x, dy + y);

        float tx = -dy;
        float ty = dx;

        dx += tx * tangentialFactor;
        dy += ty * tangentialFactor;

        dx *= radialFactor;
        dy *= radialFactor;
    }
    glEnd();
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

    float dy = 0, velocity = 0.0, acceleration = 9.8;

    glfwMakeContextCurrent(window);

    // Set up orthographic projection to match window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    double lastTimestamp = 0.0;

    float originX = WINDOW_WIDTH / 2, originY = WINDOW_HEIGHT / 2;
    float x = originX, y = originY;

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0.0, 0.5, 0.5);

        if (y > 7) {

            double currTimestamp = glfwGetTime();
            double dt = currTimestamp - lastTimestamp;
            lastTimestamp = currTimestamp;

            velocity += (acceleration * dt); // v = a * delta(t)
            dy -= (velocity * dt) * 10; // delta(y) = velocity * delta(t)
            y += dy;
        }

        if (y < 7) {
            y = 7;
        }

        drawCircle(x, y, 10, 360);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}