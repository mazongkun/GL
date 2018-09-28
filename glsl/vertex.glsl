attribute vec3 a_position;
attribute vec3 a_color;
attribute vec2 a_texCoord;

varying vec3 v_color;
varying vec2 v_texCoord;

uniform mat4 u_transform;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    v_color = a_color;
    v_texCoord = a_texCoord;
    // gl_Position = u_transform * vec4(a_position, 1.0);
    gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
    // gl_Position = vec4(a_position, 1.0);
}
