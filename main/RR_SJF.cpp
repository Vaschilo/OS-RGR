#include "RR_SJF.h"

RR_SJF::RR_SJF()
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
	this->preparation();
	this->start();
	this->specifications();
}
void RR_SJF::from_file()
{
	fstream f;
	Process pr;
	function<string(fstream& f)> GetFilename = [](fstream& f) {
		string filename;
		system("cls");
		cout << "Введите имя файла\n";
		while (1)
		{
			cin >> filename;
			f.open(filename);
			if (!f.is_open()) { system("cls"); cout << "Введите имя существующего файла\n"; }
			else
			{
				f.close();
				return filename;
			}
		}
	};
	f.open(GetFilename(f));
	while (!f.eof())
	{
		f >> pr;
		this->v.push_back(pr);
	}
	f.close();
}
void RR_SJF::from_hand()
{
	int power = 1;
	function<string(string, int)> f2 = [](string a, int i)
	{
		string n = "Std_name";
		cout << "\n" << a << i << "\n";
		cin >> n;
		return n;
	};
	function<int(string, int)> f = [](string a, int left_limit)
	{
		int n = 1;
		do
		{
			if (n < left_limit) cout << "Введите значение больше 0";
			cout << "\n" << a << "\n";
			cin >> n;
		} while (n < left_limit);
		return n;
	};

	int n = f("Введите число процессов", 1);
	string PrName;

	for (int i = 0; i < n; i++)
	{
		PrName = f2("Введите название процесса ", i);
		this->v.push_back(Process(PrName, f("Введите время выполнения процесса", 0), f("Введите время появления процесса в системе", 0)));
	}
}

void RR_SJF::print()
{
	cout << "Name" << "\t" << "Birth" << "\t" << "Runtime" << endl;
	for (int i = 0; i < v.size(); i++)
		cout << v[i].GetName() << "\t" << v[i].GetBTime() << "\t" << v[i].GetRTime() << endl;
}
void RR_SJF::print_logs()
{
	function<string(St)>f = [](St s)
	{
		if (s == St::done) return "done";
		if (s == St::ready) return "ready";
		if (s == St::run) return "run";
		return "not_l";
	};
	for (auto it = this->v.begin(); it != v.end(); it++)
		cout << f((*it).GetStatus()) << "\t";
	cout << endl;
}

int RR_SJF::GetNewProcess_ReStatus()
{
	int min = INT_MAX;
	int num = -1;
	int i = 0;
	for (auto IT = this->v.begin(); IT != this->v.end(); IT++, i++)
	{
		if ((*IT).GetRTime() == 0) (*IT).SetStatus(St::done);
		if ((*IT).GetStatus() == St::not_launched)
		{
			if ((*IT).GetBTime() == 0) (*IT).SetStatus(St::ready);
			(*IT).SetBTime((*IT).GetBTime() - 1);
		}
		if ((*IT).GetStatus() == St::ready || (*IT).GetStatus() == St::run)
		{
			(*IT).SetAllTime((*IT).GetAllTime() + 1);

			if ((*IT).GetRTime() < min)// SIF
			{
			min = (*IT).GetRTime();
			num = i;
			}
		}
	}
	return num;
}

vector<Process>::iterator RR_SJF::GetIT(int num)
{
	auto it = this->v.begin();
	while (num--)it++;
	return it;
}

void RR_SJF::preparation()
{
	system("cls");
	print();
	cout << "\n\n";
	auto IT = this->v.begin();

	for (; IT != v.end(); IT++)
	{
		cout << (*IT).GetName() << "\t";
		(*IT).SetStatus(St::not_launched);
	}
	cout << endl;
}

void RR_SJF::start()
{
	auto IT = this->v.begin();
	int PrPrev = -1;
	int PrNow = 0;

	while (fin())
	{
		this->print_logs();
		this->systime++;
		PrNow = this->GetNewProcess_ReStatus();
		if (PrNow == -1) { this->print_logs(); continue; }
		IT = this->GetIT(PrNow);
		
		(*IT).SetStatus(St::run);
		(*IT).SetRTime((*IT).GetRTime() - 1);

		if (PrPrev != PrNow)
		{
			if (PrPrev == -1) { PrPrev = PrNow; continue; }
			IT = this->GetIT(PrPrev);
			if ((*IT).GetRTime() == 0)
				(*IT).SetStatus(St::done);
			else (*IT).SetStatus(St::ready);
			PrPrev = PrNow;
		}
	};
}

bool RR_SJF::fin()
{
	int i = 0;
	for (auto it = v.begin(); it != v.end(); it++)
		if ((*it).GetStatus() == St::done) i++;
	if (i == 5) return false;
	return true;
}
void RR_SJF::specifications()
{
	cout << "\n\nВремя на выполнение всех процессов - " << this->systime << "\n\n";

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << "\t" << (*it).GetName() << ":" << endl;
		cout << "T – общее время пребывания процесса в системе = " << (*it).GetAllTime() << endl;
		cout << "Потерянное время M = T - t =  " << (*it).GetAllTime() - (*it).Gett() << endl;
		cout << "Отношение Реактивности R = t / T = " << ((*it).Gett() * 1.0) / (*it).GetAllTime() << endl;
		cout << "Штрафное отношение P = T / t  = " << ((*it).GetAllTime() * 1.0) / (*it).Gett() << endl;
		cout << endl;
	}
}