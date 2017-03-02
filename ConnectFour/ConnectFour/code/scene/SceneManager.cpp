#include"SceneManager.h"
SceneManager::SceneManager()
	:m_Scenes(), m_currentScene(nullptr)
{
}
SceneManager::~SceneManager()
{
	m_currentScene = nullptr;
	m_Scenes.clear();
}
void SceneManager::add(SceneMode _name, Scene_Ptr _scene)
{
	m_Scenes.insert(std::make_pair(_name, _scene));
}
void SceneManager::change(SceneMode _name)
{
	m_currentScene = m_Scenes.at(_name).get();
	m_currentScene->initialize();
}
void SceneManager::update(float _deltaTime)
{
	m_currentScene->update(_deltaTime);

	currentFinish();
}
void SceneManager::draw(IRenderer * _renderer)
{
	m_currentScene->draw(_renderer);
}

const bool SceneManager::isExit() const
{
	return m_currentScene->isExit();
}

void SceneManager::currentFinish()
{
	if (!m_currentScene->isEnd())
	{
		return;
	}
	m_currentScene->finish();
	change(m_currentScene->next());
}
