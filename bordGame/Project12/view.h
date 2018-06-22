#pragma once
struct key{
	bool type = 0;
	short int intval = 0;
	char character = 0;
};
class view : protected game{
private:
	_COORD cursor;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int menuitem = 0;
	void setColor(char, char);
	void Locate(int, int, bool);
	key eventkey();
	bool gameaction(int);
	void cell(int, char, char, char);
	void playercolor(int);
	void emoji(int, char);
	void ditals();
	void freebord(int, int);
	void drow(bord);
	void designbord(int, int, int);
	void getplayers();
	void li(char[], int, int);
	bool selector(int);
	void inputbox(char[], char[], int);
	void inputboxi(char[], int&, int, int, int);
	void gamemenu();
	void mainmenu();
	void creatmap();
	void escmenu();
	void playgame();
	void mapmenu();
	void winnerdetails();
	void savegame();
	void savemap();
	void loadgame();
	void loadmap();
	void randommap();
	void about();
public:
	view();
	void start();
	static void quit();
	~view();
};
view::view(){
	cursor.X = 0;
	cursor.Y = 0;
}
view::~view(){}

void view::setColor(char c, char b = 0){
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int f;
	switch (b) {
	case 'B':
	case 'b':
		f = 144;
		break;
	case 'G':
	case 'g':
		f = 160;
		break;
	case 'R':
	case 'r':
		f = 192;
		break;
	case 'W':
	case 'w':
		f = 240;
		break;
	default:
		f = b;
		break;
	}
	switch (c) {
	case 'B':
	case 'b':
		SetConsoleTextAttribute(hOut, f + 9);
		break;
	case 'G':
	case 'g':
		SetConsoleTextAttribute(hOut, f + 10);
		break;
	case 'R':
	case 'r':
		SetConsoleTextAttribute(hOut, f + 12);
		break;
	case 'W':
	case 'w':
		SetConsoleTextAttribute(hOut, f + 15);
		break;
	default:
		f += c;
		SetConsoleTextAttribute(hOut, f);
		break;
	}
}
void view::Locate(int x, int y, bool up=true){
	if (up){
		cursor.X += x;
		cursor.Y += y;
	}
	else{
		cursor.X = x;
		cursor.Y = y;
	}
	SetConsoleCursorPosition(hOut, cursor);
}
key view::eventkey(){
	key r;
	int a;
	r.character = r.intval = a = _getch();
	if (a == 224 || a == 27 || a == 13 || a == 9 || a == 8)
		r.type = 1;
	else
		r.type = 0;
	return r;
}
bool view::gameaction(int a){
	bool result = 0;
	switch (a)
	{
	default:
		break;
	}
	return a;
}
void view::li(char txt[], int width, int dly = 0){
	int ln = strlen(txt),
		l = (width - ln) / 2,
		i = 0;

	for (; i < l; i++)
	{
		cout << " ";
		if (dly > 0)
			Sleep(dly);
	}
	if (dly > 0){
		for (; i < ln+l; i++)
		{
			cout << txt[i-l];
			Sleep(dly);
		}
	}
	else{
		cout << txt;
		i += ln;
	}
	for (; i < width; i++)
	{
		cout << " ";
		if (dly > 0)
			Sleep(dly);
	}
}
void view::inputbox(char txt[], char val[], int t){
	key k;
	int i = 0, l = (strlen(txt) > t) ? strlen(txt) : t;
	li(txt, l + 4);
	Locate(0, 1);
	li(" ", l + 4);
	Locate(0, 1);
	li(" ", l + 4);
	Locate(0, -1);
	cout << "  ";
	while (k.intval != 13){
		if (k.intval == 224)
			k = eventkey();
		k = eventkey();
		if (i < t-1 && k.type == 0){
			val[i] = k.character;
			cout << k.character;
			i++;
		}
		if (k.intval == 8){
			val[i] = '\0';
			i--;
			cout << k.character << ' ' << k.character;
		}
	}
	val[i] = '\0';
	Locate(0, 3);
}
void view::inputboxi(char txt[], int &val, int t, int min, int max){
	key k;
	int b, l = (strlen(txt) > t) ? strlen(txt) : t;
	li(txt, l + 4);
	Locate(0, 1);
	li(" ", l + 4);
	Locate(0, 1);
	li(" ", l + 4);
	Locate(0, -1);
	val = min;
	cout << "  " << val;
	while (1){
		k = eventkey();
		b = val * 10 + (k.intval - 48);
		if (k.intval > 47 && k.intval < 58 && b <= max)
			val = b;
		if (k.intval == 8){
			val /= 10;
			cout << k.character << " " << k.character;
		}
		if (k.intval == 244)
			k = eventkey();
		if (k.intval == 72 && val < max)
			val++;
		if (k.intval == 80 && val > min)
			val--;
		Locate(0, 0);
		cout << "  " << val << " ";
		if (k.intval == 13){
			if (val > max || val < min){
				Locate(0, 1);
				li("Invalid Number!", l + 4);
				Locate(0, -1);
			}
			else{
				return;
			}
		}
	}
	Locate(0, 3);
}
bool view::selector(int total){
	key k;
	k = eventkey();
	if (k.type){
		if (k.intval == 13)
			return 1;
		k = eventkey();
		switch (k.intval)
		{
		case 72:
			menuitem--;
			break;
		case 80:
			menuitem++;
			break;
		}
		if (menuitem < 1)menuitem = total;
		else if (menuitem > total)menuitem = 1;
		return 0;
	}
}
void view::cell(int pos, char txt, char bc = 7, char tc = 'b'){
	setColor(bc);
	char y = 218,
		l = 196,
		t = 194,
		d = 195,
		c = 197,
		r = 180,
		v = 191,
		n = 217,
		s = 193,
		f = 192,
		w = 179;
	switch (pos){
	case 1:
		cout << y << l << l << t;
		Locate(0, 1);
		cout << w << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << d << l << l << c;
		Locate(4, -2);
		break;
	case 2:
		cout << l << l << t;
		Locate(0, 1);
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << c;
		Locate(3, -2);
		break;
	case 3:
		cout << l << l << v;
		Locate(0, 1);
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << r;
		Locate(0, 3, 0);
		break;
	case 4:
		cout << w << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << d << l << l << c;
		Locate(4, -1);
		break;
	case 5:
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << c;
		Locate(3, -1);
		break;
	case 6:
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << r;
		Locate(-cursor.X, 1);
		break;
	case 7:
		cout << w << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << f << l << l << s;
		Locate(4, -1);
		break;
	case 8:
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << s;
		Locate(3, -1);
		break;
	case 9:
		cout << " "; setColor(tc); cout << txt; setColor(bc); cout << w;
		Locate(0, 1);
		cout << l << l << n << endl;
		break;
	}
}
void view::playercolor(int a){
	switch (a-1)
	{
	case 0:
		setColor(100, 37);
		break;
	case 1:
		setColor(100, 40);
		break;
	case 2:
		setColor(100, 38);
		break;
	case 3:
		setColor(100, 39);
		break;
	case 4:
		setColor(100, 41);
		break;
	}
}
void view::emoji(int i, char t){
	switch (t)
	{
	case '1':
		cell(i, 2);
		break;
	case '2':
		cell(i, 2, 7, 'R');
		break;
	case '3':
		cell(i, 2, 7, 'G');
		break;
	case '4':
		cell(i, 2, 7, 11);
		break;
	case '5':
		cell(i, 2, 7, 13);
		break;
	case 's':
		cell(i, 5, 7, 14);
		break;
	case 'w':
		cell(i, 219, 255, 255);
		break;
	case '.':
		cell(i, ' ');
		break;
	default:
		cell(i, '?', 7, 'w');
		break;
	}
}
void view::ditals(){
	char c[15];
	int a[1];
	int i = game::playerround%game::totalplayers;
	Locate(50, 1, 0);
	setColor(71);
	li("Game Stats", 15);
	Locate(0, 1);
	li(" ", 15);
	Locate(0, 1);
	switch (i)
	{
	case 0:
		setColor(100, 37);
		a[0] = game::players[0].coines;
		break;
	case 1:
		setColor(100, 40);
		a[0] = game::players[1].coines;
		break;
	case 2:
		setColor(100, 38);
		a[0] = game::players[2].coines;
		break;
	case 3:
		setColor(100, 39);
		a[0] = game::players[3].coines;
		break;
	case 4:
		setColor(100, 41);
		a[0] = game::players[4].coines;
		break;
	}
	c[0] = '\0';
	strcatint(c, a);
	li("Player:", 16);
	Locate(0, 1);
	li(game::players[i].name, 16);
	Locate(0, 1);
	li(" ", 16);
	Locate(0, 1);
	li("Total stars:", 16);
	Locate(0, 1);
	li(c, 16);
	Locate(0, 1);
	li(" ", 16);
	setColor(137);
	Locate(0, 1);
	li("Total map stars:", 16);
	Locate(0, 1);
	a[0] = game::totalstars - game::ofstars;
	c[0] = '\0';
	strcatint(c, a);
	li(c, 16);
	Locate(0, 1);
	li("Total All stars:", 16);
	Locate(0, 1);
	a[0] = game::totalstars;
	c[0] = '\0';
	strcatint(c, a);
	li(c, 16);
	Locate(0, 1);
	li(" ", 16);
}
void view::freebord(int x, int y){
	for (int i = 0; i < y; i++){
		for (int j = 0; j < x; j++){
			if (i == 0 && j == 0){
				cell(1, ' ');
			}else
			if (i == 0 && j < x-1){
				cell(2, ' ');
			}
			else
			if (i == 0 && j == x-1){
				cell(3, ' ');
			}
			else
			if (i < y-1 && j == 0){
				cell(4, ' ');
			}
			else
			if (i < y - 1 && j < x - 1){
				cell(5, ' ');
			}
			else
			if (i < y - 1 && j == x - 1){
				cell(6, ' ');
			}
			else
			if (i == y - 1 && j == 0){
				cell(7, ' ');
			}
			else
			if (i == y - 1 && j < x - 1){
				cell(8, ' ');
			}
		}
	}
	cell(9, ' ');
}
void view::drow(bord cl){
	for (int i = 0; i < cl.height; i++){
		for (int j = 0; j < cl.width; j++){
			if (i == 0 && j == 0){
				emoji(1, cl.Ary[i][j]);
			}
			else
			if (i == 0 && j < cl.width - 1){
				emoji(2, cl.Ary[i][j]);
			}
			else
			if (i == 0 && j == cl.width - 1){
				emoji(3, cl.Ary[i][j]);
			}
			else
			if (i < cl.height - 1 && j == 0){
				emoji(4, cl.Ary[i][j]);
			}
			else
			if (i < cl.height - 1 && j < cl.width - 1){
				emoji(5, cl.Ary[i][j]);
			}
			else
			if (i < cl.height - 1 && j == cl.width - 1){
				emoji(6, cl.Ary[i][j]);
			}
			else
			if (i == cl.height - 1 && j == 0){
				emoji(7, cl.Ary[i][j]);
			}
			else
			if (i == cl.height - 1 && j < cl.width - 1){
				emoji(8, cl.Ary[i][j]);
			}
			else{
				emoji(9, cl.Ary[i][j]);
			}
		}
	}
	ditals();
}
void view::mainmenu(){
	setColor(7);
	system("cls");
	Locate(30, 0, 0);
	(menuitem == 1) ? setColor(100, 76) : setColor(100, 28);
	li("New Game", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 2) ? setColor(100, 76) : setColor(100, 28);
	li("Load Game", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 3) ? setColor(100, 76) : setColor(100, 28);
	li("About", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 4) ? setColor(100, 76) : setColor(100, 28);
	li("Exit", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	if (selector(4)){
		switch (menuitem)
		{
		case 1:
			gamemenu();
			break;
		case 2:
			loadgame();
		case 3:
			about();
		case 4:
			exit(0);
			break;
		case 0:
			mainmenu();
			break;
		}
	}
	mainmenu();
}
void view::gamemenu(){
	setColor(7);
	system("cls");
	Locate(30, 0, 0);
	(menuitem == 1) ? setColor(100, 76) : setColor(100, 28);
	li("Creat Map", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 2) ? setColor(100, 76) : setColor(100, 28);
	li("Load Map", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 3) ? setColor(100, 76) : setColor(100, 28);
	li("Random Map", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	(menuitem == 4) ? setColor(100, 76) : setColor(100, 28);
	li("Back", 18);
	Locate(0, 1);
	li(" ________________ ", 18);
	Locate(0, 1);
	if (selector(4)){
		switch (menuitem)
		{
		case 1:
			creatmap();
			break;
		case 2:
			loadgame();
			break;
		case 3:
			randommap();
			break;
		case 4:
			mainmenu();
			break;
		}
	}
	else
		gamemenu();
}
void view::creatmap(){
	char txt[100];
	int a[10];
	setColor(7);
	system("cls");
	Locate(30, 0, 0);
	setColor(30);
	li("Detailes of Map:", 26);
	Locate(0, 1);
	li(" ", 26);
	Locate(0, 2);
	setColor(47);
	li("Enter Width of Bord:", 26);
	Locate(0, 1);
	inputboxi("betwin 4 to 12:", game::Br.width, 22, 4, 12);
	Locate(0, 2);
	li("Enter Height of Bord:", 26);
	Locate(0, 1);
	inputboxi("betwin 4 to 20", game::Br.height, 22, 4, 20);
	Locate(0, 3);

	li("Enter Total Players:", 26);
	Locate(0, 1);
	a[0] = validtotals(1);
	strcpy_s(txt, "betwin 2 to ");
	strcatint(txt, a);
	inputboxi(txt, game::totalplayers, 22, 2, a[0]);
	Locate(0, 3);

	li("Enter Total Stars:", 26);
	Locate(0, 1);
	a[0] = validtotals(2);
	strcpy_s(txt, "betwin 1 to ");
	strcatint(txt, a);
	inputboxi(txt, game::totalstars, 22, 1, a[0]);
	Locate(0, 3);

	li("Enter Total Walls:", 26);
	Locate(0, 1);
	a[0] = a[1] = validtotals(3);
	strcpy_s(txt, "betwin ");
	strcatint(txt, a);
	a[0] = validtotals(2);
	strcat_s(txt, " to ");
	strcatint(txt, a);
	inputboxi(txt, game::totalwals, 22, a[1], a[0]);
	Locate(0, 3);
	
	game::newgame();
	game::gamestart = 0;
	getplayers();
	designbord(0, 0, 0);
}
void view::getplayers(){
	char txt[100];
	int i[1];
	setColor(7);
	system("cls");
	Locate(30, 0, 0);
	setColor(30);
	li("Detailes of Players:", 26);
	Locate(0, 1);
	li(" ", 26);
	Locate(0, 2);
	setColor(47);
	for (i[0] = 1; i[0] <= game::totalplayers; i[0]++){
		playercolor(i[0]);
		strcpy_s(txt, "Enter Name Player ");
		strcatint(txt, i);
		inputbox(txt, game::players[i[0]-1].name, 22);
		Locate(0, 1);
	}
	setColor(7);
	system("cls");
}
void view::designbord(int x, int y, int a){
	Locate(0, 0, 0);
	if (a == game::totalwals + game::totalstars + game::totalplayers){
		mapmenu();
	}
	else{
		//show
		for (int i = 0; i < game::Br.height; i++){
			for (int j = 0; j < game::Br.width; j++){
				if (i == 0 && j == 0){
					if (i == y && j == x)
						cell(1, 219, 7, 'g');
					else
						emoji(1, game::Br.Ary[i][j]);
				}
				else
				if (i == 0 && j < game::Br.width - 1){
					if (i == y && j == x)
						cell(2, 219, 7, 'g');
					else
						emoji(2, game::Br.Ary[i][j]);
				}
				else
				if (i == 0 && j == game::Br.width - 1){
					if (i == y && j == x)
						cell(3, 219, 7, 'g');
					else
						emoji(3, game::Br.Ary[i][j]);
				}
				else
				if (i < game::Br.height - 1 && j == 0){
					if (i == y && j == x)
						cell(4, 219, 7, 'g');
					else
						emoji(4, game::Br.Ary[i][j]);
				}
				else
				if (i < game::Br.height - 1 && j < game::Br.width - 1){
					if (i == y && j == x)
						cell(5, 219, 7, 'g');
					else
						emoji(5, game::Br.Ary[i][j]);
				}
				else
				if (i < game::Br.height - 1 && j == game::Br.width - 1){
					if (i == y && j == x)
						cell(6, 219, 7, 'g');
					else
						emoji(6, game::Br.Ary[i][j]);
				}
				else
				if (i == game::Br.height - 1 && j == 0){
					if (i == y && j == x)
						cell(7, 219, 7, 'g');
					else
						emoji(7, game::Br.Ary[i][j]);
				}
				else
				if (i == game::Br.height - 1 && j < game::Br.width - 1){
					if (i == y && j == x)
						cell(8, 219, 7, 'g');
					else
						emoji(8, game::Br.Ary[i][j]);
				}
				else{
					if (i == y && j == x)
						cell(9, 219, 7, 'g');
					else
						emoji(9, game::Br.Ary[i][j]);
				}
			}
		}
		//details
		char c, txt[100];
		Locate(50, 1, 0);
		setColor(71);
		li("Map Stats", 25);
		Locate(0, 1);
		li(" ", 15);
		Locate(0, 1);
		if (a < game::totalplayers){
			playercolor(a+1);
			strcpy_s(txt, "Position Player ");
			strcat_s(txt, game::players[a].name);
			li(txt, 25);
			Locate(0, 1);
		}
		else
		if (a < game::totalstars + game::totalplayers){
			li("Position Stars", 25);
			Locate(0, 1);
			txt[0] = '\0';
			int b[1];
			b[0] = game::totalstars - a + game::totalplayers;
			strcatint(txt, b);
			li(txt, 25);
		}
		else
		if (a < game::totalwals + game::totalstars + game::totalplayers){
			li("Position Walls", 25);
			Locate(0, 1);
			txt[0] = '\0';
			int b[1];
			b[0] = game::totalwals + game::totalstars + game::totalplayers - a;
			strcatint(txt, b);
			li(txt, 25);
		}
		// event
		key k = eventkey();
		if (k.type){
			if (k.intval == 13 && game::Br.Ary[y][x] == '.'){
				if (a < game::totalplayers){
					game::Br.Ary[y][x] = a + 49;
					game::players[a].pos.X = x;
					game::players[a].pos.Y = y;
				}
				else
				if (a < game::totalstars + game::totalplayers){
					game::Br.Ary[y][x] = 's';
					game::players[a].pos.X = x;
					game::players[a].pos.Y = y;
				}
				else
				if (a < game::totalwals + game::totalstars + game::totalplayers){
					game::Br.Ary[y][x] = 'w';
					game::players[a].pos.X = x;
					game::players[a].pos.Y = y;
				}
				a++;
			}
			else{
				k = eventkey();
				switch (k.intval)
				{
				case 72:
					if (y>0)
					y--;
					break;
				case 80:
					if (y<game::Br.height-1)
					y++;
					break;
				case 75:
					if (x>0)
					x--;
					break;
				case 77:
					if (x<game::Br.width-1)
					x++;
					break;
				}
			}
		}
		designbord(x, y, a);
	}
}
void view::mapmenu(){
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Map is ready.", 25);
	Locate(0, 1);
	(menuitem == 1) ? setColor(100, 76) : setColor(100, 28);
	li("Play Game", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	(menuitem == 2) ? setColor(100, 76) : setColor(100, 28);
	li("Save Map", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	if (selector(2)){
		switch (menuitem)
		{
		case 1:
			game::gamestart = 1;
			playgame();
			break;
		case 2:
			savemap();
			break;
		}
	}
	else
		mapmenu();
}
void view::playgame(){
	Locate(0, 0, 0);
	setColor(7);
	system("cls");
	if (game::gamestart == 1 && game::winner()){
		winnerdetails();
	}
	else if(game::gamestart == 1){
		drow(game::Br);
		bool dr = true;
		while (dr)
		{
			key k = eventkey();
			if (k.type){
				if (k.intval == 27){
					escmenu();
					dr = 0;
				}
				else{
					k = eventkey();
					switch (k.intval)
					{
					case 72:
						game::shiftup();
						dr = 0;
						break;
					case 80:
						game::shiftdown();
						dr = 0;
						break;
					case 75:
						game::shiftleft();
						dr = 0;
						break;
					case 77:
						game::shiftright();
						dr = 0;
						break;
					}
				}
			}
		}
		playgame();
	}
}
void view::escmenu(){
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Pause...", 25);
	Locate(0, 1);
	(menuitem == 1) ? setColor(100, 76) : setColor(100, 28);
	li("Continue Game", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	(menuitem == 2) ? setColor(100, 76) : setColor(100, 28);
	li("Finish Game", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	(menuitem == 3) ? setColor(100, 76) : setColor(100, 28);
	li("Save Game", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	(menuitem == 4) ? setColor(100, 76) : setColor(100, 28);
	li("Quit Game", 25);
	Locate(0, 1);
	li(" ________________ ", 25);
	Locate(0, 1);
	if (selector(4)){
		switch (menuitem)
		{
		case 1:
			cout << "Loading...";
			break;
		case 2:
			ofstars = totalstars;
			game::winner();
			winnerdetails();
			break;
		case 3:
			savegame();
			break;
		case 4:
			closegame();
			break;
		}
	}
	else
		escmenu();
}
void view::winnerdetails(){
	char c[512];
	system("cls");
	Locate(25, 0, 0);
	setColor(100, 12);
	li("Game Finished", 30);
	Locate(0, 1);
	li(" ", 30);
	Locate(0, 1);
	for (int i = 0; i < game::totalplayers; i++){
		strcpy_s(c, game::players[i].name);
		if (game::players[i].coines == game::players[0].coines)
			strcat_s(c, " Win");
		li(c, 30);
		Locate(0, 1);
	}
	_getch();
	game::closegame();
}
void view::start(){
	mainmenu();
}
void view::savegame(){
	char name[256];
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Save Game", 24);
	Locate(0, 1);
	setColor(47);
	inputbox("File Name:", name, 20);
	strcat_s(name, "_game.txt");
	game::savegame(name);
	li("Saved!", 24);
	Locate(0, 1);
	_getch();
	escmenu();
}
void view::savemap(){
	char name[256];
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Save Map", 24);
	Locate(0, 1);
	setColor(47);
	inputbox("File Name:", name, 20);
	strcat_s(name, "_map.txt");
	game::savegame(name);
	li("Saved!", 24);
	Locate(0, 1);
	_getch();
	mapmenu();
}
void view::loadgame(){
	char name[256];
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Load Game", 24);
	Locate(0, 1);
	setColor(47);
	inputbox("File Name:", name, 20);
	strcat_s(name, "_game.txt");
	if (game::loadgame(name))
		playgame();
	else{
		Locate(0, 1);
		li("Loading Faild!", 24);
		_getch();
	}
}
void view::loadmap(){
	char name[256];
	Locate(0, 0, 0);
	setColor(7);
	cout << endl << endl;
	system("cls");
	setColor(47);
	Locate(25, 0, 0);
	li("Load Map", 24);
	Locate(0, 1);
	setColor(47);
	inputbox("File Name:", name, 20);
	strcat_s(name, "_map.txt");
	if (game::loadgame(name))
		playgame();
	else{
		Locate(0, 1);
		li("Loading Faild!", 24);
		_getch();
	}
}
void view::randommap(){
	char txt[100];
	int a[10];
	setColor(7);
	system("cls");
	Locate(30, 0, 0);
	setColor(30);
	li("Detailes of Map:", 26);
	Locate(0, 1);
	li(" ", 26);
	Locate(0, 2);
	setColor(47);
	li("Enter Total Players:", 26);
	Locate(0, 1);
	strcpy_s(txt, "betwin 2 to 5");
	inputboxi(txt, game::totalplayers, 22, 2, 5);
	Locate(0, 3);
	game::randbord();
	game::newgame();
	getplayers();
	li("Please with this may take long...", 100);
	game::fillrand();
	playgame();
}
void view::about(){
	Locate(0, 0, 0);
	setColor(0, 'W');
	system("cls");
	setColor(7, 'W');
	cout << "R";
	setColor(0, 'W');
	li("Pro Programming of C++", 30, 20);
	Sleep(1000);
	Locate(0, 1);
	setColor(7, 'W');
	cout << "A";
	setColor(0, 'W');
	li("Mahdi Nasirinejad", 30, 20);
	Locate(0, 1);
	setColor(0, 'W');
	Sleep(1000);
	setColor(7, 'W');
	cout << "Y";
	setColor(0, 'W');
	li("June, 2016", 30, 20);
	Locate(0, 1);
	setColor(7, 'W');
	cout << "A";
	setColor(0, 'W');
	li("Thank's a lot", 30);
	Locate(0, 1);
	setColor(9, 'W');
	li("Press any key to back...", 35, 10);
	_getch();
	mainmenu();
}