#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <iostream>

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

int main()
{
    std::vector<int> a;
    a.push_back(5);
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices0[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices0), vertices0, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);//adding a 0 means unbinding

    //TRYING TO DRAW A RECTANGLE USING THE SAME METHOD
    //float vertices1[] = {
    //    // first triangle
    // 0.5f,  0.5f, 0.0f,  // top right
    // 0.5f, -0.5f, 0.0f,  // bottom right
    //-0.5f,  0.5f, 0.0f,  // top left 
    //// second triangle
    // 0.5f, -0.5f, 0.0f,  // bottom right
    //-0.5f, -0.5f, 0.0f,  // bottom left
    //-0.5f,  0.5f, 0.0f   // top left
    //};
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    
    //The redundant positions are removed
    float vertices1[] = {
     0.5f,  0.5f, 0.0f,  // top right 0
     0.5f, -0.5f, 0.0f,  // bottom right 1
    -0.5f, -0.5f, 0.0f,  // bottom left 2
    -0.5f,  0.5f, 0.0f   // top left  3
    };
    
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3 
    };

    unsigned int VAO1, vertexBufferObject1;
    glGenVertexArrays(1, &VAO1);

    glBindVertexArray(VAO1);

    glGenBuffers(1, &vertexBufferObject1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject1);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);// The index (first parameter) corresponds to the location value in the shader
    glEnableVertexAttribArray(0);//The value here corresponds to the location value in the vertex shader

    //Make the Element buffer object, these are also in the VAO
    unsigned int elementBufferObject;
    glGenBuffers(1, &elementBufferObject);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);



    int maxVertexAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes);
    std::cout << maxVertexAttributes << std::endl;

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO1); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0); // no need to unbind it every time 

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}



