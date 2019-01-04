#include "PhantomBat.h"
 
PhantomBat::PhantomBat(Simon * simon, Camera *camera, vector <Weapon*> * listWeaponOfEnemy)
{ 
	type = eType::PHANTOMBAT; 
	_texture = TextureManager::GetInstance()->GetTexture(type);
	_sprite = new GSprite(_texture, 70);

	this->simon = simon;
	this->camera = camera;

	this->listWeaponOfEnemy = listWeaponOfEnemy;
	weapon = new FireBall(camera);
	listWeaponOfEnemy->push_back(weapon);

	ResetResource();
}

void PhantomBat::ResetResource()
{
	x = PHANTOMBAT_DEFAULT_X;
	y = PHANTOMBAT_DEFAULT_Y;

	Health = PHANTOMBAT_DEFAULT_HEALTH;
	StatusProcessing = PHANTOMBAT_PROCESS_SLEEP;

	xBefore = x;
	yBefore = y;

	isWaiting = false;
	yLastFrame = y;
	vx = vy = 0;
	isUseBezierCurves = false;
}

PhantomBat::~PhantomBat()
{
}


void PhantomBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x+5;
	top = y;
	right = x + _texture->FrameWidth-5;
	bottom = y + _texture->FrameHeight - 10;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetHealth() <= 0)
		return;

	//DebugOut(L"\n Trang thai trc x = %d", StatusProcessing);
	 
	
	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_SLEEP:
	{
		 
		break;
	}
		
	case PHANTOMBAT_PROCESS_START_1: // đi xuống
	{
		// bắt đầu thì đi xuống 1 đoạn ngắn
		if (y >= yTarget)
		{
			vy = 0;
			StatusProcessing = PHANTOMBAT_PROCESS_START_2; // qua trạng thái di chuyển đến cửa sổ
			
			xBefore = x;
			yBefore = y;

			xTarget = 5480;
			yTarget = 201;

			vx = ((xTarget - xBefore) / (1500.0f)); // Vận tốc cần để đi đến target trong 1.5s
			vy = 0.12f; // tạo độ cong
		}
		break;
	}

	case PHANTOMBAT_PROCESS_START_2: // đi cong xuống ngay cửa sổ
	{
		if (!isWaiting)
		{
			// tạo độ cong
			vy -= 0.0001f * dt;
			if (vy < 0)
				vy = 0;
			// tạo độ cong

			if (x >= xTarget) // di chuyển xong đến mục tiêu 2
			{
				vx = 0;
				vy = 0;


				isWaiting = true; // bật trạng thái chờ
				TimeWaited = 0; // reset lại time đã chờ
			} 
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= (UINT)(2000+rand()%1500))
			{
				isWaiting = false; // ngừng chờ

				StartCurves();
			}
		}
		

		break;
	}

	case PHANTOMBAT_PROCESS_CURVES:
	{  
		if (abs(x - xBefore) >= abs(xTarget-xBefore)) // đi xong thid đi thẳng
		{
			vx = 0;
			vy = 0;
			isUseBezierCurves = false;
 
			StartStaight();

			break;
		}


		float perc = (x - xBefore) / (xTarget - xBefore); // sử dụng phần trăm đã đi được tương ứng t của Bézier curve
		 
		float ya = getPt(y1, y2, perc); 
		float yb = getPt(y2, y3, perc);
		 
		float yy = getPt(ya, yb, perc);

		vy = (yy - yLastFrame/*Khoảng cách y giữa frame trước và y dự tính đi*/) / dt;
		
		
		break;
	}

	case PHANTOMBAT_PROCESS_STRAIGHT_1:
	{
		if (abs(x - xBefore) >= abs(xTarget - xBefore) || 
			abs(y - yBefore) >= abs(yTarget - yBefore)) // đi xong thì đi thẳng theo hướng random
		{
			vx = vy = 0;
			  
			StartStaight();

		}
		break;
	}

	case PHANTOMBAT_PROCESS_STRAIGHT_2:
	{
		if (!isWaiting)
		{
			if (abs(x - xBefore) >= abs(xTarget - xBefore) ||
				abs(y - yBefore) >= abs(yTarget - yBefore)) // đi xongthì dừng
			{
				vx = vy = 0;
			 

				isWaiting = true; // bật trạng thái chờ
				TimeWaited = 0; // reset lại time đã chờ
			}
		}
		else
		{
			TimeWaited += dt;
			if (TimeWaited >= 3000)
			{
				isWaiting = false; // ngừng chờ

				int random = rand() % 3;
				switch (random)
				{
				case 0: //33 %
					StartAttack();
					break;

				default: // 66%
					StartCurves();

					break;
				}
			}
			else
			{
				ProcessSmart();
			}
		} 


		break;
	}

	case PHANTOMBAT_PROCESS_ATTACK:
	{
		if (isWaiting)
		{
			TimeWaited += dt;
			if (TimeWaited >= 1500)
			{
				isWaiting = false; // ngừng chờ
				StartStaight(); // qua trạng thái đi thẳng
			}
		}
		break;
	}


	default:
		break;
	}


