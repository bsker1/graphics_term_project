#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "glad/glad.h"

class IndexBuffer {
  private:
    GLuint id;
  
  public:
    IndexBuffer(const GLuint* indices, const GLsizeiptr size);

    GLuint* GetIDptr() { return &id; }

    void Bind();
    void Unbind();
    void Delete();
};

#endif