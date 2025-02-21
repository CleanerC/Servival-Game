#include "Animation.hpp"
#include "Helper.hpp"

class Player
{
public:
	Player();

	~Player();

	void ProcessEvent(const ExMessage& msg);

	void Move();

	void Draw(int delta);

private:
	const int SPEED = 3;
	const int FRAME_WIDTH = 80;
	const int FRAME_HEIGHT = 80;
	const int SHADOW_WIDH = 32;

private:
	IMAGE img_shadow;
	Animation* anim_left;
	Animation* anim_right;
	POINT position{ 500, 500 };
	bool is_moving_up = false;
	bool is_moving_down = false;
	bool is_moving_left = false;
	bool is_moving_right = false;
	
};