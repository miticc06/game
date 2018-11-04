#include "Animation.h"



Animation::Animation()
{
}

Animation::Animation(Sprite * sprite, int defaultTime)
{

	this->_sprite = sprite;
	this->defaultTime = defaultTime;
	this->currentFrame = -1; // chưa vẽ sprite nào
	this->lastFrameTime = -1;

}
  

void Animation::Render(float x, float y, int alpha)
{
	DWORD now = GetTickCount();
	if (currentFrame == -1)
	{
		currentFrame = 0;
		lastFrameTime = now;
	}
	else
	{
		DWORD t = this->defaultTime;//frames[currentFrame]->GetTime(); // Thời gian của frame
		if (now - lastFrameTime > t)
		{
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == _frameRectList.size())
				currentFrame = 0;
		} 
	}
	_sprite->Draw(x, y, _frameRectList[currentFrame], alpha); 
}


void Animation::addFrameRect(RECT rect)
{
	//// Nếu là rect đầu tiên thì set currentRect luôn
	//if (_frameRectList.empty())
	//{
	//	currentFrame = 0;
	//}
	_frameRectList.push_back(rect); 
}


void Animation::addFrameRect(eID id, char * firstRectName, ...)
{
	va_list vl;
	char* rectName;
	va_start(vl, firstRectName);
	rectName = firstRectName;
	while (rectName != NULL)
	{
		this->addFrameRect(SpritesManager::GetInstance()->getSourceRect(id, rectName));
		rectName = va_arg(vl, char*);
	}

	va_end(vl);
}