#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "vertices.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"

#include <iostream>



// Window resolution macros
#define RESOLUTION_X 800
#define RESOLUTION_Y 800



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
  Mesh topMesh(topVertices, sizeof(topVertices), topIndices,
    sizeof(topIndices), 3, 3, 2, 0);
  Mesh mouthMesh(mouthVertices, sizeof(mouthVertices), mouthIndices,
    sizeof(mouthIndices), 3, 3, 2, 0);
  Mesh eyeMesh(eyeVertices, sizeof(eyeVertices), eyeIndices,
    sizeof(eyeIndices), 3, 3, 2, 0);
  


  // Set scale of robot
  GLfloat robotScale = 0.2f;
  glm::vec3 robotScaleVec = glm::vec3(robotScale, robotScale, robotScale);
  GLfloat addonsScale = 0.4 * robotScale;
  glm::vec3 addonsScaleVec = glm::vec3(addonsScale, addonsScale, addonsScale);
  
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
  antennaModel = glm::rotate(antennaModel, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
  antennaModel = glm::rotate(antennaModel, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  antennaModel = glm::translate(antennaModel, glm::vec3(-0.95f * robotScale, -7.0f * robotScale, 0.0f * robotScale));
  antennaModel = glm::scale(antennaModel, addonsScaleVec);

  glm::mat4 topModel = glm::mat4(1.0f);
  topModel = glm::translate(topModel, glm::vec3(0.0f * robotScale, 6.5f * robotScale, 0.0f * robotScale));
  topModel = glm::scale(topModel, addonsScaleVec);

  glm::mat4 mouthModel = glm::mat4(1.0f);
  mouthModel = glm::rotate(mouthModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
  mouthModel = glm::translate(mouthModel, glm::vec3(5.25f * robotScale, -0.375f * robotScale, 0.75f * robotScale));
  mouthModel = glm::scale(mouthModel, addonsScaleVec);

  glm::mat4 eyeModelR = glm::mat4(1.0f);
  eyeModelR = glm::translate(eyeModelR, glm::vec3(0.375f * robotScale, 5.875f * robotScale, 0.75f * robotScale));
  eyeModelR = glm::scale(eyeModelR, addonsScaleVec);

  glm::mat4 eyeModelL = glm::mat4(1.0f);
  eyeModelL = glm::translate(eyeModelL, glm::vec3(-0.375f * robotScale, 5.875f * robotScale, 0.75f * robotScale));
  eyeModelL = glm::scale(eyeModelL, addonsScaleVec);


  
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
    topMesh.Draw(objectShader, topModel);
    mouthMesh.Draw(objectShader, mouthModel);
    eyeMesh.Draw(objectShader, eyeModelR);
    eyeMesh.Draw(objectShader, eyeModelL);

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