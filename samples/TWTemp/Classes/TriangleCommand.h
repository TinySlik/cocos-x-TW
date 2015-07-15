//
//  TriangleCommand.h
//  MyCommand
//
//  Created by Elvis on 14-2-5.
//
//

#ifndef __MyCommand__TriangleCommand__
#define __MyCommand__TriangleCommand__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class TriangleCommand : public CustomCommand
{
public:
    TriangleCommand();
    
    void init(int globalOrder,GLProgram* shader,Vec3* vertices,Color4F* colors,GLuint* indices,int indexCount,const Mat4& mv);
    
private:
    
    void useMaterial();
    void onDraw();
    
    Color4F* _squareColors;
    Vec3* _noMVPVertices;
    GLuint* _indices;
    int _vertexCount;
    Mat4 _mv;
    GLProgram* _shader;
};


#endif /* defined(__MyCommand__TriangleCommand__) */
