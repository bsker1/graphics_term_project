#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Mesh.h"
#include "Shader.h"



// Window resolution macros
#define RESOLUTION_X 800
#define RESOLUTION_Y 800



// Define vertices and indices for triangle
GLfloat triangleVertices[] = {
  -0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,
   0.5f, -0.5f, 0.0f,     1.0f, 1.0f, 1.0f,
   0.0f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f
};

GLuint triangleIndices[] = {
  0, 1, 2
};



int main() {
  // Create GLFW windo object
  GLFWwindow* window;

  // Initialize GLFW
  if (!glfwInit()) {
    return -1;
  }

  // Configure GLFW for OpenGL 3.3 core
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "OpenGL Tutorial", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLAD 
  gladLoadGL();

  // Define OpenGl viewport to size of window
  glViewport(0, 0, RESOLUTION_X, RESOLUTION_Y);



  /* ---------------
    SETUP CODE HERE
     --------------- */
  
  // Generate shader program from triangle shader files
  std::string triangleVertPath = RESOURCES_PATH "shaders/triangle.vert";
  std::string triangleFragPath = RESOURCES_PATH "shaders/triangle.frag";
  Shader triangleShader(triangleVertPath, triangleFragPath);

  // Create triangle mesh
  Mesh triangleMesh(triangleVertices, sizeof(triangleVertices), triangleIndices, sizeof(triangleIndices), 2, 3, 3, 0, 0);



  // Main program loop
  while (!glfwWindowShouldClose(window)) {
    // Clear window to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    

    /* --------------
      DRAW CODE HERE
       -------------- */

    // Select triangle shader
    triangleShader.Activate();

    // Draw triangle mesh
    triangleMesh.Draw();

    

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }



  // Cleanup OpenGL objects from memory
  triangleShader.Delete();
  triangleMesh.Delete();

  // Cleanup GLFW window object
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}