#pragma once

#include <iostream>
using namespace std;

enum St
{
	not_launched,
	ready,
	run,
	done
};

class Process
{
private:
	string name;
	int runtime;
	int b_time;
	St status;
public:
	Process() 
	{
		this->name = "Std_name";
		this->runtime = 0;
		this->b_time = 0;
		this->status = St::not_launched;
	}
	Process(string name, int runtime, int birth_time, St status) 
	{
		this->name = name;
		this->runtime = runtime;
		this->b_time = birth_time;
		this->status = status;
	}
	bool ready()
	{
		if (this->status == St::ready) return true;
		return false;
	}
	string GetStatus()
	{
		switch (this->status)
		{
		case 0:return "not_l";
		case 1:return "ready";
		case 2:return "run";
		case 3:return "done";
		}
	}
	string GetName() { return this->name; }

	friend istream& operator >>(istream& in, Process& pr)
	{
		string helper = "";
		in >> pr.name >> pr.b_time >> pr.runtime >> helper;

		pr.status = St::done;
		if (helper == "not_l") pr.status = St::not_launched;
		if (helper == "ready") pr.status = St::ready;
		if (helper == "run") pr.status = St::run;
		if (helper == "done") pr.status = St::done;
		return in;
	}

	~Process() {}
};