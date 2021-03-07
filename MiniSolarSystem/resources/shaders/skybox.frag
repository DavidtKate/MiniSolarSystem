#version 330 core

in vec3 v_texCoord;

layout(location = 0) out vec4 finalColor;

uniform samplerCube u_skybox;

void main()
{
	finalColor = texture(u_skybox, v_texCoord);
};