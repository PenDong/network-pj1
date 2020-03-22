#include"Menu.h"

void Menu::GO()
{
	string doc_path;
	string video_path;
	int video_length;
	string order;
	cout << "请分别输入 指令，文本地址，视频输出地址，视频时长(单位ms)"<<endl;
	cout << "例:encode in.bin in.avi 1000" << endl;
	cin >> order >> doc_path >> video_path >> video_length;


	while (order != "encode" && order != "ENCODE" && order != "Ecode")
	{
		cout << "无效指令,请重新输入" << endl;
		cin >> order >> doc_path >> video_path >> video_length;
	}
	if (order == "encode" || order == "ENCODE" || order == "Ecode")
	{
		Create_images::set_doc_path(doc_path);
		Video_and_Image::set_image_to_video_des(video_path);
		Video_and_Image::set_video_length(video_length);
		Create_images::create_imgaes();
		if (!Video_and_Image::image_to_vedio_fun())
		{
			cout << "生成视频出错了" << endl;
		}
	}
	else
	{
		cout << "应该是出错了" << endl;
	}

	
}