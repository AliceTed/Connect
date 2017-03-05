#include <GSgame.h>
#include <cmath>
#include "ID.h"
class MyGame : public gslib::Game
{
public:
	MyGame()
		:Game(800, 600),
		rotateY(0),
		radius(0)
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
	}

	// çXêV
	virtual void update(float deltaTime) override
	{
		//rotateY += deltaTime*0.1f;
		radius += deltaTime*0.01f;
		if (gsGetKeyTrigger(GKEY_SPACE) == GS_TRUE)
		{
			radius = 0.0f;
		}
	}
	// ï`âÊ
	virtual void draw() override
	{
		camera();
		obj_draw();
		AbsoluteWorldPosition();
		sphere_scan();

		//glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetTexture(Cast(RENDER_TARGET::DEPTHMAP), 0);
		//gsDrawRenderTarget(Cast(RENDER_TARGET::BASE));

	    /*bright();
		bloom();*/
		/*obj_depth_draw();
		gaussian_blur_high();
		gaussian_blur_row();
		synthesis();*/
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
		for (const auto& i : { GSvector3(0,0,0),GSvector3(1,0,3), GSvector3(-2,0,-6) })
		{
			GSmatrix4 mat;
			mat.identity();
			mat.rotateY(rotateY);
			mat.translate(i);
			gsBeginShader(Cast(SHADER::ABSOLUTE_WORLD_POSITION));
			gsSetShaderParamMatrix4("u_matWorld", &mat);
			gsSetShaderParamMatrix4("u_matProjection", &proj);
			gsSetShaderParamMatrix4("u_matView", &view);
			gsDrawMeshEx(Cast(MESH::SPHERE));
			gsEndShader();
		}
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
	}

	void bloom()
	{
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

	void synthesis()
	{
		gsBeginShader(Cast(SHADER::DOF));
		glActiveTexture(GL_TEXTURE0);
		//gsBindRenderTargetDepth(Cast(RENDER_TARGET::BASE));
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

	}

	void gaussian_blur_row()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::GAUSSIAN_ROW));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);

		gsBeginShader(Cast(SHADER::GAUSSIAN));
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		const float amount = 1024.0f;

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
	}
	void gaussian_blur_high()
	{
		gsBeginRenderTarget(Cast(RENDER_TARGET::GAUSSIAN_HIGH));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glActiveTexture(GL_TEXTURE0);

		gsBeginShader(Cast(SHADER::GAUSSIAN));
		gsBindRenderTargetTexture(Cast(RENDER_TARGET::BASE), 0);
		gsSetShaderParamTexture("u_sceneColor", 0);
		const float amount = 256.0f;

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
	}
	void obj_depth_draw()
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);

		GScolor color(0, 0, 1, 1);

		gsBeginRenderTarget(Cast(RENDER_TARGET::DEPTHMAP));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		for (const auto& i : { GSvector3(0,0,0),GSvector3(1,0,3), GSvector3(-2,0,-6) })
		{
			GSmatrix4 mat;
			mat.identity();
			mat.rotateY(rotateY);
			mat.translate(i);

			gsBeginShader(Cast(SHADER::DEPTHMAP));
			gsSetShaderParamMatrix4("u_matWorld", &mat);
			gsSetShaderParamMatrix4("u_matProjection", &proj);
			gsSetShaderParamMatrix4("u_matView", &view);
			gsSetShaderParam1f("u_depthOffset", 0.1f);
			gsDrawMeshEx(Cast(MESH::SPHERE));
			gsEndShader();
		}
		gsEndRenderTarget();

	}
	void obj_draw()
	{
		GSmatrix4 proj, view;
		glGetFloatv(GL_PROJECTION_MATRIX, (GLfloat*)&proj);
		glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat*)&view);
		/*GSmatrix4 mat;
		mat.identity();
		mat.rotateY(rotateY);*/
		GScolor color(1, 1, 1, 1);

		GScolor ambient = { 1.0f ,1.0f ,1.0f ,1.0f };
		GScolor diffuse = { 1.0f ,1.0f ,1.0f ,1.0f };
		GScolor specular = { 1.0f ,1.0f ,1.0f ,1.0f };
		GSvector3 position = { 0.0f,50.0f ,10.0f };

		gsBeginRenderTarget(Cast(RENDER_TARGET::BASE));
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (const auto& i : { GSvector3(0,0,0),GSvector3(1,0,3), GSvector3(-2,0,-6) })
		{
			GSmatrix4 mat;
			mat.identity();
			mat.rotateY(rotateY);
			mat.translate(i);

			gsBeginShader(Cast(SHADER::SPHERE));
			GSvector3 lightPositionEye = position*view;
			gsSetShaderParam3f("u_lightPositionEye", &lightPositionEye);
			gsSetShaderParam4f("u_lightAmbient", &ambient);
			gsSetShaderParam4f("u_lightDiffuse", &diffuse);
			gsSetShaderParam4f("u_lightSpecular", &specular);
			gsSetShaderParamMatrix4("u_matWorld", &mat);
			gsSetShaderParamMatrix4("u_matProjection", &proj);
			gsSetShaderParamMatrix4("u_matView", &view);

			gsSetShaderParamTexture("u_baseMap", 0);
			gsSetShaderParamTexture("u_normalMap", 1);
			glActiveTexture(GL_TEXTURE0);
			gsBindTexture(Cast(TEX::ROCK));
			glActiveTexture(GL_TEXTURE1);
			gsBindTexture(Cast(TEX::ROCK_NORM));

			gsSetShaderParam4f("u_color", &color);
			gsDrawMeshEx(Cast(MESH::SPHERE));
			gsEndShader();
		}
		gsEndRenderTarget();

		glActiveTexture(GL_TEXTURE0);
		gsUnbindTexture(Cast(TEX::ROCK));
		glActiveTexture(GL_TEXTURE1);
		gsUnbindTexture(Cast(TEX::ROCK_NORM));
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

	// èIóπ
	virtual void end() override
	{
		gsFinishGraphics();
	}
private:
	float rotateY;

	float radius;
};

int main()
{
	return MyGame().run();
}
