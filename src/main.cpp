#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>



// Window resolution macros
#define RESOLUTION_X 800
#define RESOLUTION_Y 800



// Define vertices and indices for leg
GLfloat legVertices[] = {
  // 0-3, foot bottom
  -0.75f, 0.0f,  0.75f,     1.0f, 0.0f, 0.0f,     0.0f, 0.0f,
  -0.25f, 0.0f,  0.75f,     1.0f, 0.0f, 0.0f,     0.5f, 0.0f,
  -0.25f, 0.0f, -0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 1.0f,
  -0.75f, 0.0f, -0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,

  // 4-5, foot front
  -0.25f, 0.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 1.0f,
  -0.75f, 0.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,

  // 6-7, foot back
  -0.75f, 0.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 0.5f,
  -0.25f, 0.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 0.5f,

  // 8-9, foot left
  -0.25f, 0.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 1.0f,
  -0.25f, 0.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 0.5f,

  // 10-11, foot right
  -0.75f, 0.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 1.0f,
  -0.75f, 0.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 0.5f,

  // 12-13, leg front
  -0.25f, 2.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.5f, 3.0f,
  -0.75f, 2.5f,  0.25f,     1.0f, 0.0f, 0.0f,     0.0f, 3.0f,

  // 14-15, leg back
  -0.75f, 2.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.0f, -1.5f,
  -0.25f, 2.5f, -0.25f,     1.0f, 0.0f, 0.0f,     0.5f, -1.5f,

  // 16-17, leg left
  -0.25f, 2.5f, -0.25f,     1.0f, 0.0f, 0.0f,     -2.0f, 1.0f,
  -0.25f, 2.5f,  0.25f,     1.0f, 0.0f, 0.0f,     -2.0f, 0.5f,

  // 18-19, leg right
  -0.75f, 2.5f, -0.25f,     1.0f, 0.0f, 0.0f,      2.5f, 1.0f,
  -0.75f, 2.5f,  0.25f,     1.0f, 0.0f, 0.0f,      2.5f, 0.5f
};

GLuint legIndices[] = {
  // foot
   0,  1,  2,  2,  3,  0,
   0,  1,  4,  4,  5,  0,
   2,  3,  6,  6,  7,  2,
   1,  2,  8,  8,  9,  1,
   0,  3, 10, 10, 11,  0,
  // leg
   5,  4, 12, 12, 13,  5,
   7,  6, 14, 14, 15,  7,
   9,  8, 16, 16, 17,  9,
  11, 10, 18, 18, 19, 11
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

  // Create leg mesh
  Mesh legMesh(legVertices, sizeof(legVertices), legIndices,
    sizeof(legIndices), 3, 3, 2, 0);
  
  // Load metal image into OpenGL texture
  std::string metalTexFilePath = RESOURCES_PATH "textures/metal.png";
  Texture metalTex(metalTexFilePath, GL_TEXTURE_2D, 0, GL_RGBA);
  // Apply texture to tex0 uniform in shader
  metalTex.TexUnit(objectShader, "tex0", 0);
  
  Camera camera(RESOLUTION_X, RESOLUTION_Y, glm::vec3(0.0f, 0.5f, 2.0f));




  glEnable(GL_DEPTH_TEST);

  // Main program loop
  while (!glfwWindowShouldClose(window)) {
    // Clear window to black
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    objectShader.Activate();

    camera.Inputs(window);
    camera.UpdateMatrix(45.0f, RESOLUTION_X / (float)RESOLUTION_Y, 0.1f, 100.0f);
    camera.SetMatrixUni(objectShader, "camMatrix");

    

    /* --------------
      DRAW CODE HERE
       -------------- */

    // Bind metal texture for object
    metalTex.Bind();

    // Draw object mesh with object shader
    legMesh.Draw(objectShader);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }



  // Cleanup OpenGL objects from memory
  objectShader.Delete();
  legMesh.Delete();

  // Cleanup GLFW window object
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}