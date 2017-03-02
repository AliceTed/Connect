#include "DataManager.h"
#include "define\TextureLoadDesc.h"
#include "define\MeshLoadDesc.h"
#include "../util/Message.h"
void DataManager::load(const TextureLoadDesc & _desc)
{
	CriticalSection::Lock guard(m_lock);
	std::string name = _desc.m_path + _desc.m_name + _desc.m_extension;
	if (gsLoadTexture(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
	Message::send("テクスチャの読み込みエラー",name);
}

void DataManager::load(const MeshLoadDesc & _desc)
{
	CriticalSection::Lock guard(m_lock);
	std::string name = _desc.m_path + _desc.m_name + _desc.m_extension;
	GSboolean(*loder)(GSuint, const char*) = _desc.m_isShader ? gsLoadMeshEx : gsLoadMesh;
	if (loder(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
	Message::send("メッシュの読み込みエラー", name);
}

void DataManager::release()
{
	eachRelease(gsDeleteTexture,TEXTURE_ID::SIZE);
	eachRelease(gsDeleteMesh, MESH_ID::SIZE);
}
