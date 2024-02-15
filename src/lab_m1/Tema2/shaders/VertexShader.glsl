#version 330

// Input
// TODO(student): Get vertex attributes from each location
layout(location = 0) in vec3 v_position;

// Uniform properties
uniform vec3 object_color;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float damage;

// Output
out vec3 color;

void main()
{
    color = object_color;

    vec3 damagePos = v_position;

    if(damage > 1.f) {
        float bendFactor = damage * 0.1; // Adjust the multiplier to control the bending
        float shrinkFactor = 1.0 - (damage * 0.08); // Adjust the multiplier to control the shrinking

        damagePos.z += sin(v_position.y * bendFactor); // Apply bending to X
        damagePos *= shrinkFactor; // Apply uniform shrinking
        
        if (damage == 2.f) {
            color = color - vec3(0.1f, 0.1f, 0.2f);
        }

        if (damage == 3.f) {
			color = color - vec3(0.1f, 0.3f, 0.3f);
		}

        if (damage == 4.f) {
            color = vec3(0.f, 0.f, 0.f);
        }
    }

    gl_Position = Projection * View * Model * vec4(damagePos, 1.0);

}
