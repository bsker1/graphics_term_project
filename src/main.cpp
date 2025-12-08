#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"



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

  // Create and bind triangle VAO
  VertexArray triangleVAO;
  triangleVAO.Bind();

  // Create vertex and index buffers for triangle, load vertices and indices to currently bound VAO
  VertexBuffer triangleVBO(triangleVertices, sizeof(triangleVertices));
  IndexBuffer triangleIBO(triangleIndices, sizeof(triangleIndices));

  // Apply layout of VBO to VAO
  triangleVAO.LinkAttrib(triangleVBO, 0, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)0);
  triangleVAO.LinkAttrib(triangleVBO, 1, 3, GL_FLOAT, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));

  // Unbind OpenGL objects before program loop
  triangleVAO.Unbind();
  triangleVBO.Unbind();
  triangleIBO.Unbind();



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

    // Bind triangle VAO
    triangleVAO.Bind();

    // Draw triangle
    glDrawElements(GL_TRIANGLES, sizeof(triangleIndices) / sizeof(GLuint), GL_UNSIGNED_INT, 0);

    

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }



  // Cleanup OpenGL objects from memory
  triangleVAO.Delete();
  triangleVBO.Delete();
  triangleIBO.Delete();
  triangleShader.Delete();

  // Cleanup GLFW window object
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}