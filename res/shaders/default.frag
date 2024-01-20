#version 460 core

out vec4 FragColor;

uniform sampler2D u_tex0;

in vec2 uv;

void main()
{
   FragColor = texture(u_tex0, uv);
}