#pragma warning(disable:4996)  //启用此宏，允许使用ctime

//加载头文件
#include<iostream>
#include<fstream>
#include<istream>
#include<streambuf>
#include<sstream>
#include<vector>
#include<string>
#include<stdlib.h>
#include<algorithm>
#include <cstdlib>
#include <ctime>
#include<stdlib.h>
//列出用到的函数
void danxuan();
void danxuan(int number);
void duoxuan();
void duoxuan(int number);
int fanwei(int largest);
void suiji();
void tiaozhuan();
void errorbook(std::vector<std::string> fields, int num);
bool icasecompare(std::string& str1, std::string& str2);
bool isLouxuan(std::string str1, std::string str2);
//main
int main() {

	int modulechoose = -1;//用于后续模式选择的判断

	std::cout << "这是一个马原练习的小程序。\n-------------------------------------------------------------------------------" << std::endl;

	while(modulechoose != 0){
		std::cout<<"单选顺序练习请输入1；\n多选顺序练习请输入2，\n随机练习请输入3，\n跳转指定习题请输入4：\n输入0以终止程序 \nVersion:1.2" << std::endl;
		std::cin >> modulechoose;
		if (modulechoose == 1) {
			std::cout << "下面为单选题练习。输入exit以提前退出。" << std::endl;
			danxuan();
		}
		else if (modulechoose == 2) {
			std::cout << "下面为多选题练习。输入exit以提前退出。" << std::endl;
			duoxuan();
		}
		else if (modulechoose == 3) {
			std::cout << "下面为随机练习。输入exit以提前退出。\n每次随机练习题量为50题。\n加载速度可能较慢，请耐心等待！ " << std::endl;
			suiji();
		}
		else if (modulechoose == 0) {
			std::cout << "--程序结束--" << std::endl;
		}
		else if (modulechoose == 4) {
			std::cout << "下面为跳转指定习题练习。输入exit以提前退出。" << std::endl;
			tiaozhuan();
		}
		else {
			std::cout << "错误！请重新输入！ \n" << std::endl;
		}
	}
	system("pause");
	return 0;
}