//	DebugOut(L"simon - boss = %f\n", sqrt((simon->GetX() - x)*(simon->GetX() - x) + (simon->GetY() - y)*(simon->GetY() - y)));
	 
	GameObject::Update(dt);
	x += dx;
	y += dy;


	//DebugOut(L"\n xCam = %f , xcam-r = %f , x = %f , y = %f \n", camera->GetXCam(), camera->GetXCam() + camera->GetWidth(), x, y);


	if (x < camera->GetXCam()
		|| camera->GetXCam()+camera->GetWidth() <x + GetWidth()
		|| y < camera->GetYCam()
		|| camera->GetYCam() + camera->GetHeight() < y + GetHeight()
		
		) // ra khỏi cam thì xử lí hướng tiếp theo
	{
/*
		if (camera->GetXCam() + camera->GetWidth() < x + GetWidth())
		{
			DebugOut(L"\n Vuot qua ben phai!!!!!!!\n");
		}

		if (x < camera->GetXCam())
		{
			DebugOut(L"\n Vuot qua ben trai!!\n");
		}
		if (y < camera->GetYCam())
		{
			DebugOut(L"\n Vuot tren!!\n");
		}
		if (camera->GetYCam() + camera->GetHeight() < y + GetHeight())
		{
			DebugOut(L"\n Vuot duoi!!\n");
		}*/

		switch (StatusProcessing)
		{
		case PHANTOMBAT_PROCESS_CURVES:
		{
			isUseBezierCurves = false;
			StartStaight();
			break;
		}

		case PHANTOMBAT_PROCESS_STRAIGHT_1:
		{
			StartStaight();
			break;
		}

		case PHANTOMBAT_PROCESS_STRAIGHT_2:
		{
			int random = rand() % 3;
			switch (random)
			{
			case 0: //33 %
				StartAttack();
				break;

			default: // 66%
				StartCurves();

				break;
			}

			break;
		}
		 
		}

	}

	yLastFrame = y;// lưu lại y frame hiện tại
}

void PhantomBat::Render(Camera * camera)
{
	if (GetHealth() <= 0)
		return;

	if (StatusProcessing == PHANTOMBAT_PROCESS_SLEEP)
		_sprite->SelectFrame(0);
	else
	{ 
		_sprite -> Update(dt);
		if (_sprite->GetCurrentFrame() == 0)
			_sprite->SelectFrame(1);
	}

	D3DXVECTOR2 pos = camera->Transform(x, y); 
	_sprite->Draw(pos.x, pos.y);  
	  
	if (IS_DEBUG_RENDER_BBOX)
	{ 
		RenderBoundingBox(camera);

		if (isUseBezierCurves) // sử dụng BezierCurves thì mới vẽ 
		{
			for (float i = 0; i < 1; i += 0.01f)
			{
				// The Green Line
				float xa = getPt(x1, x2, i);
				float ya = getPt(y1, y2, i);
				float xb = getPt(x2, x3, i);
				float yb = getPt(y2, y3, i);

				// The Black Dot
				float xx = getPt(xa, xb, i);
				float yy = getPt(ya, yb, i);


				RECT rect;
				rect.left = 0;
				rect.top = 0;
				rect.right = 5;
				rect.bottom = 5;
				D3DXVECTOR2 pos = camera->Transform(xx, yy);
				Game::GetInstance()->Draw(
					pos.x,
					pos.y,
					TextureManager::GetInstance()->GetTexture(
						eType::RENDERBBOX)->Texture,
					rect.left,
					rect.top,
					rect.right,
					rect.bottom,
					100);

			}
		}
		  
		RECT rect; 
		rect.left = 0;
		rect.top = 0;
		rect.right = 15;
		rect.bottom = 15;
		D3DXVECTOR2 pos1 = camera->Transform(xTarget, yTarget);
		Game::GetInstance()->Draw(
			pos1.x,
			pos1.y,
			TextureManager::GetInstance()->GetTexture(
				eType::RENDERBBOX)->Texture,
			rect.left,
			rect.top,
			rect.right,
			rect.bottom,
			100);
	}
}
 
float PhantomBat::getPt(float n1, float n2, float perc)
{
	float diff = n2 - n1;

	return n1 + (diff * perc);
}

