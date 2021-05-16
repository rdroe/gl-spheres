precision mediump float;

// Expect the interpolated value from the vertex shader
vec4 vVertexColor;

// Return the final color as fragColor

void main(void)  {
  // Simply set the value passed in from the vertex shader
  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
  // gl_FragColor = vVertexColor;
}
