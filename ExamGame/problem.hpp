#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "base.hpp"

void init();

struct Problem {
	String prob, ans, fname;
	bool valid;
	int row;
	Problem(String prob, String ans, int valid, String fname, int row);
	void del();
};

#endif