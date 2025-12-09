#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Mesh.h"



// Window resolution macros
#define RESOLUTION_X 800
#define RESOLUTION_Y 800



// Define vertices and indices for object
GLfloat objectVertices[] = {
  -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
   0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,     1.0f, 0.0f,
   0.5f,  0.5f, 0.0f,     0.0f, 0.0f, 1.0f,     1.0f, 1.0f,
  -0.5f,  0.5f, 0.0f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f
};

GLuint objectIndices[] = {
  0, 1, 2,
  2, 3, 0
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
  
  // Generate shader program from object shader files
  std::string objectVertPath = RESOURCES_PATH "shaders/object.vert";
  std::string objectFragPath = RESOURCES_PATH "shaders/object.frag";
  Shader objectShader(objectVertPath, objectFragPath);

  // Create object mesh
  Mesh objectMesh(objectVertices, sizeof(objectVertices), objectIndices,
    sizeof(objectIndices), 3, 3, 2, 0, "metal.png", objectShader);



  // Main program loop
  while (!glfwWindowShouldClose(window)) {
    // Clear window to black
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    

    /* --------------
      DRAW CODE HERE
       -------------- */

    // Draw object mesh with object shader
    objectMesh.Draw(objectShader);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }



  // Cleanup OpenGL objects from memory
  objectShader.Delete();
  objectMesh.Delete();

  // Cleanup GLFW window object
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}