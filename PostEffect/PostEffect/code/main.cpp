#include <GSgame.h>
#include <cmath>
#include <vector>
#include "ID.h"
#include "RenderDesc.h"
#include "DepthRenderDesc.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(800, 600),
		rotateY(0),
		radius(0),
		sphere_Pos(),
		lightPos(0,0,0)
	{
	}
private:
	virtual void start() override
	{
		gsLoadMeshEx(Cast(MESH::SPHERE), "sphere.msh");
		gsLoadMeshEx(Cast(MESH::PLANE), "plane.msh");
		gsLoadTexture(Cast(TEX::ROCK), "rockwall.png");
		gsLoadTexture(Cast(TEX::ROCK_NORM), "rockwall_normal.png");


		gsCreateRenderTarget(Cast(RENDER_TARGET::BASE), 800, 600, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::DEPTHMAP), 128, 128, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::GAUSSIAN_HIGH), 128, 128, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::GAUSSIAN_ROW), 128, 128, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::SHADOWMAP), 800, 600, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::DOF), 800, 600, GS_TRUE, GS_TRUE, GS_FALSE);
		gsCreateRenderTarget(Cast(RENDER_TARGET::RADIAL_BLUR), 800, 600, GS_TRUE, GS_FALSE, GS_FALSE);
		/*gsCreateRenderTarget(1, 128, 128, GS_FALSE, GS_FALSE, GS_FALSE);*/
		gsLoadShader(Cast(SHADER::SPHERE), "sphere.glslv", "sphere.glslf");
		gsLoadShader(Cast(SHADER::GAUSSIAN), "defalt.glslv", "gaussian.glslf");
		gsLoadShader(Cast(SHADER::DEPTHMAP), "depthMap.glslv", "depthMap.glslf");
		gsLoadShader(Cast(SHADER::DOF), "defalt.glslv", "dof_synthesis.glslf");
		gsLoadShader(Cast(SHADER::BRIGHT), "defalt.glslv", "bright.glslf");
		gsLoadShader(Cast(SHADER::BLOOM), "defalt.glslv", "bloom.glslf");
		gsLoadShader(Cast(SHADER::BLOOM_SYNTHESIS), "defalt.glslv", "bloom_synthesis.glslf");
		gsLoadShader(Cast(SHADER::SPHERE_SCAN), "sphere_scan.glslv", "sphere_scan.glslf");
		gsLoadShader(Cast(SHADER::ABSOLUTE_WORLD_POSITION), "AbsoluteWorldPosition.glslv", "AbsoluteWorldPosition.glslf");
		gsLoadShader(Cast(SHADER::SHADOWMAP), "shadowMap.glslv", "shadowMap.glslf");
		gsLoadShader(Cast(SHADER::SHADOW), "shadowRendering.glslv", "shadowRendering.glslf");
		gsLoadShader(Cast(SHADER::RADIAL_BLUR), "defalt.glslv", "radialBlur.glslf");
		
		sphere_Pos ={ GSvector3(0, 0, 0), GSvector3(1, 0, 3), GSvector3(-2, 0, -6) };
		lightPos = { 0,0,10};
	}

	// 更新
	virtual void update(float deltaTime) override
	{
		rotateY += deltaTime*0.1f;
		radius += deltaTime*0.01f;
		if (gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE)
		{
			radius = 0.0f;
		}
	}
	void draw(const RenderDesc& _desc)
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		const LightDesc& light = _desc.light;

		gsBeginShader(Cast(SHADER::SPHERE));
		GSvector3 lightPositionEye = light.position*view;
		gsSetShaderParam3f("u_lightPositionEye", &lightPositionEye);
		gsSetShaderParam4f("u_lightAmbient", &light.ambient);
		gsSetShaderParam4f("u_lightDiffuse", &light.diffuse);
		gsSetShaderParam4f("u_lightSpecular", &light.specular);
		gsSetShaderParamMatrix4("u_matWorld", &_desc.matrix);
		gsSetShaderParamMatrix4("u_matProjection", &proj);
		gsSetShaderParamMatrix4("u_matView", &view);

		gsSetShaderParamTexture("u_baseMap", 0);
		gsSetShaderParamTexture("u_normalMap", 1);
		glActiveTexture(GL_TEXTURE0);
		gsBindTexture(Cast(TEX::ROCK));
		glActiveTexture(GL_TEXTURE1);
		gsBindTexture(Cast(TEX::ROCK_NORM));

		gsSetShaderParam4f("u_color", &_desc.color);
		gsDrawMeshEx(Cast(_desc.meshID));
		gsEndShader();

		gsUnbindTexture(Cast(TEX::ROCK_NORM));
		glActiveTexture(GL_TEXTURE0);
		gsUnbindTexture(Cast(TEX::ROCK));
	}
	void draw_depth(const DepthRenderDesc& _desc)
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		gsBeginShader(Cast(SHADER::DEPTHMAP));
		gsSetShaderParamMatrix4("u_matWorld", &_desc.matrix);
		gsSetShaderParamMatrix4("u_matProjection", &proj);
		gsSetShaderParamMatrix4("u_matView", &view);
		gsSetShaderParam1f("u_depthOffset", _desc.offset);
		gsDrawMeshEx(Cast(_desc.meshID));
		gsEndShader();
	}
	void draw_AbsPos(const GSmatrix4& _matrix,MESH _meshID)
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		gsBeginShader(Cast(SHADER::ABSOLUTE_WORLD_POSITION));
		gsSetShaderParamMatrix4("u_matWorld", &_matrix);
		gsSetShaderParamMatrix4("u_matProjection", &proj);
		gsSetShaderParamMatrix4("u_matView", &view);
		gsDrawMeshEx(Cast(_meshID));
		gsEndShader();
	}
	void draw_shadowMap(const GSmatrix4& _matrix, MESH _meshID)
	{
		GSmatrix4 depthProjMat;
		gsMatrix4OrthoRH(&depthProjMat, -10, 10, -10, 10, -10, 20);
		GSmatrix4 depthViewMatrix;
		depthViewMatrix.setLookAtRH(lightPos, GSvector3(0, 0, 0), GSvector3(0, 1, 0));

		gsBeginShader(Cast(SHADER::SHADOWMAP));
		gsSetShaderParamMatrix4("u_matWorld", &_matrix);
		gsSetShaderParamMatrix4("u_matProjection", &depthProjMat);
		gsSetShaderParamMatrix4("u_matView", &depthViewMatrix);

		gsDrawMeshEx(Cast(_meshID));

		gsEndShader();
	}

	void draw_shadow(const GSmatrix4& _matrix, MESH _meshID)
	{
		GSmatrix4 depthProjMat;
		gsMatrix4OrthoRH(&depthProjMat, -10, 10, -10, 10, -10, 20);
		GSmatrix4 depthViewMatrix;
		depthViewMatrix.setLookAtRH(lightPos, GSvector3(0, 0, 0), GSvector3(0, 1, 0));

		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		GSmatrix4 bias = 
		{
			0.5, 0.0, 0.0, 0.0,
			0.0, 0.5, 0.0, 0.0,
			0.0, 0.0, 0.5, 0.0,
			0.5, 0.5, 0.5, 1.0 
		};

		gsBeginShader(Cast(SHADER::SHADOW));
		gsSetShaderParamMatrix4("u_matWorld", &_matrix);
		gsSetShaderParamMatrix4("u_matProjection", &proj);
		gsSetShaderParamMatrix4("u_matView", &view);
		gsSetShaderParamMatrix4("u_matDepthView", &depthViewMatrix);
		gsSetShaderParamMatrix4("u_matDepthProjection", &depthViewMatrix);
		gsSetShaderParamMatrix4("u_matBias", &bias);
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetDepth(Cast(RENDER_TARGET::SHADOWMAP));
		gsSetShaderParamTexture("u_shadowMap",0);

		GSvector4 lightColor(1,1,1,1);
		gsSetShaderParam4f("u_LightColor", &lightColor);
		gsSetShaderParam1f("u_LightPower",0.5f);

		gsDrawMeshEx(Cast(_meshID));

		gsEndShader();


	}

	void draw_obj()
	{
		RenderDesc desc;
		desc.light.position = lightPos;
		for (const auto& i : sphere_Pos)
		{
			desc.matrix.identity();
			desc.matrix.rotateY(rotateY);
			desc.matrix.translate(i);
			draw(desc);
		}

		desc.matrix.identity();
		desc.matrix.scale(GSvector3(30, 1, 50));
		desc.matrix.rotateX(90);
		desc.matrix.translate(GSvector3(0, 0, -20));
		desc.meshID = MESH::PLANE;
		desc.color.r = 0.0f;
		draw(desc);
	}
	void draw_depth_obj(float depth_offset )
	{
		DepthRenderDesc desc;
		desc.offset = depth_offset;
		for (const auto& i :sphere_Pos)
		{
			desc.matrix.identity();
			desc.matrix.rotateY(rotateY);
			desc.matrix.translate(i);
			draw_depth(desc);
		}

		desc.matrix.identity();
		desc.matrix.scale(GSvector3(30, 1, 50));
		desc.matrix.rotateX(90);
		desc.matrix.translate(GSvector3(0, 0, -20));
		desc.meshID = MESH::PLANE;
		draw_depth(desc);
	}

	void draw_AbsPos_obj()
	{
		GSmatrix4 matrix;
		for (const auto& i : sphere_Pos)
		{
			matrix.identity();
			matrix.rotateY(rotateY);
			matrix.translate(i);
			draw_AbsPos(matrix,MESH::SPHERE);
		}

		matrix.identity();
		matrix.scale(GSvector3(30, 1, 50));
		matrix.rotateX(90);
		matrix.translate(GSvector3(0, 0, -20));
		draw_AbsPos(matrix,MESH::PLANE);
	}
	void draw_shadowMap_obj()
	{
		GSmatrix4 matrix;
		for (const auto& i : sphere_Pos)
		{
			matrix.identity();
			matrix.rotateY(rotateY);
			matrix.translate(i);
			draw_shadowMap(matrix, MESH::SPHERE);
		}

		matrix.identity();
		matrix.scale(GSvector3(30, 1, 50));
		matrix.rotateX(90);
		matrix.translate(GSvector3(0, 0, -20));
		draw_shadowMap(matrix, MESH::PLANE);
	}

	void draw_shadow_obj()
	{
		GSmatrix4 matrix;
		for (const auto& i : sphere_Pos)
		{
			matrix.identity();
			matrix.rotateY(rotateY);
			matrix.translate(i);
			draw_shadow(matrix, MESH::SPHERE);
		}

		matrix.identity();
		matrix.scale(GSvector3(30, 1, 50));
		matrix.rotateX(90);
		matrix.translate(GSvector3(0, 0, -20));
		draw_shadow(matrix, MESH::PLANE);
	}
	//指定レンダーターゲットのバッファを描画
	void draw_RenderTarget(const RENDER_TARGET _id,bool isColorBuffer=true)
	{
		glActiveTexture(GL_TEXTURE0);
		if (isColorBuffer)
		{
			gsBindRenderTargetTexture(Cast(_id), 0);
		}
		else
		{
			gsBindRenderTargetDepth(Cast(_id));
		}
		
		
		gsDrawRenderTarget(Cast(_id));

		gsUnindRenderTargetTexture(Cast(_id), 0);
	}
	
	// 描画
	virtual void draw() override
	{
		camera();
		
		//draw_RenderTarget(RENDER_TARGET::SHADOWMAP,false);


		base_draw();

		radialBlur();

		////depth_draw();

	 //   AbsoluteWorldPosition();
		//sphere_scan();

		//bloom();
	    //dof();		
	}
	GSmatrix4 getMatScreen()
	{
		GSvector4 viewport;
		glGetIntegerv(GL_VIEWPORT, (GLint*)&viewport);
		float w = viewport.z * 0.5f;
		float h = viewport.w * 0.5f;
		return{
			w   , 0.0f,0.0f,0.0f,
			0.0f, -h  ,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			w + viewport.x, h + viewport.y, 0.0f,1.0f
		};
	}

	void AbsoluteWorldPosition()
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		gsBeginRenderTarget(Cast(RENDER_TARGET::DEPTHMAP));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_AbsPos_obj();
		gsEndRenderTarget();

	}

	void sphere_scan()
	{
		
		GSmatrix4 proj, view,screen;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);
		screen = getMatScreen();

		gsBeginShader(Cast(SHADER::SPHERE_SCAN));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		glActiveTexture(GL_TEXTURE1);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		gsSetShaderParamTexture("u_absWorldPosition",1);

		gsSetShaderParamMatrix4("u_matView", &view);
		gsSetShaderParamMatrix4("u_matProjection", &proj);
		gsSetShaderParamMatrix4("u_matScreen", &screen);

		gsSetShaderParam1f("u_blurAmount", 0.6f);
		gsSetShaderParam4f("u_scanColor",&GScolor(1,0,0,1));
		gsSetShaderParam4f("u_spherePosition",&GSvector4(0,0,0,0));
		gsSetShaderParam1f("u_sphereRadius", radius);
		gsSetShaderParam1f("u_scanWidht",1.0f);
		gsSetShaderParam2f("u_screenSize", &GSvector2(800, 600));
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
	}

	void shadowMap()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::SHADOWMAP));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_shadowMap_obj();
		gsEndRenderTarget();

		draw_shadow_obj();
	}

	void bright()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::DEPTHMAP));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gsBeginShader(Cast(SHADER::BRIGHT));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParam1f("u_minBright", 0.25f);
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
		gsEndRenderTarget();
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
	}
	void bloom()
	{
		bright();

		gsBeginRenderTarget(Cast(RENDER_TARGET::GAUSSIAN_HIGH));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gsBeginShader(Cast(SHADER::BLOOM));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParam2f("u_direction", &GSvector2(1, 0));
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
		gsEndRenderTarget();

		gsBeginShader(Cast(SHADER::BLOOM_SYNTHESIS));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		glActiveTexture(GL_TEXTURE1);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		gsSetShaderParamTexture("u_bloomColor", 1);
		gsSetShaderParam1f("u_toneScale", 0.8f);
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
	}

	void dof()
	{
		depth_draw();
		gaussian_blur(RENDER_TARGET::GAUSSIAN_ROW, 1024.0f);
		gaussian_blur(RENDER_TARGET::GAUSSIAN_HIGH,256);
		synthesis();
		draw_RenderTarget(RENDER_TARGET::DOF);
	}

	void synthesis()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::DOF));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		gsBeginShader(Cast(SHADER::DOF));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		gsSetShaderParamTexture("u_depth", 0);
		glActiveTexture(GL_TEXTURE1);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_scene", 1);
		glActiveTexture(GL_TEXTURE2);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::GAUSSIAN_ROW), 0);
		gsSetShaderParamTexture("u_blur_row", 2);
		glActiveTexture(GL_TEXTURE3);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::GAUSSIAN_HIGH), 0);
		gsSetShaderParamTexture("u_blur_high", 3);
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));

		gsEndShader();
		gsEndRenderTarget();

		glActiveTexture(GL_TEXTURE0);
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		
		glActiveTexture(GL_TEXTURE1);
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		
		glActiveTexture(GL_TEXTURE2);
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::GAUSSIAN_ROW), 0);
		
		glActiveTexture(GL_TEXTURE3);
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::GAUSSIAN_HIGH), 0);
	}
	void gaussian_blur(RENDER_TARGET _target, float amount)
	{
		gsBeginRenderTarget(Cast(_target));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gsBeginShader(Cast(SHADER::GAUSSIAN));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);

		gsSetShaderParam2f("u_scale", &GSvector2(1.0f / amount, 1.0f / amount));
		const int SIZE = 7;
		const GSvector4 gaussfilter[7] =
		{
			{ -3.0f, -3.0f, 0.0f,  1.0f / 64.0f },
			{ -2.0f, -2.0f, 0.0f,  6.0f / 64.0f },
			{ -1.0f, -1.0f, 0.0f, 15.0f / 64.0f },
			{ 0.0f,  0.0f, 0.0f, 20.0f / 64.0f },
			{ 1.0f,  1.0f, 0.0f, 15.0f / 64.0f },
			{ 2.0f,  2.0f, 0.0f,  6.0f / 64.0f },
			{ 3.0f,  3.0f, 0.0f,  1.0f / 64.0f }
		};
		gsSetShaderParamArray4f("u_gaussFilter", SIZE, gaussfilter);
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
		gsEndRenderTarget();
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
	}
	void depth_draw()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::DEPTHMAP));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		draw_depth_obj(0.4f);

		gsEndRenderTarget();
	}

	void radialBlur()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::RADIAL_BLUR));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		gsBeginShader(Cast(SHADER::RADIAL_BLUR));
		glActiveTexture(GL_TEXTURE0);
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);	   
		gsSetShaderParam1f("u_blurAmount", 0.15f);
		/*gsSetShaderParam2f("u_screenMult", &GSvector2(1.0f, 1.0f));
		gsSetShaderParam2f("u_center", &GSvector2(0.5f,0.5f));*/
	
		gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));
		gsEndShader();
		gsEndRenderTarget();
		gsUnindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);

		draw_RenderTarget(RENDER_TARGET::RADIAL_BLUR);

	}

	//beseに書き込み
	void base_draw()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::BASE));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		draw_obj();
		
		gsEndRenderTarget();
	}
	void camera()
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(
			0.0f, 5.0f, 20.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		);
	}

	// 終了
	virtual void end() override
	{
		gsFinishGraphics();
	}
private:
	float rotateY;

	float radius;
	GSvector3 lightPos;
	std::vector<GSvector3>sphere_Pos;
};

int main()
{
	return MyGame().run();
}
