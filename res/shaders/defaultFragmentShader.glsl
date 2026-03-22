#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 VertexColour;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    float scale = 50.0;
    vec2 grid = floor(TexCoord * scale);
    float checker = mod(grid.x + grid.y, 2.0);

    vec3 colorA = vec3(1.0, 0.0, 1.0); // Magenta
    vec3 colorB = vec3(0.0, 0.0, 0.0); // Black
    FragColor = vec4(mix(colorA, colorB, checker), 1.0);
}