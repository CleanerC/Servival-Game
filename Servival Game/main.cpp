#include "Animation.hpp"
#include "Helper.hpp"

const int PLAYER_ANIM_NUM = 6;

IMAGE img_player_left[PLAYER_ANIM_NUM];
IMAGE img_player_right[PLAYER_ANIM_NUM];

const int PLAYER_SPEED = 3;

int idx_current_anim = 0;

Animation* anim_left_player = nullptr;
Animation* anim_right_player = nullptr;

POINT player_pos = { 500, 500 };

const int PLAYER_WIDTH = 80;
const int PLAYER_HEIGHT = 80;
const int SHADOW_WIDTH = 32;

IMAGE img_shadow;

void DrawPlayer(int delta, int dir_x)
{
	int pos_shadow_x = player_pos.x + (PLAYER_WIDTH / 2 - SHADOW_WIDTH / 2);
	int pos_shadow_y = player_pos.y + PLAYER_HEIGHT - 8;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	static bool facing_left = false;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
		anim_left_player->play(player_pos.x, player_pos.y, delta);
	else 
		anim_right_player->play(player_pos.x, player_pos.y, delta);
}

void loadAnimation()
{
	for (size_t ii = 0; ii < PLAYER_ANIM_NUM; ++ii)
	{
		std::wstring path = L"img/player_left_" + std::to_wstring(ii) + L".png";
		loadimage(&img_player_left[ii], path.c_str());
	}
	for (size_t ii = 0; ii < PLAYER_ANIM_NUM; ++ii)
	{
		std::wstring path = L"img/player_right_" + std::to_wstring(ii) + L".png";
		loadimage(&img_player_right[ii], path.c_str());
	}
}

int main()
{
	initgraph(1280, 720);

	bool isRunning = true;

	anim_left_player = new Animation(_T("img/paimon_left_%d.png"), 6, 45);
	anim_right_player = new Animation(_T("img/paimon_right_%d.png"), 6, 45);

	ExMessage msg;
	IMAGE imgBackground;


	bool is_moving_up = false;
	bool is_moving_down = false;
	bool is_moving_left = false;
	bool is_moving_right = false;

	loadimage(&img_shadow, _T("img/shadow_player.png"));
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

		putimage(0, 0, &imgBackground);	//back ground
		DrawPlayer(1000 / 144, is_moving_right - is_moving_left);

		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 144)
		{
			Sleep(1000 / 144 - deltaTime);
		}
	}

	delete anim_left_player;
	delete anim_right_player;

	closegraph();
}