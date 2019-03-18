#version 400 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec4 plane;

void main(void){

    Normal = mat3(transpose(inverse(model)))* aNormal;
    Position = vec3(model * vec4(aPos, 1.0));
    gl_Position = projection * view * model * vec4(position.x, 0.0, position.y, 1.0);

}