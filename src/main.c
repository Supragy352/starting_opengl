#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#define DYNAMIC_CLEAR

// Function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Shaders in a separate file
#include "shaders.h"

int main()
{
    glfwInit();

    // Tell GLFW that we want to use OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Initialise window and check
    // GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to initialize GLFW");
        glfwTerminate();
        return -1;
    }
    // Make the context the one to be rendered in the calling thread
    glfwMakeContextCurrent(window);
    // Resize viewport
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    // Define the VBO location
    unsigned int vertBuff;
    // Generate a vertex buffer ID and put it in vertBuff
    glGenBuffers(1, &vertBuff);
    // Bind the VBO to vertBuffer. The object type to be bound is passed. VBO are of type GL_ARRAY_BUFFER
    // More on https://registry.khronos.org/OpenGL-Refpages/gl4/html/glBindBuffer.xhtml
    glBindBuffer(GL_ARRAY_BUFFER, vertBuff);
    // Copy the user defined Vertex Data to the buffer memory.
    // Args(Which buffer type to copy to, what is the size, the actual data, how to manage and how frequently will it be used)
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // Reference to vert shader
    unsigned int vertexShader;
    // Get a vertex shader ID
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Attach the source to the object.
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Compile the shader
    glCompileShader(vertexShader);
    // Refrence to frag shader
    unsigned int fragmentShader;
    // Get a frag shader ID
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Attach the source to the object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compile the shader
    glCompileShader(fragmentShader);
    // Shader Program is all the shaders compiled and linked
    // Reference to the Shader Program
    unsigned int shaderProgram;
    // Create a program and assign reference to the int
    shaderProgram = glCreateProgram();
    // Attach shaders
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Link the shaders
    glLinkProgram(shaderProgram);
    // Errors can be checked using the glGetProgramiv() functions. These return error messages.
    // Use the recently compiled and linked shader prgram
    glUseProgram(shaderProgram);
    // Delete the vert and frag shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        // Bind vertex buffer object
        glBindBuffer(GL_ARRAY_BUFFER, vertBuff);
        // Specify vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // Issue draw call
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    #ifndef DYNAMIC_CLEAR
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
    #endif
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
