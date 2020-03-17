#include"Decode.h"
#include<ctime>

enum Decode::COLORS;// { BLACK, RED, GREEN, YELLOW, BLUE, PURPLE, CYAN, WHITE };
int Decode::pos_x = 1;
int Decode::pos_y = 8;

int Decode::upflag0 = 0, Decode::upflag1 = 0, Decode::upflag2 = 0;
int Decode::downflag0 = 0, Decode::downflag1 = 0, Decode::downflag2 = 0;
int Decode::leftflag0 = 0, Decode::leftflag1 = 0, Decode::leftflag2 = 0;
int Decode::rightflag0 = 0, Decode::rightflag1 = 0, Decode::rightflag2 = 0;
double Decode::left_rate = 0;
double Decode::right_rate = 0;
double Decode::up_rate = 0;
double Decode::down_rate = 0;
int Decode::correct_row = 0;
int Decode::correct_col = 0;
//这是一条分割线
int Decode::temp_left = 0;
int Decode::temp_right = 0;
int Decode::temp_up = 0;
int Decode::temp_down = 0;

int Decode::row_scale = 0;
int Decode::col_scale = 0;

string Decode::image_path = "mid/image_waiting_decode/";
string Decode::proj_name = "waiting_decode";
cv::String Decode::image_path_and_name = "";
string Decode::out_file_path_and_name = "document/outfile.txt";

bool Decode::is_start = false;
bool Decode::is_end = false;
int Decode::now_image = 0;
bool Decode::is_good = true;

char Decode::buffer[119];
int Decode::buffer_index = 0;


int Decode::get_leftflag(Mat& image, int pos)
{
	for (int j = 0; j < 100; j++)
	{
		if (j == 99)
		{
			cout << "erro in leftflag0" << endl;
			//system("pause");
		}
		uchar* p = image.ptr<uchar>(pos, j);
		if (p[0] <= 100 && p[1] <= 100 && p[2] <= 100)
		{
			return j;
			break;
		}
	}
}

int Decode::get_rightflag(Mat& image, int pos)
{
	for (int j = image.cols - 1; j > 699; j--)
	{
		if (j == 700)
		{
			cout << "erro in leftflag0" << endl;
			//system("pause");
		}
		uchar* p = image.ptr<uchar>(pos, j);
		if (p[0] <= 100 && p[1] <= 100 && p[2] <= 100)
		{
			return j;
			break;
		}
	}
}

int Decode::get_upflag(Mat& image, int pos)
{
	for (int j = 0; j < 100; j++)
	{
		if (j == 99)
		{
			cout << "erro in leftflag0" << endl;
			//system("pause");
		}
		uchar* p = image.ptr<uchar>(j, pos);
		if (p[0] <= 100 && p[1] <= 100 && p[2] <= 100)
		{
			return j;
			break;
		}
	}
}

int Decode::get_downtflag(Mat& image, int pos)
{
	for (int j = image.rows - 1; j > 699; j--)
	{
		if (j == 700)
		{
			cout << "erro in leftflag0" << endl;
			//system("pause");
		}
		uchar* p = image.ptr<uchar>(j, pos);
		if (p[0] <= 100 && p[1] <= 100 && p[2] <= 100)
		{
			return j;
			break;
		}
	}
}

double Decode::get_left_and_up_rate(int x0, int x1, int x2)
{
	if (x0 == x1 && x1 == x2)
		return 0;
	if (x0 - x2 >= -2 && x0 - x2 <= 2)
		return 0;
	if (x0 == 0)
		return ((double)(x2 - x1)) / 300.0;
	if (x2 == 0)
		return ((double)(x2 - x1)) / 300.0;
	return ((double)(x2 - x0)) / 600.0;

}

double Decode::get_right_and_down_rate(int x0, int x1, int x2)
{
	if (x0 == x1 && x1 == x2)
		return 0;
	if (x0 - x2 >= -2 && x0 - x2 <= 2)
		return 0;
	if (x0 == 799)
		return ((double)(x2 - x1)) / 300.0;
	if (x2 == 799)
		return ((double)(x2 - x1)) / 300.0;
	return ((double)(x2 - x0)) / 600.0;

}

