#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_
#include "IScene.h"
#include <unordered_map>
#include <memory>
using Scene_Ptr = std::shared_ptr<IScene>;
class IRenderer;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void add(SceneMode _name, Scene_Ptr _scene);
	void change(SceneMode _name);
	void update(float _deltaTime);
	void draw(IRenderer * _renderer);
	const bool isExit()const;
private:
	void currentFinish();
private:

	using Scenes= std::unordered_map<SceneMode, Scene_Ptr>;
	Scenes m_Scenes;
	IScene* m_currentScene;
};
#endif