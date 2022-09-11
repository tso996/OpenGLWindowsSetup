
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "framebuffer_size_callback function called!" << std::endl;
	glViewport(0, 0, width, height);
}

int main(int args, char* argv[]) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World!", NULL, NULL);
	if (window == NULL) {
		std::cout << "Could not initialize glfw window.." << std::endl;
		glfwTerminate();
		return -1;
	}
	else {
		std::cout << "Window initialised ok" << std::endl;
	}



	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Could not initialize GLAD" << std::endl;
		return -1;
	}
	else {
		std::cout << "GLAD initialized ok" << std::endl;
	}

	glViewport(0, 0, 800, 600);//first 2 parameter are the lower left corner of the window

	//setting up callbacks to handle window resizing
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


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