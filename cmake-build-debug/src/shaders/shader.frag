#version 330 core

in vec4 vertexColor;
in vec2 textureCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 fragColor;

void main() {

	fragColor = mix(texture(texture1, textureCoords), texture(texture2, textureCoords), 0.5f);
}
