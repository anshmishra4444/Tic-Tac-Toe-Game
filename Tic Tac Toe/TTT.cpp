#include <iostream>
#include <vector>
using namespace std;

class Board {
private:
    vector<vector<char>> grid;
    const int size = 3;

public:
    Board() {
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }
    
    void displayBoard() {
        cout << "\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                cout << " " << grid[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << "\n";
            if (i < size - 1) cout << "---+---+---\n";
        }
        cout << "\n";
    }

    bool makeMove(int row, int col, char symbol) {
        if (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ') {
            grid[row][col] = symbol;
            return true;
        }
        return false;
    }

    char checkWinner() {
        for (int i = 0; i < size; i++) {
            if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][0] != ' ')
                return grid[i][0];
            if (grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[0][i] != ' ')
                return grid[0][i];
        }
        if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[0][0] != ' ')
            return grid[0][0];
        if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0] && grid[0][2] != ' ')
            return grid[0][2];
        return ' ';
    }

    bool isFull() {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (grid[i][j] == ' ')
                    return false;
        return true;
    }
};

class Player {
public:
    string name;
    char symbol;
    
    Player(string n, char s) : name(n), symbol(s) {}
};

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    Player *currentPlayer;

public:
    Game(string name1, char symbol1, string name2, char symbol2) 
        : player1(name1, symbol1), player2(name2, symbol2), currentPlayer(&player1) {}

    void switchPlayer() {
        currentPlayer = (currentPlayer == &player1) ? &player2 : &player1;
    }

    void play() {
        int row, col;
        while (true) {
            board.displayBoard();
            cout << currentPlayer->name << " (" << currentPlayer->symbol << "), enter row and column (0-2): ";
            cin >> row >> col;
            
            if (!board.makeMove(row, col, currentPlayer->symbol)) {
                cout << "Invalid move! Try again.\n";
                continue;
            }

            char winner = board.checkWinner();
            if (winner != ' ') {
                board.displayBoard();
                cout << currentPlayer->name << " wins!\n";
                break;
            }

            if (board.isFull()) {
                board.displayBoard();
                cout << "It's a draw!\n";
                break;
            }

            switchPlayer();
        }
    }
};

int main() {
    string name1, name2;
    cout << "Enter Player 1 name: ";
    cin >> name1;
    cout << "Enter Player 2 name: ";
    cin >> name2;
    
    Game game(name1, 'X', name2, 'O');
    game.play();
    return 0;
}
