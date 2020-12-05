#pragma once
#include "Process.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>

#define Kvant_const 2

class RR_SJF
{
private:
	vector<Process> v;
public:
	void start();
	void from_file();
	void from_hand();
	void print();
	bool fin();
	void ChangeTOS();
	void print_logs();

	RR_SJF() 
	{
		int n = 1;
		do
		{
			system("cls");
			if (n <= 0 || n >= 3) cout << "Введите корректное значение";
			cout << "\tВыберите способ ввода процессов\n\n\t1-c клавиатуры\t2-из файла\n";
			cin >> n;
		} while (n <= 0 || n >= 3);
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
};