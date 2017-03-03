#include "Load.h"
#include "../thread/LoadThread.h"
#include "../data/DataManager.h"
#include "../data/define\TextureLoadDesc.h"
#include "../data/define\MeshLoadDesc.h"
Load::Load(DataManager * _dataManager)
	:/*m_dataManager(_dataManager),*/
	m_loader(nullptr),
	m_isEnd(false)
{
}

void Load::initialize()
{
	//m_loader = std::make_shared<LoadThread>(m_dataManager);
	//m_loader->start();
}

void Load::update(float deltaTime)
{
	/*m_dataManager->load(TextureLoadDesc(TEXTURE_ID::TITLE_ROGO, "title_rogo"));
	m_dataManager->load(MeshLoadDesc(MESH_ID::SPHERE, "sphere"));*/
	m_isEnd = true;
}

void Load::draw(IRenderer * renderer)
{
}

void Load::finish()
{
	//m_loader.reset();
	//m_loader = nullptr;
}

const SceneMode Load::next() const
{
	return SceneMode::TITLE;
}

const bool Load::isEnd() const
{
	return m_isEnd;//m_loader->isEnd();
}

const bool Load::isExit() const
{
	return false;
}
