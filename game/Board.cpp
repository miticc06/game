#include "Board.h"
 
string Board::FillNumber(string s, UINT MaxNumber)
{
	while (s.size() < MaxNumber)
		s = "0" + s;
	return s;
}

Board::Board(int X, int Y)
{
 	_texture = TextureManager::GetInstance()->GetTexture(eType::BOARD);
	_sprite = new GSprite(_texture, 0);
	x = X;
	y = Y;
}
 

void Board::Render(Simon * simon , int state, Weapon * weaponSub, int RemainingTime, GameObject * boss)
{ 
	_sprite->Draw(x,y);
	_font.Draw(x + 10, y+15, "SCORE-");
	_font.Draw(x + 10, y + 15, "SCORE-" + FillNumber(std::to_string(simon->GetScore()), (UINT) 6)  );

	_font.Draw(x + 10, y+33, "PLAYER");
	_font.Draw(x + 10, y+51, "ENEMY");


	_font.Draw(x+220 , y + 15, "TIME " + FillNumber(std::to_string(RemainingTime), (UINT)4) );


	_font.Draw(x + 400 -20, y + 15, "STAGE");
	_font.Draw(x + 400 + 60, y + 15, FillNumber(std::to_string(state),2));


	_font.Draw(x + 400 + 25, y + 15+18, FillNumber(std::to_string(simon->GetHeartCollect()),2)); // Số lượng tim nhặt dc
	_font.Draw(x + 400 + 25, y + 15 + 18+18, FillNumber(std::to_string(simon->GetLives()),2)); // số mạng sông


	int BloodBoss = 16; 
	if (boss != NULL)
	{
		BloodBoss = (int)(boss->GetHealth()* 16 / 24);// HEALTH =24 -> 16 vạch
		if (BloodBoss == 0 && boss->GetHealth() > 0)
			BloodBoss = 1;
	}
	_boardHealth.Draw(x + 110, y + 30, simon->GetHealth(), BloodBoss); 
	 
	if (weaponSub != NULL)
	{
		switch (weaponSub->GetType())
		{
		case eType::DAGGER:
			weaponSub->RenderIcon(x + 330,y + 40);
			break;

		case eType::HOLYWATER:
			weaponSub->RenderIcon(x + 332, y + 33);
			break;
		case eType::STOPWATCH:
			weaponSub->RenderIcon(x + 332, y + 31);
			break;
		case eType::THROWINGAXE:
			weaponSub->RenderIcon(x + 330, y + 35);
			break;
		default:
			break;
		} 

	}

}


Board::~Board()
{
	SAFE_DELETE(_sprite);
}

void Board::SetTexture(GTexture * tex)
{
	_texture = tex;
	_sprite->_texture = tex; 
}
