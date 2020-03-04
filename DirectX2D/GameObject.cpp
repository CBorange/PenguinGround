#include"GameObject.h"
#include"D3D.h"
#include"ScriptAble.h"

GameObject::GameObject()
{
	colTag = 0;
	layer = 0;
	isActive = false;
	isRenderable = false;
	coliderIsActive = false;
	gravityIsActive = false;
	attachedScript = nullptr;
}
void GameObject::Initialize(LPCWSTR fileAdress, int layer, ScriptAble* scrt, int colTag)
{
	D3Ddevice = D3D::GetInst()->GetDevice();
	D3DSprite = D3D::GetInst()->GetSprite();
	attachedScript = scrt;

	this->layer = layer;
	isActive = true;
	isRenderable = true;
	coliderIsActive = true;
	this->colTag = colTag;

	D3DXCreateTextureFromFileEx(D3Ddevice, fileAdress, NULL, NULL, 1, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, 0x0000001, 0x00FFFFFF, 0x000000FF, &imageInfo, NULL, &texture);

	velocity = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(imageInfo.Width * 0.5f, imageInfo.Height * 0.5f, 0);
	center = scale;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
	SetRect(&spriteRect, 0, 0, imageInfo.Width, imageInfo.Height);
	color = D3DXCOLOR(1, 1, 1, 1);
}
void GameObject::Initialize(LPDIRECT3DTEXTURE9 newTexture,
	D3DXIMAGE_INFO imageInfo, int layer, ScriptAble* scrt, int colTag)
{
	D3Ddevice = D3D::GetInst()->GetDevice();
	D3DSprite = D3D::GetInst()->GetSprite();
	attachedScript = scrt;

	this->layer = layer;
	isActive = true;
	isRenderable = true;
	coliderIsActive = true;
	this->colTag = colTag;


	this->imageInfo = imageInfo;
	this->texture = newTexture;

	velocity = D3DXVECTOR2(0, 0);
	position = D3DXVECTOR3(0, 0, 0);
	scale = D3DXVECTOR3(imageInfo.Width * 0.5f, imageInfo.Height * 0.5f, 0);
	center = scale;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
	SetRect(&spriteRect, 0, 0, imageInfo.Width, imageInfo.Height);
	color = D3DXCOLOR(1, 1, 1, 1);
}
void GameObject::Initialize(ScriptAble* scrt)
{
	isActive = true;
	isRenderable = false;
}
void GameObject::Render()
{
	D3DSprite->Draw(texture, &spriteRect, &center, &position, color);
}
void GameObject::MoveWithVelocity()
{
	Translate(velocity.x, velocity.y);
}

void GameObject::Release()
{
	if (texture != nullptr)
		texture->Release();
}
//Get
bool GameObject::GetActiveState()
{
	return isActive;
}
bool GameObject::GetRenderable()
{
	return isRenderable;
}
int GameObject::GetLayer() const
{
	return layer;
}
int GameObject::GetColTag()
{
	return colTag;
}
bool GameObject::GetColiderState()
{
	return coliderIsActive;
}
bool GameObject::GetGravityState()
{
	return gravityIsActive;
}

D3DXVECTOR3 GameObject::GetPosition()
{
	return position;
}
D3DXVECTOR2 GameObject::GetScale()
{
	return D3DXVECTOR2(scale.x, scale.y);
}
RECT GameObject::GetRectPos()
{
	return rectPosition;
}
RECT GameObject::GetSpriteRect()
{
	return spriteRect;
}
D3DXCOLOR GameObject::GetColor()
{
	return color;
}
D3DXIMAGE_INFO GameObject::GetImageInfo()
{
	return imageInfo;
}
ScriptAble* GameObject::GetAttachedScript()
{
	return attachedScript;
}

//Set
//FrameScale인수는 프레임 한장의 크기전체를 의미합니다.(1/2 가 아닌 LT을 기준으로한 크기)
void GameObject::ChangeTextureForAnim(LPDIRECT3DTEXTURE9 sheet, D3DXIMAGE_INFO imageInfo,
	D3DXVECTOR2 frameScale)
{
	scale = D3DXVECTOR3(frameScale.x * 0.5, frameScale.y * 0.5, 0);
	texture = sheet;
	this->imageInfo = imageInfo;
	SetRect(&spriteRect, 0, 0, frameScale.x, frameScale.y);
}
void GameObject::SetActiveState(bool state)
{
	isActive = state;
}
void GameObject::SetColiderState(bool state)
{
	coliderIsActive = state;
}
void GameObject::SetGravityState(bool state)
{
	gravityIsActive = state;
}
void GameObject::SetSpriteRect(RECT rect)
{
	SetRect(&spriteRect, rect.left, rect.top, rect.right, rect.bottom);
}
void GameObject::SetSpriteRect(int left, int top, int right, int bottom)
{
	SetRect(&spriteRect, left, top, right, bottom);
}
void GameObject::PushSpriteRectToRight(int pixel)
{
	spriteRect.left += pixel;
	spriteRect.right = spriteRect.left + scale.x * 2;
}
void GameObject::SetColor(float r, float g, float b, float a)
{

}
void GameObject::SetColor(float a)
{

}
//Movement
void GameObject::Translate(D3DXVECTOR3 vec)
{
	position += vec;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
}
void GameObject::Translate(float x, float y)
{
	position.x += x;
	position.y += y;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
}
void GameObject::Teleport(D3DXVECTOR3 vec)
{
	position = vec;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
}
void GameObject::Teleport(float x, float y)
{
	position.x = x;
	position.y = y;
	SetRect(&rectPosition, position.x - scale.x, position.y - scale.y, position.x + scale.x,
		position.y + scale.y);
}

//Physics
D3DXVECTOR2 GameObject::GetVelocity()
{
	return velocity;
}
void GameObject::SetVelocity(float x, float y)
{
	velocity = D3DXVECTOR2(x, y);
}
void GameObject::SetVelocity(D3DXVECTOR2 vec)
{
	velocity = vec;
}
void GameObject::AddVelocity(float x, float y)
{
	velocity += D3DXVECTOR2(x, y);
}
void GameObject::AddVelocity(D3DXVECTOR2 vec)
{
	velocity += vec;
}