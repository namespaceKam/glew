#version 130

uniform vec4 Color;
uniform sampler2D Texture;

out vec4 outcolor;
void main(void)
{
  vec2 textureCoord = gl_TexCoord[0].st;
  vec4 textureColor = texture(Texture, textureCoord);
  
  outcolor = textureColor * textureColor.a
  + outcolor * outcolor.a
  * (1.0 - textureColor.a);
  
  //outcolor = textureColor;
}