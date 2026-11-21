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

// - Light Calculation Functions -
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    // For 0 value
    if (length(light.direction) == 0.0 || light.diffuse == vec3(0.0)) return vec3(0.0);
    
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    return (ambient + diffuse + specular);
}
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 FragPosition, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - FragPosition);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - FragPosition);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
// -------------------------------


void main()
{
    /*
    //// Determine the colour of just the texture
    //vec3 textureColour = texture(texture1, TexCoord).rgb;
    //// Add in the vertex colour and material colour
    //vec3 unlitColour = textureColour * VertexColour.rgb * material.colour;

    // Ambient "Light"
    vec3 ambientLight = texture(material.diffuse, TexCoord).rgb  * VertexColour.rgb * light.ambient;

    // diffuseColour = diffuseTexture * diffuseValue
    // diffuseColour = diffuseColour * VertexColour

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
    //FragColor = vec4(ambientLight), 1.0);
    //FragColor = (ambientLight + diffuseLight) * unlitColour;

    //FragColor = vec4(texture(material.specular, TexCoord).rgb, 1.0);
    */

    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDirection = normalize(view.position - FragPosition);
    vec3 lightingResult = vec3(0);

    // phase 1: Directional lighting
    for(int i = 0; i < NUMBER_OF_DIRECTIONAL_LIGHTS; i++)
        lightingResult += CalculateDirectionalLight(directionalLights[i], norm, viewDirection);
    // phase 2: Point lights
    for(int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++)
        lightingResult += CalculatePointLight(pointLights[i], norm, FragPosition, viewDirection);
    // phase 3: Spot light // NUMBER_OF_SPOT_LIGHTS
    //result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

    FragColor = vec4(lightingResult, 1.0);
    //FragColor = vec4(norm, 1.0f);
}    