void danxuan() {
	std::ifstream data("1.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//用于显示题目数
	int wrongnum = 0;//用于记录用户做错的题数
	int exitnum = 0;//用于用户退出程序
	if (!data.is_open()) {//判断文件是否能够打开
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
		std::vector<std::string> fields;//声明一个字符串向量
		std::string field, userchoice;
		int judgeTF = 1;//用于判断用户输入答案对错

		int wrongtime = 0;//用于判断用户做错同一题的次数
		while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			//第三个是字符！！！不是字符串！
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF) {
			std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
				<< num << "."
				<< fields[1] << "\n"
				<< "A." << fields[2] << "\n"
				<< "B." << fields[3] << "\n"
				<< "C." << fields[4] << "\n"
				<< "D." << fields[5] << "\n";
			std::cin >> userchoice;
			std::string qstr = "q";
			std::string exitstr = "exit";
			if (icasecompare(userchoice, exitstr)) {
				exitnum = 1;
				wrongtime++;//此处错误次数增加表明此题算是错了，但实际上此处wrongtime增加无实际意义，因为即将exit了
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "答案为：\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				std::cout << "答案错误！想要查看答案请输入q " << std::endl;
				wrongtime++;

				if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
					//写入错题集
					errorbook(fields, num);
					wrongnum++;
				}
			}
		}
		num++;
		std::cout << std::endl;
		if (exitnum == 1)
			break;
	}
	data.close();//关闭文件
	num--;
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "练习结束。本次练习一共" << num << "道题，\n做对" << right << "题， 做错" << wrongnum << "题。\n正确率为: "
		<< percentage << "%。\n错题已保存在wrongbook.txt " << std::endl;
}
// overload danxuan()
void danxuan(int number) {
	std::ifstream data("1.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//用于显示题目数
	int wrongnum = 0;//用于记录用户做错的题数
	int exitnum = 0;//用于用户退出程序
	int judgeNum = 0;//用于判断题号是否符合
	if (!data.is_open()) {//判断文件是否能够打开
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
		std::vector<std::string> fields;//声明一个字符串向量
		std::string field, userchoice;
		int judgeTF = 1;//用于判断用户输入答案对错
		int wrongtime = 0;//用于判断用户做错同一题的次数
		if (num == number)//题号符合，judgeNum=1，用于后续一直循环出题
			judgeNum = 1;
		while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			//第三个是字符！！！不是字符串！
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF&&judgeNum) {
			std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
				<< num << "."
				<< fields[1] << "\n"
				<< "A." << fields[2] << "\n"
				<< "B." << fields[3] << "\n"
				<< "C." << fields[4] << "\n"
				<< "D." << fields[5] << "\n";
			std::cin >> userchoice;
			std::string qstr = "q";
			std::string exitstr = "exit";
			if (icasecompare(userchoice, exitstr)) {
				exitnum = 1;
				wrongtime++;//此处错误次数增加表明此题算是错了，但实际上此处wrongtime增加无实际意义，因为即将exit了
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "答案为：\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				std::cout << "答案错误！想要查看答案请输入q " << std::endl;
				wrongtime++;

				if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
					//写入错题集
					errorbook(fields, num);
					wrongnum++;
				}
			}
		}
		num++;
		//std::cout << std::endl;
		if (exitnum == 1)
			break;
	}
	data.close();
	num--;
	num = num - number + 1;//将num从原本的总题数变为减去前面未做的题后实际所做的题目数
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "练习结束。本次练习一共" << num << "道题，\n做对" << right << "题， 做错" << wrongnum << "题。\n正确率为: "
		<< percentage << "%。\n错题已保存在wrongbook.txt " << std::endl;
}
void duoxuan() {
	std::ifstream data("2.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//用于显示题目数
	int wrongnum = 0;//用于记录用户做错的题数
	int exitnum = 0;//用于用户退出程序
	if (!data.is_open()) {//判断文件是否能够打开
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
		std::vector<std::string> fields;//声明一个字符串向量
		std::string field, userchoice;
		int judgeTF = 1;//用于判断用户输入答案对错

		int wrongtime = 0;//用于判断用户做错同一题的次数
		while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			//第三个是字符！！！不是字符串！
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF) {
			std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
				<< "[多选]" << num << "."
				<< fields[1] << "\n"
				<< "A." << fields[2] << "\n"
				<< "B." << fields[3] << "\n"
				<< "C." << fields[4] << "\n"
				<< "D." << fields[5] << "\n";
			std::cin >> userchoice;
			std::string qstr = "q";
			std::string exitstr = "exit";
			if (icasecompare(userchoice, exitstr)) {
				exitnum = 1;
				wrongtime++;
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "答案为：\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				if (isLouxuan(userchoice, fields[6]))
					std::cout << "答案漏选！想要查看答案请输入q " << std::endl;
				else
					std::cout << "答案错误！想要查看答案请输入q " << std::endl;
				wrongtime++;
				if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
					//写入错题集
					errorbook(fields, num);
					wrongnum++;
				}
			}
		}

		num++;
		std::cout << std::endl;
		if (exitnum == 1)
			break;
	}
	data.close();
	num--;
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "练习结束。本次练习一共" << num << "道题，\n做对" << right << "题， 做错" << wrongnum << "题。\n正确率为: "
		<< percentage << "%。\n错题已保存在wrongbook.txt " << std::endl;
}

void duoxuan(int number) {
	std::ifstream data("2.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//用于显示题目数
	int wrongnum = 0;//用于记录用户做错的题数
	int exitnum = 0;//用于用户退出程序
	int judgeNum = 0;//用于判断题号是否符合
	if (!data.is_open()) {//判断文件是否能够打开
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
		std::vector<std::string> fields;//声明一个字符串向量
		std::string field, userchoice;
		int judgeTF = 1;//用于判断用户输入答案对错
		int wrongtime = 0;//用于判断用户做错同一题的次数
		if (num == number)//题号符合，judgeNum=1，用于后续一直循环出题
			judgeNum = 1;
		while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
			//第三个是字符！！！不是字符串！
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF&&judgeNum) {
			std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
				<< "[多选]" << num << "."
				<< fields[1] << "\n"
				<< "A." << fields[2] << "\n"
				<< "B." << fields[3] << "\n"
				<< "C." << fields[4] << "\n"
				<< "D." << fields[5] << "\n";
			std::cin >> userchoice;
			std::string qstr = "q";
			std::string exitstr = "exit";
			if (icasecompare(userchoice, exitstr)) {
				exitnum = 1;
				wrongtime++;
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "答案为：\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				if (isLouxuan(userchoice, fields[6]))
					std::cout << "答案漏选！想要查看答案请输入q " << std::endl;
				else
					std::cout << "答案错误！想要查看答案请输入q " << std::endl;
				wrongtime++;
				if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
					//写入错题集
					errorbook(fields, num);
					wrongnum++;
				}
			}
		}

		num++;
		//std::cout << std::endl;
		if (exitnum == 1)
			break;
	}
	data.close();
	num--;
	num = num - number + 1;//将num从原本的总题数变为减去前面未做的题后实际所做的题目数
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "练习结束。本次练习一共" << num << "道题，\n做对" << right << "题， 做错" << wrongnum << "题。\n正确率为: "
		<< percentage << "%。\n错题已保存在wrongbook.txt " << std::endl;
}

