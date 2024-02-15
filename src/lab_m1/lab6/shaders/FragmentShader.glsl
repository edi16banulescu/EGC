#version 330

// Input
// TODO(student): Get values from vertex shader
in vec3 f_position;
in vec3 f_normal;
in vec2 f_coord;
in vec3 f_color;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    // TODO(student): Write pixel out color
    out_color = vec4(f_normal, 1);
}
