#version 330 core

struct Material {
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
};

in vec2 v_TexCoords;

uniform Material u_Material;

out vec4 FragColor;

void main() {
    FragColor = texture(u_Material.texture_diffuse1, v_TexCoords);
}
