#pragma once

/**
* @file DataManager.h
* @brief データ管理用クラス
* @author 松尾裕也
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
	* @brief 指定関数でデータを開放
	* @param (_func) 指定関数
	* @param (_size) 開放するデータのサイズ
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
