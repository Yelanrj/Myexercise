#pragma warning(disable:4996)  //���ô˺꣬����ʹ��ctime

//����ͷ�ļ�
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
//�г��õ��ĺ���
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

	int modulechoose = -1;//���ں���ģʽѡ����ж�

	std::cout << "����һ����ԭ��ϰ��С����\n-------------------------------------------------------------------------------" << std::endl;

	while(modulechoose != 0){
		std::cout<<"��ѡ˳����ϰ������1��\n��ѡ˳����ϰ������2��\n�����ϰ������3��\n��תָ��ϰ��������4��\n����0����ֹ���� \nVersion:1.2" << std::endl;
		std::cin >> modulechoose;
		if (modulechoose == 1) {
			std::cout << "����Ϊ��ѡ����ϰ������exit����ǰ�˳���" << std::endl;
			danxuan();
		}
		else if (modulechoose == 2) {
			std::cout << "����Ϊ��ѡ����ϰ������exit����ǰ�˳���" << std::endl;
			duoxuan();
		}
		else if (modulechoose == 3) {
			std::cout << "����Ϊ�����ϰ������exit����ǰ�˳���\nÿ�������ϰ����Ϊ50�⡣\n�����ٶȿ��ܽ����������ĵȴ��� " << std::endl;
			suiji();
		}
		else if (modulechoose == 0) {
			std::cout << "--�������--" << std::endl;
		}
		else if (modulechoose == 4) {
			std::cout << "����Ϊ��תָ��ϰ����ϰ������exit����ǰ�˳���" << std::endl;
			tiaozhuan();
		}
		else {
			std::cout << "�������������룡 \n" << std::endl;
		}
	}
	system("pause");
	return 0;
}

