#ifndef _COLOR_H_

#define _COLOR_H_


#include <Windows.h>
#include <iostream>

using namespace std;

void setTextColor(int foreground, int background);

class Color {
	int _foreground, _background;
public:
	Color(int foreground, int background)
		: _foreground(foreground), _background(background) {}

	friend ostream& operator<<(ostream& out, const Color& c) {
		setTextColor(c._foreground, c._background);
		return out;
	}
};

#endif // _COLOR_H_