#pragma once
/**
* @file IDeskVisit.h
* @brief Desk�̖K��җp�C���^�[�t�F�C�X
* @author �����T��
* @date 2016/2/8
*/
#include "Desk/DeskDefine.h"
class IDeskVisitor
{
public:
	virtual~IDeskVisitor() {}
	virtual void visit(const Container& _container)=0;
};