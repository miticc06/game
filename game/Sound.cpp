
#include "Sound.h"
 
Sound* Sound::__Instance = NULL;

Sound::Sound()
{
	Init();
	LoadResourceSound();
}



void Sound::LoadResourceSound()
{
	AddSound(eSound::soundWhip, L"Resources/sound/usingwhip.wav");
	AddSound(eSound::soundHit, L"Resources/sound/hit.wav");
	AddSound(eSound::soundCollectItem, L"Resources/sound/collectitem.wav");
	AddSound(eSound::soundCollectWeapon, L"Resources/sound/collectweapon.wav");

	AddSound(eSound::soundStopTimer, L"Resources/sound/stoptimer.wav");
	AddSound(eSound::soundDagger, L"Resources/sound/usingdagger.wav");
	AddSound(eSound::soundDisplayMonney, L"Resources/sound/display_monney.wav");

	AddSound(eSound::soundHurting, L"Resources/sound/hurting.wav");
	AddSound(eSound::soundOpenDoor, L"Resources/sound/opendoor.wav");



	AddSound(eSound::musicState1, L"Resources/music/Stage_01_Vampire_Killer.wav");
	AddSound(eSound::musicLifeLost, L"Resources/music/Life_Lost.wav");


}

bool Sound::isPlaying(eSound type)
{
	return _ArrSound[type]->IsSoundPlaying();
}


void Sound::AddSound(eSound type, LPTSTR filename)
{
 	CSound *wave;
 	HRESULT result= dsound->Create(&wave, filename);
	if (result != DS_OK)
	{
		DebugOut(L"[SOUND] Load Sound that bai. eSound = %d \n", (int)type);
		return;
	} 
	_ArrSound[type] = wave;
}

void Sound::Play(eSound type, bool isLoop)
{
	_ArrSound[type]->Play(0, isLoop);
	//DSBPLAY_LOOPING             0x00000001 -> int = 1

}

void Sound::Stop(eSound type)
{
	_ArrSound[type]->Stop();
}



void Sound::Init()
{
	dsound = new CSoundManager();
	dsound->Initialize(Game::GetInstance()->GetWindowHandle(), DSSCL_PRIORITY);
	dsound->SetPrimaryBufferFormat(2, 22050, 16);
}

Sound * Sound::GetInstance()
{
	if (__Instance == NULL)
		__Instance = new Sound();
	return __Instance;
} 