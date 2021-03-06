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
		:Game(1280, 720, false),
		m_renderer(),
		m_gameTread(nullptr),
		m_minBright(0.4f),
		m_toneScale(0.8f)
	{
	}
private:
	virtual void start() override
	{
		//データのlordをクラス化する
		DataManager::load(TextureLoadDesc(TEXTURE_ID::TITLE_ROGO, "title_rogo"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL, "rockwall"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL_NORMAL, "rockwall_normal"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::ROCKWALL_MASK, "rockwall_mask"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::SKYDOME, "skydome"));
		DataManager::load(TextureLoadDesc(TEXTURE_ID::CIRCLE_MASK, "circle_mask"));


		DataManager::load(MeshLoadDesc(MESH_ID::SPHERE, "sphere", true));
		DataManager::load(MeshLoadDesc(MESH_ID::SKYDOME, "skydome", true));

		//defalt.glslvはポストエフェクト用バーテックスシェーダー
		DataManager::load(ShaderLoadDesc(SHADER_ID::SPHERE, "sphere"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BRIGHT, "defalt", "bright"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BLOOM_BLUR, "defalt", "bloom_blur"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::BLOOM, "defalt", "bloom"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::SKYBOX, "defalt", "skybox"));
		DataManager::load(ShaderLoadDesc(SHADER_ID::RADIAL_BLUR, "defalt", "radialBlur"));

		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE), 1280, 720, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BRIGHT), 128, 128, GS_TRUE, GS_FALSE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 128, 128, GS_TRUE, GS_FALSE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM), 1280, 720, GS_TRUE, GS_FALSE, GS_FALSE);
		gsCreateRenderTarget(CastID::id2uint(RENDER_TARGET_ID::RADIAL_BLUR), 1280, 720, GS_TRUE, GS_FALSE, GS_FALSE);


		m_gameTread = std::make_unique<MyGameThread>(&m_renderer);
		m_gameTread->start();

		//AI探査をコンポジットパターンでやってみる？
		
		//m_renderer->initialize();
		//LightDesc light;
		//light.ambient = Color4(0.5f, 0.5f, 0.5f, 1.0f);//Color4(1.0f, 1.0f,1.0f, 1.0f);
		//light.diffuse = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.specular = Color4(1.0f, 1.0f, 1.0f, 1.0f);
		//light.position = Vector3(100.0f,100.0f,100.0f);
		//m_renderer->light(light);
		//m_renderer->lookAt({ 0,0,5 }, { 0,0,0 }, { 0,1,0 });
	}

	// 更新
	virtual void update(float deltaTime) override
	{
		//レンダーターゲットをクラス化

		//baseのフレームバッファに書き込む
		/*gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/

		// レンダリングを行う
		m_renderer.render();

		//gsEndRenderTarget();

		////光度抽出 brightに書き込む
		//gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BRIGHT));
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//gsBeginShader(CastID::id2uint(SHADER_ID::BRIGHT));
		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BASE), 0);
		//gsSetShaderParamTexture("u_sceneColor", 0);
		//gsSetShaderParam1f("u_minBright", m_minBright);
		//gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		//gsEndShader();
		//gsEndRenderTarget();

		////抽出した光度にブラーをかける　
		//gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR));
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//gsBeginShader(CastID::id2uint(SHADER_ID::BLOOM_BLUR));
		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BRIGHT), 0);
		//gsSetShaderParamTexture("u_sceneColor", 0);
		//gsSetShaderParam2f("u_direction", &GSvector2(1, 0.0f));
		//gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		//gsEndShader();
		//gsEndRenderTarget();

		////デフォルトとブラーをかけたものを合成
		//gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BLOOM));
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//gsBeginShader(CastID::id2uint(SHADER_ID::BLOOM));
		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BASE), 0);
		//glActiveTexture(GL_TEXTURE1);
		//gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 0);
		//gsSetShaderParamTexture("u_sceneColor", 0);
		//gsSetShaderParamTexture("u_bloomColor", 1);
		//gsSetShaderParam1f("u_toneScale", m_toneScale);
		//gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		//gsEndShader();
		//gsEndRenderTarget();

		//gsUnindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BLOOM_BLUR), 0);


		////RadialBlur
		//gsBeginRenderTarget(CastID::id2uint(RENDER_TARGET_ID::RADIAL_BLUR));
		//glClearColor(0, 0, 0, 1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//gsBeginShader(CastID::id2uint(SHADER_ID::RADIAL_BLUR));
		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::BLOOM), 0);
		//gsSetShaderParamTexture("u_sceneColor", 0);
		//glActiveTexture(GL_TEXTURE1);
		//gsBindTexture(CastID::id2uint(TEXTURE_ID::CIRCLE_MASK));
		//gsSetShaderParamTexture("u_mask", 1);		

		//gsSetShaderParam1f("u_blurAmount", 0.4f);
		///*gsSetShaderParam2f("u_screenMult", &GSvector2(1.0f, 1.0f));
		//gsSetShaderParam2f("u_center", &GSvector2(0.5f,0.5f));*/

		//gsDrawRenderTarget(CastID::id2uint(RENDER_TARGET_ID::BASE));
		//gsEndShader();
		//gsEndRenderTarget();
		//gsUnbindTexture(CastID::id2uint(TEXTURE_ID::CIRCLE_MASK));
		//glActiveTexture(GL_TEXTURE0);
		//gsUnindRenderTargetTexture(CastID::id2uint(RENDER_TARGET_ID::RADIAL_BLUR), 0);


		//GSuint bloom = CastID::id2uint(RENDER_TARGET_ID::RADIAL_BLUR);
		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(bloom, 0);
		//gsDrawRenderTarget(bloom);
		//gsUnindRenderTargetTexture(bloom, 0);

	}
	// 描画
	virtual void draw() override
	{
	}
	// 終了
	virtual void end() override
	{
		DataManager::release();
	}
private:
	Renderer m_renderer;
	std::unique_ptr<MyGameThread>m_gameTread;

	float m_minBright;
	float m_toneScale;
};

int main()
{
	return MyGame().run();
}
