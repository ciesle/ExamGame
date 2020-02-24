#include "button.hpp"
Button::Button(Rect button, Color color, int ft, String str, bool valid) :button(button), color(color), str(str), font(Font(ft)), valid(valid) {
	color.a = 150;
}
void Button::draw() {
	if (!valid || (button.mouseOver() && MouseL.pressed())) color.a = 100;
	else if (button.mouseOver()) color.a = 180;
	else color.a = 255;
	button.draw(color);
	font(str).drawAt(button.center());
}
bool Button::onclick() {
	return valid && (button.mouseOver() && MouseL.pressed());
}