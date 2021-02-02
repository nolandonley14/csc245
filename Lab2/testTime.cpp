
#include <iostream>
#include "time.h"
using namespace std;

Time Schedules[10];

int main() {
    Time myTime = Time(9,30,0);
    myTime.Write();
    myTime.WriteAmPm();
    myTime.Set(8,0,0);
    myTime.WriteAmPm();
    myTime.Mealtime();

    for (int i = 0; i < 10; i++)
    {
        Schedules[i].Set(11,0,0);
        Schedules[i].WriteAmPm();
    }
    return 0;
}
