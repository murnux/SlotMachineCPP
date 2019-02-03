#include <iostream>
#include <string>
#include "SlotMachine.h"

using namespace std;

int main() {
    cout << "Welcome to the Slot Machine!" << endl;
    
    SlotMachine sm1;

    sm1.play();
    
    //cout << sm1.getMachineName() << endl;

    cout << "Playing first machine again to test state." << endl;
    sm1.play();

    return 0;
}