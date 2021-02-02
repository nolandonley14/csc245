
#include <iostream>
#include <string>
using namespace std;

const int SIZE = 100;

struct DateType
{
	string month;
	int day;
	int year;
};

// Insert EventType definition HERE
struct EventType
{
	string place;
	DateType date;
};


void PrintStruct (DateType Holiday);
void AssignMonth (EventType Dates[]);

int main()
{
	DateType Holiday;
	Holiday.month = "September";
	Holiday.day = 2;
	Holiday.year = 2019;

	EventType Dates[SIZE];


	PrintStruct (Holiday);
	AssignMonth (Dates);
	return 0;
}

void PrintStruct (DateType Holiday)
{
	// pre  : Holiday is intialized with three field values
	cout << Holiday.month << " " << Holiday.day << ", " << Holiday.year << endl;
	// post : Function prints date of Holiday in form mm dd, yy
}

void AssignMonth (EventType Dates[])
{
	// pre  : none
	for (int i = 0; i < SIZE; i++)
	{
		Dates[i].date.month = "September";
	}
	// post : The month field of every date record in array is assigned a month
}
