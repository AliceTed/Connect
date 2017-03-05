#include <GSgame.h>
#include <memory>
#include "renderer\Renderer.h"
#include "scene\SceneManager.h"

#include "data\DataManager.h"
#include "data\define\TextureLoadDesc.h"
#include "data\define\MeshLoadDesc.h"
#include "data\define\ShaderLoadDesc.h"
#include "id\RENDER_TARGET_ID.h"

#include "gamethread\MyGameThread.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(800, 600),
		m_renderer(),
		m_gameTread(nullptr)
	{
	}
private:
	virtual void start() override
	{
		DataManager::load(TextureLoadDesc(TEXTURE_ID::TITLE_ROGO, "title_rogo"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL, "rockwall"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL_NORMAL, "rockwall_normal"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL_MASK, "rockwall_mask"));
		
		DataManager::load(MeshLoadDesc(MESH_ID::SPHERE, "sphere",true));
		
		//defalt.glslv�̓|�X�g�G�t�F�N�g�p�o�[�e�b�N�X�V�F�[�_�[
		DataManager::load(ShaderLoadDesc(SHADER_ID::SPHERE, "sphere"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BRIGHT,"defalt","bright"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BLOOM_BLUR, "defalt", "bloom_blur"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BLOOM, "defalt", "bloom"));

		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE),800,600,GS_TRUE, GS_TRUE,GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BRIGHT),128,128, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 128, 128, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM), 800, 600, GS_TRUE, GS_TRUE, GS_FALSE);
		m_gameTread = std::make_unique<MyGameThread>(&m_renderer);
		m_gameTread->start();

		//AI�T�����R���|�W�b�g�p�^�[���ł���Ă݂�H

		//m_renderer->initialize();
		//LightDesc light;
		//light.ambient = Color4(0.5f, 0.5f, 0.5f, 1.0f);//Color4(1.0f, 1.0f,1.0f, 1.0f);
		//light.diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.specular = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.position = Vector3(100.0f,100.0f,100.0f);
		//m_renderer->light(light);
		//m_renderer->lookAt({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	}

	// �X�V
	virtual void update(float deltaTime) override
	{
		//base�̃t���[���o�b�t�@�ɏ�������
		gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		 // �����_�����O���s��
		 m_renderer.render();

		gsEndRenderTarget();

		//���x���o bright�ɏ�������
		gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BRIGHT));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gsBeginShader(CastID::id2uint(SHADER_ID::BRIGHT));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParam1f("u_minBright", 0.25f);
		gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		gsEndShader();
		gsEndRenderTarget();

		//���o�������x�Ƀu���[��������@
		gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gsBeginShader(CastID::id2uint(SHADER_ID::BLOOM_BLUR));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BRIGHT), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParam2f("u_direction", &GSvector2(1, 0));
		gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		gsEndShader();
		gsEndRenderTarget();

		//�f�t�H���g�ƃu���[�����������̂�����
		gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM));
		gsBeginShader(CastID::id2uint(SHADER_ID::BLOOM));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BASE), 0);
		glActiveTexture(GL_TEXTURE1);
		gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParamTexture("u_bloomColor", 1);
		gsSetShaderParam1f("u_toneScale", 0.8f);
		gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		gsEndShader();
		gsEndRenderTarget();

		gsUnindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 0);

		GSuint bloom = CastID::id2uint(RENDER_TARGET_ID::BLOOM);
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(bloom, 0);
		gsDrawRenderTarget(bloom);

		gsUnindRenderTargetTexture(bloom, 0);

	}
	// �`��
	virtual void draw() override
	{
	}
	// �I��
	virtual void end() override
	{
		DataManager::release();
	}
private:
	Renderer m_renderer;
	std::unique_ptr<MyGameThread>m_gameTread;
};

int main()
{
	return MyGame().run();
}
