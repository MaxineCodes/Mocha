
#include "Debug.h"

// window and opengl bindings
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GUI
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// maths
#include <glm\glm.hpp>
// image reading
#include <stb_image.h>


bool debugEnabled = true;


namespace Mocha::Debug
{
    void PrintHelloWorld()
    {
        if (!debugEnabled) return;

        std::cout << "Hello World!" << std::endl;
    }


    // Testing function to get something going on the screen and check that external dependencies are working
    void DoGraphicsSomething()
    {
        if (!debugEnabled) return;

        // Vertex shader source code
        const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;
        void main()
        {
            gl_Position = vec4(aPos, 1.0);
        }
        )";

        // Fragment shader source code
        const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main()
        {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
        )";

        // Initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            return;
        }

        // Create a windowed mode window and its OpenGL context
        GLFWwindow* window = glfwCreateWindow(1280, 960, "App-Core Graphics Template", NULL, NULL);

        if (!window)
        {
            glfwTerminate();
            std::cerr << "Failed to create GLFW window" << std::endl;
            return;
        }

        // Make the window's context current
        glfwMakeContextCurrent(window);

        // Initialize GLEW
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            return;
        }

        // Setup ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");



        // Define the vertex data for a triangle
        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        // Create a vertex buffer object (VBO)
        GLuint VBO;
        glGenBuffers(1, &VBO);

        // Create a vertex array object (VAO)
        GLuint VAO;
        glGenVertexArrays(1, &VAO);

        // Bind the VAO
        glBindVertexArray(VAO);

        // Bind the VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Define the vertex attributes
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Create and compile the vertex shader
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
        glCompileShader(vertexShader);

        // Check for shader compile errors
        int success;
        char infoLog[512];
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Create and compile the fragment shader
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
        glCompileShader(fragmentShader);

        // Check for shader compile errors
        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        }

        // Link shaders to create a shader program
        GLuint shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        // Check for linking errors
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
            std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        }

        // Clean up shaders as they're no longer needed
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);



        // Main loop
        while (!glfwWindowShouldClose(window))
        {
            // Poll for and process events
            glfwPollEvents();

            // Render here
            glClear(GL_COLOR_BUFFER_BIT);

            // Start the ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            // Create a simple ImGui window
            ImGui::Begin("Hello, world!");
            ImGui::Text("Bla bla bla bla bla. ^^;");
            ImGui::End();

            // Show demo window
            ImGui::ShowDemoWindow();

            // Rendering
            ImGui::Render();
            glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Render the triangle
            glUseProgram(shaderProgram);
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            // Swap front and back buffers
            glfwSwapBuffers(window);
        }

        // Cleanup ImGui
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();


        // Cleanup glfw
        glfwDestroyWindow(window);
        glfwTerminate();

        // Cleanup OpenGL resources
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);

    }

    namespace Logging
    {
        // Bools used to store whether these LogLevels should be logged.
        bool logInfo, logWarning, logError;

        // Determines which LogLevels should get logged, for instance:
        // Info: Print everything including info.
        // Error: Only print errors, no warnings or info.
        // Should only be used once, preferably before program initialisation. 
        void SetGlobalMinimumLogLevel(const LogLevel level)
        {
            switch (level)
            {
            case Info:      logInfo = true;  logWarning = true;  logError = true;  break; // All true
            case Warning:   logInfo = false; logWarning = true;  logError = true;  break;
            case Error:     logInfo = false; logWarning = false; logError = true;  break;
            case None:      logInfo = false; logWarning = false; logError = false; break; // All false
            default:        logInfo = true;  logWarning = true;  logError = true;  break; // Identical to Info
            }

            return;
        }

        void Log(const LogLevel level, const std::string message)
        {
            if (!debugEnabled) return;

            // If all log levels are disabled, skip this function altogether.
            if (!logInfo && !logWarning && !logError) return;

            const char* messageChar = message.c_str();
            Log(level, messageChar);
        }

        void Log(const LogLevel level, const char* message)
        {
            if (!debugEnabled) return;

            // If all log levels are disabled, skip this function altogether.
            if (!logInfo && !logWarning && !logError) return;
            
            // If the user inputs 'None' as the log warning level, no message will be printed, this warning is in place to prevent silly mistakes.
            if (logWarning && level == None)
            {
                message = "LogLevel 'None' is not intended for logging messages and is reserved for disabling logging altogether. Did you mean to use LogLevel 'Info' instead?";
                std::cout << "[Warning]: " << message << std::endl;
                return;
            }

            if (logInfo && level == Info)
            {
                std::cout << "[info]: " << message << std::endl;
                return;
            }

            if (logWarning && level == Warning)
            {
                std::cout << "[Warning]: " << message << std::endl;
                return;
            }

            if (logError && level == Error)
            {
                std::cout << "  !-+[ERROR]+-!  : " << message << std::endl;
                return;
            }
        }
    }
}
