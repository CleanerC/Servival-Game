#include <graphics.h>
#include <Windows.h>
#include <string>

const int PLAYER_ANIM_NUM = 6;
const int PLAYER_SPEED = 3;

int idx_current_anim = 0;

IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

#pragma comment(lib, "Msimg32.lib")

inline void putimage_alpha(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h, GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA });
}

void loadAnimation()
{
	for (size_t ii = 0; ii < PLAYER_ANIM_NUM; ++ii)
	{
		std::wstring path = L"img/paimon_left_" + std::to_wstring(ii) + L".png";
		loadimage(&img_player_left[ii], path.c_str());
	}

	for (size_t ii = 0; ii < PLAYER_ANIM_NUM; ++ii)
	{
		std::wstring path = L"img/paimon_right_" + std::to_wstring(ii) + L".png";
		loadimage(&img_player_right[ii], path.c_str());
	}
}

POINT player_pos = { 500, 500 };

int main()
{
	initgraph(1280, 720);

	bool isRunning = true;

	ExMessage msg;
	IMAGE imgBackground;

	bool is_moving_up = false;
	bool is_moving_down = false;
	bool is_moving_left = false;
	bool is_moving_right = false;


	loadimage(&imgBackground, _T("img/background.png"));
	loadAnimation();

	BeginBatchDraw();

	while (isRunning)
	{
		DWORD startTime = GetTickCount();

		while (peekmessage(&msg))
		{
			if (msg.message == WM_KEYDOWN)
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					is_moving_up = true;
					break;
				case VK_DOWN:
					is_moving_down = true;
					break;
				case VK_LEFT:
					is_moving_left = true;
					break;
				case VK_RIGHT:
					is_moving_right = true;
					break;
				}
			}
			else if (msg.message == WM_KEYUP)
			{
				switch (msg.vkcode)
				{
				case VK_UP:
					is_moving_up = false;
					break;
				case VK_DOWN:
					is_moving_down = false;
					break;
				case VK_LEFT:
					is_moving_left = false;
					break;
				case VK_RIGHT:
					is_moving_right = false;
					break;
				}
			}
		}

		if (is_moving_up)
		{
			player_pos.y -= PLAYER_SPEED;
		}
		if (is_moving_down)
		{
			player_pos.y += PLAYER_SPEED;
		}
		if (is_moving_left)
		{
			player_pos.x -= PLAYER_SPEED;
		}
		if (is_moving_right)
		{
			player_pos.x += PLAYER_SPEED;
		}

		static int counter = 0;
		if (++counter % 5 == 0)
		{
			idx_current_anim++;
		}

		idx_current_anim = idx_current_anim % PLAYER_ANIM_NUM;

		cleardevice();

		putimage(0, 0, &imgBackground);
		putimage_alpha(player_pos.x, player_pos.y, &img_player_left[idx_current_anim]);

		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 144)
		{
			Sleep(1000 / 144 - deltaTime);
		}
	}
}