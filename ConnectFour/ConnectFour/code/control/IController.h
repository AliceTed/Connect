#pragma once
/**
* @file IController.h
* @brief �R���g���[���̃C���^�[�t�F�C�X
* @author �����T��
* @date 2016/2/8
*/
class IController
{
public:
	virtual ~IController() {}

	virtual void left()=0;
	virtual void right() = 0;
	virtual void place() = 0;
	virtual void nothing() = 0;
};