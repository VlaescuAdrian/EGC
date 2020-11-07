#version 330

// TODO: get values from fragment shader

in vec3 color1;


layout(location = 0) out vec4 out_color;

void main()
{
	// TODO: write pixel out color
	out_color = vec4(color1, 1);
}