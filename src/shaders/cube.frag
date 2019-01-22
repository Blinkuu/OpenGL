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

struct Spotlight {
	vec3 direction;

	vec3 diffuse;

	float innerCutOff;
	float outerCutOff;
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
uniform Spotlight u_spotlight;
uniform Material material;

out vec4 out_Color;

void main() {
	
	vec3 norm = normalize(v_NormalVec);

	// Ambient
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, v_TexCoords));
	
	// Diffuse
	vec3 lightDir = normalize(light.direction - v_FragmentPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, v_TexCoords));

	// Specular
	vec3 viewDir = normalize(u_cameraPosition - v_FragmentPos);
	vec3 reflectDir = normalize(reflect(-lightDir, v_NormalVec)); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, v_TexCoords));  

	// Spotlight
	float theta = dot(viewDir, normalize(-u_spotlight.direction));
	float epsilon = u_spotlight.innerCutOff - u_spotlight.outerCutOff;
	float intensity = clamp((theta - u_spotlight.outerCutOff)/epsilon, 0.0f, 1.0f);	
vec3 spotlight = intensity * u_spotlight.diffuse * vec3(texture(material.diffuse, v_TexCoords));

	// Attenuation
	float distanceToSource = length(light.direction - v_FragmentPos);
	float distanceToObject = length(u_cameraPosition - v_FragmentPos);
	float attenuation = 1.0f/(light.constant + light.linear * distanceToSource +
			    light.quadratic * (distanceToSource * distanceToSource));
	float spotlightAttenuation = 1.0f/(u_spotlight.constant + u_spotlight.linear * distanceToObject + u_spotlight.quadratic * (distanceToObject * distanceToObject));

	ambient = ambient * attenuation;
	diffuse = diffuse * attenuation;
	specular = specular * attenuation;
	spotlight = spotlight * spotlightAttenuation;
	vec3 lightResult = ambient + diffuse + specular + spotlight;
	out_Color = vec4(lightResult, 1.0f);
}
