#include "RR_SJF.h"

void RR_SJF::from_file()
{
	fstream f;
	Process pr;
	function<string(fstream& f)> GetFilename = [](fstream& f) {
		string filename;
		system("cls");
		cout << "¬ведите им€ файла\n";
		while (1)
		{
			cin >> filename;
			f.open(filename);
			if (!f.is_open()) { system("cls"); cout << "¬ведите им€ существующего файла\n"; }
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
			if (n <= 0) cout << "¬ведите значение больше 0";
			cout << "\n" << a << "\n";
			cin >> n;
		} while (n <= 0);
		return n;
	};

	int n = f("¬ведите число процессов");
	string PrName;

	for (int i = 0; i < n; i++)
	{
		PrName = f2("¬ведите название процесса");
		this->v.push_back(Process(PrName, f("¬ведите врем€ выполнени€ процесса"), f("¬ведите врем€ по€влени€ процесса в системе")));
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
bool RR_SJF::fin()
{
	int counter = 0;
	for (auto it = this->v.begin(); it != v.end(); it++)
	{
		if ((*it).GetStatus() == St::done) counter++;
	}
	if (counter == v.size()) return false;
	return true;
}
void RR_SJF::ChangeTOS() 
{
	for (auto it = this->v.begin(); it != v.end(); it++)
	{
		(*it).SetAllTime((*it).GetAllTime() + 1);
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

	int Kvant = 0;
	int Q = Kvant_const;

	auto IT = this->v.begin();
	while (fin())
	{
		if (IT->GetStatus() != St::done)
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
}