#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_coord;
layout(location = 1) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// Output
// TODO(student): Output values to fragment shader
out vec3 f_position;
out vec3 f_normal;
out vec2 f_coord;
out vec3 f_color;

void main()
{
    // TODO(student): Send output to fragment shader
    f_position = v_position;
    f_normal = v_normal;
    f_coord = v_coord;
    f_color = v_color;

    // TODO(student): Compute gl_Position
    vec3 time_position = v_position + vec3(sin(Time), 0, sin(Time));
    gl_Position = Projection * View * Model * vec4(time_position, 1.0f);

}
