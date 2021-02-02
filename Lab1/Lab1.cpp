#include <iostream>
using namespace std;

double convert(double value);
double celciusValue;

int main() {
    cout << "Please enter a Celcius value: ";
    cin >> celciusValue;
    cout << celciusValue << " degrees Celcius is "
        << convert(celciusValue) << " degrees Fahrenheit." << endl;
    return 0;
}

double convert(double tmp) {
    return 1.8*tmp+32.0;
}
