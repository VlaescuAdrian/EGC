#version 430

layout(location = 0) in vec3 world_position;
layout(location = 1) in vec3 world_normal;

uniform sampler2D texture_1;
uniform samplerCube texture_cubemap;

uniform vec3 camera_position;

layout(location = 0) out vec4 out_color;

vec3 V;

vec3 myReflect()
{
    // TODO - compute the reflection color value
	vec3 R = reflect(V, world_normal);

	return texture(texture_cubemap, R).rgb;
}

vec3 myRefract(float refractive_index)
{
    // TODO - compute the refraction color value
	vec3 R = refract(V, world_normal, refractive_index);

	return texture(texture_cubemap, R).rgb;
}

void main()
{
	V = normalize(world_position - camera_position);
	
    vec4 reflection = vec4(myReflect(), 0);
	vec4 refraction = vec4(myRefract(1.33), 0);

	out_color = mix(reflection,refraction, 0.5);
}
