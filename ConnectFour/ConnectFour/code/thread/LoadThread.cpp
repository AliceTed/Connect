#include "LoadThread.h"
#include "../data/DataManager.h"
#include "../data/define\TextureLoadDesc.h"
#include "../data/define\MeshLoadDesc.h"
LoadThread::LoadThread(DataManager* _dataManager)
	:m_dataManager(_dataManager),
	m_isEnd(false)
{
}

LoadThread::~LoadThread()
{
	exit();
}

void LoadThread::run()
{
	while (!m_isEnd)
	{
		m_dataManager->load(TextureLoadDesc(TEXTURE_ID::TITLE_ROGO, "title_rogo"));
		m_dataManager->load(MeshLoadDesc(MESH_ID::SPHERE, "sphere"));
		m_isEnd = true;
	}
}

bool LoadThread::isEnd() const
{
	return m_isEnd;
}

void LoadThread::exit()
{
	m_isEnd = true;
	join();
}
