#version 130

uniform mat4 ProjectionMatrix;
uniform mat4 TransformMatrix;

//gl_Vertex

in vec2 vertex;
in vec2 texture_coordinate;

void main(void)
{
  //float tx, ty;
  //if( gl_Vertex.x > 0 )
  //  tx = 0;
  // else
  //  tx = 1;
    
  //if( gl_Vertex.y < 0 )
  //  ty = 0;
  //else ty = 1;

  gl_Position =  ProjectionMatrix * TransformMatrix * vec4(vertex, 0, 1);
  gl_TexCoord[0] = vec4(texture_coordinate, 0, 0);
  //vec4(tx,ty,0,0);
}