#include <graphics.h>
#include <string>
#include <vector>
#include <Windows.h>
#include <tchar.h>
#include "Helper.hpp"

class Animation
{
public:
	Animation(LPCTSTR path, int num, int interval);

	~Animation();

	void play(int x, int y, int delta_time);

private:
	int timer = 0;
	int idx_frame = 0;
	int interval_ms = 0;
	std::vector<IMAGE*> frame_list;
};