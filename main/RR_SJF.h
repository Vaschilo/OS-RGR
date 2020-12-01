#pragma once
#include "Process.h"
#include <vector>
#include <functional>
#include <fstream>

class RR_SJF
{
private:
	vector<Process> v;
public:
	RR_SJF() 
	{
		int n = 1;
		while (1)
		{
			system("cls");
			if (n <= 0 || n >= 3) cout << "������� ���������� ��������";
			else break;
			cout << "\t�������� ������ ����� ���������\n\n\t1-c ����������\t2-�� �����\n";
			cin >> n;
		}
		switch (n)
		{
		case 1:
			this->from_hand();
			break;
		case 2:
			this->from_file();
			break;
		}
		this->start();
	}
	~RR_SJF() {}

	void from_file()
	{
		fstream f;
		Process pr;
		function<string(fstream& f)> GetFilename = [](fstream& f){
			string filename;
			system("cls");
			cout << "������� ��� �����\n";
			while (1) 
			{
				cin >> filename;
				f.open(filename);
				if (!f.is_open()) { system("cls"); cout << "������� ��� ������������� �����\n"; }
				else return filename;
			}
		};
		f.open(GetFilename(f));
		if (!f.is_open()) return;
		while (!f.eof())
		{
			f >> pr;
			this->v.push_back(pr);
		}
		f.close();
	}

	void from_hand()
	{
		int power = 1;
		string name = "Std_name";

		function<int(string)> f = [](string a)
		{
			int n = 1;
			do
			{
				if (n <= 0) cout << "������� �������� ������ 0";
				cout << "\n" << a << "\n";
				cin >> n;
			} while (n <= 0);
			return n;
		};

		int n = f("������� ����� ���������");

		for (int i = 0; i < n; i++)
			this->v.push_back(Process());
	}

	void start()
	{

	}
};