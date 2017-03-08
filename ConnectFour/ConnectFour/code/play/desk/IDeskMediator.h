#pragma once
/**
* @file IDeskMediator.h
* @brief デスクのインターフェイス
* @author 松尾裕也
* @date 2016/2/8
*/
#include<vector>
#include "../../id/CONTROLLER_ID.h"
#include "../../util/IntVector2.h"
#include "DeskDefine.h"
class Rule;
class IDeskVisitor;
class IDeskMediator
{
public:
	virtual ~IDeskMediator(){}
	virtual bool isFinish()const = 0;
	virtual bool isWin(const Rule& _rule,const IntVector2& _location,CONTROLLER_ID _id) = 0;
	virtual void accept(IDeskVisitor* _visitor)const=0;
	virtual void placePiece(const IntVector2& _location, CONTROLLER_ID _id)=0;

	virtual std::vector<IntVector2> getFreeLoactions()const=0;
	virtual IntVector2 getFreeMinimalLocation()const=0;
	virtual IntVector2 getFreeSpaceColumn(unsigned int _column)const = 0;
	virtual bool isFreeLocation(const IntVector2& _location)const=0;
	virtual bool isSamePiece(const IntVector2& _location,CONTROLLER_ID _id)const=0;

	virtual void push_back()=0;
	virtual void pop_back()=0;
};
