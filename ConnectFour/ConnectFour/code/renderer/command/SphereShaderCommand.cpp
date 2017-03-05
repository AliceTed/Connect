#include "SphereShaderCommand.h"
#include <gslib.h>
#include "../../id/CastID.h"
#include "../../id/MESH_ID.h"
#include "../../id/SHADER_ID.h"
#include "../../id/TEXTURE_ID.h"
SphereShaderCommand::SphereShaderCommand(const SphereShaderDesc & _desc)
	:m_desc(_desc)
{
}

void SphereShaderCommand::render()
{
	GSmatrix4 proj, view;
	glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
	glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

	gsBeginShader(CastID::id2uint(SHADER_ID::SPHERE));
	const LightDesc& light = m_desc.light;
	GSvector3 lightPositionEye = light.position *view;
	gsSetShaderParam3f("u_lightPositionEye", &lightPositionEye);
	gsSetShaderParam4f("u_lightAmbient", &light.ambient);
	gsSetShaderParam4f("u_lightDiffuse", &light.diffuse);
	gsSetShaderParam4f("u_lightSpecular", &light.specular);
	gsSetShaderParamMatrix4("u_matWorld", &m_desc.matrix);
	gsSetShaderParamMatrix4("u_matProjection", &proj);
	gsSetShaderParamMatrix4("u_matView", &view);

	gsSetShaderParamTexture("u_baseMap", 0);
	gsSetShaderParamTexture("u_normalMap", 1);
	glActiveTexture(GL_TEXTURE0);
	gsBindTexture(CastID::id2uint(TEXTURE_ID::ROCKWALL));
	glActiveTexture(GL_TEXTURE1);
	gsBindTexture(CastID::id2uint(TEXTURE_ID::ROCKWALL_NORMAL));

	gsSetShaderParam4f("u_color", &m_desc.color);
	gsDrawMeshEx(m_desc.meshID);
	gsEndShader();

	gsUnbindTexture(CastID::id2uint(TEXTURE_ID::ROCKWALL_NORMAL));
	glActiveTexture(GL_TEXTURE0);
	gsUnbindTexture(CastID::id2uint(TEXTURE_ID::ROCKWALL));	
}
