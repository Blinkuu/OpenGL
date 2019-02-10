#version 330 core

layout (location = 0) in vec3 l_Position;
layout (location = 1) in vec3 l_Normal;
layout (location = 2) in vec2 l_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoords;

void main() {
    v_TexCoords = l_TexCoords;
	gl_Position = u_Projection * u_View * u_Model * vec4(l_Position, 1.0f);
}
