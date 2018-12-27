#ifndef __SOUND_H__
#define __SOUND_H__

#include "Game.h"
#include "dsutil.h"
#include <unordered_map>



enum eSound
{
	soundWhip = 1,
	soundHit = 2,
	soundCollectItem = 3,
	soundCollectWeapon = 4,
	soundStopTimer = 5,
	soundDagger = 6,
	soundDisplayMonney = 7,
	soundHurting = 8,
	soundOpenDoor = 9,
	soundBrokenBrick = 10,
	soundHolyWater = 11,
	soundSplashwater = 12,
	soundFallingDownWaterSurface = 13,
	soundGetScoreTimer = 14,
	soundGetScoreHeart = 15,
	soundAxe = 16,
	soundStopWatch = 17,
	soundInvisibilityPotion_Begin = 18,
	soundInvisibilityPotion_End = 19,
	soundHolyCross = 20,
	soundBoomerang = 21,


	musicState1 = 51,
	musicLifeLost = 52,
	music_PhantomBat = 53,
	musicStateClear = 54,
	musicGame_Start_Prologue = 55
};


class Sound
{
private:
	unordered_map<eSound, CSound* > _ArrSound;

public:
	static Sound * __Instance;
	static Sound * GetInstance();


	CSoundManager *dsound;

	void Init();
	Sound();

	void AddSound(eSound type, LPTSTR filename);
	void Play(eSound type, bool isLoop = false, LONG lVolume = 0L);
	void Stop(eSound type);
	void LoadResourceSound();

	bool isPlaying(eSound type);

	void StopAll();

};

#endif

