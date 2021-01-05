#version 430
in vec2 text_coord;

uniform sampler2D texture;

out vec4 out_color;

void main()
{

	vec4 color = texture2D(texture, text_coord);

	//TODO discard when alfa component < 0.75
	if (color.a < 0.75) discard;

	out_color = color;
}