void suiji() {
	srand(time(nullptr));//根据系统时钟，产生不同的随机数种子。
	int a = 1;//第一题
	int b = 601;//最后一题
	int c = 400;//单选最后一题
	int wrongnum = 0;//用于记录用户做错的题数
	int exitnum = 0;//用于用户退出程序
	int yizuonum = 0;//用户已做题目数
	for (int i = 0; i < 50; i++) {
		yizuonum++;
		int count = rand() % (b - a + 1) + a;//题号(随机生成)
		std::cout << count << std::endl;
		if (count > c && count <= b) {
			std::ifstream data("2.csv", std::ios::in);
			std::string line;
			std::getline(data, line);
			int num = 1;//用于显示题目数

			if (!data.is_open()) {//判断文件是否能够打开
				std::cout << "Error: opening file fail" << std::endl;
				std::exit(1);
			}

			while (std::getline(data, line)) {
				std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
				std::vector<std::string> fields;//声明一个字符串向量
				std::string field, userchoice;
				int judgeTF = 1;//用于判断用户输入答案对错

				int wrongtime = 0;//用于判断用户做错同一题的次数
				while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
					//第三个是字符！！！不是字符串！
				{
					fields.push_back(field);

					// std::cout << atol(field.c_str());
				}
				while (judgeTF && (num + c == count)) {
					std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
						<< "[多选]" << num << "."
						<< fields[1] << "\n"
						<< "A." << fields[2] << "\n"
						<< "B." << fields[3] << "\n"
						<< "C." << fields[4] << "\n"
						<< "D." << fields[5] << "\n";
					std::cin >> userchoice;
					std::string qstr = "q";
					std::string exitstr = "exit";
					if (icasecompare(userchoice, exitstr)) {
						exitnum = 1;
						wrongtime++;
						if (wrongtime <= 1)
							wrongnum++;
						break;
					}
					if (icasecompare(userchoice, qstr)) {
						std::cout << "答案为：\t" << fields[6] << std::endl;
						wrongtime++;
						continue;
					}
					if (icasecompare(userchoice, fields[6])) {
						judgeTF = 0;
					}
					else {
						if (isLouxuan(userchoice, fields[6]))
							std::cout << "答案漏选！想要查看答案请输入q " << std::endl;
						else
							std::cout << "答案错误！想要查看答案请输入q " << std::endl;
						wrongtime++;
						if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
							//写入错题集
							errorbook(fields, num);
							wrongnum++;
						}
					}

				}
				num++;
				//std::cout << std::endl;
				if (exitnum == 1)
					break;

			}
			data.close();
			if (exitnum == 1)
				break;

			
		}
		else if (count >= a && count <= c) {
			std::ifstream data("1.csv", std::ios::in);
			std::string line;
			std::getline(data, line);
			int num = 1;//用于显示题目数

			if (!data.is_open()) {//判断文件是否能够打开
				std::cout << "Error: opening file fail" << std::endl;
				std::exit(1);
			}

			while (std::getline(data, line)) {
				std::istringstream sin(line);//将整行字符串line读入到字符串流istringstream中
				std::vector<std::string> fields;//声明一个字符串向量
				std::string field, userchoice;
				int judgeTF = 1;//用于判断用户输入答案对错

				int wrongtime = 0;//用于判断用户做错同一题的次数
				while (std::getline(sin, field, ','))//将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
					//第三个是字符！！！不是字符串！
				{
					fields.push_back(field);

					// std::cout << atol(field.c_str());
				}
				while (judgeTF && (num== count)) {
					std::cout << "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
						<< num << "."
						<< fields[1] << "\n"
						<< "A." << fields[2] << "\n"
						<< "B." << fields[3] << "\n"
						<< "C." << fields[4] << "\n"
						<< "D." << fields[5] << "\n";
					std::cin >> userchoice;
					std::string qstr = "q";
					std::string exitstr = "exit";
					if (icasecompare(userchoice, exitstr)) {
						exitnum = 1;
						wrongtime++;
						if (wrongtime <= 1)
							wrongnum++;
						break;
					}
					if (icasecompare(userchoice, qstr)) {
						std::cout << "答案为：\t" << fields[6] << std::endl;
						wrongtime++;
						continue;
					}
					if (icasecompare(userchoice, fields[6])) {
						judgeTF = 0;
					}
					else {
						std::cout << "答案错误！想要查看答案请输入q " << std::endl;
						wrongtime++;

						if (wrongtime <= 1) {//同一题不论错多少次，只算错了一道题
							//写入错题集
							errorbook(fields, num);
							wrongnum++;
						}
					}

				}
				num++;
				//std::cout << std::endl;
				if (exitnum == 1)
					break;

			}
			data.close();
			if (exitnum == 1)
				break;


		
		}
		else {
			std::cout << "Error! The number is not available! " << std::endl;
		}

	}
	int right = yizuonum - wrongnum;
	float percentage = 100.00 * right / yizuonum;
	std::cout << "练习结束。本次练习一共" << yizuonum << "道题，\n做对" << right << "题， 做错" << wrongnum << "题。\n正确率为: "
		<< percentage << "%。\n错题已保存在wrongbook.txt " << std::endl;




}

