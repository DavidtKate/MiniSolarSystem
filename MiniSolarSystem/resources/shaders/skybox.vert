#version 330 core

layout(location = 0) in vec4 position;

out vec3 v_texCoord;

uniform mat4 u_MVP;

void main()
{
	v_texCoord = position.rgb;
	vec4 pos = u_MVP * position;
	gl_Position = pos.xyww;
};