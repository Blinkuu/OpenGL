#version 460 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 tex;

uniform mat4 transform;

out vec4 vertexColor;
out vec2 textureCoords;

void main() {
	vertexColor = vec4(color, 1.0f);
	textureCoords = tex;
	gl_Position = transform * vec4(position, 1.0f);
}
