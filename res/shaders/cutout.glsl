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
struct View
{
    vec3 position;
};
uniform View view;
// ----------------------------

// ---------- Lights ----------
struct Light // TEMPORARY LIGHT FOR TESTING
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLights[NUMBER_OF_DIRECTIONAL_LIGHTS];

struct PointLight
{
    vec3 position;
    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];

struct SpotLight
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLights[NUMBER_OF_SPOT_LIGHTS];
// ----------------------------

void main()
{
    vec4 texColor = texture(material.diffuse, TexCoord);
    if(texColor.a < 0.1f) discard; // Discard fragment by alpha cutoff value = 0.1f
    FragColor = texColor;
}