#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec3 v_position;
out vec2 v_texCoord;
out vec3 v_normal;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * position;
	v_position = position.rgb;
	v_texCoord = texCoord;
	v_normal = normal;
};