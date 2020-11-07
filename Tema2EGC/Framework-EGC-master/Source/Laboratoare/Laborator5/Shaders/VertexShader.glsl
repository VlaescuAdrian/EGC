#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_coord;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// TODO: output values to fragment shader
out vec3 color1;
out vec3 normal;

float rand( vec3 st){
	return fract(sin(dot(st,vec3(10,10,10)))* 400);
}

void main()
{
	// TODO: send output to fragment shader
	color1 = v_color;
	normal = v_normal;
	float theta = rand(v_position);
	float r = rand(v_position);

	float x = cos(theta) * r;
	float y = sin(theta) * r;
	float z = rand(v_position);
	

	// TODO: compute gl_Position
	gl_Position = Projection * View * Model * vec4(v_position + vec3(x,y,z), 1.0);
}