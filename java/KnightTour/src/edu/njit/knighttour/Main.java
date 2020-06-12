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

    KnightSquare[][] board = new KnightSquare[8][8];
    public int START = -1;
    public int BEFORE = 0;
    public int TEMP = 99;
    public int AFTER = 100;

    public Chessboard(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                board[i][j] = new KnightSquare(i, j);
            }
        }
        board[0][0].status = START;
    }

    public boolean solve(){
        return solve(0, 0, 0);
    }

    public boolean solve(int x, int y, int n){
        boolean found = false;
        int i;
        int j;
        if(board[x][y].status == TEMP || board[x][y].status == AFTER){
            board[x][y].visit = n;
            return found;
        }
        n++;
        board[x][y].status = TEMP;
        board[x][y].visit = n;
        if(board[x][y].status == START || n == 63){
            found = true;
            board[x][y].visit = n;
            board[x][y].status = AFTER;
            return found;
        }else{
            for(int q = 0; q < 8; q++){
                if(board[x][y].possibilities[q] != null){
                    i = board[x][y].possibilities[q].x;
                    j = board[x][y].possibilities[q].y;
                    if(board[i][j].status == BEFORE){
                        found = solve(i, j, n);
                        if(found){
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

    public void printBoard(){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                if(this.board[i][j].visit < 10){
                    System.out.print(" ");
                }
                System.out.print(this.board[i][j].visit);
                System.out.print(" ");
            }
            System.out.println();
        }
    }
}

class KnightSquare {

    Position p;
    int visit;
    int status;
    Position[] possibilities;

    public KnightSquare(int x, int y){
        p = new Position(x, y);
        visit = 0;
        status = 0;
        possibilities = findPossibilities();
    }

    public Position[] findPossibilities(){
        Position[] poss = new Position[8];
        int n = 0;
        if(this.p.x + 1 <= 7){
            if(this.p.y + 2 <= 7){
                poss[n] = (new Position(this.p.x + 1, this.p.y + 2));
                n++;
            }
            if(this.p.y - 2 >= 0){
                poss[n] = (new Position(this.p.x + 1, this.p.y - 2));
                n++;
            }
        }
        if(this.p.x + 2 <= 7){
            if(this.p.y + 1 <= 7){
                poss[n] = (new Position(this.p.x + 2, this.p.y + 1));
                n++;
            }
            if(this.p.y - 1 >= 0){
                poss[n] = (new Position(this.p.x + 2, this.p.y - 1));
                n++;
            }
        }
        if(this.p.x - 1 >= 0){
            if(this.p.y + 2 <= 7){
                poss[n] = (new Position(this.p.x - 1, this.p.y + 2));
                n++;
            }
            if(this.p.y - 2 >= 0){
                poss[n] = (new Position(this.p.x - 1, this.p.y - 2));
                n++;
            }
        }
        if(this.p.x - 2 >= 0){
            if(this.p.y + 1 <= 7){
                poss[n] = (new Position(this.p.x - 2, this.p.y + 1));
                n++;
            }
            if(this.p.y - 1 >= 0){
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

