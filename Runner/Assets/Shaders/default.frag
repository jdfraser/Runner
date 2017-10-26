#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
    color = texture(textureSampler, vec2(UV.x, 1.0 - UV.y)).rgb;
}