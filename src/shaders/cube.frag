#version 330

in vec3 v_NormalVec;
in vec3 v_FragmentPos;

uniform vec3 u_objectColor; 
uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;
uniform vec3 u_cameraPosition;

out vec4 out_Color;

void main() {
	float ambientStrength = 0.1f;
	float specularStrength = 0.5f;
	vec3 ambient = ambientStrength * u_lightColor;
	
	vec3 lightDir = normalize(u_lightPosition - v_FragmentPos);
	float diff = max(dot(v_NormalVec, lightDir), 0.0f);
	vec3 diffuse = diff * u_lightColor;

	vec3 viewDir = normalize(u_cameraPosition - v_FragmentPos);
	vec3 reflectDir = normalize(reflect(-lightDir, v_NormalVec)); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * u_lightColor;  

	vec3 lightResult = (ambient + diffuse + specular) * u_objectColor;

	out_Color = vec4(lightResult, 1.0f);
}
