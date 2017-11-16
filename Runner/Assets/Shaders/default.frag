#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D textureSampler;

void main() {
	const vec3 fogColor = vec3(0.5, 0.5, 0.5);
	const float fogStart = 5;
	const float fogEnd = 10;

	float dist = gl_FragCoord.z / gl_FragCoord.w;

	float fogFactor = (fogEnd - dist) / (fogEnd - fogStart);
	fogFactor = clamp(fogFactor, 0.0, 1.0);

	color = texture(textureSampler, vec2(UV.x, 1.0 - UV.y)).rgb;
	color = mix(fogColor, color, fogFactor);
}