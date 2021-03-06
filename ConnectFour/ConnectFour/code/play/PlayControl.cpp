#include "PlayControl.h"
#include "../play/desk/Desk.h"
#include "../control/Controller.h"
#include "../control/PlaceTarget.h"

#include "../ai/EasyAI.h"
#include "../ai/NormalAI.h"
#include "../ai/HardAI.h"
#include "../handler/InputHandler.h"
#include "../handler/AIHandler.h"

#include "../replay/CommandReader.h"
#include "../replay/CommandRecorder.h"
#include "../handler/ReplayHandler.h"

#include "../renderer/IRenderer.h"
#include "../control/ControllerManager.h"
#include "../renderer/desc/LookAtDesc.h"
#include "../renderer/desc/SkyBoxRenderDesc.h"
#include "../id/CastID.h"
#include "../id/MESH_ID.h"
PlayControl::PlayControl()
	:m_desk(std::make_shared<Desk>()),
	m_manager(std::make_shared<ControllerManager>()),
	m_rule(),
	m_recorder(std::make_shared<CommandRecorder>()),
	m_time(0.0f)
{
	m_desk->reset();
	m_manager->initialize();
}

PlayControl::~PlayControl()
{
	
}

void PlayControl::start()
{
	m_manager->start();
}

void PlayControl::update(float deltaTime, bool _isStop)
{
	m_desk->update(deltaTime);
	if (_isStop)return;
	m_manager->update(deltaTime, m_rule);
	m_time += deltaTime;
}

void PlayControl::draw(IRenderer * _renderer) const
{
	const float size = MAP_SIZE*PIECE_SIZE;
	const float half = size*0.5f-(PIECE_SIZE*0.5f);
	LookAtDesc lookat;
	lookat.eye = { half,half,size*1.5f};
	lookat.at = { half,half,0 };
	_renderer->lookAt(lookat);

	SkyBoxRenderDesc skybox;
	skybox.meshID = CastID::id2uint(MESH_ID::SKYDOME);
	//skybox.time = -m_time;
	_renderer->draw(skybox);

	m_desk->draw(_renderer);
	m_manager->draw(_renderer);	
}

void PlayControl::addPlayer(CONTROLLER_ID _id)
{
	TargetPtr target = std::make_shared<PlaceTarget>(_id);
	HandlerPtr handler = std::make_shared<InputHandler>();
	ControllerPtr controller = std::make_shared<Controller>(m_desk, handler, target, _id, m_recorder);
	m_manager->add(controller);
}

void PlayControl::addEasyAI(CONTROLLER_ID _id)
{
	TargetPtr target = std::make_shared<PlaceTarget>(_id);
	AIPtr level = std::make_shared<EasyAI>();
	HandlerPtr handler = std::make_shared<AIHandler>(level);
	ControllerPtr controller = std::make_shared<Controller>(m_desk, handler, target, _id, m_recorder);
	m_manager->add(controller);
}

void PlayControl::addNormalAI(CONTROLLER_ID _id)
{
	TargetPtr target = std::make_shared<PlaceTarget>(_id);
	AIPtr level = std::make_shared<NormalAI>(m_desk, target,m_manager);
	HandlerPtr handler = std::make_shared<AIHandler>(level);
	ControllerPtr controller = std::make_shared<Controller>(m_desk, handler, target, _id, m_recorder);
	m_manager->add(controller);
}
void PlayControl::addHardAI(CONTROLLER_ID _id)
{
	TargetPtr target = std::make_shared<PlaceTarget>(_id);
	AIPtr level = std::make_shared<HardAI>(m_desk, target, m_manager);
	HandlerPtr handler = std::make_shared<AIHandler>(level);
	ControllerPtr controller = std::make_shared<Controller>(m_desk, handler, target, _id, m_recorder);
	m_manager->add(controller);
}
void PlayControl::replay()
{
	CommandReader reader("record");
	for (auto i : reader.getActiveID())
	{
		TargetPtr target = std::make_shared<PlaceTarget>(i);
		HandlerPtr handler = std::make_shared<ReplayHandler>(reader.getCommand(i));
		ControllerPtr rep = std::make_shared<Controller>(m_desk, handler, target, i, m_recorder);
		m_manager->add(rep);
	}
}

bool PlayControl::isFinish() const
{
	return m_desk->isFinish() ;
}

bool PlayControl::isWin() const
{
	return m_manager->isFinish()&&gsGetKeyTrigger(GKEY_SPACE);
}

CONTROLLER_ID PlayControl::getWinner() const
{
	return m_manager->getCurrentID();
}

void PlayControl::record()
{
	m_recorder->record("record");
}
