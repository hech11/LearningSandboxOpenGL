#version 330 core


out vec4 color;
uniform vec4 u_Color =  vec4(1.0f, 1.0f, 1.0f, 1.0f);

uniform sampler2D u_Sampler;
uniform sampler2D u_Sampler2;
uniform int T;
in vec2 v_texCoords;

void main() {
	if(T == 0)
		color = texture2D(u_Sampler, v_texCoords) * u_Color;
	else
		color = texture2D(u_Sampler2, v_texCoords) * u_Color;
}