void PhantomBat::Stop()
{
	vx = vy = 0;
}

void PhantomBat::ProcessSmart()
{
	if (simon->isJumping && sqrt((simon->GetX() - x)*(simon->GetX() - x) + (simon->GetY() - y)*(simon->GetY() - y)) <= 150.0f) // nếu nhảy lên & khoảng cách nhỏ hơn 150 thì random cách xử lí
	{
		int random = rand() % 6;
		switch (random)
		{
		case 0:
			StartStaight();
			return;
		case 1:
			StartCurves();
			return;
		case 2:
			StartAttack();
			return;

		default:
			break;
		}
	}

	if (rand() % 5 == 0) //20%
	{
		if (Health <= 10 && simon->isAttacking)
		{
			StartCurves();
		}
	}
	
}

void PhantomBat::Start() 
{
	StatusProcessing = PHANTOMBAT_PROCESS_START_1;
	yBefore = y;
	vy = 0.05f;
	vx = 0.0f;
	yTarget = y + 40; // lúc đầu thì đi xuống 40px
}

void PhantomBat::StartCurves()
{
	DebugOut(L"Curves!\n");

	xBefore = x;
	yBefore = y;

	x1 = x;
	y1 = y;

	x2 = simon->GetX();
	y2 = simon->GetY() + simon->GetHeight();

	if (simon->GetX() < x) // simon bên trái boss
		xTarget = camera->GetXCam() - 100 + rand() % ((int)(simon->GetX() - camera->GetXCam() + 100));
	else // simon bên phải boss
		xTarget = simon->GetX() + simon->GetWidth() + rand() % ((int)(camera->GetXCam() + camera->GetWidth() - (simon->GetX() + simon->GetWidth()) + 100)); 

	yTarget = simon->GetY() + simon->GetHeight() - 100;

	x3 = xTarget;
	y3 = yTarget;

	vx = -(x - xTarget) / (abs(xTarget-xBefore)*1000.0f/150); // vận tốc cần để đi đến Target // quy ước: cứ 1 giây đi 150px
	vy = 0;

	isUseBezierCurves = true;
	StatusProcessing = PHANTOMBAT_PROCESS_CURVES;
}

void PhantomBat::StartStaight()
{
	DebugOut(L"Staight!\n");

	switch (StatusProcessing)
	{
	case PHANTOMBAT_PROCESS_STRAIGHT_1:
		StatusProcessing = PHANTOMBAT_PROCESS_STRAIGHT_2;
		break;
	default:
		StatusProcessing = PHANTOMBAT_PROCESS_STRAIGHT_1;
		break;
	}
	xBefore = x;
	yBefore = y;
	xTarget = (float) PHANTOMBAT_BOUNDARY_START_STAIGHT_LEFT + rand() % (PHANTOMBAT_BOUNDARY_START_STAIGHT_RIGHT- PHANTOMBAT_BOUNDARY_START_STAIGHT_LEFT);
	yTarget = 80.0f + rand() % (190 - 80);

//	DebugOut(L"StatusProcessing = %d, Target (%f, %f) \n", StatusProcessing, xTarget, yTarget);
	
 
	vx = (xTarget - xBefore) / (1000); // cho đi 1 giây
	vy = (yTarget - yBefore) / (1000);
}

void PhantomBat::StartAttack()
{
 
	DebugOut(L"ATTACK!\n");
	int DirectionWeapon = 0;
	float xAttack = x + GetWidth() / 2;
	float yAttack = y + GetHeight() / 2;

	if (xAttack < simon->GetX())
		DirectionWeapon = 1;
	else
		DirectionWeapon = -1;
	 
	// khoảng cách đạn bắn trúng simon
	float S = sqrt((xAttack - simon->GetX()) *(xAttack - simon->GetX()) + (yAttack - simon->GetY())*(y - simon->GetY())); //s=sqrt(x^2+y^2)

	// thời gian bắn trúng nếu dùng vận tốc FIREBALL_SPEED
	float t = S / FIREBALL_SPEED;

	weapon->SetSpeed( DirectionWeapon* abs(xAttack - simon->GetX())/t, abs(yAttack - simon->GetY())/t);
	weapon->Create(xAttack, yAttack, 1);

	StatusProcessing = PHANTOMBAT_PROCESS_ATTACK;

	//DebugOut(L"vx = %f , vy = %f , isFinish = %d\n", weapon->GetVx(), weapon->GetVy(), weapon->GetFinish());


	//DebugOut(L"!------------------------!\n\n");

	Sound::GetInstance()->Play(eSound::soundHit);

	TimeWaited = 0;
	isWaiting = true;
}
