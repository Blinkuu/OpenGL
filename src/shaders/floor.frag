#version 330

struct Light {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

in vec2 v_TexCoords;
in vec3 v_NormalVec;
in vec3 v_FragmentPos;

uniform vec3 u_cameraPosition;
uniform Light light;
uniform Material material;

out vec4 out_Color;

void main() {
	// Distance to light source
	float distanceToSource = length(light.direction - v_FragmentPos);
	float attenuation = 1.0f/(light.constant + light.linear * distanceToSource +
			    light.quadratic * (distanceToSource * distanceToSource));

	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoords));
	
	// Diffuse
	vec3 norm = normalize(v_NormalVec);
	vec3 lightDir = normalize(light.direction - v_FragmentPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoords));

	// Specular
	vec3 viewDir = normalize(u_cameraPosition - v_FragmentPos);
	vec3 reflectDir = normalize(reflect(-lightDir, v_NormalVec)); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoords));  

	ambient = ambient * attenuation;
	diffuse = diffuse * attenuation;
	specular = specular * attenuation;
	vec3 lightResult = ambient + diffuse + specular;
	out_Color = vec4(lightResult, 1.0f);
}
