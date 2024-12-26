#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

out vec3 color;
out vec2 texCoords;

uniform float scale;
uniform mat4 projection;

void main() {
    gl_Position = projection * vec4(aPos + aPos * scale, 1.0);
    color = aColor;
    texCoords = aTexCoords;
}