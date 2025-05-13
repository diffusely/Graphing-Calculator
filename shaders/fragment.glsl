#version 330 core

in vec2 fragPos;
out vec4 FragColor;

void main()
{
	float axisThreshold = 0.01;

	if (abs(fragPos.x) < axisThreshold)
	{
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if (abs(fragPos.y) < axisThreshold)
	{
		FragColor = vec4(1.0, 1.0, 1.0, 1.0);
	}
	else if (abs(fragPos.x) == 0.)
	{
		FragColor = vec4(0.6, 0.6, 0.6, 0.3);
	}
	else
	{
		FragColor = vec4(0.2, 0.2, 0.2, 0.2);
	}
}
