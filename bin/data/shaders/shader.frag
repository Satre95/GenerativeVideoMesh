#version 150

//System vars
in vec2 texCoordVarying;

//Output vars
out vec4 outputColor;

//Custom var
uniform sampler2DRect tex0;
uniform float elapsedTime;
uniform float programNoise;

/*
float cubicPulse( float c, float w, float x ){
    x = abs(x - c);
    if( x>w ) return 0.0;
    x /= w;
    return 1.0 - x*x*(3.0-2.0*x);
}

float pcurve( float x, float a, float b )
{
    float k = pow(a+b,a+b) / (pow(a,a)*pow(b,b));
    return k * pow( x, a ) * pow( 1.0-x, b );
}
*/
 
void main() {
    
    vec4 mainTexture = texture( tex0, texCoordVarying);
    
    float scale = 10;
    float coordCalc = texCoordVarying.y / texCoordVarying.x * scale;
    
    float redPct = abs(sin(elapsedTime)/(mainTexture.r + 1));
    float greenPct = abs(sin(elapsedTime)/(mainTexture.g + 1));
    float bluePct = abs(sin(elapsedTime) / (mainTexture.b + 1));

    mainTexture.r = mix( mainTexture.r, mainTexture.g, redPct);
    mainTexture.g = mix( mainTexture.g, mainTexture.b, greenPct);
    mainTexture.b = mix( mainTexture.b, mainTexture.r, bluePct);
    
    outputColor = mainTexture;
}