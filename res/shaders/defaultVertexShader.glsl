#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec4 aColour;

out vec3 FragPosition;
out vec3 Normal;
out vec2 TexCoord;
out vec4 VertexColour;

uniform mat4 transform;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // Out
    FragPosition = vec3(model * vec4(aPos, 1.0));
    Normal = aNormal;
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
    VertexColour = aColour;
}