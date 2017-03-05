#pragma once
/**
* @file SphereShaderCommand.h
* @brief スフィアシェーダ用描画コマンド
* @author 松尾裕也
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