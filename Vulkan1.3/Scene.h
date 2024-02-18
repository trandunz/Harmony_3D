#pragma once
#ifndef _SCENE_H
#define _SCENE_H

class Scene
{
public:
	virtual ~Scene() {};

	virtual void Start() {};
	virtual void Update() {};
	virtual void Draw() {};
};
#endif

