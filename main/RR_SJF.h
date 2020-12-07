#pragma once
#include "Process.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>

#define Kvant_const 3

class RR_SJF
{
private:
	vector<Process> v;
	int systime = 0;
public:
	void start();
	void from_file();
	void from_hand();
	void print();
	bool fin(St status);
	void ChangeTOS();
	void print_logs();

	RR_SJF();
	~RR_SJF() {}
};