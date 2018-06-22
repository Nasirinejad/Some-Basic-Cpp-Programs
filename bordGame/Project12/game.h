#pragma once
//global structure
struct bord
{
	char **Ary;
	int width, height;
};
struct player
{
	int coines = 0;
	char name[256];
	_COORD pos;

};
class game{
protected:
	int
		gamestart = 0,
		totalplayers,
		playerround = 0,
		totalstars,
		ofstars = 0,
		totalwals;
	bord Br;
	player *players;
	void newgame();
	bool isplayer(char);
	void shiftup();
	void shiftdown();
	void shiftleft();
	void shiftright();
	void nextround();
	int validtotals(int);
	bool winner();
	void closegame();
	void savegame(char[]);
	bool loadgame(char[]);
	void fillrand();
	void randbord();
public:
	game(){}
	~game(){}
};
void game::newgame(){
	Br.Ary = new char*[Br.height];
	for (int i = 0; i < Br.height; i++)
		Br.Ary[i] = new char[Br.width];
	players = new player[totalplayers];
	if (!players || !Br.Ary){
		cout << "Memorise Erorr!!\n";
		system("pause");
		exit(0);
	}
	for (int i = 0; i<Br.height; i++)
	for (int j = 0; j<Br.width; j++)
		Br.Ary[i][j] = '.';
	ofstars = 0;
}
void game::closegame(){
	gamestart = 0;
	totalplayers = 0;
	playerround = 0;
	totalstars = 0;
	ofstars = 0;
	totalwals = 0;
	Br.height = 0;
	Br.width = 0;
}
void game::nextround(){
	playerround++;
	if (playerround == totalplayers)
		playerround = 0;
}
bool game::isplayer(char m){
	if (m == '1' || m == '2' || m == '3' || m == '4' || m == '5')
		return true;
	return false;
}
void game::shiftup(){
	player p = players[playerround];
	int i;
	for (i = p.pos.Y; i > 0; i--){
		if (Br.Ary[i - 1][p.pos.X] == 'w')
			break;
		if (isplayer(Br.Ary[i - 1][p.pos.X])){
			if (i > 2 && (Br.Ary[i - 2][p.pos.X] == 'w' || isplayer(Br.Ary[i - 2][p.pos.X])))
				break;
			if (i-1 == 0)
				break;
		}
		if (Br.Ary[i - 1][p.pos.X] == 's'){
			Br.Ary[i - 1][p.pos.X] = '.';
			p.coines++;
			ofstars++;
		}
	}
	Br.Ary[p.pos.Y][p.pos.X] = '.';
	p.pos.Y = i;
	Br.Ary[p.pos.Y][p.pos.X] = playerround + 49;
	players[playerround] = p;
	nextround();
}
void game::shiftdown(){
	player p = players[playerround];
	int i;
	for (i = p.pos.Y; i < Br.height-1; i++){
		if (Br.Ary[i + 1][p.pos.X] == 'w')
			break;
		if (isplayer(Br.Ary[i + 1][p.pos.X])){
			if (i < Br.height - 2 && (Br.Ary[i + 2][p.pos.X] == 'w' || isplayer(Br.Ary[i + 2][p.pos.X])))
				break;
			if (i + 2 == Br.height)
				break;
		}
		if (Br.Ary[i + 1][p.pos.X] == 's'){
			Br.Ary[i + 1][p.pos.X] = '.';
			p.coines++;
			ofstars++;
		}
	}
	Br.Ary[p.pos.Y][p.pos.X] = '.';
	p.pos.Y = i;
	Br.Ary[p.pos.Y][p.pos.X] = playerround + 49;
	players[playerround] = p;
	nextround();
}
void game::shiftleft(){
	player p = players[playerround];
	int i;
	for (i = p.pos.X; i > 0; i--){
		if (Br.Ary[p.pos.Y][i - 1] == 'w')
			break;
		if (isplayer(Br.Ary[p.pos.Y][i - 1])){
			if (i - 1 == 0)
				break;
			if (i > 2 && (Br.Ary[p.pos.Y][i - 2] == 'w' || isplayer(Br.Ary[p.pos.Y][i - 2])))
				break;
		}
		if (Br.Ary[p.pos.Y][i - 1] == 's'){
			Br.Ary[p.pos.Y][i - 1] = '.';
			p.coines++;
			ofstars++;
		}
	}
	Br.Ary[p.pos.Y][p.pos.X] = '.';
	p.pos.X = i;
	Br.Ary[p.pos.Y][p.pos.X] = playerround + 49;
	players[playerround] = p;
	nextround();
}
void game::shiftright(){
	player p = players[playerround];
	int i;
	for (i = p.pos.X; i < Br.width-1; i++){
		if (Br.Ary[p.pos.Y][i + 1] == 'w')
			break;
		if (isplayer(Br.Ary[p.pos.Y][i + 1])){
			if (i < Br.width - 2 && (Br.Ary[p.pos.Y][i + 2] == 'w' || isplayer(Br.Ary[p.pos.Y][i - 2])))
				break;
			if (i + 2 == Br.width)
				break;
		}
		if (Br.Ary[p.pos.Y][i + 1] == 's'){
			Br.Ary[p.pos.Y][i + 1] = '.';
			p.coines++;
			ofstars++;
		}
	}
	Br.Ary[p.pos.Y][p.pos.X] = '.';
	p.pos.X = i;
	Br.Ary[p.pos.Y][p.pos.X] = playerround+49;
	players[playerround] = p;
	nextround();
}
int game::validtotals(int a){
	int min, max, k;
	min = (Br.width > Br.height) ? Br.height : Br.width;
	max = (Br.width < Br.height) ? Br.height : Br.width;
	switch (a)
	{
	case 1://Max Player
		k = min / 2;
		if (k>5)k = 5;
		return k;
		break;
	case 2://max stars or walls
		k = min * max / 2 - totalplayers - 1;
		return k;
		break;
	case 3://min walls
		k = min / 2;
		return k;
		break;
	default:
		break;
	}
}
bool game::winner(){
	if (ofstars == totalstars){
		player tpl;
		for (int i = 0; i < totalplayers; i++){
			for (int j = i + 1; j < totalplayers; j++){
				if (players[j].coines > players[i].coines){
					tpl = players[i];
					players[i] = players[j];
					players[j] = tpl;
				}
			}
		}
		return 1;
	}
	return 0;
}
void game::savegame(char name[]){
	ofstream in_file;
	in_file.open(name);
	in_file << gamestart << " " << totalplayers << " " << playerround << " " << totalstars << " " << ofstars << " " << totalwals << endl;
	in_file << Br.height << " " << Br.width << endl;
	for (int i = 0; i < Br.height; i++){
		for (int j = 0; j < Br.width; j++)
			in_file << Br.Ary[i][j] << " ";
		in_file << endl;
	}
	for (int i = 0; i < totalplayers; i++)
		in_file << players[i].coines << " " << players[i].name << " " << players[i].pos.X << " " << players[i].pos.Y << " " << endl;
	in_file.close();
}
bool game::loadgame(char name[]){
	ifstream in_file;
	in_file.open(name);
	if (!in_file.is_open())
		return false;
	in_file >> gamestart >> totalplayers >> playerround >> totalstars >> ofstars >> totalwals;
	in_file >> Br.height >> Br.width;
	for (int i = 0; i<Br.height; i++)
	for (int j = 0; j<Br.width; j++)
		in_file >> Br.Ary[i][j];
	for (int i = 0; i < totalplayers; i++)
		in_file >> players[i].coines >> players[i].name >> players[i].pos.X >> players[i].pos.Y;
	in_file.close();
	return 1;
}
void game::randbord(){
	Br.height = mt_rand(totalplayers * 2, 20);
	Br.width = mt_rand(totalplayers * 2, 13);
}
void game::fillrand(){
	int x, y, min, max, k;
	totalstars = mt_rand(2, validtotals(2));
	totalwals = validtotals(3)+1;
	savegame("logs");
	for (int i = 0; i < totalstars; i++){
		do{
			x = mt_rand(0, Br.width);
			y = mt_rand(0, Br.height);
		} while (Br.Ary[y][x] != '.');
		Br.Ary[y][x] = 's';
	}
	for (int i = 0; i < totalwals; i++){
		do{
			x = mt_rand(0, Br.width);
			y = mt_rand(0, Br.height);
		} while (Br.Ary[y][x] != '.');
		Br.Ary[y][x] = 'w';
	}
	for (int i = 0; i < totalplayers; i++){
		do{
			x = mt_rand(0, Br.width);
			y = mt_rand(0, Br.height);
		} while (Br.Ary[y][x] != '.');
		Br.Ary[y][x] = i + 49;
		players[i].pos.X = x;
		players[i].pos.Y = y;
	}
	game::gamestart = 1;
}