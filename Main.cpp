#include <iostream>
//#include <chrono>// Useless
//#include <thread> // Useless
#ifdef _WIN32
#include<conio.h>
#include<Windows.h>
#endif
#ifdef __linux
//#include <stdio.h> // Useless
//#include <string.h> // Useless
//#include <ctype.h> // Useless
//#include <stdlib.h> // Useless
//#include <sys/ioctl.h> // Useless
#include <unistd.h> 
#include <termios.h>
#include <fcntl.h>
#endif
//constexpr auto ESC = 27;  // Added constexpr // Useless
using namespace std;

class Watch {
public:
    Watch() {
        this->sec = 0;
        this->min = 0;
        this->hour = 0;
    }

    Watch(int sec, int min, int hour) {
        this->sec = sec;
        this->min = min;
        this->hour = hour;
    }

    /* Useless *\
    Watch(const Watch& other) {
        sec = other.sec;
        min = other.min;
        hour = other.hour;
    }

    Watch(const Watch&& other) noexcept {
        sec = other.sec;
        min = other.min;
        hour = other.hour;
    }

    Watch operator=(const Watch& other) {
        if (this == &other) {
            return *this;
        }
        sec = other.sec;
        min = other.min;
        hour = other.hour;
        return *this;
    }

    ~Watch() { }
    */

    friend ostream& operator<<(ostream& out, Watch& obj) {
        out << "Час роботи програми\n";
        out << "год: " << obj.hour << "\nхв: " << obj.min << "\nсек: " << obj.sec << endl;
        return out;
    }
#ifdef _WIN32
    void counter(Watch& name) {
        while (!_kbhit()) {
            system("cls");
            cout << "Для виходу в будь-який момент можете натиснути -> будь-яку клавішу\n"; // Exit any key
            cout << name; name.sec++;
            if (name.sec == 60) {
                name.min++;
                name.sec = 0;
            }
            if (name.min == 60) {
                name.hour++;
                name.min = 0;
            }
            Sleep(1000); //this_thread::sleep_for(chrono::seconds(1));
        }
    }
#endif
#ifdef __linux
    int _kbhit() { // void - Removed
        struct termios oldt, newt;
        int ch, oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }
    void counter(Watch& name) {
        while (!_kbhit()) {
            system("clear");
            cout << "Для виходу в будь-який момент можете натиснути -> будь-яку клавішу\n"; // Exit any key
            cout << name;
            name.sec++;
            if (name.sec == 60) {
                name.min++;
                name.sec = 0;
            }
            if (name.min == 60) {
                name.hour++;
                name.min = 0;
            }
            sleep(1); //this_thread::sleep_for(chrono::seconds(1));
        }
    }
#endif
protected:
    int sec;
    int min;
    int hour;
};

int main() {
    Watch watch; // using for both
#ifdef _WIN32
    system("chcp 1251>nul"); // Important
    watch.counter(watch);
#endif

#ifdef __linux
    //cout << "Для виходу в будь-який момент можете натиснути -> будь-яку клавішу\n"; moved to (void counter)
    //this_thread::sleep_for(chrono::seconds(5)); Removed
    watch.counter(watch);
#endif
    return 0; // Important
}

/*
Розгляньте приклад програми. Постарайтеся зрозуміти, як вона працює. По можливості покращіть її:
1) вилучіть зайвий код;
2) зменшіть кількість використаної пам’яті;
3) усі ваші зміни обґрунтуйте в коментарях.
*/
