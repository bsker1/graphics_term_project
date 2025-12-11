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
  -0.25f, 0.0f,  0.50f,     1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
   0.25f, 0.0f,  0.50f,     1.0f, 1.0f, 1.0f,     0.5f, 0.0f,
   0.25f, 0.0f, -0.50f,     1.0f, 1.0f, 1.0f,     0.5f, 1.0f,
  -0.25f, 0.0f, -0.50f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,

  // 4-5, foot front
   0.25f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.5f, 1.0f,
  -0.25f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.0f, 1.0f,

  // 6-7, foot back
  -0.25f, 0.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.0f, 0.5f,
   0.25f, 0.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.5f, 0.5f,

  // 8-9, foot left
   0.25f, 0.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.0f, 1.0f,
   0.25f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.0f, 0.5f,

  // 10-11, foot right
  -0.25f, 0.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.5f, 1.0f,
  -0.25f, 0.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.5f, 0.5f,

  // 12-13, leg front
   0.25f, 2.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.5f, 3.0f,
  -0.25f, 2.5f,  0.0f,      1.0f, 1.0f, 1.0f,     0.0f, 3.0f,

  // 14-15, leg back
  -0.25f, 2.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.0f, -1.5f,
   0.25f, 2.5f, -0.50f,     1.0f, 1.0f, 1.0f,     0.5f, -1.5f,

  // 16-17, leg left
   0.25f, 2.5f, -0.50f,     1.0f, 1.0f, 1.0f,     -2.0f, 1.0f,
   0.25f, 2.5f,  0.0f,      1.0f, 1.0f, 1.0f,     -2.0f, 0.5f,

  // 18-19, leg right
  -0.25f, 2.5f, -0.50f,     1.0f, 1.0f, 1.0f,      2.5f, 1.0f,
  -0.25f, 2.5f,  0.0f,      1.0f, 1.0f, 1.0f,      2.5f, 0.5f
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



// Define vertices and indices for torso
GLfloat torsoVertices[] = {
  // 0-3, bottom
  -1.0f, 0.0f,  0.5f,     1.0f, 1.0f, 1.0f,      0.0f,  0.0f,
   1.0f, 0.0f,  0.5f,     1.0f, 1.0f, 1.0f,      2.0f,  0.0f,
   1.0f, 0.0f, -0.5f,     1.0f, 1.0f, 1.0f,      2.0f,  1.0f,
  -1.0f, 0.0f, -0.5f,     1.0f, 1.0f, 1.0f,      0.0f,  1.0f,

  // 4-5, front
   1.0f, 2.5f,  0.5f,     1.0f, 1.0f, 1.0f,      2.0f,  2.5f,
  -1.0f, 2.5f,  0.5f,     1.0f, 1.0f, 1.0f,      0.0f,  2.5f,

  // 6-7, back
  -1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,      0.0f, -1.0f,
   1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,      2.0f, -1.0f,

  // 8-9, left
   1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,     -0.5f,  1.5f,
   1.0f, 2.5f,  0.5f,     1.0f, 1.0f, 1.0f,     -0.5f,  0.5f,

  // 10-11, right
  -1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,      2.5f,  1.5f,
  -1.0f, 2.5f,  0.5f,     1.0f, 1.0f, 1.0f,      2.5f,  0.5f,

  // 12-13 top
   1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,      2.0f,  3.5f,
  -1.0f, 2.5f, -0.5f,     1.0f, 1.0f, 1.0f,      0.0f,  3.5f
};

GLuint torsoIndices[] = {
  0, 1,  2,  2,  3, 0,
  0, 1,  4,  4,  5, 0,
  2, 3,  6,  6,  7, 2,
  1, 2,  8,  8,  9, 1,
  0, 3, 10, 10, 11, 0,
  5, 4, 12, 12, 13, 5
};



// Define vertices and indices for head
GLfloat headVertices[] = {
  // 0-3, bottom
  -0.75f, 0.0f,  0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
   0.75f, 0.0f,  0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 0.0f,
   0.75f, 0.0f, -0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 1.5f,
  -0.75f, 0.0f, -0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 1.5f,

  // 4-5, front
   0.75f, 1.5f,  0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 1.5f,
  -0.75f, 1.5f,  0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 1.5f,

  // 6-7, back
  -0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 0.0f,
   0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 0.0f,

  // 8-9, left
   0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 1.5f,
   0.75f, 1.5f,  0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 0.0f,

  // 10-11, right
  -0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 1.5f,
  -0.75f, 1.5f,  0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 0.0f,

  // 12-13, top
   0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     1.5f, 3.0f,
  -0.75f, 1.5f, -0.75f,      1.0f, 1.0f, 1.0f,     0.0f, 3.0f
};

