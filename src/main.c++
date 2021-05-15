
#include <stdio.h>
#include <emscripten.h>
#include <SDL.h>
#include <SDL_opengles2.h>
#include <iostream>
#include <fstream>

#include <functional>
#include <emscripten.h>
#include <iostream>
#include <algorithm>
#include <vector>

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "normals/normals.h++"
#include "sphere/sphere.h++"
#include "util/file_util/file_util.h++"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <SDL2/SDL.h>

#include <SDL2/SDL_opengles2.h>
#define GL_GLEXT_PROTOTYPES
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>

std::function<void()> loop;
void main_loop() { loop(); }

SDL_Window *window;
SDL_GLContext g_GLContext = NULL;
GLuint shaderProgram;
GLuint sphereVAO;

std::vector<GLuint> sphereIndices;
std::vector<GLuint> sphereVertices;
std::vector<GLuint> sphereNormals;
std::vector<glm::mat4> sphereMatrices;

std::vector<glm::mat4> translations;

GLint aVertexPosition;
GLint aVertexNormal;

// Shader locations
GLint uProjectionMatrix;
GLuint uModelViewMatrix;
GLint uNormalMatrix;
GLint uMaterialDiffuse;
GLint uLightDiffuse;
GLint uLightDirection;

GLfloat lightDiffuseColor[3] = {1.0, 1.0, 1.0};
GLfloat lightDirection[3] = {0.0, -1.0, -1.0};
GLfloat sphereColor[3] = {0.5, 0.8, 0.1};

glm::mat4 normalMatrix= glm::mat4(1.0f);;

  glm::mat4 proj = glm::perspective(90.0f, (float)1280 / 720, 0.1f, 10000.0f);
glm::mat4 norm = glm::transpose(glm::inverse(glm::translate(normalMatrix, glm::vec3(0, 0, -1.5))));


void initSdl() {
    // Setup SDL, mainly for imgui
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
      printf("Error: %s\n", SDL_GetError());
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    window = SDL_CreateWindow("spheres webgl demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    g_GLContext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    // Begin imgui add
    if (!g_GLContext)
    {
      fprintf(stderr, "Failed to initialize WebGL context!\n");
    }
}

void initImgui() {

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui_ImplSDL2_InitForOpenGL(window, g_GLContext);
    ImGui_ImplOpenGL3_Init("#version 100");
    // end an imgui add

}

GLuint getShader(GLenum shaderType, std::string strSource) {

  const GLchar* src = strSource.c_str();
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &src, 0);
  glCompileShader(shader);

  GLint isCompiled = 0;

  glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

  if(isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

    for (std::vector<char>::const_iterator i = errorLog.begin(); i != errorLog.end(); ++i)
      std::cout << *i;
    
    std::cout<< std::endl;
    // Provide the infolog in whatever manor you deem best.
    // Exit with failure.
    glDeleteShader(shader); // Don't leak the shader.
  }

  return shader;
}

void ensureLinked(GLint shaderProgram) {
  // Check the status of the compile/link
  // glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLen);
  GLint linked;
  GLint infoLen = 0;
  glGetProgramiv ( shaderProgram, GL_LINK_STATUS, &linked );
  if (!linked) {
    glGetProgramiv ( shaderProgram, GL_INFO_LOG_LENGTH, &infoLen );
    if (infoLen > 1)
    {
      char* infoLog = (char*)malloc (sizeof(char) * infoLen );
      glGetProgramInfoLog ( shaderProgram, infoLen, NULL, infoLog );
      printf ( "Error linking program:\n%s\n", infoLog );
      free ( infoLog );
    }
  }
}

void initShaders() {
  
  std::string vertexSource = file_util::read("shaders/vertex.shader");
  std::string fragmentSource = file_util::read("shaders/fragment.shader");
  
  GLuint vertexShader = getShader(GL_VERTEX_SHADER, vertexSource);
  GLuint fragmentShader = getShader(GL_FRAGMENT_SHADER, fragmentSource);

  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  ensureLinked(shaderProgram);

  glUseProgram(shaderProgram);
}

