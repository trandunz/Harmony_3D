#pragma once
#ifndef _SCENE_DEMO_H
#define _SCENE_DEMO_H

#include "Scene.h"
class Scene_Demo :
    public Scene
{
public:
    ~Scene_Demo();

    virtual void Start() override;
    virtual void Update() override;
    virtual void Draw() override;

protected:
    class StaticMeshComponent* DemoStaticMeshComponent{ nullptr };
};
#endif

