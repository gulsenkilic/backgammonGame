//GULSEN KILIC 1306180038  (written with microsoft visual studio..)

#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>  


using namespace std;

void guidance(int n);
void startgame();
void rolldice();
void rolldice2();
void game();
void showBoard();
void firstboard();
void instruction();
void move(string m);
void move2(string m);
bool open(string k);
void rod();
bool cnt1();
void cnt2();
void cnt3();
void function(string k);
void function2(string k);
void updateFile();
bool finish();
void finish2();
void finish3(string k);
void finish4(string k);
void countinue(int i, string k);


int dice[2];
string board[10][14];
char a;
int toplam = 0;
int w = 0; 
int w2 = 0;
bool fnsh=false;
bool fnsh2 = false;


void start() {  
	cout << (char)42 << (char)42 << " BACKGAMMON GAME " << (char)42 << (char)42 << endl;
	cout << (char)42 << " WELCOME OUR GAME " << (char)42 << endl;
	cout << "-If you want to choose one of this operations, please pressing number which at the beginning of the operation.-" << endl;
	cout << "1) Start new game " << endl;
	cout << "2) Continue the old game. " << endl;
	cout << "8) Exit the application" << endl;
	int n;
	cout << endl << "Please press a number: ";
	cin >> n;
	guidance(n);
}
void guidance(int n) {
	if (n == 1) {
		startgame(); //oyuna baþlamak için gerekli zarlar atýlýyor..
		firstboard();// ilk tahta oluþturulur..
		game(); //oyun döngüsü..

	}
	if (n == 2) {
		int a1 = 0;
		ifstream dosyaOku("dice.txt");
		string satir = "";
		if (dosyaOku.is_open()) {
			
			while (getline(dosyaOku, satir)) {
				if (a1 > 1) {
					a = satir[0];
					dice[0] = int(satir[2])-48;
					dice[1] = int(satir[4])-48;

				}
				a1++;
			}
			dosyaOku.close();
			a1 = 0;
		}

		ifstream dosyaOku2("board.dat");
		string satir2 = "";
		if (dosyaOku2.is_open()) {
			while (getline(dosyaOku2, satir2)) {
				countinue(a1, satir2);
				a1++;
			}
			dosyaOku2.close();
		}
		a1 = 0;
		ifstream dosyaOku3("countinue.txt");
		string satir3 = "";
		if (dosyaOku3.is_open()) {
			while (getline(dosyaOku3, satir3)) {
				if (a1 == 0) {
					toplam = stoi(satir3);
					
				}
				if (a1 == 1) { w = stoi(satir3); }
				if (a1 == 2) { w2 = stoi(satir3); }
				if (a1 == 3) {
					if (satir3 == "0") { fnsh == false; }
					else if (satir3 == "1") { fnsh == true; }
				}
				if (a1 == 4) {
					if (satir3 == "0") { fnsh2 == false; }
					else if (satir3 == "1") { fnsh2 == true; }
				}
				a1++;
			}
			dosyaOku3.close();
		}
		if (toplam == 0) {
			if (a == 'Y') a = 'X';
		    else if (a == 'X') a = 'Y'; 
			rolldice();
			game();
				
		}
		else if (toplam = dice[0] + dice[1]) {
			cout << dice[0] << " -- " << dice[1] << endl;
			game();
		}
		else if (toplam == dice[0]) {
			cout << dice[0]  << endl;
			game();
		}
		else if (toplam == dice[1]) {
			cout << dice[1] << endl;
			game();
		}
		
	}
	if (n == 8) {
		remove("countinue.txt");
		ofstream dosyaYaz("countinue.txt");
		ofstream outputYazma;
		outputYazma.open("countinue.txt", ios::app);
		outputYazma << toplam << endl;
		outputYazma << w << endl;
		outputYazma << w2 << endl;
		outputYazma << fnsh << endl;
		outputYazma << fnsh2 << endl;

		outputYazma.close();

		cout << endl << "The application is closing.." << endl;
		cout << "If you liked our app, don't forget to share it with your friends." << endl;
		cout << endl << "Have a nice day :)" << endl;
		exit(1);

	}

}
void startgame() {
	cout << "The dice are rolling to get started...." << endl;
	remove("dice.txt");
	ofstream dosyaYaz("dice.txt");
	rolldice2();
	cout << endl;
	cout << "The dice for the first player is: " << dice[0] << endl;
	cout << "The dice for the second player is: " << dice[1] << endl;
	cout << endl;
	if (dice[0] < dice[1]) {
		a = 'Y';
		cout << "The second player will start the game." << endl;
		cout << "You can use " << dice[0] << " and " << dice[1] << " for first move." << endl;
		cout << endl;
	}
	else if (dice[1] < dice[0]) {
		a = 'X';
		cout << "The first player will start the game." << endl;
		cout << "You can use " << dice[0] << " and " << dice[1] << " for first move." << endl;
		cout << endl;
	}
	else {
		cout << "Since the numbers are the same, the roll of the dice will be repeated...." << endl;
		cout << endl;
		startgame();
	}

}
void game() {
	cout << "Please play with " << a << " flakes." << endl;
	showBoard();
	if (cnt1() == true) {
    	rod();
	}
	if(fnsh==false &&a=='X'){
		if (dice[0] == dice[1]) {
			cnt3();
		}
		else cnt2();
	}//else finish2();
	
	if (fnsh2 == false && a == 'Y') {
		if (dice[0] == dice[1]) {
			cnt3();
		}
		else cnt2();
	}

	else finish2();
} 
	
	

