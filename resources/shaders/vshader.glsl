#version 330

layout (location = 0) in vec4 vertex;
layout (location = 1) in vec4 vColor;
out vec4 color;

uniform mat4 mProjection;
uniform mat4 mCamera;
uniform mat4 mWorld;

void main(void)
{
    gl_PointSize = 12;
    gl_Position = mProjection * mCamera * mWorld * vertex;
    color = vColor;
}
