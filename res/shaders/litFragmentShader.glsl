#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPosition;
in vec4 VertexColour;

uniform sampler2D texture1;
uniform sampler2D texture2;
  
uniform vec3 materialColour;
uniform vec3 lightColour;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

void main()
{
    //float ambientStrength = 0.1f;
    vec3 ambientColour = vec3(0.1, 0.1, 0.1);
    float specularStrength = 0.5;

    // Determine the colour of just the texture
    vec4 textureColour = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.0);
    // Add in the vertex colour and material colour
    vec4 unlitColour = textureColour * VertexColour * vec4(materialColour, 1.0);

    // Ambient "Light"
    vec4 ambientLight = vec4(ambientColour, 1.0);

    // Diffuse Lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuseLight = vec4(diff * lightColour, 1.0);

    // Specular Lighting
    vec3 viewDir = normalize(viewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specularLight = vec4(specularStrength * spec * lightColour, 1.0);


    // Output
    FragColor = (ambientLight + diffuseLight + specularLight) * unlitColour;
    //FragColor = (ambientLight + diffuseLight) * unlitColour;
}