#version 330 core

in vec3 vColor;
in vec2 texUV;

out vec4 fColor;

uniform sampler2D noiseTexture;

void main() {

    float h = texture(noiseTexture, texUV).r;

    float r = (67.0 - 42.0 * h) / 255.0;
    float g = (198.0 - 170.0 * h) / 255.0;
    float b = (172.0 - 88.0 * h) / 255.0;

    fColor = vec4(r,g,b,1.0);

    //fColor = texture(noiseTexture, texUV);
}