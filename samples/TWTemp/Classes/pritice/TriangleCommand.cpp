//
//  TriangleCommand.cpp
//  MyCommand
//
//  Created by Elvis on 14-2-5.
//
//

#include "TriangleCommand.h"
TriangleCommand::TriangleCommand()
{
    func=std::bind(&TriangleCommand::onDraw,this);
}

void TriangleCommand::init(int globalOrder,GLProgram* shader,Vec3* vertices,Color4F* colors,GLuint* indices,int indexCount,const Mat4& mv)
{
    _globalOrder=globalOrder;
    _shader=shader;
    _squareColors=colors;
    _noMVPVertices=vertices;
    _indices=indices;
    _vertexCount=indexCount;
    
    _mv=mv;
}

void TriangleCommand::useMaterial()
{
    _shader->use();
    _shader->setUniformsForBuiltins(_mv);
}

void TriangleCommand::onDraw()
{
    useMaterial();
    
    GL::enableVertexAttribs( GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR );
    
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, _noMVPVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, _squareColors);
    
    glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, _indices);
    
    CC_INCREMENT_GL_DRAWS(1);
}
