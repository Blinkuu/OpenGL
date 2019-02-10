#version 330 core

layout (location = 0) in vec3 l_Position;
layout (location = 1) in vec3 l_Normal;
layout (location = 2) in vec2 l_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_TexCoords;
out vec3 v_NormalVec;
out vec3 v_FragmentPos;

void main() {
    v_TexCoords = l_TexCoords;
    v_NormalVec = mat3(transpose(inverse(u_Model))) * l_Normal;
    v_FragmentPos = vec3(u_Model * vec4(l_Position, 1.0f));

	gl_Position = u_Projection * u_View * u_Model * vec4(l_Position, 1.0f);
}
