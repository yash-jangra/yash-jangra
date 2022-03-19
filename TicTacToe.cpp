#include<bits/stdc++.h>

using namespace std;

int startgame(){
    cout<<"Hey user, I want to play Tic-Tac-Toe with you!"<<endl
        <<"What symbol will you use?"<<endl
        <<"X or O?"<<endl;
    char ch;
    cin>>ch;
    int user=5;
    if(ch == 'O' || ch=='o'){
        user=5;
    }
    else{
        user = 3;
    }
    return user;
}

void invert_user(int &user){
    if(user==3){
        user = 5;
    }
    else{
        user = 3;
    }
}

void make_move(vector<vector<int>> &board, int pos, int user){
    int i=0, j=0;
    if(pos==1){
        i=0, j=0;
    }
    else if(pos==2){
        i=0, j=1;
    }
    else if(pos==3){
        i=0, j=2;
    }
    else if(pos==4){
        i=1, j=0;
    }
    else if(pos==5){
        i=1, j=1;
    }
    else if(pos==6){
        i=1, j=2;
    }
    else if(pos==7){
        i=2, j=0;
    }
    else if(pos==8){
        i=2, j=1;
    }
    else{
        i=2, j=2;
    }
    board[i][j]=user;
    return;
}

int non_corner(vector<vector<int> > &board){
    if(board[0][1] == 2){
        return 2;
    }
    else if(board[1][0] == 2){
        return 4;
    }
    else if(board[1][2] == 2){
        return 6;
    }
    else if(board[2][1] == 2){
        return 8;
    }
    return 0;
}

int rowmatching(vector<vector<int>>& board, int target){
    for(int i=0; i<3; i++){
        int prod= 1;
        for(int j=0; j<3; j++){
            prod *= board[i][j];
        }
        if(prod == target){
            int pos = i*3+1;
            if(i==0){
                pos=1;
            }

            for(int j = 0; j<3; j++){
                if(board[i][j] == 2){
                    pos+=j;
                }
            }
            return pos;
        }
    }
    return 0;
}

int columnmatching(vector<vector<int>>&board, int target){
    int pos=0;
    for(int i = 0; i<3; i++){
        int prod = 1;
        for(int j=0; j<3; j++){
            prod*= board[j][i];
        }
        if(prod == target){
            for(int j=0; j<3; ++j){
                if(board[j][i]==2){
                    pos = 3*j+1+i;
                    return pos;
                }
            }
        }
    }
    return 0;
}

int diagonalmatching(vector<vector<int>>&board, int target){
    if(board[0][0]*board[1][1]*board[2][2] == target){
        if(board[0][0]==2){
            return 1;
        }
        else if(board[1][1] == 2){
            return 5;
        }
        else{
            return 9;
        }
    }
    else if(board[0][2]*board[1][1]*board[2][0] == target){
        if(board[0][2]==2){
            return 3;
        }
        else if(board[1][1] == 2){
            return 5;
        }
        else{
            return 7;
        }
    }
    return 0;
}

int corners(vector<vector<int>> & board){
    if(board[0][0]==2){
        return 1;
    }
    else if(board[0][2]==2){
        return 3;
    }
    else if(board[2][0] == 2){
        return 7;
    }
    else if(board[2][2]==2){
        return 9;
    }
    return 0;
}
int posswin(vector<vector<int>>& board, int user){
    int opponent = user;
    invert_user(opponent);
    int user_target = 2*user*user, opp_target = 2*opponent*opponent;
    
    int pos=0;
    // Checking best position for current user.
    if(rowmatching(board, user_target)){
        pos = rowmatching(board, user_target);
    }
    else if(columnmatching(board, user_target)){
        pos = columnmatching(board, user_target);
    }
    else if(diagonalmatching(board, user_target)){
        pos = diagonalmatching(board, user_target);
    }
    if(pos){
        return pos;
    }

    // Checking for Opponent.
    if(rowmatching(board, opp_target)){
        pos = rowmatching(board, opp_target);
    }
    else if(columnmatching(board, opp_target)){
        pos = columnmatching(board, opp_target);
    }
    else if(diagonalmatching(board, opp_target)){
        pos = diagonalmatching(board, opp_target);
    }
    if(pos){
        return pos;
    }  
    
    if(non_corner(board)){
        pos = non_corner(board);
    }

    if(pos){
        return pos;
    }
    return corners(board);
}


int check_victory(vector<vector<int> >&board){
    // Checking rows first.
    if(board[0][0]==board[0][1] and board[0][1]==board[0][2]){
        return board[0][0];
    }
    else if(board[1][0]== board[1][1] and board[1][1]==board[1][2]){
        return board[1][0];
    }
    else if(board[2][0]==board[2][1] and board[2][1]==board[2][2]){
        return board[2][0];
    }

    // Checking columns.
    if(board[0][0]==board[1][0] and board[1][0]==board[2][0]){
        return board[0][0];
    }
    else if(board[0][1]==board[1][1] and board[1][1]==board[2][1]){
        return board[0][1];
    }
    else if(board[0][2]==board[1][2] and board[1][2]==board[2][2]){
        return board[0][2];
    }

    //Checking the diagonals.
    if((board[0][0]==board[1][1] and board[1][1]==board[2][2]) || 
    (board[0][2]==board[1][1] and board[0][2]==board[2][0])){
        return board[1][1];
    }

    return 2;
}

void display(vector<vector<int>>&board){
    cout<<endl;
    for(int i=0; i<3; ++i){
        for(int j=0; j<3; ++j){
            cout<<board[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int main(){
    int user = startgame(), player = user, victory = 2;
    vector<vector<int>> board(3, vector<int> (3, 2)); // Filling the board with 2 as 2 symbolises empty square.
    unordered_set<int> occupied_positions; // For storing the positions that are occupied.

    invert_user(player);
    while(victory!=1 and victory!=3 and victory != 5){
        invert_user(player);
        if(player== user){
            cout<<"Enter the position for your move!"<<endl;
            int pos;
            while(cin>>pos){
                if(occupied_positions.count(pos)==0){
                    occupied_positions.insert(pos);
                    break;
                }
                else{
                    cout<<"Position already occupied! \nEnter the position Again."<<endl;
                }
            }
            make_move(board, pos, player);
        }
        else{
            cout<<"My turn! Move at position ";
            int pos;
            if(board[1][1]==2){
                pos = 5;
            }
            else if(posswin(board, player)){
                pos = posswin(board, player);
            }
            if(!pos){
                victory= player==user?user:player;
                break;
            }
            cout<<pos<<"."<<endl;
            make_move(board, pos, player);
            occupied_positions.insert(pos);
        }
        display(board);
        victory = check_victory(board);
    }

    if(victory==user){
        cout<<"Congrats! you are the winner."<<endl;
    }
    else{
        cout<<"You lost! Better luck next time. :p"<<endl;
    }
    return 0;
}