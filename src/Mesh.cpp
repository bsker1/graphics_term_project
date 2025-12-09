#include "Mesh.h"

Mesh::Mesh(GLfloat* inVertices, const GLsizeiptr inVerticesSize,
  GLuint* inIndices, const GLsizeiptr inIndicesSize,
  const GLuint numDimensions, const GLuint numColorComponents,
  const GLuint numTextureCoords, const GLuint numNormalDimensions) {
    // Assign vertex/index arrays to passed pointers
    vertices = inVertices;
    verticesSize = inVerticesSize;
    indices = inIndices;
    indicesSize = inIndicesSize;
    
    // Bind VAO of mesh
    vao.Bind();

    // Create vertex and index buffers for triangle, load vertices and indices to currently bound VAO
    VertexBuffer vbo(vertices, verticesSize);
    IndexBuffer ibo(indices, indicesSize);
    // Store location of vbo/ibo
    VBOptr = &vbo;
    IBOptr = &ibo;

    // Calculate stride for linking attributes
    GLuint stride = (numDimensions + numColorComponents + numTextureCoords + numNormalDimensions) * sizeof(GLfloat);

    // Link attributes in VAO with provided layout
    vao.LinkAttrib(vbo, 0, numDimensions, GL_FLOAT, stride, (void*)0);
    // Link remaining attributes if provided
    GLuint offset = 0;
    if (numColorComponents) {
      offset += numDimensions;
      vao.LinkAttrib(vbo, 1, numColorComponents, GL_FLOAT, stride, (void*)(offset * sizeof(GLfloat)));
    }
    if (numTextureCoords) {
      offset += numColorComponents;
      vao.LinkAttrib(vbo, 2, numTextureCoords, GL_FLOAT, stride, (void*)(offset * sizeof(GLfloat)));
    }
    if (numNormalDimensions) {
      offset += numTextureCoords;
      vao.LinkAttrib(vbo, 3, numNormalDimensions, GL_FLOAT, stride, (void*)(offset * sizeof(GLfloat)));
    }

    // Unbind OpenGL objects before program loop
    vao.Unbind();
    vbo.Unbind();
    ibo.Unbind();
}

void Mesh::Draw(Shader& shader) {
  shader.Activate();
  vao.Bind();
  glDrawElements(GL_TRIANGLES, indicesSize / sizeof(GLuint), GL_UNSIGNED_INT, 0);
}

void Mesh::Delete() {
  vao.Delete();
  glDeleteBuffers(1, VBOptr->GetIDptr());
  glDeleteBuffers(1, IBOptr->GetIDptr());
}