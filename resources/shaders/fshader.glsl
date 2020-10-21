#version 330

layout(location = 0, index = 0) out vec4 fragColor;
in vec4 color;

void main( void )
{
    fragColor = color;
}