void showBoard() {

	ifstream dosyaOku("board.dat");
	string satir = "";
	if (dosyaOku.is_open()) {
		while (getline(dosyaOku, satir)) {
			cout << satir << endl;
		}
		dosyaOku.close();
	}

}
void firstboard() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			if (i == 0) {
				board[i][j] = to_string(j + 13);
			}
			if (i == 9) {
				/*if (j <= 8) {
					board[i][j] = "0" + to_string(j + 1);
				}
				else if (j > 8) board[i][j] = to_string(j + 1);	*/
				if (j <= 2) {
					board[i][j] = to_string(12 - j);
				}
				else if (j > 2) {
					board[i][j]="0" + to_string(12 - j);
				}
			}
			if (i == 1) {
				if (j != 0 && j != 4 && j != 6 && j != 11) {
					board[i][j] = "00";
				}
			}
			if (i == 8) {
				if (j != 0 && j != 4 && j != 6 && j != 11) {
					board[i][j] = "00";
				}
			}
		}
		}

		board[1][0] = "5Y";
		board[1][4] = "3X";
		board[1][6] = "5X";
		board[1][11] = "2Y";

		board[8][0] = "5X";
		board[8][4] = "3Y";
		board[8][6] = "5Y";
		board[8][11] = "2X";

		board[3][5] = "0Y";
		board[5][5] = "0X";

		board[0][13] = "0X";
		board[9][13] = "0Y";
		
	

		remove("board.dat");
		ofstream dosyaYaz("board.dat");
		ofstream outputYazma;
		outputYazma.open("board.dat", ios::app);
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 14; j++) {
				outputYazma << board[i][j] << " ";
			}
			outputYazma << endl;
		}
		outputYazma.close();
	
}
void instruction() {
	int a;
	cout << "Press 1 to move, 8 to exit the game: " << endl;
	cin >> a;
	if (a == 8) {
		guidance(a);
	}
	if (a == 1) {
		string m;
		cout << "firstly, enter the number of the flake you want to move (like 02 or 13 etc.)" << endl;
		cin >> m;
		if (m == "8")guidance(8);
		if (dice[0] == dice[1]) {
			move2(m);
		}else move(m);
	}
}
bool cnt1() {
	if (a == 'X' && board[5][5]!="0X") {
		cout << board[5][5];
		return true;
	}
	else if (a == 'Y' && board[3][5]!="0Y"){
		cout << board[3][5];
		return true;
	}
}
void rod() {
	cout << "You have flake on the bar. You have to play on these first." << endl;
	int sya = 0;
	if (toplam == dice[0] + dice[1]) {
		string c[2];
		if (a == 'X') {
			if (board[5][5] != " ") {
				for (int i = 6; i < 12; i++) {
					if (open(board[9][i]) == true) {
						sya++;
					}
				}
				if (sya == 0) {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();//buraya diðerine geçme fonksiyonu yazýlacak
				}
				else {
					string s1;
					int s2[2];
					if (dice[0] == 1) {
						if (open(board[9][11]) == true) {
							cout << board[9][11] << " / ";
							c[0] = board[9][11];
						}
					}
					if (dice[0] == 2) {
						if (open(board[9][10]) == true) {
							cout << board[9][10] << " / ";
							c[0] = board[9][10];
						}
					}
					if (dice[0] == 3) {
						if (open(board[9][9]) == true) {
							cout << board[9][9] << " / ";
							c[0] = board[9][9];
						}
					}
					if (dice[0] == 4) {
						if (open(board[9][8]) == true) {
							cout << board[9][8] << " / ";
							c[0] = board[9][8];
						}
					}
					if (dice[0] == 5) {
						if (open(board[9][7]) == true) {
							cout << board[9][7] << " / ";
							c[0] = board[9][7];
						}
					}
					if (dice[0] == 6) {
						if (open(board[9][6]) == true) {
							cout << board[9][6] << " / ";
							c[0] = board[9][6];
						}
					}
					if (dice[1] == 1) {
						if (open(board[9][11]) == true) {
							cout << board[9][11] << " / ";
							c[1] = board[9][11];
						}
					}
					if (dice[1] == 2) {
						if (open(board[9][10]) == true) {
							cout << board[9][10] << " / ";
							c[1] = board[9][10];
						}
					}
					if (dice[1] == 3) {
						if (open(board[9][9]) == true) {
							cout << board[9][9] << " / ";
							c[1] = board[9][9];
						}
					}
					if (dice[1] == 4) {
						if (open(board[9][8]) == true) {
							cout << board[9][8] << " / ";
							c[1] = board[9][8];
						}
					}
					if (dice[1] == 5) {
						if (open(board[9][7]) == true) {
							cout << board[9][7] << " / ";
							c[1] = board[9][7];
						}
					}
					if (dice[1] == 6) {
						if (open(board[9][6]) == true) {
							cout << board[9][6] << " / ";
							c[1] = board[9][6];
						}
					}
					cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
					
					cin >> s1;
					if (s1 == "8")guidance(8);
					if (s1 == c[0]) {
						toplam = dice[1];
					}
					else if (s1 == c[1]) {
						toplam = dice[0];
					}
					char r = board[5][5][0];
					r = char(int(r) - 1);
					if (r == '0') {
						board[5][5]="0X";
					}
					else {
						board[5][5] = "";
						board[5][5].push_back(r);
						board[5][5].push_back('X');
					}
					function(s1);
					if (board[5][5] != "0X") {
						rod();
					}
					else {
						cnt2();
					}


				}
			}
		}

		else if (a == 'Y') {
			if (board[3][5] != " ") {
				for (int i = 6; i < 12; i++) {
					if (open(board[0][i]) == true) {
						sya++;
					}
				}
				if (sya == 0) {
					cout << "You have no place to move.." << endl;
					a = 'X';
					rolldice();
					game();//buraya diðerine geçme fonksiyonu yazýlacak
				}
				else {
					if (dice[0] == 1) {
						if (open(board[0][11]) == true) {
							cout << board[0][11] << " / ";
							c[0] = board[0][11];
						}
					}
					if (dice[0] == 2) {
						if (open(board[0][10]) == true) {
							cout << board[0][10] << " / ";
							c[0] = board[0][10];
						}
					}
					if (dice[0] == 3) {
						if (open(board[0][9]) == true) {
							cout << board[0][9] << " / ";
							c[0] = board[0][9];
						}
					}
					if (dice[0] == 4) {
						if (open(board[0][8]) == true) {
							cout << board[0][8] << " / ";
							c[0] = board[0][8];
						}
					}
					if (dice[0] == 5) {
						if (open(board[0][7]) == true) {
							cout << board[0][7] << " / ";
							c[0] = board[0][7];
						}
					}
					if (dice[0] == 6) {
						if (open(board[0][6]) == true) {
							cout << board[0][6] << " / ";
							c[0] = board[0][6];
						}
					}
					if (dice[1] == 1) {
						if (open(board[0][11]) == true) {
							cout << board[0][11] << " / ";
							c[1] = board[0][11];
						}
					}
					if (dice[1] == 2) {
						if (open(board[0][10]) == true) {
							cout << board[0][10] << " / ";
							c[1] = board[0][10];
						}
					}
					if (dice[1] == 3) {
						if (open(board[0][9]) == true) {
							c[1] = board[0][9];
							cout << board[0][9] << " / ";
						}
					}
					if (dice[1] == 4) {
						if (open(board[0][8]) == true) {
							cout << board[0][8] << " / ";
							c[1] = board[0][8];
						}
					}
					if (dice[1] == 5) {
						if (open(board[0][7]) == true) {
							cout << board[0][7] << " / ";
							c[1] = board[0][7];
						}
					}
					if (dice[1] == 6) {
						if (open(board[0][6]) == true) {
							cout << board[0][6] << " / ";
							c[1] = board[0][6];
						}
					}
					string s1;
					cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
					cin >> s1;
					if (s1 == "8")guidance(8);
					if (s1 == c[0]) {
						toplam = dice[1];
					}
					else if (s1 == c[1]) {
						toplam = dice[0];
					}

					char r = board[3][5][0];
					r = char(int(r) - 1);
					if (r == '0') {
						board[3][5]="0Y";
					}
					else {
						board[3][5] = "";
						board[3][5].push_back(r);
						board[3][5].push_back('Y');
					}

					function(s1);
					if (board[3][5] != "0Y") {
						rod();
					}
					else {
						cnt2();
					}
				}
			}
		}
	}
	else if (dice[1] == dice[0]) {
		if (a == 'X') {
			string s1;
			int s2[2];
			if (dice[0] == 1) {
				if (open(board[9][11]) == true) {
					cout << board[9][11] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}
			if (dice[0] == 2) {
				if (open(board[9][10]) == true) {
					cout << board[9][10] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}
			if (dice[0] == 3) {
				if (open(board[9][9]) == true) {
					cout << board[9][9] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}
			if (dice[0] == 4) {
				if (open(board[9][8]) == true) {
					cout << board[9][8] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}
			if (dice[0] == 5) {
				if (open(board[9][7]) == true) {
					cout << board[9][7] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}
			if (dice[0] == 6) {
				if (open(board[9][6]) == true) {
					cout << board[9][6] << " / ";

				}
				else {
					cout << "You have no place to move.." << endl;
					a = 'Y';
					rolldice();
					game();
				}
			}

			cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
			cin >> s1;
			if (s1 == "8")guidance(8);
			char r = board[5][5][0];
			if (r == '1') {
				r = char(int(r) - 1);
				if (r == '0') {
					board[5][5]="0X";
				}
				else {
					board[5][5] = "";
					board[5][5].push_back(r);
					board[5][5].push_back('X');
				}
				function(s1);

				toplam = toplam - dice[0];
				cnt3();
			}
			else if (r == '2') {
				r = char(int(r) - 2);
				if (r == '0') {
					board[5][5] = "0X";
				}
				else {
					board[5][5] = "";
					board[5][5].push_back(r);
					board[5][5].push_back('X');
				}
				function(s1);
				cout << endl;
				function(s1);
				cnt2();
			}
			else if (r == '3') {
				r = char(int(r) - 3);
				if (r=='0') {
					board[5][5] = "0X";
				}
				else {
					board[5][5] = "";
					board[5][5].push_back(r);
					board[5][5].push_back('X');
				}
				function(s1);
				cout << endl;
				function(s1);
				cout << endl;
				function(s1);
				cout << endl;
				cnt2();
			}
			else if (r == '4') {
				r = char(int(r) - 4);
				if (r == '0') {
					board[5][5] = "0X";
				}
				else {
					board[5][5] = "";
					board[5][5].push_back(r);
					board[5][5].push_back('X');
				}
				function(s1);
				cout << endl;
				function(s1);
				cout << endl;
				function(s1);
				cout << endl;
				function(s1);

				a = 'Y';
				rolldice();
				game();
			}

		}
		if (a == 'Y') {
			if (board[3][5] != " ") {

				if (dice[0] == 1) {
					if (open(board[0][11]) == true) {
						cout << board[0][11] << " / ";
					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}
				if (dice[0] == 2) {
					if (open(board[0][10]) == true) {
						cout << board[0][10] << " / ";
					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}
				if (dice[0] == 3) {
					if (open(board[0][9]) == true) {
						cout << board[0][9] << " / ";
					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}
				if (dice[0] == 4) {
					if (open(board[0][8]) == true) {
						cout << board[0][8] << " / ";
					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}
				if (dice[0] == 5) {
					if (open(board[0][7]) == true) {
						cout << board[0][7] << " / ";

					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}
				if (dice[0] == 6) {
					if (open(board[0][6]) == true) {
						cout << board[0][6] << " / ";
					}
					else {
						cout << "You have no place to move.." << endl;
						a = 'X';
						rolldice();
						game();
					}
				}

				string s1;
				cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);

				char r = board[3][5][0];
				if (r == '1') {
					r = char(int(r) - 1);
					if  (r == '0') {
						board[3][5]="0Y";
					}
					else {
						board[3][5] = "";
						board[3][5].push_back(r);
						board[3][5].push_back('Y');
					}
					function(s1);

					toplam = toplam - dice[0];
					cnt3();
				}
				else if (r == '2') {
					r = char(int(r) - 2);
					if (r == '0') {
						board[3][5] = "0Y";
					}
					else {
						board[3][5] = "";
						board[3][5].push_back(r);
						board[3][5].push_back('Y');
					}
					function(s1);
					cout << endl;
					function(s1);
					cnt2();
				}
				else if (r == '3') {
					r = char(int(r) - 3);
					if (r == '0') {
						board[3][5] = "0Y";
					}
					else {
						board[3][5] = "";
						board[3][5].push_back(r);
						board[3][5].push_back('Y');
					}
					function(s1);
					cout << endl;
					function(s1);
					cout << endl;
					function(s1);
					cout << endl;
					cnt2();
				}
				else if (r == '4') {
					r = char(int(r) - 4);
					if (r == '0') {
						board[3][5] = "0Y";
					}
					else {
						board[3][5] = "";
						board[3][5].push_back(r);
						board[3][5].push_back('Y');
					}
					function(s1);
					cout << endl;
					function(s1);
					cout << endl;
					function(s1);
					cout << endl;
					function(s1);

					a = 'X';
					rolldice();
					game();
				}
			}
		}
		
	}
	else if(toplam == dice[0] || toplam == dice[1]) {
				sya = 0;
				if (a == 'X') {
					if (board[5][5] != " ") {
						for (int i = 6; i < 12; i++) {
							if (open(board[9][i]) == true) {
								sya++;
							}
						}
						if (sya == 0) {
							cout << "You have no place to move.." << endl;
							a = 'Y';
							rolldice();
							game();//buraya diðerine geçme fonksiyonu yazýlacak
						}
						else {
							string s1;
							int s2[2];
							if (toplam == 1) {
								if (open(board[9][11]) == true) {

									cout << board[9][11] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							if (toplam == 2) {
								if (open(board[9][10]) == true) {
									cout << board[9][10] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							if (toplam == 3) {
								if (open(board[9][9]) == true) {
									cout << board[9][9] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							if (toplam == 4) {
								if (open(board[9][8]) == true) {
									cout << board[9][8] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							if (toplam == 5) {
								if (open(board[9][7]) == true) {
									cout << board[9][7] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							if (toplam== 6) {
								if (open(board[9][6]) == true) {
									cout << board[9][6] << " / ";
									
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'Y';
									rolldice();
									game();
								}
							}
							
							cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
							cin >> s1;
							if (s1 == "8")guidance(8);

							char r = board[5][5][0];
							r = char(int(r) - 1);
							if (r == '0') {
								board[5][5]="0X";
							}
							else {
								board[5][5] = "";
								board[5][5].push_back(r);
								board[5][5].push_back('X');
							}

							function(s1);	

						    a = 'Y';
							rolldice();
							game();


						}
					}
				}
				else if (a == 'Y') {
					if (board[3][5] != " ") {
						for (int i = 6; i < 12; i++) {
							if (open(board[0][i]) == true) {
								sya++ ;
							}
						}
						if (sya == 0) {
							cout << "You have no place to move.." << endl;
							rolldice();
							a = 'X';
							game();//buraya diðerine geçme fonksiyonu yazýlacak
						}
						else {
							if (toplam == 1) {
								if (open(board[0][11]) == true) {
									cout << board[0][11] << " / ";
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							if (toplam == 2) {
								if (open(board[0][10]) == true) {
									cout << board[0][10] << " / ";
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							if (toplam == 3) {
								if (open(board[0][9]) == true) {
									cout << board[0][9] << " / ";
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							if (toplam == 4) {
								if (open(board[0][8]) == true) {
									cout << board[0][8] << " / ";
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							if (toplam== 5) {
								if (open(board[0][7]) == true) {
									cout << board[0][7] << " / ";

								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							if (toplam == 6) {
								if (open(board[0][6]) == true) {
									cout << board[0][6] << " / ";
								}
								else {
									cout << "You have no place to move.." << endl;
									a = 'X';
									rolldice();
									game();
								}
							}
							
							string s1;
							cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
							cin >> s1;
							if (s1 == "8")guidance(8);

							char r = board[3][5][0];
							r = char(int(r) - 1);
							if (r == '0') {
								board[3][5] = "0Y";
							}
							else {
								board[3][5] = "";
								board[3][5].push_back(r);
								board[3][5].push_back('Y');
							}

							function(s1);
						    a = 'X';
							rolldice();
							game();

						}
					}
				}
}
}
void function(string k) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			if (board[i][j] == k) {
				if (i == 0) {
					if (a == 'X' && board[1][j] == "1Y") {				
					   char r = board[3][5][0];
						r = char(int(r) + 1);
						board[3][5].clear();
						//board[3][5] = "";
						board[3][5].push_back(char(r));
						board[3][5].push_back('Y');
						
				       board[1][j] = "1X";
						
					
					} 
					else if (a == 'Y' && board[1][j] == "1X") {
						char r = board[5][5][0];
						r = char(int(r) + 1);
						board[5][5].clear();
						//board[5][5] = "";
						board[5][5].push_back(char(r));
						board[5][5].push_back('X');
					
					   board[1][j] = "1Y";
						
						
					} else {
						char r = board[1][j][0];
						r = char(int(r) + 1);
						board[1][j] = "";
						board[1][j].push_back(r);
						board[1][j].push_back(a);
					}
					
				}
				else if (i == 9) {
					if (a == 'X' && board[8][j] == "1Y") {
						char r = board[3][5][0];
						r = char(int(r) + 1);
						board[3][5].erase();
						board[3][5].push_back(char(r));
						board[3][5].push_back('Y');
					/*	if (board[8][j] == "1Y") {*/
						 board[8][j] = "1X";
						//}
					}
					else if (a == 'Y' && board[8][j] == "1X") {
						char r = board[5][5][0];
						r = char(int(r) + 1);
						board[5][5].erase();
						board[5][5].push_back(char(r));
						board[5][5].push_back('X');
						/*if (board[8][j] == "1X") {*/
						board[8][j] = "1Y";
						//}
						
					}
					
				
					else {
						char r = board[8][j][0];
						r = char(int(r) + 1);
						board[8][j] = "";
						board[8][j].push_back(char(r));
						board[8][j].push_back(a);
					}
					
				}
			}
		}

	}
	updateFile();
	showBoard();
	if (finish() != false &&a=='X') {
		fnsh = true;
	}
	if (finish() != false && a == 'Y') {
		fnsh2 = true;
	}
}
void function2(string k) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 12; j++) {
			if (board[i][j] == k) {
				if (i == 0) {
					char r = board[1][j][0];
					r = char(int(r) - 1);
					if (r == '0') {
						board[1][j] = "00";
					}
					else {
						board[1][j] = "";
						board[1][j].push_back(r);
						board[1][j].push_back(a);
					}
				}
				else if (i == 9) {
					char r = board[8][j][0];
					r = char(int(r) - 1);
					if (r == '0') {
						board[8][j] = "00";
					}
					else {
						board[8][j] = "";
						board[8][j].push_back(r);
						board[8][j].push_back(a);
					}
				}
				break;
			}
		}
	}	
	updateFile();
	//showBoard();
}
void move(string m) {
	if (toplam == dice[0] + dice[1]) {
		int c0 = 0, c1 = 0, c2 = 0;
		string c[3];
		string s1;
		if (a == 'X') {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 12; j++) {
					if (board[i][j] == m) {
						if (i == 0) {
							int b = 0;
							switch (b)
							{
							case 0:
								c0 = j + dice[0];
								if (open(board[0][c0]) == true) {
									cout << board[0][c0] << " / ";
									c[0] = board[0][c0];
								}
							case 1:
								c1 = j + dice[1];
								if (open(board[0][c1]) == true) {
									cout << board[0][c1] << " / ";
									c[1] = board[0][c1];
								}
							case 2:
								c2 = j + toplam;
								if (open(board[0][c2]) == true) {
									cout << board[0][c2];
									c[2] = board[0][c2];

								}
							default:
								break;
							}
						}
						else if (i == 9) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j - dice[0];
								if (c0 > 0) {
									if (open(board[9][c0]) == true) {
										cout << board[9][c0] << " / ";
										c[0] = board[9][c0];
									}
								}
								else if (c0 < 0) {
									c0 = c0 * (-1);
									c0 = c0 - 1;
									if (open(board[0][c0]) == true) {
										cout << board[0][c0] << " / ";
										c[0] = board[0][c0];
									}
								}
							case 1:
								c1 = j - dice[1];
								if (c1 > 0) {
									if (open(board[9][c1]) == true) {
										cout << board[9][c1] << " / ";
										c[1] = board[9][c1];
									}
								}
								else if (c1 < 0) {
									c1 = c1 * (-1);
									c1 = c1 - 1;
									if (open(board[0][c1]) == true) {
										cout << board[0][c1] << " / ";
										c[1] = board[0][c1];
									}
								}
							case 2:

								c2 = j - toplam;
								if (c2 > 0) {
									if (open(board[9][c2]) == true) {
										cout << board[9][c2] << " / ";
										c[2] = board[9][c2];
									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[0][c2]) == true) {
										cout << board[0][c2];
										c[2] = board[0][c2];

									}
								}
							default:
								break;
							}

						}
					}
				}
			}
			if (c[0] == "" && c[1] == "" && c[2] == "") {
				cout <<endl<< "You have no place to move.. Please choose other place" << endl;
				instruction();
			}
			else {
				cout << endl;
				cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				if (s1 == c[0]) {
					toplam = dice[1];
				}
				else if (s1 == c[1]) {
					toplam = dice[0];
				}
				else  if (s1 == c[2]) {
					toplam = 0;
				}

				function2(m);
				function(s1);
				if (toplam == 0) {
					a = 'Y';
					rolldice();
					game();
				}
				else {
					if (fnsh == false) cnt2();
					else finish2();
					
				}
			}
		}
		else if (a == 'Y') {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 12; j++) {
					if (board[i][j] == m) {
						if (i == 0) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j - dice[0];
								if (c0 > 0) {
									if (open(board[0][c0]) == true) {
										cout << board[0][c0] << " / ";
										c[0] = board[0][c0];
									}
								}
								else if (c0 < 0) {
									c0 = c0 * (-1);
									c0 = c0 - 1;
									if (open(board[9][c0]) == true) {
										cout << board[9][c0] << " / ";
										c[0] = board[9][c0];
									}
								}
							case 1:
								c1 = j - dice[1];
								if (c1 > 0) {
									if (open(board[0][c1]) == true) {
										cout << board[0][c1] << " / ";
										c[1] = board[0][c1];
									}
								}
								else if (c1 < 0) {
									c1 = c1 * (-1);
									c1 = c1 - 1;
									if (open(board[9][c1]) == true) {
										cout << board[9][c1] << " / ";
										c[1] = board[9][c1];
									}
								}
							case 2:

								c2 = j - toplam;
								if (c2 > 0) {
									if (open(board[0][c2]) == true) {
										cout << board[0][c2] << " / ";
										c[2] = board[0][c2];

									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[9][c2]) == true) {
										cout << board[9][c2];
										c[2] = board[9][c2];

									}
								}
							default:
								break;
							}

						}
						else if (i == 9) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j + dice[0];
								if (open(board[9][c0]) == true) {
									cout << board[9][c0] << " / ";
									c[0] = board[9][c0];
								}
							case 1:
								c1 = j + dice[1];
								if (open(board[9][c1]) == true) {
									cout << board[9][c1] << " / ";
									c[1] = board[9][c1];
								}
							case 2:
								c2 = j + toplam;
								if (open(board[9][c2]) == true) {
									cout << board[9][c2];
									c[2] = board[9][c2];

								}
							default:
								break;
							}
						}
					}
				}
			}
			if (c[0] == "" && c[1] == "" && c[2] == "") {
				cout << endl<<"You have no place to move..Please choose other place.." << endl;
				instruction();
			}
			else {
				cout << endl;
				cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				if (s1 == c[0]) {
					toplam = dice[1];
				}
				else if (s1 == c[1]) {
					toplam = dice[0];
				}
				else  if (s1 == c[2]) {
					toplam = 0;
				}

				function2(m);
				function(s1);
				if (toplam == 0) {
					a = 'X';
					rolldice();
					game();
				}
				else {
					if (fnsh2 == false) cnt2();
					else finish2();
				}
			}
		}
	}
	else if (toplam == dice[0] || toplam == dice[1]) {
		int c0 = 0, c1 = 0, c2 = 0;
		string c[3];
		string s1;
		if (a == 'X') {

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 12; j++) {
					if (board[i][j] == m) {
						if (i == 0) {
							c0 = j + toplam;
							if (open(board[0][c0]) == true) {
								cout << board[0][c0] << " / ";
								c[0] = board[0][c0];
							}
						}
						else if (i == 9) {
							c0 = j - toplam;
							if (c0 > 0) {
								if (open(board[9][c0]) == true) {
									cout << board[9][c0] << " / ";
									c[0] = board[9][c0];
								}
							}
							else if (c0 < 0) {
								c0 = c0 * (-1);
								c0 = c0 - 1;
								if (open(board[0][c0]) == true) {
									cout << board[0][c0] << " / ";
									c[0] = board[0][c0];
								}
							}
						}
						break;
					}
				}
			}
			if (c[0] == "" && c[1] == "" && c[2] == "") {
				cout << "You have no place to move.." << endl;
				instruction();
			}
			else {
				cout << endl;
				cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
				cin >> s1;

				function2(m);
				function(s1);
				a = 'Y';
				rolldice();
				game();


			}
		} 
		if (a == 'Y') {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 12; j++) {
					if (board[i][j] == m) {
						if (i == 0) {

							c0 = j - toplam;
							if (c0 > 0) {
								if (open(board[0][c0]) == true) {
									cout << board[0][c0] << " / ";
									c[0] = board[0][c0];
								}
							}
							else if (c0 < 0) {
								c0 = c0 * (-1);
								c0 = c0 - 1;
								if (open(board[9][c0]) == true) {
									cout << board[9][c0] << " / ";
									c[0] = board[9][c0];
								}
							}



						}
						else if (i == 9) {

							c0 = j + toplam;
							if (open(board[9][c0]) == true) {
								cout << board[9][c0] << " / ";
								c[0] = board[9][c0];
							}


						}
					}
				}
			}
			if (c[0] == "" && c[1] == "" && c[2] == "") {
				cout << "You have no place to move.." << endl;
				instruction();
			}
			else {
				cout << endl;
				cout << "Where do you want to move? (like 02 or 13 etc.)" << endl;
				cin >> s1;
				function2(m);
				function(s1);
				a = 'X';
				rolldice();
				game();

			}
		}
	}
}
void rolldice() {
	srand(time(NULL));
	int loop = 0, i = 0;
	while ((i <= 6) && (loop < 2))
	{
		i = rand() % 6 + 1;
		dice[loop] = i;
		loop++;
	}

	if (dice[1] == dice[0]) {
		toplam = 4 * dice[0];
	}
	else toplam = dice[1] + dice[0];
	cout << "The dice are rolling to get started...." << endl;
	cout << endl;
	cout << dice[0] << "--" << dice[1] << endl;
	ofstream outputYazma;
	outputYazma.open("dice.txt", ios::app);
	outputYazma << a << " " << dice[0] << " " << dice[1] << endl;
	outputYazma.close();


}
void rolldice2() {
	srand(time(NULL));
	int loop = 0, i = 0;
	while ((i <= 6) && (loop < 2))
	{
		i = rand() % 6 + 1;
		dice[loop] = i;
		loop++;
	}
	
	 toplam = dice[1] + dice[0];
	
	ofstream outputYazma;
	outputYazma.open("dice.txt", ios::app);
	outputYazma << dice[0] << endl;
	outputYazma << dice[1] << endl;
	outputYazma.close();


}
bool open(string k) {
	if (a == 'X') {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (board[i][j] == k) {
					if (i == 0) {
						if (board[i + 1][j] == "00") {
							return true;
							break;
						}
						else if (board[i + 1][j] == "1Y") {
							return true;
							break;
						}
						else if (board[i + 1][j][1] == 'X') {
							return true;
							break;
						}
					}
					else if (i == 9) {
						if (board[i - 1][j] == "00") {
							return true;
							break;
						}
						else if (board[i - 1][j] == "1Y") {
							return true;
							break;
						}
						else if (board[i - 1][j][1] == 'X') {
							return true;
							break;
						}
					}
				}

			}
		}
	}
	else if (a == 'Y') {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (board[i][j] == k) {
					if (i == 0) {
						if (board[i + 1][j] == "00") {
							return true;
							break;
						}
						else if (board[i + 1][j] == "1X") {
							return true;
							break;
						}
						else if (board[i + 1][j][1] == 'Y') {
							return true;
							break;
						}
					}
					else if (i == 9) {
						if (board[i - 1][j] == "00") {
							return true;
							break;
						}
						else if (board[i - 1][j] == "1X") {
							return true;
							break;
						}
						else if (board[i - 1][j][1] == 'Y') {
							return true;
							break;
						}
					}
				}

			}
		}
	}
}
void updateFile() {
	remove("board.dat");
	ofstream dosyaYaz("board.dat");
	ofstream outputYazma;
	outputYazma.open("board.dat", ios::app);
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 14; j++) {
			outputYazma << board[i][j] << " ";
		}
		outputYazma << endl;
	}
	outputYazma.close();

}
void move2(string m){ 
	string arr[4];
	int c0 = 0, c1 = 0, c2 = 0;
	string c[4] = {"00","00","00","00"};
	string s1;
	if (a == 'X') {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (board[i][j] == m) {
					if (i == 0) {
						int b = 0;
						switch (b)
						{
						case 0:
							c0 = j + dice[0];
							if (open(board[0][c0]) == true) {
								c[0] = board[0][c0];
							}
						case 1:
							c1 = j + 2*dice[0];
							if (open(board[0][c1]) == true) {
								c[1] = board[0][c1];
							}
						case 2:
							c2 = j + 3*dice[0];
							if (open(board[0][c2]) == true) {
								c[2] = board[0][c2];

							}
						case 3:
							c2 = j + 4 * dice[0];
							if (open(board[0][c2]) == true) {
								c[3] = board[0][c2];

							}
						default:
							break;
						}
					}
					else if (i == 9) {
						int b = 0;
						switch (b) {
						case 0:
							c0 = j - dice[0];
							if (c0 > 0) {
								if (open(board[9][c0]) == true) {
									c[0] = board[9][c0];
								}
							}
							else if (c0 < 0) {
								c0 = c0 * (-1);
								c0 = c0 - 1;
								if (open(board[0][c0]) == true) {
									c[0] = board[0][c0];
								}
							}
						case 1:
							c1 = j - 2*dice[1];
							if (c1 > 0) {
								if (open(board[9][c1]) == true) {
									c[1] = board[9][c1];
								}
							}
							else if (c1 < 0) {
								c1 = c1 * (-1);
								c1 = c1 - 1;
								if (open(board[0][c1]) == true) {
									c[1] = board[0][c1];
								}
							}
						case 2:

							c2 = j - 3*dice[0];
							if (c2 > 0) {
								if (open(board[9][c2]) == true) {
									c[2] = board[9][c2];
								}
							}
							else if (c2 < 0) {
								c2 = c2 * (-1);
								c2 = c2 - 1;
								if (open(board[0][c2]) == true) {
									c[2] = board[0][c2];

								}
							}
						case 3:
							c2 = j - 4 * dice[0];
							if (c2 > 0) {
								if (open(board[9][c2]) == true) {
									c[3] = board[9][c2];
								}
							}
							else if (c2 < 0) {
								c2 = c2 * (-1);
								c2 = c2 - 1;
								if (open(board[0][c2]) == true) {
									c[3] = board[0][c2];

								}
							}
						default:
							break;
						}

					}
				}
			}
		}
		if (c[0] == "00" && c[1] == "00" && c[2] == "00"&&c[3]=="00") {
			cout << endl << "You have no place to move.. Please choose other place" << endl;
			instruction();
		}
		else {
			if (toplam == dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] <<endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				a = 'Y';
				rolldice();
				game();
			}else if (toplam == 2 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0]<<" / "<<c[1] << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = dice[0];
					
					if (fnsh == false) cnt2();
					else finish2();
				
				}
				else if(s1 == c[1]) {
					a = 'Y';
					rolldice();
					game();
				}
				
			}
			else if (toplam == 3 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << " / " << c[1] <<" / "<<c[2]<< endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = 2*dice[0];
					if (fnsh == false) cnt2();
					else finish2();
				}
				else if (s1 == c[1]) {
					toplam = dice[0];
					if (fnsh == false) cnt2();
					else finish2();
				}
				else if (s1 == c[2]) {
					a = 'Y';
					rolldice();
					game();
				}
				 //bu da gidebilir..
				//yönlendirmeeeeeeee
			}
			else if (toplam == 4 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << " / " << c[1] << " / " << c[2] <<" / "<<c[3]<< endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = 3 * dice[0];
					if (fnsh == false) cnt3();
					else finish2();
					
				}
				else if (s1 == c[1]) {
					toplam =2* dice[0];
					if (fnsh == false) cnt2();
					else finish2();
				}
				else if (s1 == c[2]) {
					toplam = 1 * dice[0];
					if (fnsh == false) cnt2();
					else finish2();
				}
				else if (s1 == c[3]) {
					a = 'Y';
					rolldice();
					game();
				}
				
			}
			
		}
	}
	else if (a == 'Y') {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (board[i][j] == m) {
					if (i == 0) {
						int b = 0;
						switch (b) {
						case 0:
							c0 = j - dice[0];
							if (c0 > 0) {
								if (open(board[0][c0]) == true) {
									c[0] = board[0][c0];
								}
							}
							else if (c0 < 0) {
								c0 = c0 * (-1);
								c0 = c0 - 1;
								if (open(board[9][c0]) == true) {
									c[0] = board[9][c0];
								}
							}
						case 1:
							c1 = j - 2*dice[1];
							if (c1 > 0) {
								if (open(board[0][c1]) == true) {
									c[1] = board[0][c1];
								}
							}
							else if (c1 < 0) {
								c1 = c1 * (-1);
								c1 = c1 - 1;
								if (open(board[9][c1]) == true) {
									c[1] = board[9][c1];
								}
							}
						case 2:

							c2 = j - 3*dice[0];
							if (c2 > 0) {
								if (open(board[0][c2]) == true) {
									c[2] = board[0][c2];

								}
							}
							else if (c2 < 0) {
								c2 = c2 * (-1);
								c2 = c2 - 1;
								if (open(board[9][c2]) == true) {
									c[2] = board[9][c2];

								}
							}
						case 3:

							c2 = j - 4 * dice[0];
							if (c2 > 0) {
								if (open(board[0][c2]) == true) {
									c[3] = board[0][c2];

								}
							}
							else if (c2 < 0) {
								c2 = c2 * (-1);
								c2 = c2 - 1;
								if (open(board[9][c2]) == true) {
									c[3] = board[9][c2];

								}
							}
						default:
							break;
						}

					}
					else if (i == 9) {
						int b = 0;
						switch (b) {
						case 0:
							c0 = j + dice[0];
							if (open(board[9][c0]) == true) {
								c[0] = board[9][c0];
							}
						case 1:
							c1 = j + 2*dice[1];
							if (open(board[9][c1]) == true) {
								c[1] = board[9][c1];
							}
						case 2:
							c2 = j + 3 * dice[0];
							if (open(board[9][c2]) == true) {
								c[2] = board[9][c2];

							}
							case 3:
								c2 = j + 4 * dice[0];
								if (open(board[9][c2]) == true) {
									c[3] = board[9][c2];

								}
						default:
							break;
						}
					}
				}
			}
		}
		if (c[0] == "" && c[1] == "" && c[2] == "" && c[3] == "") {
			cout << endl << "You have no place to move.. Please choose other place" << endl;
			instruction();
		}
		else {
			if (toplam == dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				a = 'X';
				rolldice();
				game();
			}
			else if (toplam == 2 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << " / " << c[1] << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = dice[0];
					if (fnsh2 == false) cnt2();
					else finish2();
				}
				else if (s1 == c[1]) {
					a = 'X';
					rolldice();
					game();
				}
			}
			else if (toplam == 3 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << " / " << c[1] << " / " << c[2] << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = 2 * dice[0];
					if (fnsh2 == false) cnt2();
					else finish2();
				}
				else if (s1 == c[1]) {
					toplam = dice[0];
					if (fnsh2 == false) cnt2();
					else finish2();
				}
				else if (s1 == c[2]) {
					a = 'X';
					rolldice();
					game();
				}
			}
			else if (toplam == 4 * dice[0]) {
				cout << endl << "Where you can make a move: " << c[0] << " / " << c[1] << " / " << c[2] << " / " << c[3] << endl;
				cin >> s1;
				if (s1 == "8")guidance(8);
				function2(m);
				function(s1);
				if (s1 == c[0]) {
					toplam = 3 * dice[0];
					if (fnsh2 == false) cnt3();
					else finish2();
				}
				else if (s1 == c[1]) {
					toplam = 2 * dice[0];
					if (fnsh2 == false) cnt2();
					else finish2();
				}
				else if (s1 == c[2]) {
					toplam = 1 * dice[0];
					if (fnsh2 == false) cnt2();
					else finish2();
				}
				else if (s1 == c[3]) {
					a = 'X';
					rolldice();
					game();
				}
			}

		}
	}
}
void cnt2() {
	int c0 = 0, c1 = 0, c2 = 0;
	string c[3];
	string s1;
	int count = 0;
	int b = 0;
	if (toplam == dice[0] + dice[1]) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {

				if (a == 'X') {
					if (i == 0) {
						if (board[1][j][1] == a)
						int b = 0;
						switch (b)
						{
						case 0:
							c0 = j + dice[0];
							if (open(board[0][c0]) == true) {
								count++;
							}
						case 1:
							c1 = j + dice[1];
							if (open(board[0][c1]) == true) {
								count++;
							}
						case 2:
							c2 = j + toplam;
							if (open(board[0][c2]) == true) {
								count++;

							}
						default:
							break;
						}
					}
					else if (i == 9) {
						if (board[8][j][1] == a) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j - dice[0];
								if (c0 > 0) {
									if (open(board[9][c0]) == true) {
										count++;
									}
								}
								else if (c0 < 0) {
									c0 = c0 * (-1);
									c0 = c0 - 1;
									if (open(board[0][c0]) == true) {
										count++;
									}
								}
							case 1:
								c1 = j - dice[1];
								if (c1 > 0) {
									if (open(board[9][c1]) == true) {
										count++;
									}
									else if (c1 < 0) {
										c1 = c1 * (-1);
										c1 = c1 - 1;
										if (open(board[0][c1]) == true) {
											count++;
										}
									}
							case 2:

								c2 = j - toplam;
								if (c2 > 0) {
									if (open(board[9][c2]) == true) {
										count++;
									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[0][c2]) == true) {
										count++;
									}
								}
							default:
								break;
								}

							}
						}

					}
				}
				if (a == 'Y') {
					for (int i = 0; i < 10; i++) {
						for (int j = 0; j < 12; j++) {
							if (i == 0) {
								if (board[1][j][1] == a) {
									int b = 0;
									switch (b) {
									case 0:
										c0 = j - dice[0];
										if (c0 > 0) {
											if (open(board[0][c0]) == true) {
												count++;
											}
										}
										else if (c0 < 0) {
											c0 = c0 * (-1);
											c0 = c0 - 1;
											if (open(board[9][c0]) == true) {
												count++;
											}
										}
									case 1:
										c1 = j - dice[1];
										if (c1 > 0) {
											if (open(board[0][c1]) == true) {
												count++;
											}
										}
										else if (c1 < 0) {
											c1 = c1 * (-1);
											c1 = c1 - 1;
											if (open(board[9][c1]) == true) {
												count++;
											}
										}
									case 2:

										c2 = j - toplam;
										if (c2 > 0) {
											if (open(board[0][c2]) == true) {
												count++;
											}
										}
										else if (c2 < 0) {
											c2 = c2 * (-1);
											c2 = c2 - 1;
											if (open(board[9][c2]) == true) {
												count++;
											}
										}
									default:
										break;
									}
								}
							}
							else if (i == 9) {
								if (board[8][j][1] == a) {
									int b = 0;
									switch (b) {
									case 0:
										c0 = j + dice[0];
										if (open(board[9][c0]) == true) {
											count++;
										}
									case 1:
										c1 = j + dice[1];
										if (open(board[9][c1]) == true) {
											count++;
										}
									case 2:
										c2 = j + toplam;
										if (open(board[9][c2]) == true) {
											count++;
										}
									default:
										break;
									}
								}
							}
						}
					}

				}
			}
		}
		if (count == 0) {
			cout << endl << "You do not have any right to move..." << endl;
			if (a == 'X') { a = 'Y'; }
			else if (a == 'Y') { a = 'X'; }
			rolldice();
			game();
		}
		else instruction();
	}
    else if (toplam == dice[0] || toplam == dice[1]) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (a == 'X') {						
				if (i == 0) {
					if (board[1][j][1] == a) {
						c0 = j + toplam;
						if (open(board[0][c0]) == true) {
							count++;
						}
					}
				}
				else if (i == 9) {
					if (board[8][j][1] == a) {
						c0 = j - toplam;
						if (c0 > 0) {
							if (open(board[9][c0]) == true) {
								count++;
							}
						}
						else if (c0 < 0) {
							c0 = c0 * (-1);
							c0 = c0 - 1;
							if (open(board[0][c0]) == true) {
								count++;
							}
						}
					}
				}
				}
				else if (a == 'Y') {				
					if (i == 0) {
						if (board[1][j][1] == a) {
							c0 = j - toplam;
							if (c0 > 0) {
								if (open(board[0][c0]) == true) {
									count++;
								}
							}
							else if (c0 < 0) {
								c0 = c0 * (-1);
								c0 = c0 - 1;
								if (open(board[9][c0]) == true) {
									count++;
								}
							}
						}
					}
					else if (i == 9) {
						if (board[8][j][1] == a) {
							c0 = j + toplam;
							if (open(board[9][c0]) == true) {
								count++;
							}
						}
					}
							
				}
			
			}
		}
		if (count == 0) {
			cout << endl << "You do not have any right to move..." << endl;
			if (a == 'X') { a = 'Y'; }
			else if (a == 'Y') { a = 'X'; }
			rolldice();
			game();
		}
		else instruction();
	}
}
void cnt3() {
	int count = 0;
	if (toplam == 4 * dice[0]) {
		int c0 = 0, c1 = 0, c2 = 0;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 12; j++) {
				if (a == 'X') {
					if (i == 0) {
						if (board[1][j][1] == a) {
							int b = 0;
							switch (b)
							{
							case 0:
								c0 = j + dice[0];
								if (open(board[0][c0]) == true) {
									count++;
								}
							case 1:
								c1 = j + 2 * dice[0];
								if (open(board[0][c1]) == true) {
									count++;
								}
							case 2:
								c2 = j + 3 * dice[0];
								if (open(board[0][c2]) == true) {
									count++;

								}
							case 3:
								c2 = j + 4 * dice[0];
								if (open(board[0][c2]) == true) {
									count++;

								}
							default:
								break;
							}
						}
					}
					else if (i == 9) {
						if (board[8][j][1] == a) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j - dice[0];
								if (c0 > 0) {
									if (open(board[9][c0]) == true) {
										count++;
									}
								}
								else if (c0 < 0) {
									c0 = c0 * (-1);
									c0 = c0 - 1;
									if (open(board[0][c0]) == true) {
										count++;
									}
								}
							case 1:
								c1 = j - 2 * dice[1];
								if (c1 > 0) {
									if (open(board[9][c1]) == true) {
										count++;
									}
								}
								else if (c1 < 0) {
									c1 = c1 * (-1);
									c1 = c1 - 1;
									if (open(board[0][c1]) == true) {
										count++;
									}
								}
							case 2:

								c2 = j - 3 * dice[0];
								if (c2 > 0) {
									if (open(board[9][c2]) == true) {
										count++;
									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[0][c2]) == true) {
										count++;

									}
								}
							case 3:
								c2 = j - 4 * dice[0];
								if (c2 > 0) {
									if (open(board[9][c2]) == true) {
										count++;
									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[0][c2]) == true) {
										count++;

									}
								}
							default:
								break;
							}
						}
					}
				}
				else if (a == 'Y') {
					if (i == 0) {
						if (board[1][j][1] == a) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j - dice[0];
								if (c0 > 0) {
									if (open(board[0][c0]) == true) {
										count++;
									}
								}
								else if (c0 < 0) {
									c0 = c0 * (-1);
									c0 = c0 - 1;
									if (open(board[9][c0]) == true) {
										count++;
									}
								}
							case 1:
								c1 = j - 2 * dice[1];
								if (c1 > 0) {
									if (open(board[0][c1]) == true) {
										count++;
									}
								}
								else if (c1 < 0) {
									c1 = c1 * (-1);
									c1 = c1 - 1;
									if (open(board[9][c1]) == true) {
										count++;
									}
								}
							case 2:

								c2 = j - 3 * dice[0];
								if (c2 > 0) {
									if (open(board[0][c2]) == true) {
										count++;

									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[9][c2]) == true) {
										count++;

									}
								}
							case 3:

								c2 = j - 4 * dice[0];
								if (c2 > 0) {
									if (open(board[0][c2]) == true) {
										count++;

									}
								}
								else if (c2 < 0) {
									c2 = c2 * (-1);
									c2 = c2 - 1;
									if (open(board[9][c2]) == true) {
										count++;

									}
								}
							default:
								break;
							}
						}
					}
					else if (i == 9) {
						if (board[8][j][1] == a) {
							int b = 0;
							switch (b) {
							case 0:
								c0 = j + dice[0];
								if (open(board[9][c0]) == true) {
									count++;
								}
							case 1:
								c1 = j + 2 * dice[1];
								if (open(board[9][c1]) == true) {
									count++;
								}
							case 2:
								c2 = j + 3 * dice[0];
								if (open(board[9][c2]) == true) {
									count++;

								}
							case 3:
								c2 = j + 4 * dice[0];
								if (open(board[9][c2]) == true) {
									count++;

								}
							default:
								break;
							}
						}
					}
				}
			}
		}
	}
	else if (toplam == 3 * dice[0]) {
	 int c0 = 0, c1 = 0, c2 = 0; 
	 for (int i = 0; i < 10; i++) {
		 for (int j = 0; j < 12; j++) {
			 if (a == 'X') {
				 if (i == 0) {
					 if (board[1][j][1] == a) {
						 int b = 0;
						 switch (b)
						 {
						 case 0:
							 c0 = j + dice[0];
							 if (open(board[0][c0]) == true) {
								 count++;
							 }
						 case 1:
							 c1 = j + 2 * dice[0];
							 if (open(board[0][c1]) == true) {
								 count++;
							 }
						 case 2:
							 c2 = j + 3 * dice[0];
							 if (open(board[0][c2]) == true) {
								 count++;

							 }
						 default:
							 break;
						 }
					 }
				 }
				 else if (i == 9) {
					 if (board[8][j][1] == a) {
						 int b = 0;
						 switch (b) {
						 case 0:
							 c0 = j - dice[0];
							 if (c0 > 0) {
								 if (open(board[9][c0]) == true) {
									 count++;
								 }
							 }
							 else if (c0 < 0) {
								 c0 = c0 * (-1);
								 c0 = c0 - 1;
								 if (open(board[0][c0]) == true) {
									 count++;
								 }
							 }
						 case 1:
							 c1 = j - 2 * dice[1];
							 if (c1 > 0) {
								 if (open(board[9][c1]) == true) {
									 count++;
								 }
							 }
							 else if (c1 < 0) {
								 c1 = c1 * (-1);
								 c1 = c1 - 1;
								 if (open(board[0][c1]) == true) {
									 count++;
								 }
							 }
						 case 2:

							 c2 = j - 3 * dice[0];
							 if (c2 > 0) {
								 if (open(board[9][c2]) == true) {
									 count++;
								 }
							 }
							 else if (c2 < 0) {
								 c2 = c2 * (-1);
								 c2 = c2 - 1;
								 if (open(board[0][c2]) == true) {
									 count++;

								 }
							 }

						 default:
							 break;
						 }
					 }
				 }
			 }
			 else if (a == 'Y') {
				 if (i == 0) {
					 if (board[1][j][1] == a) {
						 int b = 0;
						 switch (b) {
						 case 0:
							 c0 = j - dice[0];
							 if (c0 > 0) {
								 if (open(board[0][c0]) == true) {
									 count++;
								 }
							 }
							 else if (c0 < 0) {
								 c0 = c0 * (-1);
								 c0 = c0 - 1;
								 if (open(board[9][c0]) == true) {
									 count++;
								 }
							 }
						 case 1:
							 c1 = j - 2 * dice[1];
							 if (c1 > 0) {
								 if (open(board[0][c1]) == true) {
									 count++;
								 }
							 }
							 else if (c1 < 0) {
								 c1 = c1 * (-1);
								 c1 = c1 - 1;
								 if (open(board[9][c1]) == true) {
									 count++;
								 }
							 }
						 case 2:

							 c2 = j - 3 * dice[0];
							 if (c2 > 0) {
								 if (open(board[0][c2]) == true) {
									 count++;

								 }
							 }
							 else if (c2 < 0) {
								 c2 = c2 * (-1);
								 c2 = c2 - 1;
								 if (open(board[9][c2]) == true) {
									 count++;

								 }
							 }

						 default:
							 break;
						 }
					 }
				 }
				 else if (i == 9) {
					 if (board[8][j][1] == a) {
						 int b = 0;
						 switch (b) {
						 case 0:
							 c0 = j + dice[0];
							 if (open(board[9][c0]) == true) {
								 count++;
							 }
						 case 1:
							 c1 = j + 2 * dice[1];
							 if (open(board[9][c1]) == true) {
								 count++;
							 }
						 case 2:
							 c2 = j + 3 * dice[0];
							 if (open(board[9][c2]) == true) {
								 count++;

							 }

						 default:
							 break;
						 }
					 }
				 }
			 }
		 }
	 }
	}
	if (count == 0) {
		cout << endl << "You do not have any right to move..." << endl;
		if (a == 'X') { a = 'Y'; }
		else if (a == 'Y') { a = 'X'; }
		rolldice();
		game();
	}
	else {
		instruction();
	}

}
bool finish() {
	
	if (a == 'Y') {
		for (int i = 0; i < 12; i++) {
			if (board[1][i][1] == 'Y') {
				return false;
			} 
		}
		for (int i = 0; i < 6; i++) {
			if (board[8][i][1] == 'Y') {
				return false;
			}
		}	
	} 
	if (a == 'X') {
		for (int i = 0; i < 12; i++) {
			if (board[8][i][1] == 'X') {
				return false;
			}
		}
		for (int i = 0; i < 6; i++) {
			if (board[1][i][1] == 'X') {
				return false;
			}
		}
		
	}
}

