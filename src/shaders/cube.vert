#version 330
layout (location = 0) in vec3 l_Position;
layout (location = 1) in vec3 l_NormalVec;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 v_NormalVec;
out vec3 v_FragmentPos;

void main() {
	v_NormalVec = mat3(transpose(inverse(model))) * l_NormalVec;
	v_FragmentPos = vec3(model * vec4(l_Position, 1.0f));
	gl_Position = projection * view * model * vec4(l_Position, 1.0f);
}

