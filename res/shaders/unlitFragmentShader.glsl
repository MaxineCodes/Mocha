#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 VertexColour;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform vec3 materialColour;

void main()
{
    vec4 sampled = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.0);
    FragColor = sampled * vec4(materialColour, 1.0) * VertexColour;
}