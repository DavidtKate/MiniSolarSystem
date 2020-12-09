#version 330 core

in vec3 v_position;
in vec2 v_texCoord;
in vec3 v_normal;

layout(location = 0) out vec4 finalColor;

uniform mat4 u_Model;
uniform vec3 u_viewPos;
uniform sampler2D u_texture;

uniform struct Light {
   vec3 position;
   vec3 color;
   float ambientCoef;
   float specularCoef;
} u_light;

void main()
{
	// Calculate ambient
    vec3 ambient = u_light.ambientCoef * u_light.color;

	// Transform to world space
	mat3 normalMatrix = transpose(inverse(mat3(u_Model)));
    vec3 normal = normalize(normalMatrix * v_normal);
	vec3 pos = vec3(u_Model * vec4(v_position, 1));

	// Calculate light direction
	vec3 lightDir = normalize(u_light.position - pos);

	// Calculate diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * u_light.color;

	// Calculate specular
	vec3 viewDir = normalize(u_viewPos - pos);
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = u_light.specularCoef * spec * u_light.color;  

	// Calculate final color
	vec4 surfaceColor = texture(u_texture, v_texCoord);
	finalColor = vec4((ambient + diffuse + specular) * surfaceColor.rgb, surfaceColor.a);
};