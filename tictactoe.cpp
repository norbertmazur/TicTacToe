#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctime>

using namespace std;
typedef vector<vector<char>> Table;

//all it does is check if there are any blank spaces
int countFreeSpaces(int, Table);
void computerVSplayer (Table);
void playerVSplayer (Table);
void playerMove(Table &board, char, string);
void displayBoard(Table board);

//checks the board for a winner
bool check(Table board, char, char, string, string );



//checks for a draw based on free spaces and if the last move was a win
bool draw(Table); 

//checks if x and y are located within the given size and if the square is occupied
bool valid(int x, int y, int size, Table);

//checks whether coordinates belong to the board
bool belongsToBoard(int, int, int);

//whether a square does not have any neighbours
bool notalone(Table, int, int);

//states the possible moves a computer is going to have
vector<pair<int, int>> possibleMoves(Table);
void computerMove(Table &board, char, string);
void game();

int main()
{
	char ans;
	cout<<"\nWelcome to TicTacToe! \n";
	do {
		game();
		cout << "\n\nDo you wish to play again?\nEnter Y if yes, N if no.\nWhat's your choice?: "; 
		cin >> ans;
	}while (ans == 'Y');
		cout<<"\nThank you for playing! Goodbye!";
	return 0;
}

void game()
{
	Table board;
	int size;
	char sign;
	bool with_Computer;
	char ans;
	cout<<"\nEnter the size of the board (from 3 - 10): ";
	cin>>size;
	if ((size>10) || (size<3)){
		cout<<"\nInvalid size. Restart the game to try again!";
	}
	else{		
		board= Table(size, vector<char>(size, ' '));
		if ((size==3) || (size==4)) cout<<"\nThree characters in a row needed to win!\n";
		else cout<<"\nFive characters in a row needed to win!\n";
		cout<<"\nWhich gamemode do you want to play? \nFor Player vs Player enter 0 \nFor Computer vs Player enter 1 \nWhat's your choice?: ";
		cin >> with_Computer;
		if (with_Computer == 1){
			computerVSplayer(board);
		}
		else{
			playerVSplayer(board);
		}
	}
}

void displayBoard(Table board)
{
	int size = board.size();
	cout<<" ";
	for (int y = 0; y < size; y++)
	{
		cout<<" "<< y;
	}
	cout << endl;

    for (int y = 0; y < size-1; y++)
    {
		cout<< y<< " ";
        for (int x = 0; x < size-1; x++)
        {
            cout << board [x][y] << '|';
        }
        cout << board [size - 1][y] << '\n';
		cout<< " " <<" ";
        for (int x = 0; x < 2 * size - 1; x++)
        {
            cout <<'-';
        }
        cout << '\n';
    }
	cout<< size-1<< " ";
    for (int x = 0; x < size - 1; x++)
    {
        cout << board[x][size - 1] << '|';
    }
    cout << board [size - 1][size - 1] << "\n" << endl;
}

bool valid(int x, int y, int size, Table board)
{

	if ((x<size) && (y<size) && (x>=0) && (y>=0)){ 
		if (board[y][x] ==' '){
			return true;
		}
		else{
			cout<<"This square is already occupied. You lose your move.\n";
			return false;
		}
	}
	else{
		cout<<"The coordinates you entered are located out of the table. You lose your move.";
		return false;
	}
}

void computerVSplayer(Table board)
{
	string namePlayer, nameComputer;
	char sign1, sign2;
	int x, y;

	cout<<"Enter Your name: ";
	cin>> namePlayer;
	nameComputer = "Computer";

	char signs[2] = { 'X', 'O' };
	srand(time (0));
	sign1 = signs[rand() % 2];
	cout<< namePlayer<< " plays with "<< sign1<<"\n";
	if (sign1 == 'X') sign2='O';
	else sign2 ='X';
	cout<< nameComputer<< " plays with "<< sign2<<"\n";

	int first;
	srand (time(0));
    first=rand () % 2 + 1 ;

	if(first==1){
		do
		{
			cout<<"\n";
			displayBoard(board);

			playerMove(board, sign1, namePlayer);
			if(check(board, sign1, sign2, namePlayer, nameComputer) || draw(board)) break;

			displayBoard(board);

			computerMove(board, sign2, nameComputer);

			if(check(board, sign1, sign2, namePlayer, nameComputer) || draw(board)) break;
		} while ((check(board, sign1, sign2, namePlayer, nameComputer) == false) && (draw(board) == false));
	}else{
		do
		{
			cout<<"\n";
			displayBoard(board);

			computerMove(board, sign2, nameComputer);
			if(check(board, sign1, sign2, namePlayer, nameComputer) || draw(board)) break;

			displayBoard(board);

			playerMove(board, sign1, namePlayer); 

		} while ((check(board, sign1, sign2, namePlayer, nameComputer) == false) && (draw(board) == false));
	}
}

