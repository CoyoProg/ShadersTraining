#ifndef MyScene_H
#define MyScene_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class MyScene : public Scene 
{
public:
    MyScene();
    ~MyScene();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    float cubeRotationAngle = 0.0f;
    Game *game;
    GLuint vao;
    CubeMesh* cubeMesh;

    Matrix4 projection;
    Shader shader;
    float tesselationLevel = 1;
    bool wireFrame = true;

    vector<CubeObject> cubes;
    float newXPosition { 0 };
};


#endif //MyScene_H
