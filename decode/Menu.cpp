#include"Menu.h"

void Menu::GO()
{
	string order;
	string video_path;
	string out_file_path;
	cout << "请按顺序输入 指令，视频地址，输出文件，检查有效文件（暂时还没）" << endl;
	cin >> order >> video_path >> out_file_path;
	while (order != "decode" && order != "DECODE" && order != "Decode")
	{
		cout << "指令输入错误，应输入decode或DECODE或Decode,请重新输入" << endl;
		cin >> order >> video_path >> out_file_path;
	}
	Video_and_Image::set_video_to_image_source(video_path);
	Decode::set_out_file_path_and_name(out_file_path);


	Video_and_Image::video_to_image_fun();
	Cut_QRcode::cut_qrcodes();
	Decode::decode();
}