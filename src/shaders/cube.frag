#version 330

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 v_NormalVec;
in vec3 v_FragmentPos;

uniform vec3 u_cameraPosition;
uniform Light light;
uniform Material material;

out vec4 out_Color;

void main() {
	// Ambient
	vec3 ambient = light.ambient * material.ambient;
	
	// Diffuse
	vec3 norm = normalize(v_NormalVec);
	vec3 lightDir = normalize(light.position - v_FragmentPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	// Specular
	vec3 viewDir = normalize(u_cameraPosition - v_FragmentPos);
	vec3 reflectDir = normalize(reflect(-lightDir, v_NormalVec)); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);  

	vec3 lightResult = ambient + diffuse + specular;
	out_Color = vec4(lightResult, 1.0f);
}
