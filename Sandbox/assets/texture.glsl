#type vertex
#version 410 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexPos;

out vec2 v_TexPos;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_TransformMatrix;

void main()
{
    gl_Position = u_ViewProjectionMatrix * u_TransformMatrix * vec4(a_Position, 1.0f);
    v_TexPos = a_TexPos;
}

#type fragment
#version 410 core

out vec4 FragColor;

in vec2 v_TexPos;

uniform sampler2D u_Texture;

void main()
{ 
    FragColor = texture(u_Texture, v_TexPos);
}