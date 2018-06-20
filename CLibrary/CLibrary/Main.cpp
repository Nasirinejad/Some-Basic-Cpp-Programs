#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;
#include "Users.h"
#include "Books.h"
#include "functions.h"
void main(){
	system("TITLE Library");
	meno();
	Hotkey();
	system("cls");
	setColor('b');
	cout << "\t___________________________________________________________\n\t";
	setColor('i');
	cout << "\tProgramers: Mahdi Nasirinejad\n\t";
	setColor('g');
	cout << "\t\tphp , Asp, Js, HTML&Css\t\n";
	setColor('b');
	cout << "______________________________________________________";
	Sleep(3000);
}
