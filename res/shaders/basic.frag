#version 330 core

in vec2 vertex_position;

out vec4 fragment_color;

void main() {
    fragment_color = vec4(vertex_position.x, -vertex_position.x, 0.5, 1.0);
}
