#include"Video_and_Image.h"

cv::String Video_and_Image::image_to_video_source;
cv::String Video_and_Image::image_to_video_des;
int Video_and_Image::video_length;
//cv::String Video_and_Image::video_to_image_source = "video_in/in_video.mp4";
//cv::String Video_and_Image::video_to_image_des;



bool Video_and_Image::image_to_vedio_fun()
{
	VideoWriter video;
	String pattern = "mid/image_save/first_try*.jpg";		// ��һ���ļ����¶�ȡ����jpgͼƬ
	vector<String> fn;							//�趨ͼƬ����fn
	glob(pattern, fn, false);
	size_t count = fn.size();
	String path = "mid/image_save/first_try";
	String temp_path;

	double time_per_frame =  1000.0*count/(double)video_length ;
	video.open(image_to_video_des, CV_FOURCC('X', 'V', 'I', 'D'), time_per_frame, Size(1080, 1080), true);// ����һ��VideoWriter(��ַ����ʽ��֡�ʡ���С���Ҷ�ֵ)
	//cout << count << endl;
	for (size_t i = 0; i < count; i++)
	{
		//cout << fn[i] << endl;
		temp_path = path+to_string((int)i) + ".jpg";
		cout << temp_path << endl;
		Mat image = imread(temp_path);				//�����ȡͼƬ
		if (!image.data)
		{
			cout << "û��ͼƬ";
			return false;
		}

		//cout << fn[i] << endl;
		resize(image, image, Size(1080, 1080));	// �趨֡�Ĵ�С�������С��VideoWriter���캯���еĴ�Сһ�¡�
		video << image;							// ������������֡������Ƶ
	}
	cout << "������ϣ�" << endl;
	return true;
}


void Video_and_Image::set_image_to_video_source(string str)
{
	image_to_video_source = str;
}

void Video_and_Image::set_video_length(int l)
{
	video_length = l;
}

void Video_and_Image::set_image_to_video_des(string str)
{
	image_to_video_des = str;
}