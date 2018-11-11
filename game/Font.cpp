#include "Font.h"



Font::Font()
{
	_texture = TextureManager::GetInstance()->GetTexture(eID::FONT);
	_sprite = new GSprite(_texture, 0);
}


Font::~Font()
{ 
	SAFE_DELETE(_sprite);
}

void Font::Draw(int x, int y, string s)
{ 
	for (UINT i = 0; i < s.size(); i++)
	{
		if (s[i] == ' ')
			continue;
		if (s[i] >= 'A' && s[i] <= 'Z')
		{
			_sprite->SelectIndex(s[i] - 'A');
		}
		else
			if (s[i] >= '0' && s[i] <= '9')
			{
				_sprite->SelectIndex(s[i] - '0' + 26);
			}
			else
				_sprite->SelectIndex(36);
		_sprite->Draw(x + i * _texture->FrameWidth, y);
	}
}
