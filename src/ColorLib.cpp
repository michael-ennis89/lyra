#include "ColorLib.hpp"

bool graph_lib::Screen::isWindows() {
	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
		return true;
	#else
		return false;
	#endif
}


void graph_lib::Screen::setBackgroundColor(const Color& col) {
	back_color = col;

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbi;

	DWORD dwConSize;

	COORD coordScreen = { 0, 0 };

	DWORD cCharsWritten;



	GetConsoleScreenBufferInfo(hConsole, &csbi);

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;



	// Change the text background color to blue and foreground to cyan

	/*if (!FillConsoleOutputAttribute(hConsole,
	FOREGROUND_BLUE | FOREGROUND_GREEN |

	FOREGROUND_INTENSITY | BACKGROUND_BLUE,

	dwConSize, coordScreen, &cCharsWritten))

	{*/

	WORD wAttr;

	switch (col) {
	case Color::RED:
		wAttr = 0x0008 | 0x0040;
		break;
	case Color::GREEN:
		wAttr = 0x0008 | 0x0020;
		break;
	case Color::BLUE:
		wAttr = 0x0008 | 0x0010;
		break;
	case Color::BLACK:
		wAttr = 0x00;
		break;
	case Color::WHITE:
		wAttr = 0xFF;
		break;
	default:

	    break;
	}

	WBack = wAttr;

	if (!FillConsoleOutputAttribute(hConsole,
		wAttr,
		dwConSize, coordScreen, &cCharsWritten))
	{

		MessageBox(NULL, TEXT("FillConsoleOutputAttribute"),
			TEXT("Console Error"), MB_OK);
		return;

	}

	if (!SetConsoleTextAttribute(hConsole,
		wAttr))
	{
		MessageBox(NULL, TEXT("SetConsoleTextAttribute"),
		TEXT("Console Error"), MB_OK);
		return;
	}


	#else
		switch (col) {
		case Color::RED:
		strcpy(UBack, "\033[31m");
			break;
		case Color::GREEN:
		strcpy(UBack, "\033[32m");
			break;
		case Color::BLUE:
		strcpy(UBack, "\033[34m");
			break;
		case Color::BLACK:
		strcpy(UBack, "\033[30m");
			break;
		case Color::WHITE:
		strcpy(UBack, "\033[37m");
			break;
		default:
		strcpy(UBack, "\033[30m");
			break;
		}
		std::cout << UBack;
	#endif

}


void graph_lib::Screen::setFontColor(const Color& col) {
	font_color = col;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32)

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	WORD wAttr;

	switch (col) {
	case Color::RED:
		wAttr = 0x0008 | 0x0004;
		break;
	case Color::GREEN:
		wAttr = 0x0008 | 0x0002;
		break;
	case Color::BLUE:
		wAttr = 0x0008 | 0x0001;
		break;
	case Color::BLACK:
		wAttr = 0x0000 | 0x0008;
		break;
	case Color::WHITE:
		wAttr =  0X0007;
		break;
	default:
		wAttr = 0x0000;
		break;
	}


	if (!SetConsoleTextAttribute(hConsole,
		WBack | wAttr))

	{
		MessageBox(NULL, TEXT("SetConsoleTextAttribute"),

			TEXT("Console Error"), MB_OK);

		return;

	}

#else


	switch (col) {
		case Color::RED:
        strcpy(UTBack, "\033[41m");
			break;
		case Color::GREEN:
		strcpy(UTBack, "\033[42m");
			break;
		case Color::BLUE:
		strcpy(UTBack, "\033[44m");
			break;
		case Color::BLACK:
		strcpy(UTBack, "\033[40m");
			break;
		case Color::WHITE:
		strcpy(UTBack, "\033[47m");
			break;
		default:
		strcpy(UTBack, "\033[40m");
			break;
		}
		std::cout << UBack;


#endif

}


void graph_lib::Screen::setDefaultScreenColor() {
	setBackgroundColor(Color::BLACK);
	setFontColor(Color::WHITE);
}

#define ANSI_COLOR_RESET   "\x1b[0m"
void graph_lib::Screen::resetTextColor() {
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32)
		setFontColor(Color::WHITE);
	#else
		std::cout << ANSI_COLOR_RESET;
	#endif
}
