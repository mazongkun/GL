attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;

varying vec3 v_color;
varying vec2 v_texCoord;

void main() {
    v_color = a_color;
    v_texCoord = a_texCoord;
    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
}
