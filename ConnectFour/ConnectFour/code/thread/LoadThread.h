#pragma once
/**
* @file LoadThread.h
* @brief [hpthread
* @author ¼öTç
* @date 2016/2/15
*/

#include "Thread.h"
class DataManager;
class LoadThread:public Thread
{
public:
	LoadThread(DataManager* _dataManager);
	~LoadThread();
	virtual void run()override;
	bool isEnd()const;
	//­§I¹
	void exit();
private:
	bool m_isEnd;
	DataManager* m_dataManager;
};