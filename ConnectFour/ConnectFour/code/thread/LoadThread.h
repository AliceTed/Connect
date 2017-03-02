#pragma once
/**
* @file LoadThread.h
* @brief ロード用thread
* @author 松尾裕也
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
	//強制終了
	void exit();
private:
	bool m_isEnd;
	DataManager* m_dataManager;
};