#version 330
layout(location = 0) in vec4 in_Position;
layout(location = 2) in vec3 in_Normal;
layout(location = 8) in vec2 in_TexCoord;
layout(location = 14) in vec3 in_Tangent;
layout(location = 15) in vec3 in_Binormal;
out vec2 out_TexCoord;
out vec3 out_Normal;
out vec3 out_View;
out vec3 out_Light;

uniform mat4 u_matWorld;
uniform mat4 u_matView;
uniform mat4 u_matProjection;
uniform vec3 u_lightPositionEye;
void main(void)
{
	// テクスチャ座標の出力
	out_TexCoord = in_TexCoord;
	// 頂点座標の計算
	vec4 worldPosition = u_matWorld * in_Position;
	vec4 viewPosition  = u_matView  * worldPosition;
	gl_Position = u_matProjection * viewPosition;
	// 法線ベクトルの計算
	vec3 worldNormal = mat3(u_matWorld) * in_Normal;
	vec3 viewNormal  = mat3(u_matView)  * worldNormal;
	// 接ベクトルの計算
	vec3 worldTangent = mat3(u_matWorld) * in_Tangent;
	vec3 viewTangent  = mat3(u_matView)  * worldTangent;
	// 従法線ベクトルの計算
	vec3 worldBinormal = mat3(u_matWorld) * in_Binormal;
	vec3 viewBinormal  = mat3(u_matView)  * worldBinormal;
	// 接空間変換行列の作成
	mat3 matTBN = mat3(normalize(viewTangent), normalize(viewBinormal), normalize(viewNormal));
	// 視点方向のベクトルの出力
	out_View   = vec3(-viewPosition) * matTBN;
	// ライト方向のベクトルの出力
	out_Light  = (u_lightPositionEye - vec3(viewPosition)) * matTBN;
}
