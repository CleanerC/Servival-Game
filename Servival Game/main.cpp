#include "Helper.hpp"
#include "Player.hpp"

Player player;

int main()
{
	initgraph(1280, 720);

	bool isRunning = true;

	ExMessage msg;
	IMAGE imgBackground;

	loadimage(&imgBackground, _T("img/background.png"));

	BeginBatchDraw();

	while (isRunning)
	{
		DWORD startTime = GetTickCount();

		while (peekmessage(&msg))
		{
			player.ProcessEvent(msg);
		}

		cleardevice();

		putimage(0, 0, &imgBackground);	//back ground

		player.Move();
		player.Draw(1000 / 144);

		FlushBatchDraw();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		if (deltaTime < 1000 / 144)
		{
			Sleep(1000 / 144 - deltaTime);
		}
	}

	closegraph();
}