//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <filesystem>
//
//#define ASSERT(x) if (!(x)) __debugbreak();
//#define GLCALL(x) errorLogging::glClearError();\
//x;\
//ASSERT(errorLogging::glLogCall(#x, __FILE__, __LINE__))
//
//namespace errorLogging {
//    static void glClearError() {
//        while (glGetError != GL_NO_ERROR) {
//
//        }
//    }
//
//    static bool glLogCall(const char* function, const char* file, int line) {
//        while (GLenum error = glGetError()) {
//            std::cout << "[OpenGL error: " << error <<": "<<function<<" "<< file<< " "<< line<< std::endl;
//            return false;
//        }
//
//        return true;
//    }
//}
//
//struct ShaderProgramSource
//{
//    std::string vertexSource{};
//    std::string fragmentSource{};
//};
//
//static ShaderProgramSource parseShader(const std::string& filepath) {
//
//    std::cout << filepath << std::endl;
//    std::cout << "current working:" << std::filesystem::current_path() << std::endl;
//    std::ifstream stream(filepath);
//    std::ifstream infile(filepath);
//    if (infile.good()) {
//        std::cout << "file found" << std::endl;
//    }
//    enum class ShaderType {
//    NONE = -1, VERTEX = 0, FRAGMENT = 1
//    };
//
//    std::string line;
//    std:: stringstream ss[2];
//
//    ShaderType type = ShaderType::NONE;
//
//    while (getline(stream, line)) {
//        if (line.find("#shader") != std::string::npos) {
//            if (line.find("vertex") != std::string::npos) {
//                type = ShaderType::VERTEX;
//            }
//            else if (line.find("fragment") != std::string::npos) {
//                type = ShaderType::FRAGMENT;
//            }
//        }
//        else {
//            ss[(int)type] << line << '\n';
//        }
//        
//    }
//
//    ShaderProgramSource sp;
//    sp.vertexSource = ss[0].str();
//    sp.fragmentSource = ss[1].str();
//    return sp;
//
//}
//
//
//
//static int compileShader(unsigned int type, const std::string& source) {//it needs to actually be a reference to the original string so that the pointer is valid even if the function is over
//    GLuint shdrId = glCreateShader(type);
//    const char* shdrCode = source.c_str();
//    GLCALL(glShaderSource(shdrId, 1, &shdrCode, NULL));
//    GLCALL(glCompileShader(shdrId));
//    //maybe some error handling here
//    int result{};
//    GLCALL(glGetShaderiv(shdrId, GL_COMPILE_STATUS, &result));
//
//    if (result!=GL_FALSE) {
//        std::cout << "shader compiled ok.." << std::endl;
//    }
//    else {
//        std::cout << "shader compilation error" << std::endl;
//        int length{};
//        GLCALL(glGetShaderiv(shdrId, GL_INFO_LOG_LENGTH, &length));
//        char* message = (char*)alloca(sizeof(char) * length);
//        GLCALL(glGetShaderInfoLog(shdrId, length, &length, message));
//        std::cout << "could not compile correctly: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
//        GLCALL(glDeleteShader(shdrId));
//        return 0;
//    }
//
//    return shdrId;
//
//}
//
//static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
//    unsigned int program = glCreateProgram();
//    unsigned int vertexShdr = compileShader(GL_VERTEX_SHADER, vertexShader);
//    unsigned int fragmentShdr = compileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//    GLCALL(glAttachShader(program, vertexShdr));
//    GLCALL(glAttachShader(program, fragmentShdr));
//    GLCALL(glLinkProgram(program));
//    GLCALL(glValidateProgram(program));
//
//    //the shaders could actually be deleted since they are already linked. The obj files are deleted
//    GLCALL(glDeleteShader(vertexShdr));
//    GLCALL(glDeleteShader(fragmentShdr));
//
//    return program;
//
//}
//
//
//
//int main(void)
//{
//    GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//    
//
//    //setting up the opengl version to use
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(640, 480, "OpenGL Setup", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window);
//
//    glfwSwapInterval(1);
//
//
//    if (glewInit() != GLEW_OK) {
//        std::cout << "GLEW did not initialize properly!" << std::endl;
//    }
//    else {
//        std::cout << "GLEW initialized.." << std::endl;
//        std::cout << glGetString(GL_VERSION) << std::endl;
//    }
//
//    float positions[12] = {
//          0.5f, 0.5f,
//          0.5f, -0.5f,
//         -0.5f, -0.5f,      
//         -0.5f, 0.5f,
//    };
//
//    unsigned int indices[] = {
//        0, 1, 2,
//        2, 3, 0
//    };
//
//    unsigned int buffer{};
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, positions, GL_STATIC_DRAW);
//
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
//    glEnableVertexAttribArray(0);
//
//    unsigned int indexBuffer{};
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * 6, indices, GL_STATIC_DRAW);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//    ShaderProgramSource source = parseShader("Res/Shaders/Basic.shader");
//
//    std::cout << "VERTEX" << std::endl;
//    std::cout << source.vertexSource << std::endl;
//    std::cout << "FRAGMENT" << std::endl;
//    std::cout << source.fragmentSource << std::endl;
//    
//    
//    /*std::string vertexShader = "#version 330 core\n"
//        "\n"
//        "layout(location = 0) in vec4 position;"
//        "void main(){\n"
//        "gl_Position = position; "
//        "\n}";
//
//    std::string fragmentShader = "#version 330 core\n"
//        "\n"
//        "layout(location = 0) out vec4 color;\n"
//        "void main(){\n"
//        "color = vec4(1.0, 0.0, 0.0, 1.0) ; "
//        "\n}";*/
//
//    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
//    GLCALL(glUseProgram(shader));
//
//    GLCALL(int location = glGetUniformLocation(shader, "u_color"));//find the variable
//    ASSERT(location != -1);//location is -1, so stop it could not be found
//    GLCALL(glUniform4f(location, 0.8, 0.3, 0.8, 1.0));//set the variable
//
//    GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
//    GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0));
//    GLCALL(glUseProgram(0));
//
//    float r = 0.0f;
//    float increment = 0.05f;
//    /* Loop until the user closes the window */
//    while (!glfwWindowShouldClose(window))
//    {
//        /* Render here */
//        GLCALL(glClear(GL_COLOR_BUFFER_BIT));
//
//        //glClearError();//The error handler we made. Another reason start needs to be in caps
//
//
//        GLCALL(glBindBuffer(GL_ARRAY_BUFFER, buffer));
//        GLCALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0));
//        GLCALL(glEnableVertexAttribArray(0));
//
//        GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer));
//
//
//        GLCALL(glUseProgram(shader));
//        GLCALL(glUniform4f(location, r, 0.3, 0.8, 1.0));//set the variable
//        
//        
//        GLCALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//        //ASSERT(errorLogging::glLogCall());
//
//
//        if (r > 1.0f) {
//            increment = -0.05f;
//        }
//        if (r < 0.0f) {
//            increment = 0.05f;
//        }
//        r += increment;
//        
//        //glEnd();
//
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//    GLCALL(glDeleteProgram(shader));
//
//    glfwTerminate();
//    return 0;
//}