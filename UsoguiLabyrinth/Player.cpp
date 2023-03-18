#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <conio.h>
#include <cmath>

#include "Player.h"
#include "Mode2.h"
using std::cout;
using std::cin;
using std::endl;
using std::abs;

#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define HIT_WALL true
#define WON false
#define HIT_WALL2 -2
#define WON2 -1
#define LOST -3
#define DONT_SHOW_WALLS false
#define SHOW_WALLS true
#define PLAYER_SYM 'O'
#define PLAYER_RIGHT '>'
#define PLAYER_LEFT '<'
#define PLAYER_UP '^'
#define PLAYER_DOWN 'v'
#define PLAYER_LIVES 2
#define _VWALL_ '|'
#define _HWALL_ '='
#define _JOINT_ '+'
#define _ROOM_ ' '

#define DEBUG(x, y) cout << x << y << endl; (_getch() != char(13) ? _getch() : 1);
#define PAUSE if (int c = _getch() != char(13)) {c = _getch();}

Player::Player(string Name) : symbol(PLAYER_SYM), Name(Name){

}

Player::Player(int id) : id(id), symbol(PLAYER_SYM) {

}

Player::Player() : symbol(PLAYER_SYM) {

}

bool Player::Move() {
	int c, ex;

	this->Own.alter(this->pos, this->symbol);
	this->Own.printLabyrinth(this->Name, false);

	c = _getch();

	if (c && c != 224)
		return false;

	ex = _getch();

	while (!this->Own.isClosed(pos, ex)) {
		switch (ex)
		{
		case KEY_UP:
			this->pos.first -= 1;
			break;
		case KEY_DOWN:
			this->pos.first += 1;
			break;
		case KEY_LEFT:
			this->pos.second -= 1;
			break;
		case KEY_RIGHT:
			this->pos.second += 1;
			break;
		}


		this->Own.alter(this->pos, this->symbol);
		system("cls");
		this->Own.printLabyrinth(this->Name, DONT_SHOW_WALLS);

		if (this->pos == this->Own.getFinish())
			return WON;

		ex = _getch();

		if (c && c != 224)
			return false;

		ex = _getch();
	}
	return HIT_WALL;
}

string Player::getName() const {
	return this->Name;
}

char Player::getSymbol() const {
	return this->symbol;
}

void Player::setPos(coordinate p) {
	this->pos = p;
}

coordinate Player::getPos() const {
	return this->pos;
}

int Player::getID() const {
	return this->id;
}

