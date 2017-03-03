#pragma once

/**
* @file DataManager.h
* @brief �f�[�^�Ǘ��p�N���X
* @author �����T��
* @date 2016/2/15
*/
#include<gslib.h>
#include "../id/CastID.h"
#include "../thread/CriticalSection.h"
struct TextureLoadDesc;
struct MeshLoadDesc;
class DataManager
{
public:
	DataManager()=default;
	~DataManager()=default;
	static void load(const TextureLoadDesc& _desc);
	static void load(const MeshLoadDesc& _desc);

	static void release();
protected:
	/**
	* @fn
	* @brief �w��֐��Ńf�[�^���J��
	* @param (_func) �w��֐�
	* @param (_size) �J������f�[�^�̃T�C�Y
	*/
	template<class Func,class DataEnum> 
	static void eachRelease(Func _func, DataEnum _size);
private:
	//CriticalSection m_lock;
};

template<class Func, class DataEnum>
void DataManager::eachRelease(Func _func, DataEnum _size)
{
	for (auto i = 0U; i < CastID::id2uint(_size); i++)
	{
		_func(i);
	}
}
