#version 450 core

in vec4 position;

out VS_OUT
{
    vec4 color;
} vs_out;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
    gl_Position = proj_matrix * mv_matrix * position;

    // Calculate the color based on the cube's X position as a turquoise gradient
    float xPos = position.x;
    float turquoiseR = 0.0;
    float turquoiseG = 0.8;  // Adjust this value to control the green component
    float turquoiseB = 1.0;
    vs_out.color = vec4(turquoiseR + xPos, turquoiseG + xPos, turquoiseB, 1.0);
}
