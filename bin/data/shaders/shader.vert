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
    
    float scale = 100;
    
    //use the each RGB value to influence the displacement in the XYZ directions
    vec4 tex1 = texture(tex0, texcoord);
    float offset = 0.5;
    float displacementX = tex1.r - offset;
    float displacementY = tex1.g - offset;
    float displacementZ = tex1.b - offset;
    
    //modify the y position using the scale and displacement
    modifiedPosition.x += scale * displacementX;
    modifiedPosition.y += scale * displacementY;
    modifiedPosition.z += scale * displacementZ;
    
    //output the new position
    gl_Position = modifiedPosition;
    
    //pass on the coordinates to fragment shader.
    texCoordVarying = texcoord;
}