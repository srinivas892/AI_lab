#include<iostream>
using namespace std;
int board[9] = {2,2,2,2,2,2,2,2,2};
int winpos[8][3] ={
{0,1,2},
{3,4,5},
{6,7,8},
{2,4,6},  // winning condition
{0,4,8},
{0,3,6},
{1,4,7},
{2,5,8}};
void print(){
    for(int i = 0; i <9; i+= 3){
        for(int j = i; j <i + 3; j++ ){
            if(board[j] == 2)
            cout << "   " << "|";    
        if(board[j] == 3)
            cout << " X " << "|";          // prints the board
        if(board[j] == 5)
            cout << " O " << "|";
        } 
        cout << endl;
    }
    cout<<endl;
}
int iswin(){   // checks any one is win
    for(int i = 0; i <8; i++){
            if(board[winpos[i][0]] == board[winpos[i][1]] && board[winpos[i][1]] == board[winpos[i][2]] && board[winpos[i][1]] != 2) 
            return 1;
    }
return 0;

}

int poswin(int a){
    for(int i = 0; i <8; i++){
        int c = 0;
        int empty  = -1;
        for(int j = 0; j < 3; j++){
            if(board[winpos[i][j]] == a) c++;
            else if(board[winpos[i][j]] == 2) empty = winpos[i][j];   // checking the winning condition for next move
            else c--;
        }
    
        if(c == 2) return empty;
    }
return -1;

}
int anywhere(){
    for(int i = 0; i<9; i++){
        if(board[i] ==  2) return i; // enter the on any position
    }
    return -1;
}
void go( int a, int b){   // play the possition
    board[a] = b;
}
int make2(){
    if(board[4] == 2) return 4; 
    else if(board[1] == 2) return 1;
    else if(board[3] == 2) return 3;      // plays the middle position
    else if(board[5] == 2) return 5;
    else if(board[7] == 2) return 7;
    return -1;
}
void makemove(int a, int b, int c){    // playing condition according to the turns
    switch(a){
        case 0: go(0,b);
        break; 
        case 1:if(board[4] == 2) go(4, b);
            else go(0,b); 
            break;
        case 2:if(board[8]== 2)go(8,b);     
                else go(2,b);
            break;
        case 3:
          if(poswin(c) != -1) go(poswin(c), b);
          else if(board[2] == 2) go(2,b);
          else go(make2(),b);
          break;
        case 4:
            if(poswin(c) != -1){ go(poswin(c), b); }
              else if(poswin(b) != -1)  go(poswin(b), b);
               
               else if(board[6] == 2) go(6,b);
               else go(2,b);
               break;
        case 5:
           if(poswin(b) != -1) {go(poswin(b), b);}
           else if(poswin(c) != -1) go(poswin(c), b);
           else go(make2(),b);
            break;
        case 6:
        if(poswin(b) != -1) go(poswin(b), b);
        else if(poswin(c) != -1) go(poswin(c), b);
        else go(anywhere() , b);
        break;
        case 7:
        if(poswin(b) != -1) go(poswin(b), b);
        else if(poswin(c) != -1) go(poswin(c), b);
        else go(anywhere() , b);
        break;
        case 8:
        if(poswin(b) != -1) go(poswin(b), b);
        else if(poswin(c) != -1) go(poswin(c), b);
        else go(anywhere() , b);
        break;
        default: cout<<" wrong input";
        break;

    }

}
int main(){
    
    int a;
    cout<<"Enter the which player you want 3 for X or 5 for O";
    cin>>a;
    int i = 0;
    if(a == 3){    // if player choose X
        int comp = 5;
        cout<<"play \n";
        while(i<9){
            int x;
            switch(i){
                case 0:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 1:
                makemove(i,comp,a);
                break;
                case 2:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 3:
                makemove(i,comp,a);
                break;
                case 4:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 5:
                makemove(i,comp,a);
                break;
                case 6:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 7:
                makemove(i,comp,a);
                break;
                case 8:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;

            }
            print();
            if(iswin()){
                if(i%2 == 0)
                cout << "player O  is win";
                else cout<<"player X id win";
                return 0;
            }
            i++;
        }
    }

    else if(a == 5){   // if player choose the O
        int comp = 3;
        cout << " play \n";
        while(i<9){
            int x;
            switch(i){
                case 0:
               makemove(i,comp,a);
                break;
                case 1:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                
                break;
                case 2:
               makemove(i,comp,a);
                break;
                case 3:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 4:
                makemove(i,comp,a);
                break;
                case 5:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a; 
                else {cout << "wrong input" ; return -1;}
                break;
                case 6:
                 makemove(i,comp,a);
                break;
                case 7:
                cin>> x;
                if(board[x-1] == 2)
                board[x-1] = a;
                else {cout << "wrong input" ; return -1;}
                break;
                case 8:
                  makemove(i,comp,a);
                break;
                default: cout<<"wrong input";
        }
        print();
            if(iswin()){
                if(i%2 == 0)
                cout << "player X  is win";
                else cout<<"player O id win";
                return 0;
            }

        i++;
    }

    }
    else cout<< "wrong input";

    cout << "game is draw !!!"; // after loop exixution if nobody wins then draws
    
    return 0;
}

 
