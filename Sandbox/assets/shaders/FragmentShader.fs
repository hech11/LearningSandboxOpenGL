#version 330 core


out vec4 color;
uniform vec4 u_Color =  vec4(1.0f, 1.0f, 1.0f, 1.0f);


void main() {
	color = vec4(1.0f, 1.0f, 1.0f, 1.0f) * u_Color;
}