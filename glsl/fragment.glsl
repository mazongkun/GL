uniform vec4 u_color;
uniform sampler2D u_texture;
uniform sampler2D u_back_texture;

varying vec3 v_color;
varying vec2 v_texCoord;

void main() {
    // gl_FragColor = u_color;
    // gl_FragColor = vec4(v_color, 1.0);
    // gl_FragColor = texture2D(u_texture, v_texCoord) * vec4(v_color, 1.0);
    // gl_FragColor = texture2D(u_texture, v_texCoord);
    gl_FragColor = mix(texture2D(u_texture, v_texCoord), texture2D(u_back_texture, v_texCoord), 0.5);
}
