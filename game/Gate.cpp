#include "Gate.h"



Gate::Gate(float X, float Y)
{
	type = eType::GATE;
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 200);
	Health = 1;
	isStart = GATE_CLOSE;
	x = X;
	y = Y;
}


Gate::~Gate()
{
}

void Gate::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + _texture->FrameWidth - 40;
	bottom = y + _texture->FrameHeight;

}

void Gate::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	GameObject::Update(dt); // update dt
}

void Gate::Render(Camera * camera)
{
	switch (isStart)
	{
	case GATE_CLOSE:
	{

		break;
	}
	case GATE_OPEN_1:
	{
		_sprite->timeAccumulated += dt;
		if (_sprite->timeAccumulated >= 1000)
		{
			_sprite->timeAccumulated = 0;
			_sprite->Next();
			isStart++;
			Sound::GetInstance()->Play(eSound::soundOpenDoor);
		}
		break;
	}
	case GATE_OPEN_2:
	{
		_sprite->timeAccumulated += dt;
		if (_sprite->timeAccumulated >= 100)
		{
			_sprite->timeAccumulated = 0;
			_sprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_3:
	{
		_sprite->timeAccumulated += dt;
		if (_sprite->timeAccumulated >= 100)
		{
			_sprite->timeAccumulated = 0;
			_sprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_4:
	{
		_sprite->timeAccumulated += dt;
		if (_sprite->timeAccumulated >= 500)
		{
			_sprite->timeAccumulated = 0;
			_sprite->Next();
			isStart++;
		}
		break;
	}
	default:
		break;
	}


	D3DXVECTOR2 pos = camera->Transform(x, y);
	_sprite->Draw(pos.x, pos.y);


	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);

}

void Gate::Start()
{
	isStart = GATE_OPEN_1;
}

int Gate::GetStart()
{
	return isStart;
}
