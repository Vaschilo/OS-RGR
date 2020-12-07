#include "RR_SJF.h"

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
	function<string(string)> f2 = [](string a)
	{
		string n = "Std_name";
		cout << "\n" << a << "\n";
		cin >> n;
		return n;
	};
	function<int(string)> f = [](string a)
	{
		int n = 1;
		do
		{
			if (n < 0) cout << "Введите значение больше 0";
			cout << "\n" << a << "\n";
			cin >> n;
		} while (n < 0);
		return n;
	};

	int n = f("Введите число процессов");
	string PrName;

	for (int i = 0; i < n; i++)
	{
		PrName = f2("Введите название процесса");
		this->v.push_back(Process(PrName, f("Введите время выполнения процесса"), f("Введите время появления процесса в системе")));
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
bool RR_SJF::fin(St status)
{
	int counter = 0;
	for (auto it = this->v.begin(); it != v.end(); it++)
	{
		if ((*it).GetStatus() == status) counter++;
	}
	if (counter == v.size()) return false;
	return true;
}
void RR_SJF::ChangeTOS() 
{
	this->systime++;
	for (auto it = this->v.begin(); it != v.end(); it++)
	{
		if ((*it).GetStatus() == St::ready || (*it).GetStatus() == St::run)
			(*it).SetAllTime((*it).GetAllTime() + 1);
		if ((*it).GetStatus() == St::not_launched)
			if ((*it).GetBTime() > 0) (*it).SetBTime((*it).GetBTime() - 1);
			else (*it).SetStatus(St::ready);
	}
}
void RR_SJF::start()
{
	system("cls");
	sort(this->v.begin(), this->v.end(), [](Process& a, Process& b)
		{
			if (a.GetBTime() + a.GetRTime() < b.GetBTime() + b.GetRTime()) return true;
			return false;
		});
	print();
	cout << "\n\n"; for (int i = 0; i < v.size(); i++) cout << v[i].GetName() << "\t";
	cout << endl;

	int Q = Kvant_const;

	while (!fin(St::not_launched)) 
	{
		ChangeTOS(); print_logs();
	}

	auto IT = this->v.begin();
	while (fin(St::done))
	{
		if (IT->GetStatus() != St::done && IT->GetStatus() != St::not_launched)
		{
			IT->SetStatus(St::run);
			for (int i = 0; i < Q; i++)
			{
				(*IT).IsProcessDone();
				ChangeTOS();
				IT->SetRTime(IT->GetRTime() - 1);
				print_logs();
				(*IT).IsProcessDone();
			};
			IT->SetStatus(St::ready);
			(*IT).IsProcessDone();
		}
		++IT;
		if (IT == this->v.end()) { IT = this->v.begin(); }
	};

	cout << "\n\nВремя на выполнение всех процессов - " << this->systime << "\n\n";

	for (auto it = v.begin(); it != v.end(); it++)
	{
		cout << (*it).GetName() << ":" << endl;
		cout << "T – общее время пребывания процесса в системе = " << (*it).GetAllTime() << endl;
		cout << "Потерянное время M = T - t =  " << (*it).GetAllTime() - (*it).Gett() << endl;
		cout << "Отношение Реактивности R = t / T = " << ((*it).Gett() * 1.0) / (*it).GetAllTime() << endl;
		cout << "Штрафное отношение P = T / t  = " << ((*it).GetAllTime() * 1.0) / (*it).Gett() << endl;
		cout << endl;
	}
}