void Mode1Player::BuildLabyrinth() {
	char RowColumn[3] = { ' ', ' '}, dir;
	//char RowColumn2[3] = { ' ', ' ' };
	int c;
	coordinate start, finish;

	do {
		this->Own.printLabyrinth(this->Name, SHOW_WALLS);
		cout << endl << "Build your labyrinth:" << endl;
		while ((RowColumn[0] < 'a' || RowColumn[0] > 'f') || (RowColumn[1] < '1' || RowColumn[1] > '6')) {
			cout << "Starting point: ";
			scanf_s(" %2s", RowColumn, 3);
			while ((c = fgetc(stdin)) != '\n' && c != EOF);
		}
		start = pair<int, int>(RowColumn[0] - 'a', RowColumn[1] - '1');
		RowColumn[0] = ' '; RowColumn[1] = ' ';
		while ((RowColumn[0] < 'a' || RowColumn[0] > 'f') || (RowColumn[1] < '1' || RowColumn[1] > '6')) {
			cout << "Finishing point: " << std::flush;
			scanf_s("%2s", RowColumn, 3);
			while ((c = fgetc(stdin)) != '\n' && c != EOF);
		}
		finish = pair<int, int>(RowColumn[0] - 'a', RowColumn[1] - '1');

		//this->Own.alter(start, 'S');
		this->Own.setStart(start);
		//this->Own.alter(finish, 'F');
		this->Own.setFinish(finish);

		/*RowColumn[0] = ' '; RowColumn[1] = ' ';
		RowColumn2[0] = ' '; RowColumn2[1] = ' ';
		for (int i = 1; i <= 20 && (RowColumn[0] != '-' && RowColumn[1] != '1'); ++i) {
			system("cls");
			this->Own.printLabyrinth(this->Name, SHOW_WALLS);
			cout << endl << "Build your labyrinth:" << endl;
			while ((RowColumn[0] < 'a' || RowColumn[0] > 'f') || (RowColumn[1] < '1' || RowColumn[1] > '6')) {
				cout << "Add wall(" << i << "/20) between: ";
				scanf_s("%2s", RowColumn, 3);
				while ((c = fgetc(stdin)) != '\n' && c != EOF);
				if (RowColumn[0] == '-' && RowColumn[1] == '1') return;
			}
			while ((RowColumn2[0] < 'a' || RowColumn2[0] > 'f') || (RowColumn2[1] < '1' || RowColumn2[1] > '6')) {
				cout << "                    and: ";
				scanf_s("%2s", RowColumn2, 3);
				while ((c = fgetc(stdin)) != '\n' && c != EOF);
			}

			start = pair<int, int>(RowColumn[0] - 'a', RowColumn[1] - '1');
			finish = pair<int, int>(RowColumn2[0] - 'a', RowColumn2[1] - '1');
			//cout << start.first << start.second << endl;
			//cout << finish.first << finish.second << endl;
			//cin.get();
			if (abs((c = start.first - finish.first)) == 1) {
				this->Own.alter(start, (c == 1 ? 1 : 3));
			}
			else if (abs((c = start.second - finish.second)) == 1) {
				this->Own.alter(start, (c == 1 ? 4 : 2));
			}
			RowColumn[0] = ' '; RowColumn[1] = ' ';
			RowColumn2[0] = ' '; RowColumn2[1] = ' ';
		}
		*/

		RowColumn[0] = ' '; RowColumn[1] = ' ';
		for (int i = 1; i <= 20 && (RowColumn[0] != '-' && RowColumn[1] != '1'); ++i) {
			system("cls");
			this->Own.printLabyrinth(this->Name, SHOW_WALLS);
			cout << endl << "Build your labyrinth (Enter -1 to stop building):" << endl;
			while ((RowColumn[0] < 'a' || RowColumn[0] > 'f') || (RowColumn[1] < '1' || RowColumn[1] > '6')) {
				//cout << "Press -1 to stop building" << endl;
				cout << "Choose block to add wall around (" << i << "/20): ";
				scanf_s("%2s", RowColumn, 3);
				while ((c = fgetc(stdin)) != '\n' && c != EOF);
				if (RowColumn[0] == '-' && RowColumn[1] == '1') return;
			}
			cout << "Choose direction to add wall(w/a/s/d): ";
			cin >> dir;

			start = pair<int, int>(RowColumn[0] - 'a', RowColumn[1] - '1');
			switch (dir) {
			case KEY_UP:
				this->Own.BuildWall(start, 1);
				break;
			case KEY_LEFT:
				this->Own.BuildWall(start, 4);
				break;
			case KEY_DOWN:
				this->Own.BuildWall(start, 3);
				break;
			case KEY_RIGHT:
				this->Own.BuildWall(start, 2);
				break;
			default:
				--i;
				break;
			
			}

			RowColumn[0] = ' '; RowColumn[1] = ' ';
		}

		system("cls");
		this->Own.printLabyrinth(this->Name, SHOW_WALLS);
		cout << endl << "Finish labyrinth building?(y/n): ";
		cin >> RowColumn[0];
		if (RowColumn[0] == 'y')
			return;
		this->Own = Labyrinth();
		RowColumn[0] = ' ';
		RowColumn[1] = ' ';
		//RowColumn2[0] = ' ';
		//RowColumn2[1] = ' ';
		c = 0;
		start = coordinate();
		finish = coordinate();
		system("cls");
	} while (1);
}

bool Mode1Player::Move(Labyrinth& Other) {
	int c;

	Other.alter(this->pos, this->symbol);
	Other.printLabyrinth(this->Name, DONT_SHOW_WALLS);

	c = _getch();

	//if (c && c != 224) {
	//	cout << "[DEBUG]" << "exiting" << endl;
	//	cin.get();
	//	return false;
	//}

	while (!Other.isClosed(this->pos, c)) {
		//cout << "[DEBUG]" << c << endl;
		//cin.get();
		switch (c)
		{
		case KEY_UP:
			if (this->pos.first > 0) {
				Other.alter(this->pos, PLAYER_UP);
				this->pos.first -= 1;
			}
			//cout << "[DEBUG]" << this->pos.first << endl;
			//cin.get();
			break;
		case KEY_DOWN:
			if (this->pos.first < 5) {
				Other.alter(this->pos, PLAYER_DOWN);
				this->pos.first += 1;
			}
			break;
		case KEY_LEFT:
			if (this->pos.second > 0) {
				Other.alter(this->pos, PLAYER_LEFT);
				this->pos.second -= 1;
			}
			//cout << "[DEBUG]" << this->pos.second << endl;
			//cin.get();
			break;
		case KEY_RIGHT:
			if (this->pos.second < 5) {
				Other.alter(this->pos, PLAYER_RIGHT);
				this->pos.second += 1;
			}
			break;
		}


		Other.alter(this->pos, this->symbol);
		system("cls");
		Other.printLabyrinth(this->Name, DONT_SHOW_WALLS);

		if (this->pos == Other.getFinish()) {
			//cout << "[DEBUG]" << "Finished" << endl;
			//cin.get();
			return WON;
		}

		c = _getch();
	}

	//system("cls");
	//cout << "[DEBUG]" << "Hit wall: " << Other.getFinish().first << ' ' << Other.getFinish().second << endl;
	//cout << "[DEBUG]" << "Hit wall: " << this->pos.first << ' ' << this->pos.second << endl;
	//cin.get();
	return HIT_WALL;
}

