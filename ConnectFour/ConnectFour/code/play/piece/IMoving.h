#pragma once
/**
* @file IMoving.h
* @brief 動きかたの定義用インターフェイス
* @author 松尾裕也
* @date 2016/2/12
*/
struct GSvector3;
class IMoving
{
public:
	virtual ~IMoving(){}
	virtual bool moveTo(const GSvector3& _v,float deltaTime)=0;
};
