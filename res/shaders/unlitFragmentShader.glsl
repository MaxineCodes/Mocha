#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;
in vec4 VertexColour;

// Defines 
// 16 + 8 + 8 = 32 lights total
#define NUMBER_OF_POINT_LIGHTS 16
#define NUMBER_OF_SPOT_LIGHTS 8
#define NUMBER_OF_DIRECTIONAL_LIGHTS 8

// --------- Material ---------
struct Material 
{
    vec3 ambient;
    float shininess;

    sampler2D diffuse;          vec3 diffuseValue;
    sampler2D specular;         vec3 specularValue;
    sampler2D emission;         vec3 emissionValue;
}; 
uniform Material material;
// ----------------------------

// ---------- Camera ----------
uniform vec3 viewPosition;
struct View 
{
    vec3 position;
};
uniform View view;
// ----------------------------

void main()
{
    vec4 diffuseColour = texture(material.diffuse, TexCoord);
    vec4 unlitColour = diffuseColour * VertexColour * vec4(material.diffuseValue, 1.0f);
    FragColor = unlitColour;
}