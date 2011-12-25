#pragma once
#include "DGLE2.h"
#include"DGLE2_EXT.h"
#include <vector>
using namespace DGLE2;
using namespace std;
class SoundClass
{
public:
	static vector<IMusic*> Samples;
	static void AddSample(IMusic* sample);
	static void Play(int index);
	SoundClass(void);
	~SoundClass(void);
};

