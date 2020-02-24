#include "base.hpp"

struct Button {
	Rect button;
	Font font;
	Color color;
	String str;
	bool valid;
	Button(Rect button, Color color, int ft, String str, bool valid);
	//場所サイズ、色、フォントサイズ、文字列、使用可能か
	void draw();
	bool onclick();
};