Labyrinth& Player::getLabyrinth() {
	return this->Own;
}

//Mode1Player::Mode1Player() {
//	this->Other = nullptr;
//}

//void Mode1Player::setLabyrinth(Labyrinth& l) {
//	this->pos = l.getStart();
//	this->Other = &l;
//}

Mode2Player::Mode2Player() : points(0), lives(PLAYER_LIVES), dead(false), m2(nullptr) {

}

Mode2Player::Mode2Player(int id, Mode2 *mode) : points(0), lives(PLAYER_LIVES), dead(false), m2(mode) {
	this->id = id;
	this->symbol = PLAYER_SYM;
}

void Mode2Player::setPoints(int v) {
	this->points = v;
}
void Mode2Player::setName(string name) {
	this->Name = name;
}
int Mode2Player::getPoints() const {
	return this->points;
}
void Mode2Player::IncPoints(int value) {
	this->points += value;
}
void Mode2Player::DecPoints(int value) {
	this->points -= value;
}
int Mode2Player::LoseLife() {
	--(this->lives);
	if (!this->lives)
		this->dead = true;

	return this->lives;
}

Mode2Player* Mode2Player::MetSomeone(vector<Mode2Player>& v) {
	for (Mode2Player& p : v) {
		if (this->pos == p.getPos() && this->id != p.getID()) {
			system("cls");
			cout << "You've met Player: " << p.getName() << endl;
			PAUSE
			return &p;
		}
		//cout << "Player " << p.getID() << endl;
	}
	//if (int c = _getch() != char(13))
	//	c = _getch();
	return nullptr;
}

int Mode2Player::Bet(Mode2Player* p) {
	int bet, points = p->getPoints();

	system("cls");

	cout << "Your points: " << points << endl;
	cout << "How many points will you bet?: ";
	cin >> bet;
	while (bet > points) {
		system("cls");
		cout << "Your points: " << points << endl;
		cout << "INVALID ANSWER, CAN'T BET MORE POINTS THAN YOU HAVE" << endl;
		cout << "How many points you will bet?: ";
		cin >> bet;
	}
	//DEBUG("Dec ", "points")
	p->DecPoints(bet);
	//DEBUG("After Dec ", "points")
	return bet;
}

int Mode2Player::Battle(Mode2Player* p) {
	int bet1, bet2;

	bet1 = Bet(this);
	system("cls");
	//DEBUG("After Dec points", 2)
	cout << p->getName() << "'s turn" << endl;
	cout << "Press enter to contiue...";
	PAUSE
	bet2 = Bet(p);
	system("cls");

	switch (bet1 != bet2)
	{
	case true:
		switch (bet1 > bet2)
		{
		case true:
			// player 2 loses
			cout << "Player " << p->getName() << " lost battle" << endl;
			if (p->LoseLife() == 0) {
				m2->ConfirmDeath(p->getID());
				cout << "Player " << p->getName() << " lost the game" << endl;
			}
			cout << this->Name << "'s turn" << endl;
			cout << "Press enter to contiue...";
			PAUSE
			return this->id;
		default:
			// player 1 loses
			cout << "Player " << this->Name << " lost battle" << endl;
			if (this->LoseLife() == 0) {
				m2->ConfirmDeath(this->id);
				cout << "Player " << this->getName() << " lost the game" << endl;
			}
			cout << p->getName() << "'s turn" << endl;
			cout << "Press enter to contiue...";
			PAUSE
			return p->getID();
		}
	default:
		// draw
		cout << "Draw" << endl;
		cout << p->getName() << "'s turn" << endl;
		cout << "Press enter to contiue...";
		PAUSE
 		return p->getID();
		break;
	}
}

