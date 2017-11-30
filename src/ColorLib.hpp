#ifndef COLORLIB_H
#define COLORLIB_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif // defined

#include <iostream>
#include <string>
#include <cstring>

namespace graph_lib {

	enum class Color {
		RED,
		GREEN,
		BLUE,
		WHITE,
		BLACK
	};

	class Screen {
	public:
	    Screen() {};
	    ~Screen() {}
		void setDefaultScreenColor();
		void setBackgroundColor(const Color& col);
        void setFontColor(const Color& col);
        void setTextBackColor(const Color& col);
        void resetTextColor();
	private:
        Color back_color;
		Color text_backcolor;
		Color font_color;

		unsigned short WBack = 0; //WORD SCREEN BACKCOLOR
		unsigned short WTBack = 0; //WORD TEXT BACKCOLOR
		char UBack[10]; //UNIX SCREEN BACKCOLOR
		char UTBack[10]; //UNIX TEXT BACKCOLOR


        bool isWindows();
	};
};







#endif // COLORLIB_H
