#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Mesh.h"
#include<d3d11.h>
#include "Entity.h"
#include "Camera.h"
//#include "Material.h"
#include "Lights.h"
#include "Physics.h"
#include "UI.h"
#include "Scenes.h"
#include "Emitter.h"
#include <Audio.h>
#include"pch.h"
#include <memory>

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void OnSuspending(); // for audio
	void OnResuming();  // for audio
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);
	void Highlight();

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);

	// detecting new audio devices
	void OnNewAudioDevice()
	{
		m_retryAudio = true;
	}
	
private:

	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	//void CreateMatrices();
	void CreateMeshes();
	void CreateEntities();
	void CreateCamera();
	//void CreateMaterial();
	void RenderShadowMap(); // render the shadow map
	//void CreateSound(HWND hwnd);
	//void CreateBasicGeometry();
	
	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	//DirectX::XMFLOAT4X4 worldMatrix;
	//DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	DirectX::XMFLOAT4X4 viewMatrix2;
	DirectX::XMFLOAT4X4 projectionMatrix2;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	// Create 3 private Mesh variables
	Mesh *m1;
	Mesh *m2;
	Mesh *m3;
	// Create a new mesh using constructor overloading
	//Mesh * conemesh;
	//Mesh * cube;
	//Mesh * cylinder;
	//Mesh * helix;
	//Mesh * sphere;
	//Mesh * torus;
	//Mesh * plane;



	// Create entities
	std::vector<Entity*> E;
	std::vector<Mesh *> mesh_list;
	std::vector<std::string> mesh_names;
	std::vector<int> en_pos;
	std::vector<int> count_down;
	int curr_time;
	int prev_time;
	bool entity_vanish;
	XMFLOAT3 vanish_location;

	Entity * Ground;
	Mesh * Ground_Mesh;
	Entity * LightSource;
	Mesh * LightSource_Mesh;
	//Entity * E[12]; // an array of 12 entities
	//Entity * Entity_obj;

	// Create a camera
	Camera *c;

	// Create materials for different textures
	//Material * ma_metal;
	//Material * ma_concrete;

	// Create a field of DirectionalLight (no pointer)
	DirectionalLight directionalLight;
	DirectionalLight directionalLight2;
	PointLight pointLight;

	// ----assignment 6----
	ID3D11ShaderResourceView* SRV_Metal;
	ID3D11ShaderResourceView* SRV_Concrete;
	ID3D11SamplerState* SampleState;

	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;
	ID3D11ShaderResourceView* srvlight;
	ID3D11ShaderResourceView* normalMapSRV;


	ID3D11RenderTargetView* ppRTV;		// Allows us to render to a texture
	ID3D11ShaderResourceView* ppSRV;	// Allows us to sample from the same texture
	ID3D11RenderTargetView* ppbRTV;		// Allows us to render to a texture
	ID3D11ShaderResourceView* ppbSRV;	// Allows us to sample from the same texture
	ID3D11RenderTargetView* ppbloomRTV;		// Allows us to render to a texture
	ID3D11ShaderResourceView* ppbloomSRV;

	SimpleVertexShader* ppVS;
	SimplePixelShader* ppPS;
	SimpleVertexShader* ebVS;
	SimplePixelShader* ebPS;
	SimpleVertexShader* boVS;
	SimplePixelShader* boPS;


	SpriteBatch *spriteBatch; // post process background



	// --------------------

	// ---for shadow mapping---
	//ID3D11Texture2D* shadowMapTexture;		// a depth stencil texture
	int shadowMapSize;
	ID3D11DepthStencilView* DSV_Shadow;		// depth stecil view
	ID3D11ShaderResourceView* SRV_Shadow;	// shader resource view
	ID3D11SamplerState* Sampler_Shadow;		// shader sampler
	ID3D11RasterizerState* RS_Shadow;		// rasterizer state
	SimpleVertexShader* VS_Shadow;			// shadow vertex shader
	DirectX::XMFLOAT4X4 shadowViewMatrix;	// shadow view matrix
	DirectX::XMFLOAT4X4 shadowProjectionMatrix;	// shadow projection matrix
	//SimplePixelShader* PS_Shadow;
	// D3D11_VIEWPORT myViewPort;


	// for audio stuff
	std::unique_ptr<DirectX::AudioEngine> m_audEngine;
	bool m_retryAudio;

	// adding sounds
	std::unique_ptr<DirectX::SoundEffect> m_explode;
	std::unique_ptr<DirectX::SoundEffect> m_ambient;
	std::unique_ptr<std::mt19937> m_random;
	float explodeDelay;

	// for looping a sound
	std::unique_ptr<DirectX::SoundEffectInstance> m_nightLoop;
	// audio end

	UI *scoreText[4];
	//UI *instruction;
	int score;
	wchar_t showScore[256];

	//wchar_t instruction[256];
	wchar_t * instruction;
	wchar_t * writable;

	//	Scenes *scene[2];
	UI * startText[2];

	UI * endText[1];

	int level;

	std::vector<Physics *> pp;

	XMVECTOR dir;
	//XMVECTOR pos;

	//for skybox
	ID3D11ShaderResourceView* skySRV;
	SimpleVertexShader * skyVS;
	SimplePixelShader * skyPS;
	ID3D11RasterizerState * rsSky;
	ID3D11DepthStencilState * dsSky;

	// Particle stuff
	ID3D11ShaderResourceView* particleTexture;
	SimpleVertexShader* particleVS;
	SimplePixelShader* particlePS;
	ID3D11DepthStencilState* particleDepthState;
	ID3D11BlendState* particleBlendState;
	Emitter* emitter_yellow_explosion;
	Emitter* emitter_red_explosion;
	Emitter* emitter_red_explosion2;
	Emitter* emitter_red_explosion3;
	Emitter* emitter_red_explosion4;
	Emitter* emitter_fog;
	Emitter* emitter_fog1;
	Emitter* emitter_fog2;

	ID3D11ShaderResourceView* particleTexture1;
	ID3D11ShaderResourceView* fogParticleTexture;

	float deltaTimeNew;
	int tempEmitterFlag;
	int tempResetEmitterFlag;
	float TimeSinceBeginningForGame;

	string Random_Mesh;

	//bool decals;

	// for detecting the cursor
	BoundingFrustum camFrustum;
	XMFLOAT4X4 proj;
	XMFLOAT3 tempRayDir;
	XMMATRIX view;
	XMVECTOR rayDir;
	XMVECTOR rayPos;
	bool mouseMove;

	// for the outline hightlight

	// Shader resource view for outline
	ID3D11RasterizerState* RS_Outline;
	SimpleVertexShader * VS_Outline;
	SimplePixelShader * PS_Outline;

};

