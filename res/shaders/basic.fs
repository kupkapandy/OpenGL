#version 460 core

out vec4 FragColor;
in vec3 colorVec;

void main()
{
  FragColor = vec4(colorVec, 1.0);
}
