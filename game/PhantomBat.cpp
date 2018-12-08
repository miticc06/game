#include "PhantomBat.h"
 
PhantomBat::PhantomBat(Simon * simon, Camera *camera, vector <Weapon*> * listWeaponOfEnemy)
{ 
	type = eType::PHANTOMBAT; 
	_texture = TextureManager::GetInstance()->GetTexture(eType::PHANTOMBAT);
	_sprite = new GSprite(_texture, 70);

	this->simon = simon;
	this->camera = camera;

	this->listWeaponOfEnemy = listWeaponOfEnemy;
	weapon = new FireBall();
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
	left = x;
	top = y;
	right = x + _texture->FrameWidth;
	bottom = y + _texture->FrameHeight;
}

void PhantomBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetHealth() <= 0)
		return;

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
			if (TimeWaited >= 4000)
			{
				isWaiting = false; // ngừng chờ

				StartCurves();
			}
		}
		

		break;
	}

	case PHANTOMBAT_PROCESS_CURVES:
	{  
		if (abs(x - xBefore) >= abs(xTarget-xBefore) || x <camera->GetXCam() || x+GetWidth()>camera->GetXCam()+ camera->GetWidth()) // đi xong hoặc chạm biên trái phải màn hình thì dừng
		{
			vx = 0;
			vy = 0;
			isUseBezierCurves = false;

			/*vượt quá camera thì đẩy lại vào cam*/
			if (x < camera->GetXCam())
				x += 1.0f;
			
			if (x + GetWidth() > camera->GetXCam() + camera->GetWidth())
			{
				x -= 1.0f;
			}
			/*vượt quá camera thì đẩy lại vào cam*/
			 

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
			abs(y - yBefore) >= abs(yTarget - yBefore) ||
			x <camera->GetXCam() || 
			x + GetWidth()>camera->GetXCam() + camera->GetWidth()) // đi xong hoặc chạm biên trái phải màn hình thì dừng
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
				abs(y - yBefore) >= abs(yTarget - yBefore) ||
				x <camera->GetXCam() ||
				x + GetWidth()>camera->GetXCam() + camera->GetWidth()) // đi xong hoặc chạm biên trái phải màn hình thì dừng
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

				int random = rand() % 2;
				switch (random)
				{
				case 0: //25 %
					StartAttack();
					break;

				default: // 75%
					StartCurves();

					break;
				}
				 
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


	GameObject::Update(dt);
	x += dx;
	y += dy;
	yLastFrame = y;// lưu lại y frame hiện tại
}

void PhantomBat::Render(Camera * camera)
{
	if (GetHealth() <= 0)
		return;

	if (StatusProcessing == PHANTOMBAT_PROCESS_SLEEP)
		_sprite->SelectIndex(0);
	else
	{ 
		_sprite -> Update(dt);
		if (_sprite->_index == 0)
			_sprite->SelectIndex(1);
	}

	D3DXVECTOR2 pos = camera->Transform(x, y); 
	_sprite->Draw((int)pos.x, (int)pos.y); 
	if (IS_DEBUG_RENDER_BBOX)
		RenderBoundingBox(camera);
	  
	if (IS_DEBUG_RENDER_BBOX)
	{ 
		if (isUseBezierCurves) // sử dụng BezierCurves thì mới vẽ 
		{
			for (float i = 0; i < 1; i += 0.01)
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
				float l, t, r, b;
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
		float l, t, r, b;
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
	xTarget = 5178 + rand() % (5492-5178);
	yTarget = 80 + rand() % (190 - 80);

	DebugOut(L"StatusProcessing = %d, Target (%f, %f) \n", StatusProcessing, xTarget, yTarget);
	
	//float tt = 1000.0f / (50 + rand() % 100);
	//vx = (xTarget - xBefore) / (abs(xTarget - xBefore)*tt);
	//vy = (yTarget - yBefore) / (abs(yTarget - yBefore)*tt);
	vx = (xTarget - xBefore) / (1000); // cho đi 1 giây
	vy = (yTarget - yBefore) / (1000);
}

void PhantomBat::StartAttack()
{
	//DebugOut(L"\n\n!===========================!\n");

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
