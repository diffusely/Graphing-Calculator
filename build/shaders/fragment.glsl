#version 330 core

in vec2 fragPos;
out vec4 FragColor;

uniform vec3 uColor;

void main()
{
	FragColor = vec4(uColor, 1.0);
}
