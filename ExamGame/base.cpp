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