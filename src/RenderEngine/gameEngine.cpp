//
// Created by 54367 on 2019/3/8.
//

#include "gameEngine.h"
#include "../Skybox/skyboxRenderer.h"
#include "mainRenderer.h"


float GameEngine::lastX = 640.0;
float GameEngine::lastY = 320.0;
bool GameEngine::firstMouse = true;
float GameEngine::ratio = 0.5;
Camera GameEngine::camera = Camera(glm::vec3(0.0f, 1.0f, 3.0f));

GameEngine::GameEngine() {

    DisplayManager::createWindow(1280, 720, "learnOpenGL");
    GLFWwindow *wwindow = DisplayManager::window();
    glfwSetInputMode(wwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(wwindow, mouse_callback);
    glfwSetScrollCallback(wwindow, scroll_callback);

}

GameEngine::~GameEngine() {

}

void GameEngine::start() {
    float waterHeight = 0.0f;

    //初始化各个渲染器
    MainRenderer mainRenderer;
    WaterFbo waterFbo;
    WaterRenderer waterRenderer(waterFbo);
    Light light(glm::vec3(4.0, 6.0, -4.0), glm::vec3(1, 1, 1));
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CLIP_DISTANCE0);

    while (!glfwWindowShouldClose(DisplayManager::window())) {

        //
        processInput(DisplayManager::window());
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DisplayManager::calcFrame();
        //创建一个渲染程序


        //渲染反射缓冲
        float distance = 2 * (camera.getPosition().y - waterHeight);
        float negative = distance > 0.0 ? 1.0f : -1.0f;
        camera.getPosition().y -= distance;
        camera.invertPitch();
        waterFbo.bindReflectionFbo();
        mainRenderer.setUboPlane(glm::vec4(0.0, 1, 0.0, waterHeight));
        mainRenderer.render(camera);
        //复原摄像机
        camera.getPosition().y += distance;
        camera.invertPitch();

        //渲染折射缓冲
        waterFbo.bindRefractionFbo();
        Camera cameraTmp(camera);
        mainRenderer.setUboPlane(glm::vec4(0.0, -1, 0.0, waterHeight));
        mainRenderer.render(cameraTmp);

        mainRenderer.setUboPlane(glm::vec4(0.0, 0.0, 0.0, 0.0));
        waterFbo.unbindFbo();

        //渲染实际画面

        mainRenderer.render(camera);
        waterRenderer.render(camera, light);

        //清除缓冲，响应窗口事件
        DisplayManager::update();
    }
    glfwTerminate();
}

void GameEngine::processInput(GLFWwindow *wwindow) {
    auto deltaTime = static_cast<float>(DisplayManager::getDeltaTime());
    if (glfwGetKey(wwindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(wwindow, true);
    if (glfwGetKey(wwindow, GLFW_KEY_UP) == GLFW_PRESS)
        ratio = std::min(ratio + 0.001f, 1.0f);
    if (glfwGetKey(wwindow, GLFW_KEY_DOWN) == GLFW_PRESS)
        ratio = std::max(ratio - 0.001f, 0.0f);
    //处理视角移动
    if (glfwGetKey(wwindow, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(wwindow, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(wwindow, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(wwindow, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(wwindow, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(wwindow, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

}

void GameEngine::mouse_callback(GLFWwindow *wwindow, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (float) xpos;
        lastY = (float) ypos;
        firstMouse = false;
    }
    float xoffset = (float) xpos - lastX;
    float yoffset = lastY - (float) ypos;
    lastX = (float) xpos;
    lastY = (float) ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void GameEngine::scroll_callback(GLFWwindow *wwindow, double xoffset, double yoffset) {
    camera.ProcessMouseScroll((float) yoffset);
}













