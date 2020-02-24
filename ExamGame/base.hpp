#ifndef BASE_HPP
#define BASE_HPP

#include <Siv3D.hpp>

typedef long long ll;
typedef double ld;


extern const Vec2 gravity;
extern const Color bcolor;
extern const ld inf;
extern const int ssize;
extern const ld PI;
extern int scene;
extern int psize;

extern Vec2 ppos;

extern Vec2 cpos;
extern Stopwatch sw;

extern Array<int>scores;

Vec2 adj(Vec2 pos);

#endif