void tiaozhuan() {
	std::string module;
	std::string danxuanstr="A";
	std::string duoxuanstr="B";
	std::string exitstr = "exit";
	int judge = 1;
	int tiaonum;
	while (judge)
	{
		std::cout << "请输入模式：（输入对应字母）\nA.\t单选题；\nB.\t多选。 " << std::endl;
		std::cin >> module;
		if (icasecompare(module, danxuanstr)) {
			judge = 0;
			tiaonum = fanwei(400);
			if (tiaonum == -1) {
				std::cout << "Error! \nThe number should not exist! (-1)" << std::endl;
				exit(0);
			}
			else {
				std::cout << "正在加载中……" << std::endl;
				danxuan(tiaonum);
			}

		}
		else if (icasecompare(module, duoxuanstr)) {
			judge = 0;
			tiaonum = fanwei(201);
			if (tiaonum == -1) {
				std::cout << "Error! \nThe number should not exist! (-1)" << std::endl;
				exit(0);
			}
			else {
				std::cout << "正在加载中……" << std::endl;
				duoxuan(tiaonum);
			}
		}
		else if (icasecompare(module, exitstr)) {
			judge = 0;
		}
		else {
			std::cout << "输入不合法！请重试！ " << std::endl;
		}

	}

}
int fanwei(int largest) {
	int judge = 1;
	int tiaonum=0;
	while (judge) {
		std::cout << "题目范围为： 1 - " << largest << " 。请输入范围内的一个数： " << std::endl;
		std::cin >> tiaonum;
		if (tiaonum >= 1 && tiaonum <= largest) {
			judge = 0;
			return tiaonum;
		}
		else {
			std::cout << "请输入范围内的数字！ " << std::endl;
		}
	}
	return -1;//返回报错信息
}

void errorbook(std::vector<std::string> fields, int num) {
	std::ofstream ofs;
	ofs.open("errorbook.txt", std::ios::out | std::ios::app);//打开errorbook.txt，如果没有就创建，以追加写的形式写入错题
	time_t curtime;
	time(&curtime);
	ofs << ctime(&curtime)  << "-----------------------------------------"<<"\n"
		<< "题目章节：\t" << fields[0] << "\t" << "难度： \t" << fields[7] << "\n"
		<< num << "."
		<< fields[1] << "\n"
		<< "A." << fields[2] << "\n"
		<< "B." << fields[3] << "\n"
		<< "C." << fields[4] << "\n"
		<< "D." << fields[5] << "\n"
		<< "答案为： " << fields[6] << std::endl;

}

bool icasecompare(std::string& str1, std::string& str2) {
	//忽略大小写比较答案是否相等，相等返回1，不等返回0
	//拷贝临时对象，算法在临时对象上做修改
	std::string str1Cpy(str1);
	std::string str2Cpy(str2);
	std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
	std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
	return (str1Cpy == str2Cpy);

}
bool isLouxuan(std::string str1, std::string str2) {
	if (str1.length() >= str2.length()) {
		//若用户答案长度大于等于正确答案长度，那么用户一定是错选
		return false;
	}
	else {
		std::string str1Cpy(str1);
		std::string str2Cpy(str2);
		std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
		std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
		int judge = 0;
		for (int i = 0; i < str1Cpy.length(); i++) {
			//此处情况较少，可以直接暴力法，情况过多需要KMP
			for (int j = 0; j < str2Cpy.length(); j++) {
				if (str1Cpy[i] == str2Cpy[j]) {
					judge = 1;
				}
			}
			if (judge == 0)
				return false;
		}
		return true;
	}
}
