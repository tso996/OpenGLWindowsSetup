 #version 330 core  

 in vec3 vertexColor;
 in vec2 texCoord;

 out vec4 FragColor;  

 uniform sampler2D texture1;
 uniform sampler2D texture2;  

 void main()  
 {  
     FragColor = mix(texture(texture1, texCoord), texture(texture2, texCoord), 0.2);
    //FragColor = texture(texture1, texCoord) * vec4(vertexColor, 1.0);  
    //FragColor = newColor;  
 };