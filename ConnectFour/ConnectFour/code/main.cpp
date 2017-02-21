#include <GSgame.h>
#include <memory>
#include "renderer\Renderer.h"
#include "scene\SceneManager.h"
#include "scene\Load.h"
#include "scene\Title.h"
#include "scene\GamePlay.h"
#include "data\DataManager.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(800, 600),
		m_renderer(std::make_unique<Renderer>()),
		m_sceneManager(),
		m_dataManager()
	{
	}
private:
	virtual void start() override
	{
		m_renderer->initialize();
		LightDesc light;
		light.ambient = Color4(0.5f, 0.5f, 0.5f, 1.0f);//Color4(1.0f, 1.0f,1.0f, 1.0f);
		light.diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		light.specular = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		light.position = Vector3(100.0f,100.0f,100.0f);

		m_renderer->light(light);
	

		m_renderer->lookAt({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
		Scene_Ptr load = std::make_shared<Load>(&m_dataManager);
		Scene_Ptr title = std::make_shared<Title>();
		Scene_Ptr gameplay = std::make_shared<GamePlay>();
		m_sceneManager.add(SceneMode::LOAD, load);
		m_sceneManager.add(SceneMode::TITLE,title);
		m_sceneManager.add(SceneMode::GAMEPLAY,gameplay);
		m_sceneManager.change(SceneMode::LOAD);		
	}

	// XV
	virtual void update(float deltaTime) override
	{
		m_sceneManager.update(deltaTime);
	}
	// •`‰æ
	virtual void draw() override
	{
		m_sceneManager.draw(m_renderer.get());
	}
	// I—¹
	virtual void end() override
	{
		m_dataManager.release();
	}
private:
	using RenderPtr = std::unique_ptr<IRenderer>;
	RenderPtr m_renderer;
	SceneManager m_sceneManager;
	DataManager m_dataManager;
};

int main()
{
	return MyGame().run();
}
