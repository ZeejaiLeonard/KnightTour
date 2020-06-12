// Zeejai Leonard 
// 10 June 2020 
// CS280-451
// Knight Tour

#include <iostream>

class Position {
public:
    int x;
    int y;

    Position() {
        x = -1; 
        y = -1; 
    }

    Position(int i, int j) {
        x = i;
        y = j;
    }
};

class KnightSquare {
public:
    Position p;
    int visit;
    int status;
    Position possibilities[8];

    KnightSquare() {
        visit = 0;
        status = 0; 
        p = Position(0, 0); 
    }

    void findPossibilities() {
        int n = 0;
        if (p.x + 1 <= 7) {
            if (p.y + 2 <= 7) {
                possibilities[n] = Position(p.x + 1, p.y + 2);
                n++;
            }
            if (p.y - 2 >= 0) {
                possibilities[n] = Position(p.x + 1, p.y - 2);
                n++;
            }
        }
        if (p.x + 2 <= 7) {
            if (p.y + 1 <= 7) {
                possibilities[n] = Position(p.x + 2, p.y + 1);
                n++;
            }
            if (p.y - 1 >= 0) {
                possibilities[n] = Position(p.x + 2, p.y - 1);
                n++;
            }
        }
        if (p.x - 1 >= 0) {
            if (p.y + 2 <= 7) {
                possibilities[n] = Position(p.x - 1, p.y + 2);
                n++;
            }
            if (p.y - 2 >= 0) {
                possibilities[n] = Position(p.x - 1, p.y - 2);
                n++;
            }
        }
        if (p.x - 2 >= 0) {
            if (p.y + 1 <= 7) {
                possibilities[n] = Position(p.x - 2, p.y + 1);
                n++;
            }
            if (p.y - 1 >= 0) {
                possibilities[n] = Position(p.x - 2, p.y - 1);
                n++;
            }
        }
    }

    KnightSquare(int i, int j) {
        p = Position(i, j);
        visit = 0;
        status = 0;
        findPossibilities();
    }

};

class Chessboard {
public: 
    KnightSquare board[8][8]; 
    int START = -1; 
    int BEFORE = 0; 
    int TEMP = 99; 
    int AFTER = 100; 

    Chessboard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = KnightSquare(i, j); 
            }
        }
        board[0][0].status = START; 
    }

    void printBoard() {
        for (int r = 0; r < 8; r++) {
            for (int c = 0; c < 8; c++) {
                if (board[r][c].visit < 10) {
                    std::cout << " ";
                }
                std::cout << board[r][c].visit;
                std::cout << " ";
            }
            std::cout << "" << std::endl;
        }
    }

    bool solve(int x, int y, int n) {
        bool found = false; 
        int i; 
        int j; 
        if (board[x][y].status == TEMP) {
            board[x][y].visit = n; 
            return found; 
        }
        n++; 
        board[x][y].status = TEMP; 
        board[x][y].visit = n;
        if (board[x][y].p.x == 0 && board[x][y].p.y == 0 && n != 1) {
            found = true; 
            board[x][y].status = AFTER;
            return true; 
        } else {
            for (int q = 0; q < 8; q++) {
                if (board[x][y].possibilities[q].x != -1 && board[x][y].possibilities[q].y != -1) {
                    i = board[x][y].possibilities[q].x; 
                    j = board[x][y].possibilities[q].y; 
                    if (board[i][j].status == BEFORE) {
                        found = solve(i, j, n); 
                        if (found) {
                            board[x][y].visit = n;
                            board[x][y].status = AFTER; 
                            return found; 
                        }
                    }
                }
                
            }
        }
        return found; 
    }

    bool solve() {
        return solve(0, 0, 0);
    }

};

int main() {
    std::cout << "Zeejai Leonard Presents: The Knight's Tour" << std::endl;
    std::cout << "Once upon a time ..." << std::endl; 
    Chessboard c = Chessboard(); 
    c.solve(); 
    c.printBoard(); 
    std::cout << "The End." << std::endl;
}
 