int Mode2Player::Move(vector<Mode2Player>& v, bool agro) {
	int c;
	Mode2Player* p;

	if (this->dead)
		return this->id + 1;

	this->Own.alter(this->pos, this->symbol);
	this->Own.printLabyrinth(this->Name, DONT_SHOW_WALLS);
	cout << "Your points: " << this->points;

	c = _getch();

	//if (c && c != 224) {
	//	cout << "[DEBUG]" << "exiting" << endl;
	//	cin.get();
	//	return false;
	//}

	while (!this->Own.isClosed(this->pos, c)) {
		//cout << "[DEBUG]" << c << endl;
		//cin.get();
		switch (c)
		{
		case KEY_UP:
			if (this->pos.first > 0) {
				this->Own.alter(this->pos, PLAYER_UP);
				this->pos.first -= 1;
			}
			//cout << "[DEBUG]" << this->pos.first << endl;
			//cin.get();
			break;
		case KEY_DOWN:
			if (this->pos.first < 5) {
				this->Own.alter(this->pos, PLAYER_DOWN);
				this->pos.first += 1;
			}
			break;
		case KEY_LEFT:
			if (this->pos.second > 0) {
				this->Own.alter(this->pos, PLAYER_LEFT);
				this->pos.second -= 1;
			}
			//cout << "[DEBUG]" << this->pos.second << endl;
			//cin.get();
			break;
		case KEY_RIGHT:
			if (this->pos.second < 5) {
				this->Own.alter(this->pos, PLAYER_RIGHT);
				this->pos.second += 1;
			}
			break;
		}

		this->IncPoints();
		this->Own.alter(this->pos, this->symbol);
		system("cls");
		this->Own.printLabyrinth(this->Name, DONT_SHOW_WALLS);
		cout << "Your points: " << this->points;

		if ((p = MetSomeone(v)) != nullptr) {
			return Battle(p);
		}

		if (this->pos == this->Own.getFinish()) {
			//cout << "[DEBUG]" << "Finished" << endl;
			//cin.get();
			return WON2;
		}

		c = _getch();
	}

	//system("cls");
	//cout << "[DEBUG]" << "Hit wall: " << Other.getFinish().first << ' ' << Other.getFinish().second << endl;
	//cout << "[DEBUG]" << "Hit wall: " << this->pos.first << ' ' << this->pos.second << endl;
	//cin.get();
	return HIT_WALL2;
}

//int Mode2Player::SingleMove() {
//	int c;
//
//	this->Own.alter(this->pos, this->symbol);
//	this->Own.printLabyrinth(this->Name, SHOW_WALLS);
//	cout << "Your points: " << this->points;
//
//	c = _getch();
//
//	//if (c && c != 224) {
//	//	cout << "[DEBUG]" << "exiting" << endl;
//	//	cin.get();
//	//	return false;
//	//}
//
//	while (!this->Own.isClosed(this->pos, c)) {
//		//cout << "[DEBUG]" << c << endl;
//		//cin.get();
//		switch (c)
//		{
//		case KEY_UP:
//			if (this->pos.first > 0) {
//				this->Own.alter(this->pos, PLAYER_UP);
//				this->pos.first -= 1;
//			}
//			//cout << "[DEBUG]" << this->pos.first << endl;
//			//cin.get();
//			break;
//		case KEY_DOWN:
//			if (this->pos.first < 5) {
//				this->Own.alter(this->pos, PLAYER_DOWN);
//				this->pos.first += 1;
//			}
//			break;
//		case KEY_LEFT:
//			if (this->pos.second > 0) {
//				this->Own.alter(this->pos, PLAYER_LEFT);
//				this->pos.second -= 1;
//			}
//			//cout << "[DEBUG]" << this->pos.second << endl;
//			//cin.get();
//			break;
//		case KEY_RIGHT:
//			if (this->pos.second < 5) {
//				this->Own.alter(this->pos, PLAYER_RIGHT);
//				this->pos.second += 1;
//			}
//			break;
//		}
//
//		this->IncPoints();
//		this->Own.alter(this->pos, this->symbol);
//		system("cls");
//		this->Own.printLabyrinth(this->Name, SHOW_WALLS);
//		cout << "Your points: " << this->points;
//
//		c = _getch();
//	}
//
//	//system("cls");
//	//cout << "[DEBUG]" << "Hit wall: " << Other.getFinish().first << ' ' << Other.getFinish().second << endl;
//	//cout << "[DEBUG]" << "Hit wall: " << this->pos.first << ' ' << this->pos.second << endl;
//	//cin.get();
//	return HIT_WALL2;
//}