#version 100

// Input vertex attributes (from vertex shader)
// in vec2 fragTexCoord;
// in vec4 fragColor;

// // Input uniform values
// uniform vec2  iRes;
// uniform vec2  iMouse;
// uniform float iTime;

// uniform sampler2D texture0;
// uniform vec4      colDiffuse;

// // Output fragment color
// out vec4 finalColor;


// void main()
// {
//     vec2 uv = fragTexCoord.xy;
//     uv -= .1;

//     float rx = length(uv) * 5.;

//     float sx = smoothstep(rx, rx - 1., 1.3);

//     float nx   = 1. - sx;
//     finalColor = vec4(vec3(nx * 1.5) * fragColor.rgb, nx);
// }
