#include <iostream>

using namespace std;

int menu (){
    int input_user;
    cout<< "Menu 1-Combat 2-Exit" << endl;
    cin >> input_user;
    return input_user;
}


int main() {
    int choice_player = menu();
    
    return 0;
}