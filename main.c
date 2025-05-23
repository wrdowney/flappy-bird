#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h> // For exit

// OpenGL headers (if you plan to use OpenGL for rendering, which is common with GLFW)
// On Linux, these are often found in /usr/include/GL
// You might need to install development packages like libglu1-mesa-dev and mesa-common-dev
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void error_callback(int error, const char* description) {
    fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        // Handle jump
        printf("Space pressed!\n");
    }
}

int main(int argc, char* args[]) {
    GLFWwindow* window = NULL;

    glfwSetErrorCallback(error_callback);

    // Initialize GLFW
    if (!glfwInit()) {
        printf("GLFW could not initialize!\n");
        return 1;
    }

    // Hint GLFW to use OpenGL 3.3 Core Profile (optional, but good practice)
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird with GLFW", NULL, NULL);
    if (window == NULL) {
        printf("Window could not be created!\n");
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    // Vsync (optional)
    glfwSwapInterval(1);

    // Game loop
    while (!glfwWindowShouldClose(window)) {
        // Handle events
        glfwPollEvents();

        // --- Game logic would go here ---


        // Clear screen (using OpenGL)
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black
        glClear(GL_COLOR_BUFFER_BIT);

        // --- Rendering would go here (using OpenGL) ---


        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Destroy window
    glfwDestroyWindow(window);

    // Terminate GLFW
    glfwTerminate();

    return 0;
}