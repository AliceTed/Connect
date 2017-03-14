#pragma once
#include <memory>
#include <vector>
#include "../id/CONTROLLER_ID.h"
class Rule;
class IRenderer;
class Controller;
using ControllerPtr = std::shared_ptr<Controller>;
class ControllerManager
{
public:
	ControllerManager();
	~ControllerManager();
	void initialize();
	void add(ControllerPtr _controller);
	void start();
	void update(float deltaTime,const Rule& _rule);
	void draw(IRenderer* _renderer)const;

	//�Q�[�����I�������
	bool isFinish()const;
	CONTROLLER_ID getCurrentID()const;
	//�o�^����Ă���R���g���[����ID�S�Ă�z��Ŏ擾
	std::vector<CONTROLLER_ID> getActiveID()const;
private:
	void next();
	void change(Controller* _next);
	Controller* getCurrentController()const;
private:
	using Container = std::vector<ControllerPtr>;
	Container m_container;
	Controller* m_current;
	unsigned int m_currentIndex;
	bool m_isFinish;
};