#version 330 core

in vec3 v_position;
in vec2 v_texCoord;
in vec3 v_normal;

layout(location = 0) out vec4 finalColor;

uniform mat4 u_Model;
uniform vec3 u_viewPos;
uniform sampler2D u_texture;

void main()
{
	finalColor = texture(u_texture, v_texCoord);
};