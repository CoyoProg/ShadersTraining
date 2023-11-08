#version 450 core

out vec4 FragColor;

in VS_OUT
{
    vec4 color;
} fs_in;

void main()
{
    //FragColor = fs_in.color; //Dont know how to pass the color between tesc & tese
    FragColor = vec4(0.f, 0.8f, 1.f, 1.f);
}
