#include <iostream>
#include <stdio.h>

using namespace std;

int main() {
    char exitInput;

    do {
        system("CLS");
        
        int menuNumber;
        while (true) {
            printf("Menu 1\nMenu 2\nMenu 3\nMenu 4\nWhat menu do you want? \n");
            if (cin >> menuNumber && menuNumber >= 0) {
                break;
            }

            cin.clear();
            cin.ignore(1000, '\n');
        }

        switch (menuNumber) {
            case 1:
                printf("oh cool menu 1\n");
                break;
            case 2:
                printf("oh cool menu 2\n");
                break;
            case 3:
                printf("oh cool menu 3\n");
                break;
            case 4:
                printf("oh cool menu 4\n");
                break;
            default:
                printf("that isnt a menu number!\n");
                break;
        }

        printf("Want to go again? (y/Y): ");
        cin >> exitInput;
    } while (exitInput == 'y' || exitInput == 'Y');

    return 0;
}