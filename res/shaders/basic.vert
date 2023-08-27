#version 330 core

layout (location = 0) in vec2 position;

out vec2 vertex_position;

uniform float uniform_offset_x;
uniform float uniform_offset_y;

void main() {
    vertex_position = vec2(position.x + uniform_offset_x,
                           position.y + uniform_offset_y);
    gl_Position = vec4(vertex_position.xy, 0.0, 1.0);
}
