#version 330

out vec4 FragColor;
in vec2 texCoord;
in vec3 normal;

uniform sampler2D ourTexture;
uniform vec4 color;

void main()
{
    vec3 lightDir = normalize(vec3(0.0, 2, 1.0));
    float diff = max(dot(normalize(normal), lightDir), 0.0);
    float ambient = 0.5;
    vec4 ambientTexture = texture(ourTexture, texCoord) * ambient;
    FragColor = (texture(ourTexture, texCoord) + color) * diff + ambientTexture;
}