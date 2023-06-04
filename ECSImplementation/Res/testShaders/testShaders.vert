#version 450

layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec3 a_Color;

layout (location = 0) out vec3 v_Color;

void main() {
    gl_Position = vec4(a_Position.x, a_Position.y, 0.f, 1.f);
    v_Color = a_Color;
}