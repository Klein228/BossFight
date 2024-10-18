#pragma once
#include"Vector2.h"
#include"Timer.h"
#include <corecrt_math_defines.h>
class Camera
{
public:
	Camera()
	{
		timer_shake.set_one_shot(true);
		timer_shake.set_on_timeout([&]()
			{
				is_shaking = false;
				reset();
			});
	}
	~Camera() {}
	const Vector2& get_position() const
	{
		return position;
	}
	void reset()
	{
		position.x = 0;
		position.y = 0;
	}
	void on_updata(int delta)
	{
		timer_shake.on_updata(delta);

		if (is_shaking)
		{
			int angle = rand() % 360;
			float len = (rand() % 100) / 100.0;
			position.x = (shaking_strength * len) * cos(angle * 2 * M_PI / 360);
			position.y = (shaking_strength * len) * sin(angle * 2 * M_PI / 360);
		}
	}
	void shake(float strength, int duration)
	{
		is_shaking = true;
		shaking_strength = strength;
		timer_shake.set_wait_time(duration);
		timer_shake.restart();
	}
private:
	Vector2 position = { 0,0 };
	Timer	timer_shake;
	bool is_shaking = false;
	float shaking_strength = 0;//ÉãÏñ»ú¶¶¶¯·ù¶È
};