//#include<glad/glad.h>>
//#include<GLFW/glfw3.h>
//
//int main(void) {
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//	return 0;
//}

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int compileShader(unsigned int type, const std::string& source) {//it needs to actually be a reference to the original string so that the pointer is valid even if the function is over
    unsigned int shdrId = glCreateShader(type);
    const char* shdrCode = source.c_str();
    glShaderSource(shdrId, 1, &shdrCode, NULL);
    glCompileShader(shdrId);
    //maybe some error handling here
    int result{};
    glGetShaderiv(shdrId, GL_COMPILE_STATUS, &result);

    if (result!=GL_FALSE) {
        std::cout << "shader compiled ok.." << std::endl;
    }
    else {
        std::cout << "shader compilation error" << std::endl;
        int length{};
        glGetShaderiv(shdrId, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(sizeof(char) * length);
        glGetShaderInfoLog(shdrId, length, &length, message);
        std::cout << "could not compile correctly: " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        glDeleteShader(shdrId);
        return 0;
    }

    return shdrId;

}

static unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vertexShdr = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fragmentShdr = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vertexShdr);
    glAttachShader(program, fragmentShdr);
    glLinkProgram(program);
    glValidateProgram(program);

    //the shaders could actually be deleted since they are already linked. The obj files are deleted
    glDeleteShader(vertexShdr);
    glDeleteShader(fragmentShdr);

    return program;

}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW did not initialize properly!" << std::endl;
    }
    else {
        std::cout << "GLEW initialized.." << std::endl;
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer{};
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    std::string vertexShader = "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;\n"
        "void main(){\n"
        "gl_position = position; "
        "\n}";
    std::string fragmentShader = "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;\n"
        "void main(){\n"
        "color = vec4(1.0, 0.0, 0.0, 1.0) ; "
        "\n}";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawArrays(GL_TRIANGLES, 0,3);


        glEnd();


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}