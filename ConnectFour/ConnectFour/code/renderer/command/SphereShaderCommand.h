#pragma once
/**
* @file SphereShaderCommand.h
* @brief �X�t�B�A�V�F�[�_�p�`��R�}���h
* @author �����T��
* @date 2016/3/5
*/
#include "IRenderCommand.h"
#include "../desc/SphereShaderDesc.h"
class SphereShaderCommand:public IRenderCommand
{
public:
	SphereShaderCommand(const SphereShaderDesc& _desc);
	virtual void render() override;
private:
	SphereShaderDesc m_desc;
};