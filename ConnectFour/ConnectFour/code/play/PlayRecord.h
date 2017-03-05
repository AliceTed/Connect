#pragma once

/**
* @file PlayRecord.h
* @brief ���s���L�^
* @author �����T��
* @date 2016/3/5
*/
#include <unordered_map>
#include "../id/CONTROLLER_ID.h"
class PlayRecord
{
public:
	PlayRecord();
	//�f�X�g���N�^�ŋL�^
	~PlayRecord();
	//�����ҁA�����񐔂�ǉ�
	void addWinner(CONTROLLER_ID _id);
	//���������񐔂�ǉ�
	void addDraw();
private:
	//���v���������v�Z
	int calc_SumPlayCount()const;
	//�L�^
	void record();
private:
	int m_DrawCount;
	std::unordered_map<CONTROLLER_ID, int> m_WinnerCount;
};