void Decode::initiate_image(Mat& image)
{
	upflag0 = 0, upflag1 = 0, upflag2 = 0;
	downflag0 = 0, downflag1 = 0, downflag2 = 0;
	leftflag0 = 0, leftflag1 = 0, leftflag2 = 0;
	rightflag0 = 0, rightflag1 = 0, rightflag2 = 0;
	left_rate = 0;
	right_rate = 0;
	up_rate = 0;
	down_rate = 0;
	correct_row = 0;
	correct_col = 0;
	//这是一条分割线
	temp_left = 0;
	temp_right = image.cols - 1;
	temp_up = 0;
	temp_down = image.rows - 1;

	row_scale = 0;
	col_scale = 0;


	leftflag0 = get_leftflag(image, 100);
	leftflag1 = get_leftflag(image, 400);
	leftflag2 = get_leftflag(image, 700);

	rightflag0 = get_rightflag(image, 100);
	rightflag1 = get_rightflag(image, 400);
	rightflag2 = get_rightflag(image, 700);

	upflag0 = get_upflag(image, 100);
	upflag1 = get_upflag(image, 400);
	upflag2 = get_upflag(image, 700);

	downflag0 = get_downtflag(image, 100);
	downflag1 = get_downtflag(image, 400);
	downflag2 = get_downtflag(image, 700);


	/*cout << "left:" << leftflag0 << " " << leftflag1 << " " << leftflag2 << endl;
	cout << "right:" << rightflag0 << " " << rightflag1 << " " << rightflag2 << endl;
	cout << "up:" << upflag0 << " " << upflag1 << " " << upflag2 << endl;
	cout << "down:" << downflag0 << " " << downflag1 << " " << downflag2 << endl;*/


	left_rate = get_left_and_up_rate(leftflag0, leftflag1, leftflag2);
	right_rate = get_right_and_down_rate(rightflag0, rightflag1, rightflag2);
	up_rate = get_left_and_up_rate(upflag0, upflag1, upflag2);
	down_rate = get_right_and_down_rate(downflag0, downflag1, downflag2);

	/*cout << "left rate:" << left_rate << endl
		<< "right rate:" << right_rate << endl
		<< "up rate:" << up_rate << endl
		<< "down rate:" << down_rate << endl;*/
}

void Decode::change_pos()
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
			pos_x = 1;
			pos_y = 8;
			return;
		}
	}
}

Decode::COLORS Decode::int_to_color(int number)
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

Decode::COLORS Decode::further_judge_color(int p0_infor, int p1_infor, int p2_infor)
{
	bool is_sure[3] = { false,false,false };
	int p_infor[3] = { p0_infor,p1_infor,p2_infor };
	int p[3] = { 0,0,0 };
	int sure_count = 0;
	if (p0_infor <= 50)
	{
		p[0] = 0;
		is_sure[0] = true;
	}
	if (p0_infor >= 200)
	{
		p[0] = 1;
		is_sure[0] = true;
	}
	if (p1_infor <= 50)
	{
		p[1] = 0;
		is_sure[1] = true;
	}
	if (p1_infor >= 200)
	{
		p[1] = 1;
		is_sure[1] = true;
	}
	if (p2_infor <= 50)
	{
		p[2] = 0;
		is_sure[2] = true;
	}
	if (p2_infor >= 200)
	{
		p[2] = 1;
		is_sure[2] = true;
	}

	for (int i = 0; i < 3; i++)
	{
		if (is_sure[i])
			sure_count++;
	}
	if (true)
	{
		int max_pos, min_pos, mid_pos;
		int max_value = 0, min_value = 255, mid_value;
		for (int i = 0; i < 3; i++)
		{
			if (p_infor[i] > max_value)
			{
				max_pos = i;
				max_value = p_infor[i];
			}
		}
		for (int i = 0; i < 3; i++)
		{
			if (p_infor[i] < min_value)
			{
				min_pos = i;
				min_value = p_infor[i];
			}
		}
		mid_pos = 3 - max_pos - min_pos;
		mid_value = p_infor[mid_pos];
		if (max_value - min_value > 60)
		{
			p[max_pos] = 1;
			is_sure[max_pos] = true;
			p[min_pos] = 0;
			is_sure[min_pos] = true;
			if ((max_value - mid_value) * 2 > mid_value - min_value)
			{
				p[mid_pos] = 0;
			}
			else
			{
				p[mid_pos] = 1;
			}
			is_sure[mid_pos] = true;
		}
		else
		{
			if ((max_value + mid_value + mid_value) / 3 > 100)
			{
				for (int i = 0; i < 3; i++)
				{
					p[i] = 1;
					is_sure[i] = true;
				}
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					p[i] = 0;
					is_sure[i] = true;
				}
			}
		}
	}
	int ans = (p[0] * 2 + p[1]) * 2 + p[2];
	return int_to_color(ans);
}

