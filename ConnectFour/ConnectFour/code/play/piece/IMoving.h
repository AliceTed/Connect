#pragma once
/**
* @file IMoving.h
* @brief ���������̒�`�p�C���^�[�t�F�C�X
* @author �����T��
* @date 2016/2/12
*/
struct GSvector3;
class IMoving
{
public:
	virtual ~IMoving(){}
	virtual bool moveTo(const GSvector3& _v,float deltaTime)=0;
};
