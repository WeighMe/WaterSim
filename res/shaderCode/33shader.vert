#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
//
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model;
layout(std140, binding = 2) uniform uboTrans{
    mat4 projection;
    mat4 view;
};
layout(std140, binding = 1) uniform uboPlane{
    vec4 plane;
};


void main()
{
    vec4 worldPos = model * vec4(aPos, 1.0f);
    gl_ClipDistance[0] = dot(worldPos, plane);
    gl_Position = projection * view * worldPos;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
}