void danxuan() {
	std::ifstream data("1.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//������ʾ��Ŀ��
	int wrongnum = 0;//���ڼ�¼�û����������
	int exitnum = 0;//�����û��˳�����
	if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
		std::vector<std::string> fields;//����һ���ַ�������
		std::string field, userchoice;
		int judgeTF = 1;//�����ж��û�����𰸶Դ�

		int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
		while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			//���������ַ������������ַ�����
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF) {
			std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
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
				wrongtime++;//�˴�����������ӱ����������Ǵ��ˣ���ʵ���ϴ˴�wrongtime������ʵ�����壬��Ϊ����exit��
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "��Ϊ��\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
				wrongtime++;

				if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
					//д����⼯
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
	data.close();//�ر��ļ�
	num--;
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "��ϰ������������ϰһ��" << num << "���⣬\n����" << right << "�⣬ ����" << wrongnum << "�⡣\n��ȷ��Ϊ: "
		<< percentage << "%��\n�����ѱ�����wrongbook.txt " << std::endl;
}
// overload danxuan()
void danxuan(int number) {
	std::ifstream data("1.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//������ʾ��Ŀ��
	int wrongnum = 0;//���ڼ�¼�û����������
	int exitnum = 0;//�����û��˳�����
	int judgeNum = 0;//�����ж�����Ƿ����
	if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
		std::vector<std::string> fields;//����һ���ַ�������
		std::string field, userchoice;
		int judgeTF = 1;//�����ж��û�����𰸶Դ�
		int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
		if (num == number)//��ŷ��ϣ�judgeNum=1�����ں���һֱѭ������
			judgeNum = 1;
		while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			//���������ַ������������ַ�����
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF&&judgeNum) {
			std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
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
				wrongtime++;//�˴�����������ӱ����������Ǵ��ˣ���ʵ���ϴ˴�wrongtime������ʵ�����壬��Ϊ����exit��
				if (wrongtime <= 1)
					wrongnum++;
				break;
			}
			if (icasecompare(userchoice, qstr)) {
				std::cout << "��Ϊ��\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
				wrongtime++;

				if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
					//д����⼯
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
	num = num - number + 1;//��num��ԭ������������Ϊ��ȥǰ��δ�������ʵ����������Ŀ��
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "��ϰ������������ϰһ��" << num << "���⣬\n����" << right << "�⣬ ����" << wrongnum << "�⡣\n��ȷ��Ϊ: "
		<< percentage << "%��\n�����ѱ�����wrongbook.txt " << std::endl;
}
void duoxuan() {
	std::ifstream data("2.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//������ʾ��Ŀ��
	int wrongnum = 0;//���ڼ�¼�û����������
	int exitnum = 0;//�����û��˳�����
	if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
		std::vector<std::string> fields;//����һ���ַ�������
		std::string field, userchoice;
		int judgeTF = 1;//�����ж��û�����𰸶Դ�

		int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
		while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			//���������ַ������������ַ�����
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF) {
			std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
				<< "[��ѡ]" << num << "."
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
				std::cout << "��Ϊ��\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				if (isLouxuan(userchoice, fields[6]))
					std::cout << "��©ѡ����Ҫ�鿴��������q " << std::endl;
				else
					std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
				wrongtime++;
				if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
					//д����⼯
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
	std::cout << "��ϰ������������ϰһ��" << num << "���⣬\n����" << right << "�⣬ ����" << wrongnum << "�⡣\n��ȷ��Ϊ: "
		<< percentage << "%��\n�����ѱ�����wrongbook.txt " << std::endl;
}

void duoxuan(int number) {
	std::ifstream data("2.csv", std::ios::in);
	std::string line;
	std::getline(data, line);
	int num = 1;//������ʾ��Ŀ��
	int wrongnum = 0;//���ڼ�¼�û����������
	int exitnum = 0;//�����û��˳�����
	int judgeNum = 0;//�����ж�����Ƿ����
	if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
		std::cout << "Error: opening file fail" << std::endl;
		std::exit(1);
	}

	//std::cout << "Success!" << std::endl;		test1
	while (std::getline(data, line)) {
		std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
		std::vector<std::string> fields;//����һ���ַ�������
		std::string field, userchoice;
		int judgeTF = 1;//�����ж��û�����𰸶Դ�
		int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
		if (num == number)//��ŷ��ϣ�judgeNum=1�����ں���һֱѭ������
			judgeNum = 1;
		while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
			//���������ַ������������ַ�����
		{
			fields.push_back(field);

			// std::cout << atol(field.c_str());
		}
		while (judgeTF&&judgeNum) {
			std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
				<< "[��ѡ]" << num << "."
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
				std::cout << "��Ϊ��\t" << fields[6] << std::endl;
				wrongtime++;
				continue;
			}
			if (icasecompare(userchoice, fields[6])) {
				judgeTF = 0;
			}
			else {
				if (isLouxuan(userchoice, fields[6]))
					std::cout << "��©ѡ����Ҫ�鿴��������q " << std::endl;
				else
					std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
				wrongtime++;
				if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
					//д����⼯
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
	num = num - number + 1;//��num��ԭ������������Ϊ��ȥǰ��δ�������ʵ����������Ŀ��
	int right = num - wrongnum;
	float percentage = 100.00 * right / num;
	std::cout << "��ϰ������������ϰһ��" << num << "���⣬\n����" << right << "�⣬ ����" << wrongnum << "�⡣\n��ȷ��Ϊ: "
		<< percentage << "%��\n�����ѱ�����wrongbook.txt " << std::endl;
}

void suiji() {
	srand(time(nullptr));//����ϵͳʱ�ӣ�������ͬ����������ӡ�
	int a = 1;//��һ��
	int b = 601;//���һ��
	int c = 400;//��ѡ���һ��
	int wrongnum = 0;//���ڼ�¼�û����������
	int exitnum = 0;//�����û��˳�����
	int yizuonum = 0;//�û�������Ŀ��
	for (int i = 0; i < 50; i++) {
		yizuonum++;
		int count = rand() % (b - a + 1) + a;//���(�������)
		std::cout << count << std::endl;
		if (count > c && count <= b) {
			std::ifstream data("2.csv", std::ios::in);
			std::string line;
			std::getline(data, line);
			int num = 1;//������ʾ��Ŀ��

			if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
				std::cout << "Error: opening file fail" << std::endl;
				std::exit(1);
			}

			while (std::getline(data, line)) {
				std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
				std::vector<std::string> fields;//����һ���ַ�������
				std::string field, userchoice;
				int judgeTF = 1;//�����ж��û�����𰸶Դ�

				int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
				while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
					//���������ַ������������ַ�����
				{
					fields.push_back(field);

					// std::cout << atol(field.c_str());
				}
				while (judgeTF && (num + c == count)) {
					std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
						<< "[��ѡ]" << num << "."
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
						std::cout << "��Ϊ��\t" << fields[6] << std::endl;
						wrongtime++;
						continue;
					}
					if (icasecompare(userchoice, fields[6])) {
						judgeTF = 0;
					}
					else {
						if (isLouxuan(userchoice, fields[6]))
							std::cout << "��©ѡ����Ҫ�鿴��������q " << std::endl;
						else
							std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
						wrongtime++;
						if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
							//д����⼯
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
			int num = 1;//������ʾ��Ŀ��

			if (!data.is_open()) {//�ж��ļ��Ƿ��ܹ���
				std::cout << "Error: opening file fail" << std::endl;
				std::exit(1);
			}

			while (std::getline(data, line)) {
				std::istringstream sin(line);//�������ַ���line���뵽�ַ�����istringstream��
				std::vector<std::string> fields;//����һ���ַ�������
				std::string field, userchoice;
				int judgeTF = 1;//�����ж��û�����𰸶Դ�

				int wrongtime = 0;//�����ж��û�����ͬһ��Ĵ���
				while (std::getline(sin, field, ','))//���ַ�����sin�е��ַ����뵽field�ַ����У��Զ���Ϊ�ָ���
					//���������ַ������������ַ�����
				{
					fields.push_back(field);

					// std::cout << atol(field.c_str());
				}
				while (judgeTF && (num== count)) {
					std::cout << "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
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
						std::cout << "��Ϊ��\t" << fields[6] << std::endl;
						wrongtime++;
						continue;
					}
					if (icasecompare(userchoice, fields[6])) {
						judgeTF = 0;
					}
					else {
						std::cout << "�𰸴�����Ҫ�鿴��������q " << std::endl;
						wrongtime++;

						if (wrongtime <= 1) {//ͬһ�ⲻ�۴���ٴΣ�ֻ�����һ����
							//д����⼯
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
	std::cout << "��ϰ������������ϰһ��" << yizuonum << "���⣬\n����" << right << "�⣬ ����" << wrongnum << "�⡣\n��ȷ��Ϊ: "
		<< percentage << "%��\n�����ѱ�����wrongbook.txt " << std::endl;




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
		std::cout << "������ģʽ���������Ӧ��ĸ��\nA.\t��ѡ�⣻\nB.\t��ѡ�� " << std::endl;
		std::cin >> module;
		if (icasecompare(module, danxuanstr)) {
			judge = 0;
			tiaonum = fanwei(400);
			if (tiaonum == -1) {
				std::cout << "Error! \nThe number should not exist! (-1)" << std::endl;
				exit(0);
			}
			else {
				std::cout << "���ڼ����С���" << std::endl;
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
				std::cout << "���ڼ����С���" << std::endl;
				duoxuan(tiaonum);
			}
		}
		else if (icasecompare(module, exitstr)) {
			judge = 0;
		}
		else {
			std::cout << "���벻�Ϸ��������ԣ� " << std::endl;
		}

	}

}
int fanwei(int largest) {
	int judge = 1;
	int tiaonum=0;
	while (judge) {
		std::cout << "��Ŀ��ΧΪ�� 1 - " << largest << " �������뷶Χ�ڵ�һ������ " << std::endl;
		std::cin >> tiaonum;
		if (tiaonum >= 1 && tiaonum <= largest) {
			judge = 0;
			return tiaonum;
		}
		else {
			std::cout << "�����뷶Χ�ڵ����֣� " << std::endl;
		}
	}
	return -1;//���ر�����Ϣ
}

void errorbook(std::vector<std::string> fields, int num) {
	std::ofstream ofs;
	ofs.open("errorbook.txt", std::ios::out | std::ios::app);//��errorbook.txt�����û�оʹ�������׷��д����ʽд�����
	time_t curtime;
	time(&curtime);
	ofs << ctime(&curtime)  << "-----------------------------------------"<<"\n"
		<< "��Ŀ�½ڣ�\t" << fields[0] << "\t" << "�Ѷȣ� \t" << fields[7] << "\n"
		<< num << "."
		<< fields[1] << "\n"
		<< "A." << fields[2] << "\n"
		<< "B." << fields[3] << "\n"
		<< "C." << fields[4] << "\n"
		<< "D." << fields[5] << "\n"
		<< "��Ϊ�� " << fields[6] << std::endl;

}

bool icasecompare(std::string& str1, std::string& str2) {
	//���Դ�Сд�Ƚϴ��Ƿ���ȣ���ȷ���1�����ȷ���0
	//������ʱ�����㷨����ʱ���������޸�
	std::string str1Cpy(str1);
	std::string str2Cpy(str2);
	std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
	std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
	return (str1Cpy == str2Cpy);

}
bool isLouxuan(std::string str1, std::string str2) {
	if (str1.length() >= str2.length()) {
		//���û��𰸳��ȴ��ڵ�����ȷ�𰸳��ȣ���ô�û�һ���Ǵ�ѡ
		return false;
	}
	else {
		std::string str1Cpy(str1);
		std::string str2Cpy(str2);
		std::transform(str1Cpy.begin(), str1Cpy.end(), str1Cpy.begin(), ::tolower);
		std::transform(str2Cpy.begin(), str2Cpy.end(), str2Cpy.begin(), ::tolower);
		int judge = 0;
		for (int i = 0; i < str1Cpy.length(); i++) {
			//�˴�������٣�����ֱ�ӱ����������������ҪKMP
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
