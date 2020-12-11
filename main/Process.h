#pragma once

#include <iostream>
using namespace std;

enum class St
{
	not_launched = 0,
	ready = 1,
	run = 2,
	done = 3,
	start = 4
};

class Process
{
private:
	string name;
	int runtime;
	int b_time;
	int time_on_system = 0;
	St status;
	int t;
public:
	Process() 
	{
		this->name = "Std_name";
		this->runtime = 0;
		this->b_time = 0;
		this->status = St::not_launched;
		t = runtime + b_time;
	}
	Process(string name, int runtime, int birth_time) 
	{
		this->name = name;
		this->runtime = runtime;
		this->b_time = birth_time;
		this->status = St::not_launched;
		t = runtime;
	}

	void SetStatus(St status) {this->status = status;}
	St GetStatus() {return this->status;}

	string GetName() { return this->name; }

	int GetBTime() { return this->b_time; }
	void SetBTime(int b_time) { this->b_time = b_time; }

	int GetRTime() { return this->runtime; }
	void SetRTime(int runtime) { this->runtime = runtime; }

	int GetAllTime() { return this->time_on_system; };
	void SetAllTime(int time) { this->time_on_system = time; };

	int Gett() { return this->t; }

	void IsProcessDone() { if (this->GetRTime() <= 0) this->SetStatus(St::done); }

	friend istream& operator >>(istream& in, Process& pr)
	{
		in >> pr.name >> pr.b_time >> pr.runtime;
		pr.t = pr.runtime;
		return in;
	}
	~Process() {}
};