#pragma once
/**
* @file IDeskVisit.h
* @brief DeskฬKโาpC^[tFCX
* @author ผ๖T็
* @date 2016/2/8
*/
#include "Desk/DeskDefine.h"
class IDeskVisitor
{
public:
	virtual~IDeskVisitor() {}
	virtual void visit(const Container& _container)=0;
};