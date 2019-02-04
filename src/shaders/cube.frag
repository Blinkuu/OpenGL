#version 330

#define NR_POINT_LIGHTS 3

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
    vec3 direction;
    vec3 position;

    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;

    vec3 diffuse;
    vec3 specular;
};

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform DirLight u_DirLight;
uniform PointLight u_PointLights[NR_POINT_LIGHTS];
uniform SpotLight u_SpotLight;
uniform bool u_FlashlightStatus;
uniform vec3 u_CameraPosition;
uniform Material u_Material;

in vec2 v_TexCoords;
in vec3 v_NormalVec;
in vec3 v_FragmentPos;

out vec4 out_Color;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
	
	vec3 norm = normalize(v_NormalVec);
    vec3 viewDir = normalize(u_CameraPosition - v_FragmentPos);

	// Directional Light
	vec3 resultLight = CalcDirLight(u_DirLight, norm, viewDir);
	
	// Point lights
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
		resultLight += CalcPointLight(u_PointLights[i], norm, v_FragmentPos, viewDir);

	// Spotlight
	if(u_FlashlightStatus)
        resultLight += CalcSpotLight(u_SpotLight, norm, v_FragmentPos, viewDir);

	out_Color = vec4(resultLight, 1.0f);
}


vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	
	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	
	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0f), u_Material.shininess);
	
	// Calculate light
	vec3 ambient = light.ambient * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));
	
	return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
	vec3 lightDir = normalize(light.position - fragPos);

	// Diffuse
	float diff = max(dot(normal, lightDir), 0.0f);
	
	// Specular
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	
	// Attenuation
	float dist = length(light.position - fragPos);
	float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);

	// Calculate light
	vec3 ambient  = light.ambient  * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
    // Diffuse
    float diff = max(dot(normal, lightDir), 0.0f);

    // Specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

    // Attenuation
    float dist = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * dist + light.quadratic * dist * dist);
    // Calculate light
    vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoords));
    diffuse *= intensity * attenuation;
    specular *= intensity * attenuation;

    return diffuse + specular;
}