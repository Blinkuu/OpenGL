#version 330 core
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 color;
layout (location = 1) in vec2 tex;

uniform mat4 model = mat4(1.0f);
uniform mat4 view = mat4(1.0f);
uniform mat4 projection = mat4(1.0f);

out vec4 vertexColor;
out vec2 textureCoords;

void main() {
	vertexColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	textureCoords = tex;
	gl_Position = projection * view * model * vec4(position, 1.0f);
}
