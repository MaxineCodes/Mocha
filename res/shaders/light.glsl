#version 330 core
out vec4 FragColor;

uniform vec3 colour;

void main()
{
    if(colour == vec3(0,0,0))
    {
        FragColor = vec4(1.0); // Full White
    }
    else
    {
        FragColor = vec4(colour, 1.0);
    }
}