Decode::COLORS Decode::get_color(Mat& image, int temp_pos_x, int temp_pos_y)
{
	int p0_infor = 0, p1_infor = 0, p2_infor = 0;


	temp_left = leftflag1 + (int)((temp_pos_x * 32 + 16 - 400.0) * left_rate);
	temp_right = rightflag1 + (int)((temp_pos_x * 32 + 16 - 400.0) * right_rate);
	if (temp_left < 0)
		temp_left = 0;
	if (temp_right > 799)
		temp_right = 799;
	col_scale = (temp_right - temp_left + 1) / 25;


	temp_up = upflag1 + (int)((temp_pos_y * 32 + 16 - 400.0) * up_rate);
	temp_down = downflag1 + (int)((temp_pos_y * 32 + 16 - 400.0) * down_rate);
	if (temp_up < 0)
		temp_up = 0;
	if (temp_down > 799)
		temp_down = 799;
	row_scale = (temp_down - temp_up + 1) / 25;

	correct_col = ((temp_right - temp_left + 1) % 25) * temp_pos_y / 25;
	correct_row = ((temp_down - temp_up + 1) % 25) * temp_pos_x / 25;

	for (int k = temp_up + temp_pos_x * row_scale + (row_scale / 2) - 2 + correct_row; k < temp_up + temp_pos_x * row_scale + (row_scale / 2) + 3 + correct_row; k++)
	{
		for (int l = temp_left + temp_pos_y * col_scale + (col_scale / 2) - 2 + correct_col; l < temp_left + temp_pos_y * col_scale + (col_scale / 2) + 3 + correct_col; l++)
		{
			uchar* p = image.ptr<uchar>(k, l);
			p0_infor += p[0]; p1_infor += p[1]; p2_infor += p[2];
			if ((p[0] <= 50 && p[1] <= 50 && p[2] >= 100) || (p[0] <= 100 && p[1] <= 100 && p[2] >= 200))
			{
				return RED;
			}
			if ((p[0] <= 50 && p[1] >= 100 && p[2] <= 50) || (p[0] <= 100 && p[1] >= 200 && p[2] <= 100))
			{
				return GREEN;
			}
			if (p[0] <= 60 && p[1] >= 190 && p[2] >= 190)
			{
				return YELLOW;
			}
			if ((p[0] >= 100 && p[1] <= 50 && p[2] <= 50) || (p[0] >= 200 && p[1] <= 100 && p[2] <= 100))
			{
				return BLUE;
			}
			if (p[0] >= 190 && p[1] <= 60 && p[2] >= 190)
			{
				return PURPLE;
			}
			if (p[0] >= 190 && p[1] >= 190 && p[2] <= 60)
			{
				return CYAN;
			}
			if (p[0] >= 190 && p[1] >= 190 && p[2] >= 190)
			{
				return WHITE;
			}
		}
	}
	//接下来是重点

	p0_infor /= 25; p1_infor /= 25; p2_infor /= 25;

	if (p0_infor <= 50 && p1_infor <= 50 && p1_infor <= 50)
	{
		return BLACK;
	}
	if ((p0_infor <= 50 && p1_infor <= 50 && p2_infor >= 100) || (p0_infor <= 100 && p1_infor <= 100 && p2_infor >= 200))
	{
		return RED;
	}
	if ((p0_infor <= 50 && p1_infor >= 100 && p2_infor <= 50) || (p0_infor <= 100 && p1_infor >= 200 && p2_infor <= 100))
	{
		return GREEN;
	}
	if (p0_infor <= 60 && p1_infor >= 190 && p2_infor >= 190)
	{
		return YELLOW;
	}
	if ((p0_infor >= 100 && p1_infor <= 50 && p2_infor <= 50) || (p0_infor >= 200 && p1_infor <= 100 && p2_infor <= 100))
	{
		return BLUE;
	}
	if (p0_infor >= 190 && p1_infor <= 60 && p2_infor >= 190)
	{
		return PURPLE;
	}
	if (p0_infor >= 190 && p1_infor >= 190 && p2_infor <= 60)
	{
		return CYAN;
	}
	if (p0_infor >= 190 && p1_infor >= 190 && p2_infor >= 190)
	{
		return WHITE;
	}


	return further_judge_color(p0_infor, p1_infor, p2_infor);


}

int Decode::color_to_int(COLORS color)
{
	switch (color)
	{
	case BLACK:
	{
		return 0;
		break;
	}
	case RED:
	{
		return 1;
		break;
	}
	case GREEN:
	{
		return 2;
		break;
	}
	case YELLOW:
	{
		return 3;
		break;
	}
	case BLUE:
	{
		return 4;
		break;
	}
	case PURPLE:
	{
		return 5;
		break;
	}
	case CYAN:
	{
		return 6;
		break;
	}
	case WHITE:
	{
		return 7;
		break;
	}
	default:
	{
		cout << "传入了不知道什么颜色" << endl;
	}
	}
}

