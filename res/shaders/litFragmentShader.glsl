#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 VertexColour;

uniform sampler2D texture1;
uniform sampler2D texture2;
  
uniform vec3 materialColour;
uniform vec3 lightColour;

void main()
{
    float ambientStrength = 0.1f;

    // Determine the colour of just the texture
    vec4 textureColour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.0);
    // Add in the vertex colour and material colour
    vec4 unlitColour = textureColour * VertexColour * vec4(materialColour, 1.0);
    // Add in the ambient factor
    vec4 ambientColour = unlitColour * ambientStrength;

    // Output
    FragColor = ambientColour;
}