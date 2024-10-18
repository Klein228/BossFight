#pragma once
#include<functional>

class Timer
{
public:
	Timer() {}
	~Timer() {}
	void restart()
	{
		pass_time = 0;
		shotted = false;
	}
	void set_wait_time(int ms)
	{
		wait_time = ms;
	}
	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}
	void set_on_timeout(std::function<void()> callback)
	{
		this->on_timeout = callback;
	}
	void pause()
	{
		paused = true;
	}
	void resume()
	{
		paused = false;
	}

	void on_updata(int delta)
	{
		if (paused)
			return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			bool can_shot = (!one_shot || (one_shot && !shotted));
			shotted = true;
			if (can_shot && on_timeout)
				on_timeout();
			pass_time -= wait_time;
		}
	}
private:
	int pass_time = 0;//已过时间
	int wait_time = 0;//等待时间
	bool paused = false;//是否暂停
	bool shotted = false;//是否触发
	bool one_shot = false;//单次触发
	std::function<void()> on_timeout;
};
