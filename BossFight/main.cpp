#include <iostream>
#include<chrono>
#include<thread>
#include <graphics.h>
#include"Atlas.h"
#include"Animation.h"
#include "ResourcesManager.h"
static void draw_background() {
	static IMAGE* img_background=ResourcesManager::instance()->find_image("background");
	static Rect rect_dst=
	{
		(getwidth()-img_background->getwidth())/2,
		(getheight()-img_background->getheight())/2,
		img_background->getwidth(),
		img_background->getheight()
	};
	putimage_ex(img_background, &rect_dst);
}
int main() {
	using namespace std::chrono;

	HWND hwnd = initgraph(1280, 720, EW_SHOWCONSOLE);
	SetWindowText(hwnd, _T("Boss Fight"));

	try
	{
		ResourcesManager::instance()->load();
	}
	catch (const LPCTSTR id)
	{
		TCHAR err_msg[512];
		_stprintf_s(err_msg, _T("无法加载: %s"), id);
		MessageBox(hwnd, err_msg, _T("资源加载失败"), MB_OK | MB_ICONERROR);
		return -1;
	}
	const nanoseconds frame_duration(1000000000 / 144);
	steady_clock::time_point last_tick = steady_clock::now();

	ExMessage msg;
	bool is_quit = false;

	BeginBatchDraw();

	while (!is_quit) {
		while (peekmessage(&msg))
		{
			//处理消息
		}
		steady_clock::time_point frame_start = steady_clock::now();
		duration<double> delta = duration<float>(frame_start - last_tick);

		//处理更新
		setbkcolor(RGB(0, 0, 0));
		cleardevice();

		//处理绘制
		draw_background();
		FlushBatchDraw();

		last_tick = frame_start;
		nanoseconds remaining_duration = frame_duration - (steady_clock::now() - frame_start);
		if (remaining_duration > nanoseconds(0)) {
			std::this_thread::sleep_for(remaining_duration);
		}

	}
	EndBatchDraw();
	return 0;
}