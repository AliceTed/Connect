#include "MyGameThread.h"
#include <memory>
#include "../scene\Load.h"
#include "../scene\Title.h"
#include "../scene\GamePlay.h"

#include "../renderer/IRenderer.h"
#include "../renderer/desc/MeshRenderDesc.h"

#include "../renderer/desc/SpriteRenderDesc.h"
#include "../renderer/desc/StringRenderDesc.h"
MyGameThread::MyGameThread(IRenderer * _device)
	:GameThread(_device),
	m_isEnd(false),
	m_sceneManager()
{
}

MyGameThread::~MyGameThread()
{
	exit();
}

void MyGameThread::exit()
{
	m_isEnd = true;
	join();
}

void MyGameThread::initialize()
{
	//loadに関してマルチスレッド対応していないのでシーンを作製しない
	//Scene_Ptr load = std::make_shared<Load>();
	Scene_Ptr title = std::make_shared<Title>();
	Scene_Ptr gameplay = std::make_shared<GamePlay>();
	//m_sceneManager.add(SceneMode::LOAD, load);
	m_sceneManager.add(SceneMode::TITLE, title);
	m_sceneManager.add(SceneMode::GAMEPLAY, gameplay);
	m_sceneManager.change(SceneMode::TITLE);
}

void MyGameThread::update(float deltaTime)
{
	m_sceneManager.update(deltaTime);
}
void MyGameThread::draw()
{
	device()->begin();

	m_sceneManager.draw(device());	

	/*SpriteRenderDesc sprite;
	sprite.matrix.translate(GSvector3(100.5f,3,0));
	device()->draw(sprite);

	StringRenderDesc string;
	string.string = "Hoge";
	device()->draw(string);

	MeshRenderDesc desc;
	desc.color = GScolor(1, 0, 0, 1);
	device()->draw(desc);*/
	
	device()->end();
	device()->sync();
}

void MyGameThread::end()
{
}

bool MyGameThread::isEnd() const
{
	return m_isEnd;
}
