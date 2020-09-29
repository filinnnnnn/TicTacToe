#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//gobal variables
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

//prototypes
void instructions();
char askYesNo(std::string question);
int askNumber(std::string question, int high, int low = 0);
char humanPeace();
char openentPeace(char piece);
void drawBoard(const std::vector<int>& board);
char winner(const std::vector<int>& board);
bool canMove(const std::vector<int>& board, int move);
int humanMove(const std::vector<int>& board, char human);
int computerMove(const std::vector<int> board, char computer);
void anounceWinner(char winner, char computer, char human);

int main ()
{
    int move;
    const int SQURES = 9;
    std::vector<int> board(SQURES, EMPTY);
    instructions();
    char human = humanPeace();
    char computer = openentPeace(human);
    char turn = X;
    drawBoard(board);
    while (winner(board) == NO_ONE)
    {
        if (turn == human)
        {
            move = humanMove(board, human);
            board[move] == human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] == computer;
        }
        drawBoard(board);
        turn = openentPeace(turn);
    }
    anounceWinner(winner(board), computer, human);
    return 0;
}

//release functions
