#include "DataManager.h"
#include "define\TextureLoadDesc.h"
#include "define\MeshLoadDesc.h"
#include "../util/Message.h"
void DataManager::load(const TextureLoadDesc & _desc)
{
	load(_desc, gsLoadTexture, "�e�N�X�`���̓ǂݍ��݃G���[");
	
	//CriticalSection::Lock guard(m_lock);
	//std::string name = _desc.m_path + _desc.m_name + _desc.m_extension;
	//if (gsLoadTexture(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
	//Message::send("�e�N�X�`���̓ǂݍ��݃G���[",name);
}

void DataManager::load(const MeshLoadDesc & _desc)
{
	auto loader = _desc.m_isShader ? gsLoadMeshEx : gsLoadMesh;
	load(_desc, loader, "���b�V���̓ǂݍ��݃G���[");
	
	//CriticalSection::Lock guard(m_lock);
	//std::string name = _desc.m_path + _desc.m_name + _desc.m_extension;
	//auto loader = _desc.m_isShader ? gsLoadMeshEx : gsLoadMesh;
	//GSboolean(*loader)(GSuint, const char*) =_desc.m_isShader ? gsLoadMeshEx : gsLoadMesh;
	//if (loader(CastID::id2uint(_desc.m_id), name.c_str()) == GS_TRUE)return;
	//Message::send("���b�V���̓ǂݍ��݃G���[", name);
}

void DataManager::release()
{
	//�S�Ẵ��\�[�X���
	gsFinishGraphics();
	/*eachRelease(gsDeleteTexture,TEXTURE_ID::SIZE);
	eachRelease(gsDeleteMesh, MESH_ID::SIZE);*/
}
