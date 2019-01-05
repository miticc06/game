#include "Gate.h"



Gate::Gate(float X, float Y)
{
	type = eType::GATE;
	texture = TextureManager::GetInstance()->GetTexture(type);
	sprite = new GSprite(texture, 200);
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
	right = x + texture->GetFrameWidth() - 40;
	bottom = y + texture->GetFrameHeight();

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
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 1000)
		{
			sprite->timeAccumulated = 0;
			sprite->Next();
			isStart++;
			Sound::GetInstance()->Play(eSound::soundOpenDoor);
		}
		break;
	}
	case GATE_OPEN_2:
	{
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 100)
		{
			sprite->timeAccumulated = 0;
			sprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_3:
	{
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 100)
		{
			sprite->timeAccumulated = 0;
			sprite->Next();
			isStart++;
		}
		break;
	}
	case GATE_OPEN_4:
	{
		sprite->timeAccumulated += dt;
		if (sprite->timeAccumulated >= 500)
		{
			sprite->timeAccumulated = 0;
			sprite->Next();
			isStart++;
		}
		break;
	}
	default:
		break;
	}


	D3DXVECTOR2 pos = camera->Transform(x, y);
	sprite->Draw(pos.x, pos.y);


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
