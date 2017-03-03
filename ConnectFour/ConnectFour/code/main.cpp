#include <GSgame.h>
#include <memory>
#include "renderer\Renderer.h"
#include "scene\SceneManager.h"

#include "data\DataManager.h"
#include "data\define\TextureLoadDesc.h"
#include "data\define\MeshLoadDesc.h"

#include "gamethread\MyGameThread.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(800, 600),
		m_renderer(),
		m_gameTread(nullptr)
	{
		
	}
private:
	virtual void start() override
	{
		DataManager::load(TextureLoadDesc(TEXTURE_ID::TITLE_ROGO, "title_rogo"));
		DataManager::load(MeshLoadDesc(MESH_ID::SPHERE, "sphere"));

		m_gameTread = std::make_unique<MyGameThread>(&m_renderer);
		m_gameTread->start();

		//AI探査をコンポジットパターンでやってみる？

		//m_renderer->initialize();
		//LightDesc light;
		//light.ambient = Color4(0.5f, 0.5f, 0.5f, 1.0f);//Color4(1.0f, 1.0f,1.0f, 1.0f);
		//light.diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.specular = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.position = Vector3(100.0f,100.0f,100.0f);
		//m_renderer->light(light);
		//m_renderer->lookAt({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	}

	// 更新
	virtual void update(float deltaTime) override
	{
		// レンダリングを行う
		m_renderer.render();
	}
	// 描画
	virtual void draw() override
	{
	}
	// 終了
	virtual void end() override
	{
		DataManager::release();
	}
private:
	Renderer m_renderer;
	std::unique_ptr<MyGameThread>m_gameTread;
};

int main()
{
	return MyGame().run();
}
