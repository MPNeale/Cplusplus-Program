// Author : Matthew Neale
// Date : 09/19/2020
// CS-210 SNHU
// Project One : Clock

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>
using namespace std;

int currentHour24 = 24;                                             // hold current hour in 24hr format
int currentMin = 60;                                                // hold current minute
int currentSec = 60;                                                // hold current second 
int currentHour12;                                                  // hold current hour in 12hr format
string AMorPM = "AM";                                               // hold whether am or pm for 12hr format

void Display12Hour() {                                              // display clock in 12hr format
    cout << setfill('0') << setw(2) << currentHour12 << ':';        // ensure numbers are displayed with 2 digits
    cout << setfill('0') << setw(2) << currentMin << ':';
    cout << setfill('0') << setw(2) << currentSec << " " << AMorPM;
    return;
}

void Display24Hour() {                                              // display clock in 24hr format
    cout << setfill('0') << setw(2) << currentHour24 << ':';        // ensure numbers are displayed with 2 digits
    cout << setfill('0') << setw(2) << currentMin << ':';
    cout << setfill('0') << setw(2) << currentSec;
    return;
}

void FormatClock() {                                                // display both clocks to user in proper format
    cout << setfill('*') << setw(25) << '*';                        // top lines of '*'
    cout << "     ";
    cout << setfill('*') << setw(25) << '*' << endl;

    cout << "*     " << "12-Hour Clock" << "     *     ";           // clock labels
    cout << "*     " << "24-Hour Clock" << "     *" << endl;

    cout << '*' << "      ";
    Display12Hour();                                                // display 12hr clock
    cout << "      " << '*' << "     ";

    cout << '*' << "       ";
    Display24Hour();                                                // display 24hr clock
    cout << "        " << '*' << endl;

    cout << setfill('*') << setw(25) << '*';                        // bottom lines of '*'
    cout << "     ";
    cout << setfill('*') << setw(25) << '*' << endl;
}

void Convert24To12() {                                              // convert 24hr to 12hr format
    if (currentHour24 > 12) {                                       // and assign AMorPM
        currentHour12 = currentHour24 - 12;
        AMorPM = "PM";
    }
    else {
        currentHour12 = currentHour24;
        AMorPM = "AM";
        if (currentHour24 == 12) {
            AMorPM = "PM";
        }
    }
}

void AddHour() {                                                    // add 1 hour to clock
    if (currentHour24 == 23) {                                      // ensure hours do not exceed 23                
        currentHour24 = 0;                                          // reset to zero if 23 for 24hr
        currentHour12 = 12;                                         // reset to 12 for 12hr
        AMorPM = "AM";
    }
    else {
        currentHour24 += 1;
        Convert24To12();                                            // call convert function
    }
}

void AddMinute() {                                                  // add 1 minute to clock
    if (currentMin == 59) {                                         // ensure minutes do not exceed 59
        currentMin = 0;                                             // reset to zero if 59
        AddHour();                                                  // call AddHour if minutes reach 59
    }
    else {
        currentMin += 1;
    }
}

void AddSecond() {                                                  // add 1 second to clock
    if (currentSec == 59) {                                         // ensure seconds do not exceed 59
        currentSec = 0;                                             // reset to zero if 59
        AddMinute();                                                // call AddMinute if seconds reach 59
    }
    else {
        currentSec += 1;
    }
}

int main()                                                          // start main
{

    while (currentHour24 > 23 || currentHour24 < 0) {               // ensure hour is between 0-23
        cout << "Set current hour (0-23): " << endl;                // collect user input for hour
        cin >> currentHour24;
        Convert24To12();                                            // call convert function
    }
    while (currentMin > 59 || currentMin < 0) {                     // ensure minute is between 0-59
        cout << "Set current minutes (0-59): " << endl;             // collect user input for minute
        cin >> currentMin;
    }
    while (currentSec > 59 || currentSec < 0) {                     // ensure second is between 0-59
        cout << "Set current seconds (0-59): " << endl;             // collect user input for second
        cin >> currentSec;
    }

    int userChoice = 5;                                             // set exit variable for while loop

    while (userChoice != 4) {

        while (!_kbhit()) {                                         // run until user presses a key
            cout << "\033[2J\033[1;1H";                             // clear screen
            FormatClock();                                          // call FormatClock function
            AddSecond();                                            // call AddSecond function
            Sleep(1000);                                            // wait 1 second
        }
        char dummy = _getch();                                      // catch user input to exit loop

        cout << "\n1 - Add One Hour" << endl;                       // display menu to user
        cout << "2 - Add One Minute" << endl;
        cout << "3 - Add One Second" << endl;
        cout << "4 - Exit Program" << endl;
        cout << "\nWhat would you like to do?" << endl;
        cin >> userChoice;                                          // collect userChoice input

        switch (userChoice){                                        // userChoice switch
            case 1:
                AddHour();                                          // call AddHour if userChoice is 1
                break;
            case 2:
                AddMinute();                                        // call AddMinute if userChoice is 2
                break;
            case 3:
                AddSecond();                                        // call AddSecond if userChoice is 3
                break;
            default:                                                // ignore all other cases
                break;
        }

    }                                                               // end of while loop
    return 0;
}