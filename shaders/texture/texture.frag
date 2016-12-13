#version 400
in vec2 uv;
// TODO (Task 8): Declare a sampler2D uniform
out vec4 color;
uniform sampler2D tex;

void main(){
    // TODO (Task 8): Set the output color to the corresponding texel
    color = texture(tex, uv);
}
