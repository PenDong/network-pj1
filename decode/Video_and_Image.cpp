#include"Video_and_Image.h"

cv::String Video_and_Image::image_to_video_source;
cv::String Video_and_Image::image_to_video_des;
cv::String Video_and_Image::video_to_image_source = "video_in/in_video.mp4";
cv::String Video_and_Image::video_to_image_des;

void Video_and_Image::video_to_image_fun()
{
	VideoCapture videoCap(video_to_image_source);//�����Ƶ����D���µ�video1�ļ����µ�test.mp4��
	if (!videoCap.isOpened())
	{
		cout << "�Ҳ�����Ƶ" << endl;
		exit(0);
	}

	Mat img;						//����mat����
	int count = 0;					//ͼƬ˳��
	videoCap >> img;				//����֡

	cout << "��ȡ��" << endl;
	while (img.empty() == false) {  //���ȡ����ͼƬ��Ϊ��
		String imageName = "mid/image_cut/";//ͼƬ�����λ��
		ostringstream strCount;
		strCount << count;
		string str = strCount.str();
		imageName += ("origin" + str);		//��˳��������str��ͼƬ�����֣�
		imageName += ".jpg";	//ͼƬ��ʽ
		//flip(img,img, -1);			//��ͼƬ��ת180�ȣ���Ȼת������ͼƬ�ǵ��ģ�
		imwrite(imageName, img);	//д���ļ���
		count++;
		videoCap >> img;			//��ȡ��һ֡
	}
	cout << "��ȡ����" << endl;
}

void Video_and_Image::set_video_to_image_source(string str)
{
	video_to_image_source = str;
}