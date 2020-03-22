#include"Create_images.h"

enum Create_images::COLORS;// { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };
int Create_images::pos_x = 1;
int Create_images::pos_y = 8;
string Create_images::doc_path = "document/doc.txt";
string Create_images::image_save_path = "mid/image_save/";
string Create_images::project_name = "first_try";
int Create_images::number_of_image = 0;
cv::String Create_images::cv_path = "";
Mat Create_images::image;
int Create_images::sum0 = 0, Create_images::sum1 = 0, Create_images::sum2 = 0;

void Create_images::get_color_pixel(uchar*& p, Create_images::COLORS color)
{
	//int* p;
	switch (color)
	{
	case BLACK:
	{
		p[0] = 0; p[1] = 0; p[2] = 0;
		break;
	}
	case RED:
	{
		p[0] = 0; p[1] = 0; p[2] = 255;
		break;
	}
	case GREEN:
	{
		p[0] = 0; p[1] = 255; p[2] = 0;
		break;
	}
	case YELLOW:
	{
		p[0] = 0; p[1] = 255; p[2] = 255;
		break;
	}
	case BLUE:
	{
		p[0] = 255; p[1] = 0; p[2] = 0;
		break;
	}
	case PURPLE:
	{
		p[0] = 255; p[1] = 0; p[2] = 255;
		break;
	}
	case CYAN:
	{
		p[0] = 255; p[1] = 255; p[2] = 0;
		break;
	}
	case WHITE:
	{
		p[0] = 255; p[1] = 255; p[2] = 255;
		break;
	}
	default:
	{
		cout << "存在错误" << endl;
		break;
	}
	}

}

Create_images::COLORS Create_images::number_to_color(int number)
{
	switch (number)
	{
	case 0:
	{
		return BLACK;
		break;
	}
	case 1:
	{
		return RED;
		break;
	}
	case 2:
	{
		return GREEN;
		break;
	}
	case 3:
	{
		return YELLOW;
		break;
	}
	case 4:
	{
		return BLUE;
		break;
	}
	case 5:
	{
		return PURPLE;
		break;
	}
	case 6:
	{
		return CYAN;
		break;
	}
	case 7:
	{
		return WHITE;
		break;
	}
	}
}

void Create_images::draw_block(int x, int y, int scale, COLORS color)
{
	for (int i = x * scale + 50; i < x * scale + scale + 50; i++)
	{
		for (int j = y * scale + 50; j < y * scale + scale + 50; j++)
		{
			uchar* p = image.ptr<uchar>(i, j);
			//p[0] = 0; p[1] = 0; p[2] = 0;
			get_color_pixel(p, color);
		}
	}
}

void Create_images::draw_big_block(int x, int y, int scale)
{
	draw_block(x, y, scale, BLACK);
	draw_block(x, y + 1, scale, BLACK);
	draw_block(x, y + 2, scale, BLACK);
	draw_block(x, y + 3, scale, BLACK);
	draw_block(x, y + 4, scale, BLACK);
	draw_block(x, y + 5, scale, BLACK);
	draw_block(x, y + 6, scale, BLACK);

	draw_block(x + 1, y, scale, BLACK);
	draw_block(x + 2, y, scale, BLACK);
	draw_block(x + 3, y, scale, BLACK);
	draw_block(x + 4, y, scale, BLACK);
	draw_block(x + 5, y, scale, BLACK);
	draw_block(x + 6, y, scale, BLACK);

	draw_block(x + 1, y + 6, scale, BLACK);
	draw_block(x + 2, y + 6, scale, BLACK);
	draw_block(x + 3, y + 6, scale, BLACK);
	draw_block(x + 4, y + 6, scale, BLACK);
	draw_block(x + 5, y + 6, scale, BLACK);
	draw_block(x + 6, y + 6, scale, BLACK);

	draw_block(x + 6, y + 1, scale, BLACK);
	draw_block(x + 6, y + 2, scale, BLACK);
	draw_block(x + 6, y + 3, scale, BLACK);
	draw_block(x + 6, y + 4, scale, BLACK);
	draw_block(x + 6, y + 5, scale, BLACK);

	for (int i = 2; i <= 4; i++)
		for (int j = 2; j <= 4; j++)
			draw_block(x + i, y + j, scale, BLACK);
}

void Create_images::draw_dingwei()
{
	int scale = 28;
	draw_big_block(0, 0, scale);
	draw_big_block(0, 18, scale);
	draw_big_block(18, 0, scale);
	//draw_big_block(image, 93, 93);
}

void Create_images::draw_edge()
{
	int scale = 28;
	for (int i = 0; i < 25; i++)
	{
		if (i != 7 && i != 17)
		{
			draw_block(0, i, scale, BLACK);
			draw_block(24, i, scale, BLACK);
			draw_block(i, 0, scale, BLACK);
			draw_block(i, 24, scale, BLACK);
		}
	}
}

void Create_images::initiate_new_image()
{
	//cout << "initiate" << endl;
	image = Mat::zeros(800, 800, CV_8UC3);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			uchar* p = image.ptr<uchar>(i, j);
			p[0] = 255; p[1] = 255; p[2] = 255;

		}
	}
	draw_dingwei();
	draw_edge();


	for (int i = 18; i < 25; i++)//右下角封边
	{
		draw_block(i, 24, 28, BLACK);
		draw_block(24, i, 28, BLACK);
	}
	//画二维码序号
	int temp = number_of_image;
	for (int i = 15; i >= 9; i--)
	{
		draw_block(i, 7, 28, number_to_color(7 - (temp % 8)));
		temp /= 8;
	}

	//画图奇偶标识码
	if (number_of_image % 2 == 0)
	{
		draw_block(9, 17, 28, RED);
	}
	else
	{
		draw_block(15, 17, 28, BLUE);
	}
}

