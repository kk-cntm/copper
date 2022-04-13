#type vertex
#version 410 core

layout (location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_TransformMatrix;

void main()
{
    gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0f);
}

#type fragment
#version 410 core

out vec4 FragColor;

uniform vec4 u_Color;

void main()
{
    FragColor = u_Color;
}