#include "SoundClass.h"

vector<IMusic*> SoundClass::Samples = vector<IMusic*>(0);
SoundClass::SoundClass(void)
{
}

void SoundClass::AddSample(IMusic* sample)
{
	Samples.push_back(sample);
}
void SoundClass::Play(int index)
{
	bool t;
	Samples[index]->IsPlaying(t);
	if(!t)
		Samples[index]->Play(false);
}
SoundClass::~SoundClass(void)
{
}
