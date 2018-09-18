attribute vec3 a_position;
attribute vec3 a_color;
varying vec3 v_color;

void main() {
    gl_Position = vec4(a_position.x, a_position.y, a_position.z, 1.0);
    v_color = a_color;
}
