#pragma once
#include "Process.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>

class RR_SJF
{
private:
	vector<Process> v;
	int systime = 0;
public:
	void from_file();
	void from_hand();

	void print();
	void print_logs();

	void preparation();
	void start();
	bool fin();
	vector<Process>::iterator GetIT(int num);
	void specifications();
	int GetNewProcess_ReStatus();

	RR_SJF();
	~RR_SJF() {}
};