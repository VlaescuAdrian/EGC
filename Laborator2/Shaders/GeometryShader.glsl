#version 430
layout(lines) in;
layout(triangle_strip, max_vertices = 256) out;

uniform mat4 View;
uniform mat4 Projection;
uniform int vertical_translation;
uniform int orientation;
uniform vec3 control_p1, control_p2, control_p3, control_p4;
uniform int no_of_instances;
uniform int no_of_generated_points;


in int instance[2];
out vec2 text_coord;


vec3 rotateY(vec3 point, float u)
{
	float x = point.x * cos(u) - point.z *sin(u);
	float z = point.x * sin(u) + point.z *cos(u);
	return vec3(x, point.y, z);
}

vec3 translateX(vec3 point, float t)
{
	return vec3(point.x + t, point.y, point.z);
}

vec3 bezier(float t)
{
	return control_p1 * pow((1 - t), 3) + control_p2 * 3 * t * pow((1 - t), 2) + control_p3 * 3 * pow(t, 2) * (1 - t) + control_p4 * pow(t, 3);
}

void main()
{

	if (instance[0] < no_of_instances)
	{
	    int i=0;
		float points = float(no_of_generated_points);
		float dist=0.5;
		for(i=0; i<no_of_generated_points; i++){
			float r = float(i)/points;
			float r_n = float(i+1)/points;
			float offset = float(instance[0]);
			float offset_n = offset+1.0;

			vec3 b = bezier(r);
			vec3 b_n = bezier(r_n);
			if (vertical_translation == 0.0) {
				gl_Position = Projection* View * vec4(b + vec3(offset*dist, 0.0, 0.0), 1);
				vec3 p1 = b + vec3(offset*dist, 0.0, 0.0);
				text_coord = vec2(p1.x, p1.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(offset_n*dist, 0.0, 0.0), 1);
				vec3 p2 = b + vec3(offset_n*dist, 0.0, 0.0);
				text_coord = vec2(p2.x, p2.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(offset*dist, 0.0, 0.0), 1);
				vec3 p3 = b_n + vec3(offset*dist, 0.0, 0.0);
				text_coord = vec2(p3.x, p3.z);
				EmitVertex();

				EndPrimitive();
				gl_Position = Projection* View * vec4(b_n + vec3(offset*dist, 0.0, 0.0), 1);
				text_coord = vec2(p3.x, p3.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(offset_n*dist, 0.0, 0.0), 1);
				text_coord = vec2(p2.x, p2.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(offset_n*dist, 0.0, 0.0), 1);
				vec3 p4 = b_n + vec3(offset_n*dist, 0.0, 0.0);
				text_coord = vec2(p4.x, p4.z);
				EmitVertex();
				EndPrimitive();


			} else if(vertical_translation == 2.0) {
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset*dist, offset*dist, -2*offset*dist), 1);
				vec3 p5 = b + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p5.x, p5.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p6 = b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist, offset*dist, -2*offset*dist), 1);
				vec3 p7 = b_n + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				EndPrimitive();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist, offset*dist, -2*offset*dist), 1);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p8 = b_n + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p8.x, p8.z);
				EmitVertex();

			} else if(vertical_translation == 3.0) {
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset*dist -2*offset*dist , offset*dist, -2*offset*dist), 1);
				vec3 p5 = b + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p5.x, p5.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist-2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p6 = b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist-2*offset*dist, offset*dist, -2*offset*dist), 1);
				vec3 p7 = b_n + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				EndPrimitive();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist-2*offset*dist, offset*dist, -2*offset*dist), 1);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist-2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset_n*dist-2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p8 = b_n + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p8.x, p8.z);
				EmitVertex();

			} else if(vertical_translation == 4.0) {
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset*dist +2*offset*dist , offset*dist, -2*offset*dist), 1);
				vec3 p5 = b + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p5.x, p5.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist+2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p6 = b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist+2*offset*dist, offset*dist, -2*offset*dist), 1);
				vec3 p7 = b_n + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				EndPrimitive();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist+2*offset*dist, offset*dist, -2*offset*dist), 1);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist+2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset_n*dist+2*offset_n*dist, offset_n*dist, -2*offset_n*dist), 1);
				vec3 p8 = b_n + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p8.x, p8.z);
				EmitVertex();
			
			} else {
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset*dist, offset*dist, 0.0), 1);
				vec3 p5 = b + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p5.x, p5.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0), 1);
				vec3 p6 = b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist, offset*dist, 0.0), 1);
				vec3 p7 = b_n + vec3(orientation * offset*dist, offset*dist, 0.0);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				EndPrimitive();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset*dist, offset*dist, 0.0), 1);
				text_coord = vec2(p7.x, p7.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b + vec3(orientation * offset_n*dist, offset_n*dist, 0.0), 1);
				text_coord = vec2(p6.x, p6.z);
				EmitVertex();
				gl_Position = Projection* View * vec4(b_n + vec3(orientation * offset_n*dist, offset_n*dist, 0.0), 1);
				vec3 p8 = b_n + vec3(orientation * offset_n*dist, offset_n*dist, 0.0);
				text_coord = vec2(p8.x, p8.z);
				EmitVertex();
			}
		}
		//gl_Position = Projection* View * vec4(control_p1 + vec3(float(instance[0]), 0.0, 1.0);	EmitVertex();
		//gl_Position = Projection* View * vec4(control_p2, 1);	EmitVertex();
		//gl_Position = Projection* View * vec4(control_p3, 1);	EmitVertex();
		//gl_Position = Projection* View * vec4(control_p4, 1);	EmitVertex();
		//EndPrimitive();
	}
}