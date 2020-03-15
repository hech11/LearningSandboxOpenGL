#version 330 core


layout(location = 0) in vec4 aPos;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_ProjView = mat4(1.0f);

void main() {
	gl_Position = u_ProjView * u_Model * aPos;
}