// Zeejai Leonard 
// 10 June 2020 
// CS280-451
// Knight Tour

#include <iostream>

class Position {
public:
    int x;
    int y;

    Position() { //apparently I need a default constructor 
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
    Position p; //position of this square on the board
    int visit; //record number of this square on the path
    int status; //the status of this square
    Position possibilities[8]; //the possible knight moves from this square (maximum of 8)

    KnightSquare() { //apparently I need a default constructor 
        visit = 0;
        status = 0; 
        p = Position(0, 0); 
    }

    void findPossibilities() {
        int n = 0; //start index at 0
        //if valid, add this position to the list of possibilities
        //increment index
        if (p.x + 1 <= 7) { //right 1
            if (p.y + 2 <= 7) { //down 2
                possibilities[n] = Position(p.x + 1, p.y + 2);
                n++;
            }
            if (p.y - 2 >= 0) { //up 2
                possibilities[n] = Position(p.x + 1, p.y - 2);
                n++;
            }
        }
        if (p.x + 2 <= 7) { //right 2
            if (p.y + 1 <= 7) { //down 1
                possibilities[n] = Position(p.x + 2, p.y + 1);
                n++;
            }
            if (p.y - 1 >= 0) { //up 1
                possibilities[n] = Position(p.x + 2, p.y - 1);
                n++;
            }
        }
        if (p.x - 1 >= 0) { //left 1
            if (p.y + 2 <= 7) { //down 2
                possibilities[n] = Position(p.x - 1, p.y + 2);
                n++;
            }
            if (p.y - 2 >= 0) { //up 2
                possibilities[n] = Position(p.x - 1, p.y - 2);
                n++;
            }
        }
        if (p.x - 2 >= 0) { //left 2
            if (p.y + 1 <= 7) { //down 1
                possibilities[n] = Position(p.x - 2, p.y + 1);
                n++;
            }
            if (p.y - 1 >= 0) { //up 1
                possibilities[n] = Position(p.x - 2, p.y - 1);
                n++;
            }
        }
    }

    KnightSquare(int i, int j) {
        p = Position(i, j); //give this square it's position
        visit = 0; //it hasn't been visited
        status = 0; //it hasn't been tried
        findPossibilities(); //give the list of possible knight moves from this square
    }

};

class Chessboard {
public: 
    KnightSquare board[8][8]; //create a standard chessboard
    int START = -1; //starting status
    int BEFORE = 0; //hasn't been tried
    int TEMP = 99; //currently trying
    int AFTER = 100; //works

    Chessboard() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                board[i][j] = KnightSquare(i, j); //populate chessboard with squares
            }
        }
        board[1][1].status = START; //set starting square
    }

    void printBoard() { //print the chessboard with path
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

    bool solve(int x, int y, int n) { //recursive solution
        bool found = false; 
        int i; 
        int j; 
        n++; //increment path number
        board[x][y].status = TEMP; //set square status to trying
        if (n == 64) { //if it's back to the starting square or it reached the end of the path
            found = true; //we've found a solution
            board[x][y].visit = n; // give this square a number on the path
            board[x][y].status = AFTER; //set square status to done
            return found; //then this obviously isn't the way to go
        } else { //otherwise if we aren't at the end
            for (int q = 0; q < 8; q++) { //try the max 8 possibilities from this square
                if (board[x][y].possibilities[q].x != -1 && board[x][y].possibilities[q].y != -1) { //if there is a possibility
                    i = board[x][y].possibilities[q].x; 
                    j = board[x][y].possibilities[q].y; 
                    if (board[i][j].status == BEFORE) { //if this possibility hasn't been tried before
                        found = solve(i, j, n); //recursive call with this possibility
                        if (found) { //if this possibility works
                            board[x][y].visit = n; //give this square a number on the path
                            board[x][y].status = AFTER; //set square status to done
                            return found; 
                        }
                    }
                }
                
            }
        }
        board[x][y].status = BEFORE; //this square didn't work for this path, check it again later
        return found; //all the possibilities didn't work, backtrack
    }

    bool solve() {
        return solve(1, 1, 0); //initial call
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
 