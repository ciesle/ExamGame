#include "base.hpp"

const Vec2 gravity(0, 1000);
const Color bcolor(180, 180, 180);
const ld inf = 10000000;
const int ssize = 6000;
const ld PI = 3.14159265359;
int scene = 0;
int psize = 0;

Vec2 ppos;

Vec2 cpos;
Stopwatch sw;

Array<int>scores;


Vec2 adj(Vec2 pos) {
	if (ppos.x < 600) {
		return pos;
	}
	else if (ppos.x < ssize - 600) {
		return Vec2(pos.x - (ppos.x - 600), pos.y);
	}
	else {
		return Vec2(pos.x + (1200 - ssize), pos.y);
	}
}