void initProgram() {
  initSdl();
  initImgui();
  glClearColor ( 0.9f, 0.9f, 0.9f, 1.0f );
  glEnable(GL_DEPTH_TEST);
  initShaders();
}

void initBuffers() {

  glGenVertexArrays(1, &sphereVAO);
  glBindVertexArray(sphereVAO);
}

void unsetBuffers() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}


void initShaderLocations() {

  aVertexPosition = glGetAttribLocation(shaderProgram, "aVertexPosition");
  aVertexNormal = glGetAttribLocation(shaderProgram, "aVertexNormal");
  uProjectionMatrix = glGetUniformLocation(shaderProgram, "uProjectionMatrix");
  uModelViewMatrix = glGetUniformLocation(shaderProgram, "uModelViewMatrix");
  uNormalMatrix = glGetUniformLocation(shaderProgram, "uNormalMatrix");
  uMaterialDiffuse = glGetUniformLocation(shaderProgram, "uMaterialDiffuse");
  uLightDiffuse = glGetUniformLocation(shaderProgram, "uLightDiffuse");
  uLightDirection = glGetUniformLocation(shaderProgram, "uLightDirection");

}

void updateUniforms() {

  GLfloat * projPtr = glm::value_ptr( proj );
  GLfloat * normPtr = glm::value_ptr( norm );
  
    glUniform3fv(uLightDirection, 1, lightDirection);
    glUniform3fv(uLightDiffuse, 1, lightDiffuseColor);
    glUniform3fv(uMaterialDiffuse, 1, sphereColor);

    glUniformMatrix4fv(uProjectionMatrix, 1, GL_FALSE, projPtr);
    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, normPtr);
}

int main()
{
  initProgram();
  initShaderLocations();
  initBuffers();

  sphere sphere1(aVertexPosition, aVertexNormal);
  sphere sphere2(aVertexPosition, aVertexNormal);

  std::vector<sphere *> spheres(2);

  spheres[0] = &sphere1;
  spheres[1] = &sphere2;

  sphere1.initToBuffers(sphereVertices, sphereNormals, sphereIndices);
  sphere2.initToBuffers(sphereVertices, sphereNormals, sphereIndices);

  glBindVertexArray(sphereVAO);

  int ticker = 0;
  updateUniforms();

  // io.Fonts->AddFontDefault();
  ImGuiIO& io = ImGui::GetIO();
  static bool show_demo_window = true;
  static bool show_another_window = false;
  
  loop = [&] {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);
    ImGui::NewFrame();

    if (show_demo_window) {
      ImGui::ShowDemoWindow(&show_demo_window);
    }

    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");             
      ImGui::Text("This is some useful text.");   
      ImGui::Checkbox("Demo Window", &show_demo_window);
      ImGui::Checkbox("Another Window", &show_another_window);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);

      if (ImGui::Button("Button"))                  // Buttons return true when clicked
      { counter++;

      }

      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
      ImGui::End();
    }

    if (show_another_window)
    {
      ImGui::Begin("Another Window", &show_another_window);
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me")){
        show_another_window = false;
      }
      ImGui::End();
    }

    // match sphere viewpoint and coords to that of imgui
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);

    glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    try {

      glBindVertexArray(sphereVAO);
      // sphere at index 0 is always the one to move, right now.
      spheres[0]->move(glm::vec3( 0.05/4, 0, 0.1 / 4));
      for (int drawIterator = 0; drawIterator < spheres.size(); drawIterator ++) {
        spheres[drawIterator]->draw(uModelViewMatrix, ticker);
      }

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      glBindVertexArray(0);

    } catch (std::exception err) {
      std::cout << "Draw loop Error!!!!!\n";
      std::cerr << err.what() << std::endl;
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);
    ticker++;
  }; // end loop definition.

  emscripten_set_main_loop(main_loop, 0, true);
  return EXIT_SUCCESS;
}
