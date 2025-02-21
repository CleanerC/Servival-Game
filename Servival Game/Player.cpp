#include "Player.hpp"

Player::Player()
{
	loadimage(&img_shadow, _T("img/shadow_player.png"));
	anim_left = new Animation(_T("img/paimon_left_%d.png"), 6, 45);
	anim_right = new Animation(_T("img/paimon_right_%d.png"), 6, 45);
}

Player::~Player()
{
	delete anim_left;
	delete anim_right;
}

void Player::ProcessEvent(const ExMessage& msg)
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

void Player::Move()
{
	int dir_x = is_moving_right - is_moving_left;
	int dir_y = is_moving_down - is_moving_up;
	double len_dir = sqrt(dir_x * dir_x + dir_y * dir_y);
	if (len_dir != 0)
	{
		double normalized_x = dir_x / len_dir;
		double normalized_y = dir_y / len_dir;
		position.x += (int)(SPEED * normalized_x);
		position.y += (int)(SPEED * normalized_y);
	}
	
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + FRAME_WIDTH > 1280) position.x = 1280 - FRAME_WIDTH;
	if (position.y + FRAME_HEIGHT > 720) position.y = 720 - FRAME_HEIGHT;
}

void Player::Draw(int delta)
{
	int pos_shadow_x = position.x + (FRAME_WIDTH - SHADOW_WIDH) / 2;
	int pos_shadow_y = position.y + FRAME_HEIGHT - 8;
	putimage_alpha(pos_shadow_x, pos_shadow_y, &img_shadow);

	static bool facing_left = false;
	int dir_x = is_moving_right - is_moving_left;
	if (dir_x < 0)
		facing_left = true;
	else if (dir_x > 0)
		facing_left = false;

	if (facing_left)
		anim_left->play(position.x, position.y, delta);
	else
		anim_right->play(position.x, position.y, delta);
}