string Decode::ascii_to_binary(int c)
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

bool Decode::read_and_write_information(Mat& image)
{
	bool is_new_start = false;
	COLORS c0, c1, c2;
	c0 = get_color(image, pos_x, pos_y);
	c1 = get_color(image, pos_x, pos_y + 1);
	c2 = get_color(image, pos_x, pos_y + 2);

	int n0, n1, n2;
	n0 = color_to_int(c0);
	n1 = color_to_int(c1);
	n2 = color_to_int(c2);

	int infor_with_correct = ((n0 * 8 + n1) * 8) + n2;
	int infor_without_correct = infor_with_correct / 2;
	string binary_string = ascii_to_binary(infor_with_correct);

	int temp_count = 0;
	for (int i = 0; i < binary_string.length(); i++)
	{
		if (binary_string[i] == '1')
			temp_count++;
	}
	if (temp_count % 2 == 0)
	{
		cout << (char)infor_without_correct;
		if (!is_start && infor_without_correct >= 255)
		{
			is_start = true;
			is_new_start = true;
		}
		if (infor_without_correct <= 0 && is_start)
		{
			is_end = true;
		}
		if (!is_end && !is_new_start)
			buffer[buffer_index++] = (char)infor_without_correct;
		return true;
	}
	else
	{
		cout << "【校验出错了:" << (char)infor_without_correct << "】" << "x=" << pos_x << ",y=" << pos_y << endl;
		is_good = false;
		return false;
	}
}


void Decode::write_into_txt_file()
{
	ofstream out_file(out_file_path_and_name, ios::app);
	if (!out_file)
	{
		cout << "输出文件错了" << endl;
		exit(0);
	}
	out_file << noskipws;
	for (int i = 0; i < buffer_index; i++)
	{
		out_file << buffer[i];
	}
	out_file.close();
}


void Decode::decode()
{
	Mat image;
	//draw_dingweidian(image);
	//imshow("画出动态定位点", image);

	clock_t startTime, endTime;
	startTime = clock();

	for (int i = 0; ; i++)
	{
		image_path_and_name = image_path + proj_name + to_string(i) + ".jpg";
		image = imread(image_path_and_name);
		if (!image.data)
		{
			cout << "没读到终止位就异常终止" << endl;
			return;
		}
		initiate_image(image);
		pos_x = 1; pos_y = 8;
		int image_index = 0;
		for (int i = 9; i <= 15; i++)
		{
			image_index = image_index * 8 + 7 - color_to_int(get_color(image, i, 7));
		}
		cout << "图片编号为:" << image_index << endl;
		if (image_index != now_image)
		{
			cout << "图片" << image_path_and_name << "不符合图片编号条件，跳过" << endl;
			continue;
		}

		if (image_index % 2 == 0)
		{
			if (get_color(image, 9, 17) == RED && get_color(image, 15, 17) == WHITE)
			{
				cout << "图片奇偶校验正确" << endl;
			}
			else
			{
				cout << "图片奇偶校验错误,跳过" << endl;
				continue;
			}
		}
		else
		{
			if (get_color(image, 9, 17) == WHITE && get_color(image, 15, 17) == BLUE)
			{
				cout << "图片奇偶校验正确" << endl;
			}
			else
			{
				cout << "图片奇偶校验错误，跳过" << endl;
				continue;
			}
		}

		//cout << "information is:" << endl;

		int index = 0;
		is_good = true;
		buffer_index = 0;
		for (index = 0; index < 119; index++)
		{
			if (!read_and_write_information(image) || is_end)
			{
				break;
			}
			//cout << "执行flag" <<"x="<<pos_x<<",y="<<pos_y<< endl<<endl;
			change_pos();
		}

		if (is_start && is_good && !is_end)
		{
			write_into_txt_file();
			now_image++;
			continue;
		}
		if (!is_good)
		{
			cout << "丢弃当前图片" << image_path_and_name << endl;
			continue;
		}
		if (is_end)
		{
			write_into_txt_file();
			cout << "读到终止符号，解码结束" << endl;
			break;
		}
	}

	endTime = clock();
	double time_pass = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "The run time is: " << time_pass << "s" << endl;
	cout << "传输速度" << 881.0 / time_pass << "Bps," << 881.0 * 8 / time_pass << "bps" << endl;
}


void Decode::set_out_file_path_and_name(string str)
{
	out_file_path_and_name = str;
}