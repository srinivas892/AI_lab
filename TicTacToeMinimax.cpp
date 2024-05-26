#include<iostream>
#include<vector>
using namespace std;
#include<limits.h>



vector<int> board={2,2,2,2,2,2,2,2,2};
vector<vector<int>> win ={{0,1,2}, {3,4,5}, {6,7,8},{0,4,8}, {2,4,6}, {0,3,6},{1,4,7},{2,5,8}};
// 3-x for player
// 5-o for comp
// 2 empty

void printBoard(){
    cout<<"Current Board Position: \n";
    string ele;
    cout<<"-------------\n";
    for(int i=0; i<9; i++){
        if(board[i]==2) ele = "   ";
        if(board[i]==3) ele = " X ";
        if(board[i]==5) ele = " O ";
        cout<<"|"<<ele;
        if((i+1)%3==0) cout<<"|"<<'\n'<<"-------------\n";
    }
}
int checkWin(int x){
    for(int i=0; i<8; i++){
        int c=0;
        for(int j=0; j<3; j++){
            if(board[win[i][j]] == x) c++;
        }
        if(c==3) return 1;
    }
    return 0;
}
int checkDraw(){
    for(int i=0; i<9; i++){
        if(board[i] ==2) return 0;
    }
    return 1;
}
int miniMax(bool maximizing){
    if(checkWin(3)) return -1000;
    if(checkWin(5)) return 1000;
    if(checkDraw()) return 0;
    
    if(maximizing){
        int bestVal=INT_MIN;
        for (int i = 0; i < 9; i++)
        {
            if(board[i]==2){
                board[i]=5;
                bestVal=max(miniMax(!maximizing),bestVal);
                board[i]=2;
            }
        }
        return bestVal;
    }else{
        int bestVal=INT_MAX;
        for (int i = 0; i < 9; i++)
        {
            if(board[i]==2){
                board[i]=3;
                bestVal=min(miniMax(!maximizing),bestVal);
                board[i]=2;
            }
        }
        return bestVal;
    }
    
}
void player(){
    int pos;
    cout<<"Enter Position : ";
    cin>>pos;
    if(board[pos] == 2) board[pos]=3;
    else  player();
}
void computer(){
    int bestScore=INT_MIN;
    int bestPos=-1;
    for(int i=0; i<9; i++){
        if(board[i]==2){
            board[i]=5;
            int score = miniMax(false);
            if(bestScore<score){
                bestScore = score;
                bestPos = i;
            }
            board[i]=2;
        }
    }
    board[bestPos] = 5;
}
int main(){
    printBoard();
    while (1)
    {
        player();
        printBoard();
        if(checkWin(3)){
            cout<<"You have Won the Game";
            break;
        }
        if(checkDraw()){
            cout<<"Draw";
            break;
        }
        computer();
        printBoard();
        if(checkWin(5)){
            cout<<"Com have Won the Game";
            break;
        }
        if(checkDraw()){
            cout<<"Draw";
            break;
        }
    }
    return 0;
}