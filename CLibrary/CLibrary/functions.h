char pointer[4];
int p, sp, Cpr = 0;
Books books;
Users users;
void setColor(char c){
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (c) {
	case 'b':
		SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
		break;
	case 'g':
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
		break;
	case 'r':
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
		break;
	default:
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY);
		break;
	}
}
void Scmeno(){
	//system("cls");
	setColor('g'); cout << "Success!\n";
	setColor('r'); cout << "B";
	setColor('g'); cout << "ack\t";
	setColor('r'); cout << "N";
	setColor('g'); cout << "ext";
	Cpr = 2;
}
void Ftmeno(){
	//system("cls");
	setColor('g'); cout << "Oh!\n";
	setColor('r'); cout << "B";
	setColor('g'); cout << "ack\t";
	setColor('r'); cout << "R";
	setColor('g'); cout << "etry";
	Cpr = 2;
}
void meno(){
	switch (pointer[0]){
	case 'b':
	case 'B':
		p = 0;
		sp = 1;
		system("cls");
		setColor('r'); cout << "A";
		setColor('g'); cout << "dd Book\t";
		setColor('r'); cout << "R";
		setColor('g'); cout << "emove Book\t";
		setColor('r'); cout << "F";
		setColor('g'); cout << "ind Book\t";
		setColor('r'); cout << "L";
		setColor('g'); cout << "ist All\t";
		setColor('r'); cout << "B";
		setColor('g'); cout << "ack\n" << endl;
		if (Cpr == 0)Cpr++;
		break;
	case 'a':
	case 'A':
		p = 0;
		sp = 1;
		system("cls");
		setColor('r'); cout << "I";
		setColor('g'); cout << "nsert \tMake";
		setColor('r'); cout << "F";
		setColor('g'); cout << "ree\t";
		setColor('r'); cout << "C";
		setColor('g'); cout << "heck Book\t";
		setColor('r'); cout << "B";
		setColor('g'); cout << "ack\n" << endl;
		if (Cpr == 0)Cpr++;
		break;
	case 'u':
	case 'U':
		p = 0;
		sp = 1;
		system("cls");
		setColor('r'); cout << "A";
		setColor('g'); cout << "dd User\t";
		setColor('r'); cout << "R";
		setColor('g'); cout << "emove User\t";
		setColor('r'); cout << "F";
		setColor('g'); cout << "ind User\t";
		setColor('r'); cout << "L";
		setColor('g'); cout << "ist All\t";
		setColor('r'); cout << "B";
		setColor('g'); cout << "ack\n" << endl;
		if (Cpr == 0)Cpr++;
		break;
	case 'e':
	case 'E':
		Cpr = 4;
		break;
	default:
		system("cls");
		setColor('r'); cout << "B";
		setColor('g'); cout << "ook\tB";
		setColor('r'); cout << "a";
		setColor('g'); cout << "ilment \t";
		setColor('r'); cout << "U";
		setColor('g'); cout << "ser\t";
		setColor('r'); cout << "E";
		setColor('g'); cout << "xit\n" << endl;
		break;
	}

	setColor('i');
}
void request(){
	switch (pointer[0]){
	case 'b':
	case 'B':
		switch (pointer[1]){
		case 'a':
		case 'A':
			system("cls");
			setColor('g'); cout << "Books > Insert a new book\n";
			setColor('i');
			if (books.AddBook())
				Scmeno();
			else
				Ftmeno();
			break;
		case 'r':
		case 'R':
			system("cls");
			setColor('g'); cout << "Books > Remove a book\n";
			setColor('i');
			if (books.remove())
				Scmeno();
			else
				Ftmeno();
			break;
		case 'f':
		case 'F':
			system("cls");
			setColor('g'); cout << "Books > Find book ";

			if (pointer[2] == 'i' || pointer[2] == 'I'){
				cout << "By Id\n";
				setColor('i');
				books.Find(0);
			}
			else if (pointer[2] == 'n' || pointer[2] == 'N'){
				cout << "By Name\n";
				setColor('i');
				books.Find(1);
			}
			else{
				cout << endl;
				cout << "Find By ";
				setColor('r'); cout << "I";
				setColor('g'); cout << "D \t Find By ";
				setColor('r'); cout << "N";
				setColor('g'); cout << "ame\n";
				Cpr = 2;
			}
			setColor('r'); cout << "\nB";
			setColor('g'); cout << "ack";
			break;
		case 'l':
		case 'L':
			system("cls");
			setColor('g'); cout << "Books > Show list\n";
			if ((pointer[2] == 'n' || pointer[2] == 'N') && sp != 1)
				p++;
			if ((pointer[2] == 'p' || pointer[2] == 'P') && p > 0)
				p--;
			setColor('b'); cout << "Page " << p + 1;
			setColor('i');
			sp = books.showlist(p);
			if (sp == -1){
				cout << "\t There is no book!";
			}
			else{
				cout << endl;
				if (p > 0){
					setColor('r'); cout << "\t P";
					setColor('g'); cout << "rePage";
				}
				if (sp != 1){
					setColor('r'); cout << "\t N";
					setColor('g'); cout << "extPage";
				}
			}
			setColor('r'); cout << "\nB";
			setColor('g'); cout << "ack";
			Cpr = 2;
			break;
		}
		break;
	case 'a':
	case 'A':
		switch (pointer[1]){
		case 'i':
		case 'I':
			system("cls");
			setColor('g'); cout << "Books > Insert a bailment ";
			if (pointer[2] == 'i' || pointer[2] == 'I'){
				cout << "By Id\n";
				setColor('i');
				if (books.restat(0, 1))
					Scmeno();
				else
					Ftmeno();
			}
			else if (pointer[2] == 'n' || pointer[2] == 'N'){
				cout << "By Name\n";
				setColor('i');
				if (books.restat(0, 0))
					Scmeno();
				else
					Ftmeno();
			}
			else{
				cout << endl;
				cout << "\n By ";
				setColor('r'); cout << "I";
				setColor('g'); cout << "D \t By ";
				setColor('r'); cout << "N";
				setColor('g'); cout << "ame\n";
				Cpr = 2;
			}
			break;
		case 'f':
		case 'F':
			system("cls");
			setColor('g'); cout << "Books > Getback a bailment ";
			if (pointer[2] == 'i' || pointer[2] == 'I'){
				cout << "By Id\n";
				setColor('i');
				if (books.restat(1, 1))
					Scmeno();
				else
					Ftmeno();
			}
			else if (pointer[2] == 'n' || pointer[2] == 'N'){
				cout << "By Name\n";
				setColor('i');
				if (books.restat(1, 0))
					Scmeno();
				else
					Ftmeno();
			}
			else{
				cout << endl;
				cout << "\n By ";
				setColor('r'); cout << "I";
				setColor('g'); cout << "D \t By ";
				setColor('r'); cout << "N";
				setColor('g'); cout << "ame\n";
				Cpr = 2;
			}
			break;
		case 'c':
		case 'C':
			system("cls");
			setColor('g'); cout << "Books > Check book ";

			if (pointer[2] == 'i' || pointer[2] == 'I'){
				cout << "By Id\n";
				setColor('i');
				books.Find(0);
			}
			else if (pointer[2] == 'n' || pointer[2] == 'N'){
				cout << "By Name\n";
				setColor('i');
				books.Find(1);
			}
			else{
				cout << endl;
				cout << "Find By ";
				setColor('r'); cout << "I";
				setColor('g'); cout << "D \t Find By ";
				setColor('r'); cout << "N";
				setColor('g'); cout << "ame\n";
				Cpr = 2;
			}
			setColor('r'); cout << "\nB";
			setColor('g'); cout << "ack";
			break;
		}
		break;
	case 'u':
	case 'U':
		switch (pointer[1]){
		case 'a':
		case 'A':
			system("cls");
			setColor('g'); cout << "Users > Insert a new book\n";
			setColor('i');
			if (users.Adduser())
				Scmeno();
			else
				Ftmeno();
			break;
		case 'r':
		case 'R':
			system("cls");
			setColor('g'); cout << "Users > Remove a book\n";
			setColor('i');
			if (users.remove())
				Scmeno();
			else
				Ftmeno();
			break;
		case 'f':
		case 'F':
			system("cls");
			setColor('g'); cout << "Users > Find book ";

			if (pointer[2] == 'i' || pointer[2] == 'I'){
				cout << "By Id\n";
				setColor('i');
				users.Find(0);
			}
			else if (pointer[2] == 'n' || pointer[2] == 'N'){
				cout << "By Name\n";
				setColor('i');
				users.Find(1);
			}
			else{
				cout << endl;
				cout << "Find By ";
				setColor('r'); cout << "I";
				setColor('g'); cout << "D \t Find By ";
				setColor('r'); cout << "N";
				setColor('g'); cout << "ame\n";
				Cpr = 2;
			}
			setColor('r'); cout << "\nB";
			setColor('g'); cout << "ack";
			break;
		case 'l':
		case 'L':
			system("cls");
			setColor('g'); cout << "Users > Show list\n";
			if ((pointer[2] == 'n' || pointer[2] == 'N') && sp != 1)
				p++;
			if ((pointer[2] == 'p' || pointer[2] == 'P') && p > 0)
				p--;
			setColor('b'); cout << "Page " << p + 1;
			setColor('i');
			sp = users.showlist(p);
			if (sp == -1){
				cout << "\t There is no book!";
			}
			else{
				cout << endl;
				if (p > 0){
					setColor('r'); cout << "\t P";
					setColor('g'); cout << "rePage";
				}
				if (sp != 1){
					setColor('r'); cout << "\t N";
					setColor('g'); cout << "extPage";
				}
			}
			setColor('r'); cout << "\nB";
			setColor('g'); cout << "ack";
			Cpr = 2;
			break;
		}
		break;

	}
}
void Hotkey(){
	Cpr = 0;
	while (Cpr < 4){
		pointer[Cpr] = _getch();
		if (Cpr == 0)
			meno();
		else
		{
			if (pointer[Cpr] == 'b' || pointer[Cpr] == 'B'){
				pointer[Cpr] = ' ';
				Cpr--;
				pointer[Cpr] = ' ';
				if (Cpr < 2) meno();
				else request();
			}
			else
				request();
		}
	}
	if (pointer[0] != 'e' && pointer[0] != 'e')
		Hotkey();
}