GLuint headIndices[] = {
  0, 1,  2,  2,  3, 0,
  0, 1,  4,  4,  5, 0,
  2, 3,  6,  6,  7, 2,
  1, 2,  8,  8,  9, 1,
  0, 3, 10, 10, 11, 0,
  5, 4, 12, 12, 13, 5
};


// Define vertices and indices for arm
GLfloat armVertices[] = {
  // 0-3, bottom
  -0.25f, 0.0f,  0.25f,      1.0f, 1.0f, 1.0f,      0.0f,   0.0f,
   0.25f, 0.0f,  0.25f,      1.0f, 1.0f, 1.0f,      0.5f,   0.0f,
   0.25f, 0.0f, -0.25f,      1.0f, 1.0f, 1.0f,      0.5f,   0.5f,
  -0.25f, 0.0f, -0.25f,      1.0f, 1.0f, 1.0f,      0.0f,   0.5f,

  // 4-5, arm front
   0.25f, 2.0f,  0.25f,      1.0f, 1.0f, 1.0f,      0.5f,   1.0f,
  -0.25f, 2.0f,  0.25f,      1.0f, 1.0f, 1.0f,      0.0f,   1.0f,

  // 6-7, arm back
  -0.25f, 2.0f, -0.25f,      1.0f, 1.0f, 1.0f,      0.0f,  -2.5f,
   0.25f, 2.0f, -0.25f,      1.0f, 1.0f, 1.0f,      0.5f,  -2.5f,
  
  // 8-9, arm left
   0.25f, 2.0f, -0.25f,      1.0f, 1.0f, 1.0f,     -2.5f,   0.5f,
   0.25f, 2.0f,  0.25f,      1.0f, 1.0f, 1.0f,     -2.5f,  -0.5f,
  
  // 10-11, arm right
  -0.25f, 2.0f, -0.25f,      1.0f, 1.0f, 1.0f,      3.0f,   0.5f,
  -0.25f, 2.0f,  0.25f,      1.0f, 1.0f, 1.0f,      3.0f,   0.0f,

  // 12-13, shoulder bottom
   0.5f,  2.0f,  0.25f,      1.0f, 1.0f, 1.0f,      3.75f,  0.0f,
   0.5f,  2.0f, -0.25f,      1.0f, 1.0f, 1.0f,      3.75f,  0.5f,

  // 14-15, shoulder front
   0.5f,  2.5f,  0.25f,      1.0f, 1.0f, 1.0f,      3.75f,  0.5f,
  -0.25f, 2.5f,  0.25f,      1.0f, 1.0f, 1.0f,      3.0f,   0.5f,

  // 16-17, shoulder back
  -0.25f, 2.5f, -0.25f,      1.0f, 1.0f, 1.0f,      3.0f,   0.0f,
   0.5f,  2.5f, -0.25f,      1.0f, 1.0f, 1.0f,      3.75f,  0.0f,

  // 18-19, shoulder right
  -0.25f, 2.5f,  0.25f,      1.0f, 1.0f, 1.0f,      3.5f,   0.0f,
  -0.25f, 2.5f, -0.25f,      1.0f, 1.0f, 1.0f,      3.5f,   0.5f,

  // 20-21, shoulder top
   0.5f,  2.5f,  0.25f,      1.0f, 1.0f, 1.0f,      4.25f,  0.0f,
   0.5f,  2.5f, -0.25f,      1.0f, 1.0f, 1.0f,      4.25f,  0.5f
};

