#include"Menu.h"

void Menu::GO()
{
	string doc_path;
	string video_path;
	int video_length;
	string order;
	cout << "��ֱ����� ָ��ı���ַ����Ƶ�����ַ����Ƶʱ��(��λms)"<<endl;
	cout << "��:encode in.bin in.avi 1000" << endl;
	cin >> order >> doc_path >> video_path >> video_length;


	while (order != "encode" && order != "ENCODE" && order != "Ecode")
	{
		cout << "��Чָ��,����������" << endl;
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
			cout << "������Ƶ������" << endl;
		}
	}
	else
	{
		cout << "Ӧ���ǳ�����" << endl;
	}

	
}