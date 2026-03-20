#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    float scale = 50.0;
    vec2 grid = floor(TexCoord * scale);
    float checker = mod(grid.x + grid.y, 2.0);

    vec3 colorA = vec3(1.0, 0.5, 0.0); // orange
    vec3 colorB = vec3(0.2, 0.2, 0.8); // blue
    FragColor = vec4(mix(colorA, colorB, checker), 1.0);
}