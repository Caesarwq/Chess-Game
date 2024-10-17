#include <iostream>
#include "chessboard.h"
#include "chesspiece.h"

using namespace std;

int main()
{
    Board main; int selection; string filename;
    do
    {
        cout << "Welcome to the Chess Game!\n1-Save\n2-Load\n3-Play" << endl;
        cin >> selection; cout << endl;
        if(selection == 1)
        {
            cout << "Enter the file name : ";
            cin >> filename;
            main.savetofile(filename);
        }
        else if(selection == 2)
        {
            cout << "Enter the file name : ";
            cin >> filename;
            main.loadfromfile(filename);
        }
        else if(selection == 3);
        else    cout << "Wrong selection! Try again." << endl;
    }while(selection < 1 || selection > 3);

    cout << main;
    do
    {
        cout << "[White's Turn]" << endl;
        main.readMove('W');
        cout << "[Updated Board]"<< "\n" << main;
        if(main.isOver('B'))    {cout << "Checkmate! Black loses.\n" <<"Goodbye! "; break;}
        cout << "[Black's Turn]" << endl;
        main.readMove('B');
        cout << "[Updated Board]"<< "\n" << main;
        if(main.isOver('W'))    cout << "Checkmate! White loses.\n" <<"Goodbye! ";
    }
    while(!(main.isOver('W')) && !(main.isOver('B')));
    return 0;
}