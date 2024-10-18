#pragma once
#include<graphics.h>
#include<iostream>
class Scene
{
public:
	Scene() = default;
	~Scene() = default;
	virtual void on_enter() {}
	virtual void on_input(const ExMessage& msg) {}
	virtual void on_updata(int delta) {}
	virtual void on_draw() {}
	virtual void on_exit() {}
private:

};

