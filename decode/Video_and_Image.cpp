#include"Video_and_Image.h"

cv::String Video_and_Image::image_to_video_source;
cv::String Video_and_Image::image_to_video_des;
cv::String Video_and_Image::video_to_image_source = "video_in/in_video.mp4";
cv::String Video_and_Image::video_to_image_des;

void Video_and_Image::video_to_image_fun()
{
	VideoCapture videoCap(video_to_image_source);//获得视频（即D盘下的video1文件夹下的test.mp4）
	if (!videoCap.isOpened())
	{
		cout << "找不到视频" << endl;
		exit(0);
	}

	Mat img;						//定义mat变量
	int count = 0;					//图片顺序
	videoCap >> img;				//读入帧

	cout << "读取中" << endl;
	while (img.empty() == false) {  //如果取到的图片不为空
		String imageName = "mid/image_cut/";//图片的输出位置
		ostringstream strCount;
		strCount << count;
		string str = strCount.str();
		imageName += ("origin" + str);		//按顺序命名（str是图片的名字）
		imageName += ".jpg";	//图片格式
		//flip(img,img, -1);			//将图片旋转180度（不然转出来的图片是倒的）
		imwrite(imageName, img);	//写入文件夹
		count++;
		videoCap >> img;			//读取下一帧
	}
	cout << "读取结束" << endl;
}

void Video_and_Image::set_video_to_image_source(string str)
{
	video_to_image_source = str;
}