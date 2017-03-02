#pragma once
/**
* @file IDeskVisit.h
* @brief Deskの訪問者用インターフェイス
* @author 松尾裕也
* @date 2016/2/8
*/
#include "Desk/DeskDefine.h"
class IDeskVisitor
{
public:
	virtual~IDeskVisitor() {}
	virtual void visit(const Container& _container)=0;
};