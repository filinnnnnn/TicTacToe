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
void drawBoard(const std::vector<char>& board);
char winner(const std::vector<char>& board);
bool canMove(const std::vector<char>& board, int move);
int humanMove(const std::vector<char>& board, char human);
int computerMove(const std::vector<char> board, char computer);
void anounceWinner(char winner, char computer, char human);

int main ()
{
    int move;
    const int SQURES = 9;
    std::vector<char> board(SQURES, EMPTY);
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
            board[move] = human;
        }
        else
        {
            move = computerMove(board, computer);
            board[move] = computer;
        }
        drawBoard(board);
        turn = openentPeace(turn);
    }
    anounceWinner(winner(board), computer, human);
    return 0;
}

//release functions
void instructions()
{
    std::cout << "\n\t\tWelcome to TicTacToe fight!";
    std::cout << "\n\t\tTry to win, try think human :)";
    std::cout << "\nMake your turn, by entering a number: 0-8;";
    std::cout << "\nTable of positions of numbers you can see below:\n";
    std::cout << "\n 0 | 1 | 2 ";
    std::cout << "\n-----------";
    std::cout << "\n 3 | 4 | 5 ";
    std::cout << "\n-----------";
    std::cout << "\n 6 | 7 | 8 ";
    std::cout << "\n\nEverithing starts by 0, everithing...";
    std::cout << "\nNever mind, human! Let's start our fight!!!";
};

char askYesNo(std::string question)
{
    char answer;
    do
    {
        std::cout << question;
        std::cin >> answer;
    } while (answer != 'y' && answer != 'n' );
    return answer;
};

int askNumber(std::string question, int high, int low)
{
    int number;
    do
    {
        std::cout << question << "(" << low << "-" << high << "): ";
        std::cin >> number;
    } while (number > high || number < low );
    return number;
};

char humanPeace()
{
    char goFirst = askYesNo("\nSo human, you can choose... Do you want first turn?\n");
    if(goFirst == 'y')
    {
        std::cout << "\nI can't wait for the fight, human! Lat's make your first turn. Ah-ah-ah...\n";
        return X;
    } else
    {
        std::cout << "\nAh-ah-ah... You will lose bravely! Let's begin!";
        return O;
    }
};

char openentPeace(char piece)
{
    if (piece == 'X')
    {
        return O;
    }
    else
    {
        return X;
    }
};
void drawBoard(const std::vector<char>& board)
{
    std::cout << "\n " << board[0] << " | " << board[1] << " | " << board[2];
    std::cout << "\n" << "-----------";
    std::cout << "\n " << board[3] << " | " << board[4] << " | " << board[5];
    std::cout << "\n" << "-----------";
    std::cout << "\n " << board[6] << " | " << board[7] << " | " << board[8];
    std::cout << "\n\n";
    
};

char winner(const std::vector<char>& board)
{
    const int WINCONDITIONS[8][3] =
    { {0, 1, 2},
      {3, 4, 5},
      {6, 7, 8},
      {0, 3, 6},
      {1, 4, 7},
      {2, 5, 8},
      {0, 4, 8},
      {2, 4, 6} };
    
    const int TOTAL_WIN_ROW = 8;
    
    for (int row = 0; row < TOTAL_WIN_ROW; ++row)
    {
        // if any winning row has three values that are the same (and not EMPTY),
        // then we have a winner
        if ((board[WINCONDITIONS[row][0]] != EMPTY) &&
            (board[WINCONDITIONS[row][0]] == board[WINCONDITIONS[row][1]]) &&
            (board[WINCONDITIONS[row][1]] == board[WINCONDITIONS[row][2]]) )
            {
                return board[WINCONDITIONS[row][0]]; //first symbol of win row
            }
    }
    
    //cheking for a tie
    if(std::count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;
    
    //if we don't find a winer - returning game
    return NO_ONE;
};

inline bool canMove(const std::vector<char>& board, int move)
{
    return (board[move] == EMPTY); //return true if place is empty, else false
};

int humanMove(const std::vector<char>& board, char human)
{
    int move = askNumber("Were will you make your fist move?", (board.size() - 1));
    while (!canMove(board, move))
    {
        std::cout << "\nThat square is already occupied, foolish human.\n";
        move = askNumber("Where will you move?", (board.size() - 1));
    }
    std::cout << "Fine...\n";
    return move;
};

int computerMove(std::vector<char> board, char computer)
{
    unsigned int move = 0;
    bool found = false;
    
    //if machine can win to next move - make it
    while (!found && move < board.size())
    {
        if (canMove(board, move))
        {
            board[move] = computer;
            found = winner(board) == computer;
            board[move] = EMPTY;
        }
        if (!found)
        {
            ++move;
        }
    }
    
    //if human can win to next move - block it
    if (!found)
    {
        move = 0;
        char human = openentPeace(computer);
        while (!found && move < board.size())
        {
            if (canMove(board, move))
            {
                board[move] = human;
                found = winner(board) == human;
                board[move] = EMPTY;
            }
            if (!found)
            {
                ++move;
            }
            
        }
    }
    
    //make the best open sqere move
    if (!found)
    {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVES[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};
        while (!found && i < board.size())
        {
            move = BEST_MOVES[i];
            if (canMove(board, move))
            {
                found = true;
            }
            ++i;
        }
    }
    std::cout << "Let me think! Ah-ah-ah. I'll put my turn here...\n";
    return move;
};

void anounceWinner(char winner, char computer, char human)
{
    if (winner == computer)
    {
        std::cout << winner << "'s won!";
        std::cout << "\nAs i predicted, human! I am triumphant. Again! :)";
    }
    else if (winner == human)
    {
        std::cout << winner << "'s won!\n";
        std::cout << "\nNo, no! It cannot be! Somehow you tricked me, human.";
        std::cout << "\nBut never again!  I, the computer, so swear it! :(";
    }
    else
    {
        std::cout << "\nIt's a tie.";
        std::cout << "\nYou were most lucky, human, and somehow managed to tie me.";
        std::cout << "\nCelebrate... for this is the best you will ever achieve! :/";
    }
        
};
