#ifndef MESH_H
#define MESH_H

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

class Mesh {
  private:
    GLfloat* vertices;
    GLuint verticesSize;
    GLuint* indices;
    GLuint indicesSize;
    Texture* tex0ptr = nullptr;
    
    VertexArray vao;
    VertexBuffer* VBOptr;
    IndexBuffer* IBOptr;

  public:
    Mesh(GLfloat* inVertices, const GLsizeiptr inVerticesSize, GLuint* inIndices, const GLsizeiptr inIndicesSize, const GLuint numAttributes, const GLuint numDimensions, const GLuint numColorComponents, const GLuint numTextureCoords, const GLuint numNormalDimensions, const char* texFileName, Shader& shader);

    void Draw(Shader& shader);
    void Delete();
};

#endif