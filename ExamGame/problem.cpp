#include "problem.hpp"

Problem::Problem(String prob, String ans, int valid, String fname, int row) :prob(prob), ans(ans), valid(valid), fname(fname), row(row) {}
void Problem::del() {
	valid = !valid;
}