//helper: win length based on board size
int getWinLength(int size) {
	return (size == 3 || size == 4) ? 3 : 5;
}

//helper: check if board is full
bool isBoardFull(const Table &board) {
	int n = board.size();
	for (int r = 0; r < n; ++r)
		for (int c = 0; c < n; ++c)
			if (board[r][c] == ' ') return false;
	return true;
}

//helper: find winner ('X' or 'O'), or ' ' if none
char findWinner(const Table &board) {
	int n = board.size();
	int win = getWinLength(n);
	//directions: right, down, down-right, down-left
	const int dx[4] = {0, 1, 1, 1};
	const int dy[4] = {1, 0, 1, -1};
	for (int r = 0; r < n; ++r) {
		for (int c = 0; c < n; ++c) {
			char ch = board[r][c];
			if (ch == ' ') continue;
			for (int d = 0; d < 4; ++d) {
				int rr = r + (win - 1) * dx[d];
				int cc = c + (win - 1) * dy[d];
				if (rr < 0 || rr >= n || cc < 0 || cc >= n) continue;
				bool ok = true;
				for (int k = 1; k < win; ++k) {
					int nr = r + k * dx[d];
					int nc = c + k * dy[d];
					if (board[nr][nc] != ch) { ok = false; break; }
				}
				if (ok) return ch;
			}
		}
	}
	return ' ';
}

// Minimax with alpha-beta pruning
int minimax(Table &board, int depth, bool maximizing, char ai, char human, int alpha, int beta) {
	char w = findWinner(board);
	if (w == ai) return 100000 + depth;
	if (w == human) return -100000 - depth;
	if (depth == 0 || isBoardFull(board)) return 0;

	vector<pair<int,int>> moves = possibleMoves(board);
	if (moves.empty()) return 0;

	if (maximizing) {
		int best = INT_MIN;
		for (auto &m : moves) {
			int r = m.first, c = m.second;
			board[r][c] = ai;
			int val = minimax(board, depth - 1, false, ai, human, alpha, beta);
			board[r][c] = ' ';
			best = max(best, val);
			alpha = max(alpha, best);
			if (beta <= alpha) break;
		}
		return best;
	} else {
		int best = INT_MAX;
		for (auto &m : moves) {
			int r = m.first, c = m.second;
			board[r][c] = human;
			int val = minimax(board, depth - 1, true, ai, human, alpha, beta);
			board[r][c] = ' ';
			best = min(best, val);
			beta = min(beta, best);
			if (beta <= alpha) break;
		}
		return best;
	}
}

//computer move using Minimax (alpha-beta). Uses row/col indexing.
void computerMove(Table &board, char sign2, string nameComputer)
{
	int n = board.size();
	char ai = sign2;
	char human = (ai == 'X') ? 'O' : 'X';

	vector<pair<int,int>> moves = possibleMoves(board);
	if (moves.empty()) return;

	int depthLimit;
	if (n <= 3) depthLimit = 9;
	else if (n == 4) depthLimit = 6;
	else if (n <= 6) depthLimit = 4;
	else depthLimit = 3;

	int bestScore = INT_MIN;
	vector<pair<int,int>> bestMoves;
	for (auto &m : moves) {
		int r = m.first, c = m.second;
		board[r][c] = ai;
		int score = minimax(board, depthLimit - 1, false, ai, human, INT_MIN, INT_MAX);
		board[r][c] = ' ';
		if (score > bestScore) {
			bestScore = score;
			bestMoves.clear();
			bestMoves.push_back(m);
		} else if (score == bestScore) {
			bestMoves.push_back(m);
		}
	}

	srand((unsigned)time(0));
	pair<int,int> choice = bestMoves[rand() % bestMoves.size()];
	int r = choice.first, c = choice.second;
	cout << "Computer moves at row: " << c << ", column: " << r << "\n";
	// store using same convention as playerMove (board[row][col])
	board[r][c] = sign2;
}

