package edu.njit.knighttour;
// Zeejai Leonard
// 10 June 2020
// CS280-451
// Knight Tour

public class Main {
    public static void main(String[] args) {
        System.out.println("Zeejai Leonard Presents: The Knight's Tour");
        System.out.println("Once upon a time ...");
        Chessboard c = new Chessboard();
        c.solve();
        c.printBoard();
        System.out.println("The End");
    }
}

class Chessboard {

    KnightSquare[][] board = new KnightSquare[8][8]; //create a standard chessboard
    public int START = -1; //starting status
    public int BEFORE = 0; //hasn't been tried
    public int TEMP = 99; //currently trying
    public int AFTER = 100; //works

    public Chessboard(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                board[i][j] = new KnightSquare(i, j); //populate chessboard with squares
            }
        }
        board[1][1].status = START; //set starting square
    }

    public boolean solve(){
        return solve(1, 1, 0);
    } //initial call

    public boolean solve(int x, int y, int n){ //recursive solution
        boolean found = false;
        int i;
        int j;
        n++; //increment path number
        board[x][y].status = TEMP; //set square status to trying
        if(n == 64){ //if it's back to the starting square or it reached the end of the path
            found = true; //we've found a solution
            board[x][y].visit = n; //give this square a number on the path
            board[x][y].status = AFTER; //set square status to done
            return found;
        } else { //otherwise if we aren't at the end
            for(int q = 0; q < 8; q++){ //try the max 8 possibilities from this square
                if(board[x][y].possibilities[q] != null){ //if there is a possibility
                    i = board[x][y].possibilities[q].x;
                    j = board[x][y].possibilities[q].y;
                    if(board[i][j].status == BEFORE){ //if this possibility hasn't been tried before
                        found = solve(i, j, n); //recursive call with this possibility
                        if(found){ //if this possibility works
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

    public void printBoard(){ //print the chessboard with path
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(board[i][j].visit < 10){
                    System.out.print(" ");
                }
                System.out.print(board[i][j].visit);
                System.out.print(" ");
            }
            System.out.println();
        }
    }
}

class KnightSquare {

    Position p; //position of this square on the board
    int visit; //record number of this square on the path
    int status; //the status of this square
    Position[] possibilities; //the possible knight moves from this square

    public KnightSquare(int x, int y){
        p = new Position(x, y); //give this square it's position
        visit = 0; //it hasn't been visited
        status = 0; //it hasn't been tried
        possibilities = findPossibilities(); //give the list of possible knight moves from this square
    }

    public Position[] findPossibilities(){
        Position[] poss = new Position[8]; //maximum of 8 possible moves
        int n = 0; //start index at 0
        //if valid, add this position to the list of possibilities
        //increment index
        if(this.p.x + 1 <= 7){ //right 1
            if(this.p.y + 2 <= 7){ //down 2
                poss[n] = (new Position(this.p.x + 1, this.p.y + 2));
                n++;
            }
            if(this.p.y - 2 >= 0){ //up 2
                poss[n] = (new Position(this.p.x + 1, this.p.y - 2));
                n++;
            }
        }
        if(this.p.x + 2 <= 7){ //right 2
            if(this.p.y + 1 <= 7){ //down 1
                poss[n] = (new Position(this.p.x + 2, this.p.y + 1));
                n++;
            }
            if(this.p.y - 1 >= 0){ //up 1
                poss[n] = (new Position(this.p.x + 2, this.p.y - 1));
                n++;
            }
        }
        if(this.p.x - 1 >= 0){ //left 1
            if(this.p.y + 2 <= 7){ //down 2
                poss[n] = (new Position(this.p.x - 1, this.p.y + 2));
                n++;
            }
            if(this.p.y - 2 >= 0){ //up 2
                poss[n] = (new Position(this.p.x - 1, this.p.y - 2));
                n++;
            }
        }
        if(this.p.x - 2 >= 0){ //left 2
            if(this.p.y + 1 <= 7){ //down 1
                poss[n] = (new Position(this.p.x - 2, this.p.y + 1));
                n++;
            }
            if(this.p.y - 1 >= 0){ //up 1
                poss[n] = (new Position(this.p.x - 2, this.p.y - 1));
                n++;
            }
        }
        return poss;
    }

}

class Position {
    int x;
    int y;

    public Position(int x, int y){
        this.x = x;
        this.y = y;
    }
}