void finish2() {
	string s1;
	int d;
	cout << endl << "firstly, enter the number of the flake you want to move(like 02 or 13 etc.)" << endl;
	cin >> s1;
	
	if (s1 == "8") { guidance(8); }
	cout << "Please press 1 for collect flakes or press 2 for make a move: " << endl;
	cin >> d;
	if (d == 8) { guidance(8); }
	if (d == 1) { finish3(s1); }
	if (d == 2) { finish4(s1); }
	

}
void finish3(string k) {
	if (a == 'Y') {
		for (int i = 6; i < 12; i++) {
			if (board[9][i] == k) {
				if (dice[0] == 12 - i || dice[1] == 12 - i) {
					if (board[8][i] != "00") {
						cout << endl << "Your flake is collected from the " << k << "th place. " << endl;
						w2++;
						board[9][13] = to_string(w) + "Y";
						function2(k);
						showBoard();
						if (dice[0] == 12 - i) { toplam = toplam - dice[0]; }
						else if (dice[1] == 12 - i) { toplam = toplam - dice[1]; }
					}
					else {
						int y = 0;
						for (int j = i - 1; j < 7; j--) {
							if (board[8][j] == "00") {
								y++;
							}
						}
						if (y == i - 6) {
							for (int j = i + 1; j < 12; j++) {
								if (board[8][j] != "00") {
									cout << endl << "Your flake is collected from the " << board[8][j] << "th place. " << endl;
									w2++;
									board[9][13] = to_string(w) + "Y";
									function2(board[8][j]);
									showBoard();
									if (dice[0] == 12 - i) { toplam = toplam - dice[0]; }
									else if (dice[1] == 12 - i) { toplam = toplam - dice[1]; }
									break;
								}
							}
						}
						else {
							cout << endl << "You cannot collect flakes from here. Please choose different place..." << endl;
							finish2();
						}
					}
				}
				else {
					cout << endl << "Please choose different place..." << endl;
					finish2();
				}
			}
		}
		if (w2 == 15) {
			cout << endl << "Winner Y player..." << endl;
			remove("board.dat");
			remove("dice.txt");
			remove("countinue.txt");
			cout << endl << "The application is closing.." << endl;
			cout << "If you liked our app, don't forget to share it with your friends." << endl;
			cout << endl << "Have a nice day :)" << endl;
			exit(1);
		}
		if (toplam == 0) {
			a = 'X';
			rolldice();
			game();
		}
		else { finish2(); }
	}
	if (a == 'X') {
		for (int i = 6; i < 12; i++) {
			if (board[0][i] == k) {
				if (dice[0] == 12 - i || dice[1] == 12 - i) {
					if (board[1][i] != "00") {
						cout << endl << "Your flake is collected from the " << k << "th place. " << endl;
						w++;
						board[0][13] = to_string(w) + "X";
						function2(k);
						showBoard();
						if (dice[0] == 12 - i) { toplam = toplam - dice[0]; }
						else if (dice[1] == 12 - i) { toplam = toplam - dice[1]; }
					}
					else {
						int y = 0;
						for (int j = i - 1; j < 7; j--) {
							if (board[1][j] == "00") {
								y++;
							}
						}
						if (y == i - 6) {
							for (int j = i + 1; j < 12; j++) {
								if (board[1][j] != "00") {
									cout << endl << "Your flake is collected from the " << board[1][j] << "th place. " << endl;
									w++;
									board[0][13] = to_string(w) + "X";
									function2(board[1][j]);
									showBoard();
									if (dice[0] == 12 - i) { toplam = toplam - dice[0]; }
									else if (dice[1] == 12 - i) { toplam = toplam - dice[1]; }
									break;
								}
							}
						}
						else {
							cout << endl << "You cannot collect flakes from here. Please choose different place..." << endl;
							finish2();
						}
					}
				}
				else {
					cout << endl << "Please choose different place..." << endl;
					finish2();
				}
			}
		}
		if (w2 == 15) {
			cout << endl << "Winner X player..." << endl;
			remove("board.dat");
			remove("dice.txt");
			remove("countinue.txt");
			cout << endl << "The application is closing.." << endl;
			cout << "If you liked our app, don't forget to share it with your friends." << endl;
			cout << endl << "Have a nice day :)" << endl;
			exit(1);
		}
		if (toplam == 0) {
			a = 'Y';
			rolldice();
			game();
		}
		else { finish2(); }
	}

}
void finish4(string k) {
	string s1;
	string r[2];
	if (a == 'Y') {
		for (int i = 6; i < 12; i++) {
			if (board[9][i] == k) {
				if (i < 12 - dice[0] || i < 12 - dice[1]) {
					cout << endl << "Where do you want to move.." << endl;
					if (i < 12 - dice[0]) {
						cout << "0" << 12 - (i + dice[0]) << " / ";
						r[0] = "0" + to_string(12 - (i + dice[0]));
					}
					if (i < 12 - dice[1]) {
						cout << "0" << 12 - (i + dice[1]) << " / ";
						r[1] = "0" + to_string(12 - (i + dice[1]));
					}
					cin >> s1;
					if (s1 == "8") { guidance(8); }
					if (s1[1] == r[0][1]) {
						toplam = toplam - dice[0];
					}
					else if (s1[1] == r[1][1]) {
						toplam = toplam - dice[1];
					}
					function2(k);
					function(s1);


				}
				else {
					cout << endl << "Please choose different place..." << endl;
					finish2();
				}
				break;
			}
		}
		if (toplam == 0) {
			a = 'X';
			rolldice();
			game();
		}
		else { finish2(); }
	}
	if (a == 'X') {
		for (int i = 6; i < 12; i++) {
			if (board[0][i] == k) {
				if (i < 12 - dice[0] || i < 12 - dice[1]) {
					cout << endl << "Where do you want to move.." << endl;
					if (i < 12 - dice[0]) {
						cout << "0" << 12 - (i + dice[0]) << " / ";
						r[0] = "0" + to_string(12 - (i + dice[0]));
					}
					if (i < 12 - dice[1]) {
						cout << "0" << 12 - (i + dice[1]) << " / ";
						r[1] = "0" + to_string(12 - (i + dice[1]));
					}
					cin >> s1;
					if (s1 == "8") { guidance(8); }
					if (s1[1] == r[0][1]) {
						toplam = toplam - dice[0];
					}
					else if (s1[1] == r[1][1]) {
						toplam = toplam - dice[1];
					}
					function2(k);
					function(s1);
			


				}
				else {
					cout << endl << "Please choose different place..." << endl;
					finish2();
				}
				break;
			}
		}
		if (toplam == 0) {
			a = 'Y';
			rolldice();
			game();
		}
		else { finish2(); }
	}
}

void countinue(int i, string k) {
	int j = 0;
	for (int t = 0; t<k.length();t++){
		if (k[t] != ' ') {
			board[i][j].push_back(k[t]);
		}
		else if (k[t] == ' ') {
			j++;
			continue;
		}
	}

}

int main() {

	//start();
	ifstream dosyaOku("ca1.dat");
	string satir = "";
	if (dosyaOku.is_open()) {
		while (getline(dosyaOku, satir)) {
			cout << satir << endl;
		}
		dosyaOku.close();
	}

	return 0;
	
}