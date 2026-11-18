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
    sampler2D diffuse;
    vec3 colour;
    vec3 ambient;
    sampler2D specular;
    float shininess;
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
uniform DirectionalLight directionalLight;

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
uniform PointLight pointLight;

struct SpotLight 
{
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;
// ----------------------------


void main()
{
    //// Determine the colour of just the texture
    //vec3 textureColour = texture(texture1, TexCoord).rgb;
    //// Add in the vertex colour and material colour
    //vec3 unlitColour = textureColour * VertexColour.rgb * material.colour;

    // Ambient "Light"
    vec3 ambientLight = texture(material.diffuse, TexCoord).rgb  * VertexColour.rgb * light.ambient;

    // Diffuse Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * (texture(material.diffuse, TexCoord).rgb * VertexColour.rgb); // we assume VertexColour = diffuse map

    // Specular Lighting
    vec3 viewDir = normalize(view.position - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specularLight = light.specular * (spec * material.specular);
    vec3 specularLight = light.specular * spec * vec3(texture(material.specular, TexCoord));


    // Output
    FragColor = vec4((ambientLight + diffuseLight + specularLight), 1.0);
    //FragColor = (ambientLight + diffuseLight) * unlitColour;
}