varying vec4 v_fragmentColor;
varying vec2 v_coord;
void main()
{
//    gl_FragColor = v_fragmentColor * texture2D(CC_Texture0, v_coord);
//    gl_FragColor = vec4(1,0,0,1);
    gl_FragColor = v_fragmentColor;
}