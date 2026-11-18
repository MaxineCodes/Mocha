#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;
in vec4 VertexColour;

struct Material {
    sampler2D diffuse;
    vec3 colour;
    vec3 ambient;
    sampler2D specular;
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

uniform vec3 viewPosition;


void main()
{
    //// Determine the colour of just the texture
    //vec3 textureColour = texture(texture1, TexCoord).rgb;
    //// Add in the vertex colour and material colour
    //vec3 unlitColour = textureColour * VertexColour.rgb * material.colour;

    // Ambient "Light"
    vec3 ambientLight = texture(material.diffuse, TexCoord).rgb * light.ambient;

    // Diffuse Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * (texture(material.diffuse, TexCoord).rgb * VertexColour.rgb); // we assume VertexColour = diffuse map

    // Specular Lighting
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specularLight = light.specular * (spec * material.specular);
    vec3 specularLight = light.specular * spec * vec3(texture(material.specular, TexCoord));


    // Output
    FragColor = vec4((ambientLight + diffuseLight + specularLight), 1.0);
    //FragColor = (ambientLight + diffuseLight) * unlitColour;
}