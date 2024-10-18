#pragma once
#include<graphics.h>
#include <vector>
#include <string>
class Atlas
{
public:
	Atlas() {}
	~Atlas() {}

	void load(LPCTSTR filepath, int num)
	{
		img_list.clear();
		img_list.resize(num);
		TCHAR path_file[256];
		for (int i = 0; i < num; i++)
		{
			_stprintf_s(path_file, 256, filepath, i+1);
			loadimage(&img_list[i], path_file);
		}

	}
	void load(LPCTSTR filepath, int num, int width, int height)
	{
		img_list.clear();
		img_list.resize(num);
		TCHAR path_file[256];
		for (int i = 0; i < img_list.size(); i++)
		{
			_stprintf_s(path_file, 256, filepath, i+1);
			loadimage(&img_list[i], path_file, width, height);
		}

	}
	void clear_img()
	{
		img_list.clear();
	}
	int get_size()
	{
		return img_list.size();
	}
	IMAGE* get_img_at(int index)
	{
		if (index < 0 || index >= img_list.size())
			return nullptr;
		else
		{
			return &img_list[index];
		}
	}
	void add_img(IMAGE img)
	{
		img_list.push_back(img);
	}
private:
	std::vector<IMAGE> img_list;
};
