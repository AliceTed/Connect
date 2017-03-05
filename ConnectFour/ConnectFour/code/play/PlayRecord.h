#pragma once

/**
* @file PlayRecord.h
* @brief 勝敗を記録
* @author 松尾裕也
* @date 2016/3/5
*/
#include <unordered_map>
#include "../id/CONTROLLER_ID.h"
class PlayRecord
{
public:
	PlayRecord();
	//デストラクタで記録
	~PlayRecord();
	//勝利者、勝利回数を追加
	void addWinner(CONTROLLER_ID _id);
	//引き分け回数を追加
	void addDraw();
private:
	//合計試合数を計算
	int calc_SumPlayCount()const;
	//記録
	void record();
private:
	int m_DrawCount;
	std::unordered_map<CONTROLLER_ID, int> m_WinnerCount;
};