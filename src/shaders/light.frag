#version 330

struct Light {
	vec3 color;
};

uniform Light light;

out vec4 out_Color;

void main() {
	out_Color = vec4(light.color, 1.0f);
}
