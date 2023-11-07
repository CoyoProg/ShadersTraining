#include "MyScene.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include <cmath>
#include <chrono> 

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

#include "CubeMesh.h"


MyScene::MyScene()
{
}

MyScene::~MyScene() {
    clean();
}

void MyScene::setGame(Game* _game) {
    game = _game;
}

void MyScene::load() 
{
    std::srand((int)std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(50.9f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    cubeMesh = new CubeMesh();
    cubeMesh->load();

    //glEnable(GL_CULL_FACE);
    //glFrontFace(GL_CW);

    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    cubes.emplace_back(0.0f, 0.0f, cubeMesh);
}

void MyScene::clean() 
{
    cubeMesh->clean();
    delete cubeMesh;
}

void MyScene::pause() 
{
}

void MyScene::resume() 
{
}

void MyScene::handleEvent(const InputState& inputState) 
{
    if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_E))
    {
        tesselationLevel += 1;
        std::cout << tesselationLevel << std::endl;
    }
    if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_Q))
    {
        if (tesselationLevel > 1)
        {
            tesselationLevel -= 1;
        }
    }

    if (inputState.keyboardState.isJustPressed(SDL_SCANCODE_W)) {
        wireFrame = !wireFrame;
    }
}

void MyScene::update(float dt) 
{
    for (auto& cube : cubes)
    {
        cube.update();
    }

}

void MyScene::draw() 
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    shader.setInteger("tessLevel", tesselationLevel);

    for (auto& cube : cubes) 
    {
        cube.drawTesselation(shader);
    }

    if (wireFrame)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