GLuint armIndices[] = {
   0,  1,  2,  2,  3,  0,
   0,  1,  4,  4,  5,  0,
   2,  3,  6,  6,  7,  2,
   1,  2,  8,  8,  9,  1,
   0,  3, 10, 10, 11,  0,
  10, 11, 12, 12, 13, 10,
  11, 12, 14, 14, 15, 11,
  13, 10, 16, 16, 17, 13,
  10, 11, 18, 18, 19, 10,
  19, 18, 20, 20, 21, 19
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

  // Load metal image into OpenGL texture
  std::string metalTexFilePath = RESOURCES_PATH "textures/metal.png";
  Texture metalTex(metalTexFilePath, GL_TEXTURE_2D, 0, GL_RGBA);
  // Apply texture to tex0 uniform in shader
  metalTex.TexUnit(objectShader, "tex0", 0);



  // Create meshes
  Mesh legMesh(legVertices, sizeof(legVertices), legIndices,
    sizeof(legIndices), 3, 3, 2, 0);
  Mesh torsoMesh(torsoVertices, sizeof(torsoVertices), torsoIndices,
    sizeof(torsoIndices), 3, 3, 2, 0);
  Mesh headMesh(headVertices, sizeof(headVertices), headIndices,
    sizeof(headIndices), 3, 3, 2, 0);
  Mesh armMesh(armVertices, sizeof(armVertices), armIndices,
    sizeof(armIndices), 3, 3, 2, 0);
  


  // Set scale of robot
  GLfloat robotScale = 0.2f;
  glm::vec3 robotScaleVec = glm::vec3(robotScale, robotScale, robotScale);
  
  // Set models for each robot geometry
  glm::mat4 legModelR = glm::mat4(1.0f);
  legModelR = glm::translate(legModelR, glm::vec3(-0.5f * robotScale, 0.0f * robotScale, 0.25f * robotScale));
  legModelR = glm::scale(legModelR, robotScaleVec);

  glm::mat4 legModelL = glm::mat4(1.0f);
  legModelL = glm::translate(legModelL, glm::vec3(0.5f * robotScale, 0.0f * robotScale, 0.25f * robotScale));
  legModelL = glm::scale(legModelL, robotScaleVec);

  glm::mat4 torsoModel = glm::mat4(1.0f);
  torsoModel = glm::translate(torsoModel, glm::vec3(0.0f * robotScale, 2.5f * robotScale, 0.0f * robotScale));
  torsoModel = glm::scale(torsoModel, robotScaleVec);

  glm::mat4 headModel = glm::mat4(1.0f);
  headModel = glm::translate(headModel, glm::vec3(0.0f * robotScale, 5.0f * robotScale, 0.0f * robotScale));
  headModel = glm::scale(headModel, robotScaleVec);

  glm::mat4 armModelR = glm::mat4(1.0f);
  armModelR = glm::translate(armModelR, glm::vec3(-1.5f * robotScale, 2.25f * robotScale, 0.0f * robotScale));
  armModelR = glm::scale(armModelR, robotScaleVec);

  glm::mat4 armModelL = glm::mat4(1.0f);
  armModelL = glm::rotate(armModelL, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  armModelL = glm::translate(armModelL, glm::vec3(-1.5f * robotScale, 2.25f * robotScale, 0.0f * robotScale));
  armModelL = glm::scale(armModelL, robotScaleVec);

  glm::mat4 antennaModel = glm::mat4(1.0f);
  GLfloat antennaScale = 0.4 * robotScale;
  glm::vec3 antennaScaleVec = glm::vec3(antennaScale, antennaScale, antennaScale);
  antennaModel = glm::rotate(antennaModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  antennaModel = glm::rotate(antennaModel, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  antennaModel = glm::translate(antennaModel, glm::vec3(-0.95f * robotScale, -7.0f * robotScale, 0.0f * robotScale));
  antennaModel = glm::scale(antennaModel, antennaScaleVec);


  
  Camera camera(RESOLUTION_X, RESOLUTION_Y, glm::vec3(0.0f, 1.0f, 2.0f));

  glEnable(GL_DEPTH_TEST);

  // Main program loop
  while (!glfwWindowShouldClose(window)) {
    // Clear window to black
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    camera.Inputs(window);
    camera.UpdateMatrix(70.0f, RESOLUTION_X / (float)RESOLUTION_Y, 0.1f, 100.0f);

    objectShader.Activate();
    camera.SetMatrixUni(objectShader, "camMatrix");

    

    /* --------------
      DRAW CODE HERE
       -------------- */

    // Bind metal texture for object
    metalTex.Bind();

    // Draw meshes
    legMesh.Draw(objectShader, legModelR);
    legMesh.Draw(objectShader, legModelL);
    torsoMesh.Draw(objectShader, torsoModel);
    headMesh.Draw(objectShader, headModel);
    armMesh.Draw(objectShader, armModelR);
    armMesh.Draw(objectShader, armModelL);
    armMesh.Draw(objectShader, antennaModel);

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }



  // Cleanup OpenGL objects from memory
  objectShader.Delete();
  legMesh.Delete();
  torsoMesh.Delete();
  headMesh.Delete();
  armMesh.Delete();

  // Cleanup GLFW window object
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}