#include "Animation.hpp"

Animation::Animation(LPCTSTR path, int num, int interval)
{
	interval_ms = interval;
	TCHAR file_path[256];

	for (size_t ii = 0; ii < num; ii++)
	{
		_stprintf_s(file_path, path, ii);
		IMAGE* frame = new IMAGE();

		loadimage(frame, file_path);
		frame_list.push_back(frame);
	}
}

Animation::~Animation()
{
	for (size_t ii = 0; ii < frame_list.size(); ii++)
	{
		delete frame_list[ii];
	}
}

void Animation::play(int x, int y, int delta_time)
{
	timer += delta_time;
	if (timer >= interval_ms)
	{
		idx_frame = (idx_frame + 1) % frame_list.size();
		timer = 0;
	}

	putimage_alpha(x, y, frame_list[idx_frame]);
}