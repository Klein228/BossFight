#pragma once
#include"Atlas.h"
#include"utils.h"
#include"functional"
#include"Camera.h"
extern Camera main_camera;
class Animation
{
public:
	enum AnchorMode
	{
		Centered,
		BottomCentered
	};
	Animation() {
		timer.set_one_shot(false);
		timer.set_on_timeout([&]() {
			idx_frame++;
			if (idx_frame >= frame_list.size())
			{
				idx_frame = is_loop ? 0 : frame_list.size() - 1;
				if (!is_loop && on_finished)
					on_finished();
			}
			});

	}
	~Animation() {}
	void reset()
	{
		timer.restart();
		idx_frame = 0;
	}
	void set_anchor_mode(AnchorMode mode)
	{
		anchor_mode = mode;
	}
	void set_position(const Vector2& position)
	{
		this->position = position;
	}
	void set_loop(bool loop)
	{
		is_loop = loop;
	}
	void set_interval(unsigned int ms)
	{
		timer.set_wait_time(ms);
	}
	void set_on_finished(std::function<void()> on_finished)
	{
		this->on_finished = on_finished;
	}
	void add_frame(IMAGE* image, int num_h)
	{
		int width = image->getwidth();
		int height = image->getheight();
		int width_frame = width / num_h;
		for (int i = 0; i < num_h; i++)
		{
			Rect rect_src;
			rect_src.x = num_h * width, rect_src.y = 0;
			rect_src.w = width_frame, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}
	}
	void add_frame(Atlas* atlas)
	{
		for (int i = 0; i < atlas->get_size(); i++)
		{
			IMAGE* image = atlas->get_img_at(i);
			int width = image->getwidth();
			int height = image->getheight();

			Rect rect_src;
			rect_src.x = 0, rect_src.y = 0;
			rect_src.w = width, rect_src.h = height;

			frame_list.emplace_back(image, rect_src);
		}
	}
	void on_updata(int delta)
	{
		timer.on_updata(delta);
	}
	void on_render()
	{
		const Frame& frame = frame_list[idx_frame];
		Rect rect_dst;
		rect_dst.x = (int)position.x - frame.rect_src.w / 2;
		rect_dst.y = (anchor_mode == AnchorMode::Centered)
			? (int)position.y - frame.rect_src.h / 2 : (int)position.y - frame.rect_src.h;
		rect_dst.w = frame.rect_src.w, rect_dst.h = frame.rect_src.h;

		putimage_ex(frame.image, &rect_dst, &frame.rect_src);
	}
private:
	struct Frame
	{
		Rect rect_src;
		IMAGE* image = nullptr;

		Frame() = default;
		Frame(IMAGE* image, const Rect& rect_src)
			:image(image), rect_src(rect_src) {}
		~Frame() = default;

	};
	Timer timer;//控制动画播放计时器
	Vector2 position;//动画渲染位置
	bool is_loop;//是否循环播放动画
	size_t idx_frame = 0;//当前播放帧数
	std::vector<Frame> frame_list;//动画帧列表
	std::function<void()> on_finished;//动画结束调用
	AnchorMode anchor_mode = AnchorMode::Centered;//当前锚点模式
};