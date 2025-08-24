#shader vertex
#version 330 core // glsl (w/ no deprecated functions)

layout(location = 0) in vec4 position; // should match 1st val of glVertexAttribPointer 

void main()
{
   gl_Position = position;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
   color = vec4(0.2f, 0.8f, 0.2f, 1.f);
}