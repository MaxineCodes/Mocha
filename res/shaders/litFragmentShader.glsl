#version 330 core
out vec4 FragColor;
  
uniform vec3 materialColour;
uniform vec3 lightColour;

void main()
{
    FragColor = vec4(lightColour * materialColour, 1.0);
}