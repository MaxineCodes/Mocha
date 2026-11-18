#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;
in vec4 VertexColour;

struct Material {
    vec3 colour;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 lightPosition;
uniform vec3 viewPosition;


void main()
{
    // Determine the colour of just the texture
    vec3 textureColour = texture(texture1, TexCoord).rgb;
    // Add in the vertex colour and material colour
    vec3 unlitColour = textureColour * VertexColour.rgb * material.colour;

    // Ambient "Light"
    vec3 ambientLight = material.ambient * light.ambient;

    // Diffuse Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = (diff * material.diffuse) * light.diffuse;

    // Specular Lighting
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * (spec * material.specular);


    // Output
    FragColor = vec4((ambientLight + diffuseLight + specularLight) * unlitColour, 1.0);
    //FragColor = (ambientLight + diffuseLight) * unlitColour;
}