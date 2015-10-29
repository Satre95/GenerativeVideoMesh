#version 150

//System vars
in vec2 texCoordVarying;

//Output vars
out vec4 outputColor;

//Custom var
uniform sampler2DRect tex0;

void main() {
    
    vec4 mainTexture = texture( tex0, texCoordVarying);
    
    outputColor = mainTexture;
}