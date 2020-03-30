#version 330 core


layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoords;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_ProjView = mat4(1.0f);

out vec2 v_texCoords;

void main() {
	v_texCoords = aTexCoords;
	gl_Position = u_ProjView * u_Model * aPos;
}