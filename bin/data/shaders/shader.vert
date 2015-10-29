#version 150

// these are for the programmable pipeline system
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec2 texcoord;

out vec2 texCoordVarying;
uniform sampler2DRect tex0;

void main()
{
    
    
    vec4 modifiedPosition = modelViewProjectionMatrix * position;
    
    float scale = 500;
    
    //use the average of teh RGB values to affect the shader displacement
    vec4 tex1 = texture(tex0, texcoord);
    float displacementY = (tex1.r + tex1.g + tex1.b) / 3.f;
    
    //modify the y position using the scale and displacement
    modifiedPosition.y += scale * displacementY;
    
    //output the new position
    gl_Position = modifiedPosition;
    
    //pass on the coordinates to fragment shader.
    texCoordVarying = texcoord;
}