int countFreeSpaces(int size, Table board) 
{
	int freeSpace = size*size;

	//iterates through the table and checks how many there are free spaces
	for (int y = 0; y < size-1; y++)
	{
		for (int x = 0; x < size-1; x++)
		{
			if (board[y][x]!=' '){ 
				freeSpace--;
			}
		}
	}
	return freeSpace;
}

bool draw(Table board) 
{
	int size=board.size();
	if((countFreeSpaces(size, board) == 0))
	{
		cout<<"\nNo more possible moves. Game ends in a draw!";
		return true;
	}
	return false;
}

void playerVSplayer(Table board)
{
	string name1, name2;
	char sign1, sign2;
	int x, y;
	cout<<"Enter Player's 1 name: ";
	cin>>name1;

	cout<<"Enter Player's 2 name: ";
	cin>> name2;
	if(name1==name2) cout<<"Names cannot be the same! Try again!";
	else{
		//randomly selects the char 
		char signs[2] = { 'X', 'O' };
		srand(time (0));
		sign1 = signs[rand() % 2];
		if (sign1 == 'X') sign2='O';
		else sign2 ='X';

		cout<<"\n\n";
		cout<< name1<< " plays with "<< sign1<< "\n";

		cout<< name2<<" plays with "<<sign2<< "\n";

		srand (time(0));
		int first;
		first=rand () % 2 + 1 ;

		if(first==1){	
			do
			{
				cout<<"\n";
				displayBoard(board);

				playerMove(board, sign1, name1); 
				if((check(board, sign1, sign2, name1, name2)) || (draw(board))) break;

				displayBoard(board);

				playerMove(board, sign2, name2);

			} while ((check(board, sign1, sign2, name1, name2) == false) && (draw(board) == false));
		}else {
			do
			{
				cout<<"\n";
				displayBoard(board);

				playerMove(board, sign2, name2); 
				if((check(board, sign1, sign2, name1, name2)) || (draw(board))) break;

				displayBoard(board);

				playerMove(board, sign1, name1);

			} while ((check(board, sign1, sign2, name1, name2) == false) && (draw(board) == false));
		}
	}
} 
void playerMove(Table &board, char sign1, string name1)
{
	int size = board.size();
	int x;
	int y;
	do{
		cout<< name1<< " moves!\n\n";

		cout<<"Enter row: ";
		cin>> x;
		
		cout<<"Enter column: ";
		cin>> y;

		if(valid(x, y, size, board))
		{
			board[y][x] = sign1; 
			break;
		}
	}
	while(board[y][x] == ' ');
}


bool check(Table board, char sign1, char sign2, string name1, string name2)
{
	char winner = findWinner(board);
	if (winner == ' ') return false;
	
	// Display the final board state showing the winning pattern
	cout << "\n";
	displayBoard(board);
	
	// winner is either 'X' or 'O' — print the correct player's name
	if (winner == sign1) cout << "Congratulations! " << name1 << " wins!";
	else if (winner == sign2) cout << "Congratulations! " << name2 << " wins!";
	else cout << "Congratulations! Unknown wins!";
	
	return true;
}




//not really needed
bool belongsToBoard(int x, int y, int size) {
	return (0 < x) && (x < size) && (0 < y) && (y < size);
}

bool notalone(Table board, int x, int y) {
	return (board[x][y+1] != ' ') ||
		   (board[x][y-1] != ' ') ||
		   (board[x+1][y] != ' ') ||
		   (board[x-1][y] != ' ') ||

		   (board[x+1][y+1] != ' ') ||
		   (board[x-1][y-1] != ' ') ||
		   (board[x+1][y-1] != ' ') ||
		   (board[x-1][y+1] != ' ');

}

vector<pair<int, int>> possibleMoves(Table board) {

	vector<pair<int, int>> temp;

	int size = board.size();
	for (int x = 1; x < size-1; x++) {
		for (int y = 1; y < size-1; y++) {
			bool empty = (board[x][y] == ' ');
			if(notalone(board, x, y) && empty) {
				temp.push_back({x, y});
			}
		}	
	}

	// if there exist cells with some neighbors
	if (temp.size() > 0) return temp;

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (board[x][y] == ' ') {
				temp.push_back({x, y});
			}
		}	
	}
	return temp;
}