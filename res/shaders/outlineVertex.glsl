#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec4 aColour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float outlineThickness;

void main()
{
    vec3 inflated = aPos + aNormal * (outlineThickness / 100);
    gl_Position = projection * view * model * vec4(inflated, 1.0);
}