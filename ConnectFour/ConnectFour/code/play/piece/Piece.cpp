#include "Piece.h"
#include "../../id/CastID.h"
#include "../../renderer/IRenderer.h"
#include "../../renderer/desc/SphereShaderDesc.h"
#include "../../id/MESH_ID.h"
#include "../desk/DeskDefine.h"
Piece::Piece(const GSvector3& _position,COLOR_ID _id)
	:m_position(_position),
	m_color(_id),
	m_rotateY(0.0f),
	m_rotSpeed(0.2f),
	m_isConnect(false)
{
}

Piece::Piece(const GSvector3 & _position, CONTROLLER_ID _id)
	:Piece(_position,CastID::controllerID2ColorID(_id))
{
}

Piece::~Piece()
{
}
void Piece::update(float deltaTime)
{
	m_rotateY += deltaTime*m_rotSpeed;
}
void Piece::draw(IRenderer * _renderer, float _alpha) const
{
	SphereShaderDesc desc;
	float radius = PIECE_SIZE*0.5f;
	desc.meshID = CastID::id2uint(MESH_ID::SPHERE);
	desc.matrix.rotateY(m_rotateY);
	desc.matrix.scale(GSvector3(radius, radius, radius));	
	desc.matrix.translate(m_position);
	desc.color = CastID::colorID2Color(m_color);
	desc.color.a = _alpha;
	desc.light.position = m_position;
	_renderer->draw(desc);
}

bool Piece::isSameType(COLOR_ID _id) const
{
	return m_color==_id;
}

void Piece::connect()
{
	m_isConnect = true;
}