void Create_images::change_pos()
{
	//cout << 3;
	pos_y += 3;
	if (pos_x >= 1 && pos_x <= 6 && pos_y >= 17)
	{
		//cout << "执行到了";
		pos_x += 1;
		pos_y = 8;
		return;
	}
	if (pos_x == 7 && pos_y >= 17)
	{
		pos_x += 1;
		pos_y = 1;
		return;
	}
	if (pos_x >= 8 && pos_x <= 15)
	{
		if (pos_y == 7 || pos_y == 17)
		{
			pos_y += 1;
			return;
		}
		if (pos_y >= 24)
		{
			pos_x += 1;
			pos_y = 1;
			return;
		}
	}
	if (pos_x == 16)
	{
		if (pos_y == 7 || pos_y == 17)
		{
			pos_y += 1;
			return;
		}
		if (pos_y >= 24)
		{
			pos_x += 1;
			pos_y = 8;
			return;
		}
	}
	if (pos_x >= 17 && pos_x <= 22)
	{
		if (pos_y == 17)
		{
			pos_y += 1;
		}
		if (pos_y >= 24)
		{
			pos_x += 1;
			pos_y = 8;
			return;
		}
	}
	if (pos_x == 23)
	{
		if (pos_y == 17)
		{
			pos_y += 1;
		}
		if (pos_y >= 24)
		{
			write_check();
			cv_path = image_save_path + project_name + to_string(number_of_image) + ".jpg";
			imwrite(cv_path, image);
			number_of_image++;
			initiate_new_image();
			pos_x = 1;
			pos_y = 8;
			return;
		}
	}
}

string Create_images::ascii_to_binary(int c)
{
	string binary_str = "";
	int number = (int)c;
	//cout << number << endl;
	stack<int> stk;
	while (number)
	{
		int temp = number % 2;
		stk.push(temp);
		number /= 2;
	}
	while (!stk.empty())
	{
		int temp = stk.top();
		stk.pop();
		if (temp)
			binary_str += "1";
		else
			binary_str += "0";
	}
	return binary_str;
}

void Create_images::write_each(int c)
{
	//cout << pos_x << "  " << pos_y << endl;
	unsigned char CC = (unsigned)c;
	int n0, n1, n2;
	int number_of_c = (int)CC;
	n0 = number_of_c % 4;
	number_of_c /= 4;
	n0 *= 2;
	n1 = number_of_c % 8;
	number_of_c /= 8;
	n2 = number_of_c % 8;
	string binary_str = ascii_to_binary((int)CC);
	int temp_count = 0;
	for (int i = 0; i < binary_str.length(); i++)
	{
		if (binary_str[i] == '1')
		{
			temp_count++;
		}
	}
	if (temp_count % 2 == 1)
		n0 += 1;
	//cout << "字符【" << (char)c << "】" << "ASCII码为【" << c << "】" << "对应的二进制码为" << binary_str << "三位数字分别为" << "n2=" << n2 << ",n1=" << n1 << ",n0=" << n0 << endl;
	draw_block(pos_x, pos_y, 28, number_to_color(n2));
	draw_block(pos_x, pos_y + 1, 28, number_to_color(n1));
	draw_block(pos_x, pos_y + 2, 28, number_to_color(n0));
	sum0 += n0;
	sum1 += n1;
	sum2 += n2;
	//cout << 2;
	change_pos();
}

void Create_images::write_Colorful_QRcode()
{
	ifstream in(doc_path, ios::in|ios::binary);
	if (!in)
	{
		cout << "文档路径不存在" << endl;
		exit(0);
	}
	initiate_new_image();
	//write_each(255);
	draw_start();
	char character;//char  int
	in >> noskipws;
	while (in.get(character))
	{
		write_each((int)character);
		//cout << 1;
	}
	//write_each(0);
	draw_end();
	write_check();
	cv_path = image_save_path + project_name + to_string(number_of_image) + ".jpg";
	imwrite(cv_path, image);
	in.close();
}

void Create_images::create_imgaes()
{
	cout << "生成图片中...." << endl;
	write_Colorful_QRcode();
	cout << "执行完毕" << endl;
}

void Create_images::set_doc_path(string str)
{
	doc_path = str;
}

int Create_images::get_number_of_imgae()
{
	return number_of_image;
}

void Create_images::write_check()
{
	int temp0 = sum0;
	draw_block(17, 17, 28, number_to_color(temp0 % 8));
	temp0 /= 8;
	draw_block(16, 17, 28, number_to_color(temp0 % 8));

	int temp1 = sum1;
	draw_block(19, 17, 28, number_to_color(temp1 % 8));
	temp1 /= 8;
	draw_block(18, 17, 28, number_to_color(temp1 % 8));

	int temp2 = sum2;
	draw_block(21, 17, 28, number_to_color(temp2 % 8));
	temp2 /= 8;
	draw_block(20, 17, 28, number_to_color(temp2 % 8));

	sum0 = 0;
	sum1 = 0;
	sum2 = 0;
}

void Create_images::draw_start()
{
	draw_block(11, 17, 28, RED);
	draw_block(12, 17, 28, RED);
	draw_block(13, 17, 28, RED);
}

void Create_images::draw_end()
{
	draw_block(11, 17, 28, BLUE);
	draw_block(12, 17, 28, BLUE);
	draw_block(13, 17, 28, BLUE);
}