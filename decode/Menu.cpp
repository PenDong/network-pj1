#include"Menu.h"

void Menu::GO()
{
	string order;
	string video_path;
	string out_file_path;
	cout << "�밴˳������ ָ���Ƶ��ַ������ļ��������Ч�ļ�����ʱ��û��" << endl;
	cin >> order >> video_path >> out_file_path;
	while (order != "decode" && order != "DECODE" && order != "Decode")
	{
		cout << "ָ���������Ӧ����decode��DECODE��Decode,����������" << endl;
		cin >> order >> video_path >> out_file_path;
	}
	Video_and_Image::set_video_to_image_source(video_path);
	Decode::set_out_file_path_and_name(out_file_path);


	Video_and_Image::video_to_image_fun();
	Cut_QRcode::cut_qrcodes();
	Decode::decode();
}