attribute vec4 a_position;
attribute vec4 a_color;
uniform vec4 u_color;
attribute vec2 a_coord;

  
varying vec4 v_fragmentColor;
varying vec2 v_coord;
  
void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_fragmentColor = u_color;
    v_coord = a_coord;
//    v_coord = a_coord;
}
