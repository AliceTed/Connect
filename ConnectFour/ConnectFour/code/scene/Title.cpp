#include "Title.h"
#include "../play/PlayControl.h"
#include "../device/Input.h"
#include "../renderer/IRenderer.h"
#include "../renderer/desc/StringRenderDesc.h"
#include "../renderer/desc/SpriteRenderDesc.h"
#include "../id/TEXTURE_ID.h"
Title::Title()
	:m_palyControl(nullptr),
	m_toggle(0.0f)
{
}
void Title::initialize()
{
	m_isEnd = false;
	m_palyControl = std::make_unique<PlayControl>();
	m_palyControl->replay();
	m_palyControl->start();
	m_toggle = 0.01f;
}

void Title::update(float deltaTime)
{
	m_isEnd = Input::getInstance().keyDown(KEY::SPACE);
	m_palyControl->update(deltaTime);

	if (m_palyControl->isFinish() || m_palyControl->isWin())
	{
		m_palyControl.reset();
		m_palyControl = nullptr;
		m_palyControl = std::make_unique<PlayControl>();
		m_palyControl->replay();
		m_palyControl->start();
	}
}

void Title::draw(IRenderer * renderer)
{
	m_palyControl->draw(renderer);

	static StringRenderDesc desc;
	//desc.color.rgb = GSvector3(0, 0,0);
	desc.position = GSvector2(600, 500);
	desc.font.size = 50;
	desc.font.name = "ƒƒCƒŠƒI";
	desc.string = "Replay";
	if (desc.color.a > 1 || desc.color.a < 0)
	{
		m_toggle *= -1;
	}
	desc.color.a += m_toggle;
	renderer->draw(desc);

	desc.position = GSvector2(520, 450);
	desc.string = "Push Space Key";
	renderer->draw(desc);

	SpriteRenderDesc sprite;
	sprite.textureID = static_cast<unsigned int>(TEXTURE_ID::TITLE_ROGO);
	sprite.matrix.translate(GSvector3(80, 50, 0));
	renderer->draw(sprite);
}

void Title::finish()
{
	m_palyControl.reset();
	m_palyControl = nullptr;
}

const SceneMode Title::next() const
{
	return SceneMode::GAMEPLAY;
}

const bool Title::isEnd() const
{
	return m_isEnd;
}

const bool Title::isExit() const
{
	return false;
}
