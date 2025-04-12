// https://www.shadertoy.com/view/3csSWB
#version 330
// Input vertex attributes (from vertex shader)
in vec2 fragTexCoord;
in vec4 fragColor;
// Input uniform values
uniform vec2  iRes;
uniform vec2  iMouse;
uniform float iTime;

uniform sampler2D texture0;
uniform vec4      colDiffuse;
// Output fragment color
out vec4 finalColor;

void main()
{
    // it come from the renderTexture in cpp
    vec2 uv = fragTexCoord;
    // invert y axis
    // uv.y       = 1.0 - uv.y;
    finalColor = vec4(uv, 0., 1.);
}