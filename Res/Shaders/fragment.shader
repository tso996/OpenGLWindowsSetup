 #version 330 core  
 out vec4 FragColor;  
 in vec3 vertexColor; 
// uniform vec4 newColor;  
 void main()  
 {  
    FragColor = vec4(vertexColor, 1.0);  
//    FragColor = newColor;  
 };