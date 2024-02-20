

#include <iostream>
#include <string>

using namespace std;

string player= "X" ;
string name1, name2, input;
    
void Print(string matrix[3][3]){
    cout << "Current board: " << endl;
    cout << " " <<matrix[0][0] << " | " << matrix[0][1] << " | " << matrix[0][2] << endl;
    cout << "-----------" << endl;
    cout << " " <<matrix[1][0] << " | " << matrix[1][1] <<" | " << matrix[1][2] << endl;
    cout << "-----------" << endl;
    cout << " " <<matrix[2][0] << " | " << matrix[2][1] <<" | " << matrix[2][2] << endl;
}

bool checkFormat (string input){
    char sign;
    int inputLength;
    string left1, right1;
    inputLength = input.length();
    sign = input.find("-",0);
    left1 = input.substr(0,sign);
    right1 = input.substr(sign +1, inputLength);
    if (right1 == "1" && left1 == "1"){
        return true;
    }
    if(right1 == "1" && left1 == "2"){
        return true;
    }
    if(right1 == "1" && left1 == "3"){
        return true;
    }
    if(right1 == "2" && left1 == "1"){
        return true;
    }
    if(right1 == "2" && left1 == "2"){
        return true;
    }
    if(right1 == "2" && left1 == "3"){
        return true;
    }
    if(right1 == "3" && left1 == "1"){
        return true;
    }
    if(right1 == "3" && left1 == "2"){
        return true;
    }
    if(right1 == "3" && left1 == "3"){
        return true;
    }
        else{
            return false;
        }
    }

bool checkWinner(string matrix[3][3] , string player){
    string player1, player2;

    for (int i=0;i<3;i++){
        if (((matrix[i][0] == matrix[i][1] && matrix[i][2] == matrix[i][0])&&(matrix[i][0] ==player)) || ((matrix[0][i] == matrix[1][i] && matrix[0][i] == matrix[2][i]) && (matrix[1][i] == player))){
        return true;
        }
    }
    if (((matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2]) && (matrix[1][1] == player)) || ((matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0]) && (matrix[2][0] == player))){
        return true;
    }
     else{
         return false;
         
     }
    return false;
}

void playerMove(string name, string player, string matrix[3][3]){
    int row = 0, column = 0;
    string input;
    
    if (player == "X"){
        cout <<  name << ", please enter your move: ";
        cin >> input;
    }
    //checkFormat(input);
    
    if (player == "O"){
        cout<< name << ", please enter your move: ";
        cin >> input;
    }

    checkFormat(input);
    bool z = false;
    while(z == false){
        string left1, right1;
        if (checkFormat(input) == true){
            if(right1 == "1" && left1 == "1"){
                row = 0;
                column = 0;
            }
            if(right1 == "1" && left1 == "2"){
                row=0;
                column=1;
            }
            
            if(right1 == "1" && left1 == "3"){
                row=0;
                column=2;
            }
            
            if(right1 == "2" && left1 == "1"){
                row=1;
                column=0;
            }
            
            if(right1 == "2" && left1 == "2"){
                row=1;
                column=1;
            }
            
            if(right1 == "2" && left1 == "3"){
                row=1;
                column=2;
            }
            if(right1 == "3" && left1 == "1"){
                row=2;
                column=0;
            }
            if(right1 == "3" && left1 == "2"){
                row=2;
                column=1;
            }
            if(right1 == "3" && left1 == "3"){
                row=2;
                column=2;
            }
            
            if( player == "X" && matrix[row][column] != "X" && matrix[row][column] != "O"){
                matrix[row][column] = "X";
                z = true;
            }
        
            else if ( player == "O" && matrix[row][column] != "O" && matrix[row][column] != "X"){
                matrix[row][column] = "O";
                z = true;
            }
        
            else{
                cout<< "That location is already full!"<< endl;
                cout<<  name << ", please enter your move: ";
                cin >> input;
                z = false;
            }
        }
        else{
            cout << "Please enter correct move format!" << endl;
            cout<<  name << ", please enter your move: ";
            cin >> input;
            z = false;
        }
    }
    //Print(matrix);
}

void playGame(string name1, string player1, string name2, string player2, int &score1, int &score2 ){
    string matrix[3][3] = {{" ", " ", " " }, {" ", " ", " " }, {" ", " ", " "}};
    string input;
    score1 = 0;
    score2 = 0;
    int mark = 0;
    
    cout << "Starting a new game..."<< endl;
    //cout << "Starting a new game..."<< endl;
    Print(matrix);
    bool z = true;
    while(z == true){
        playerMove (name1, player1, matrix);
        mark += 1;
        //playerMove (name2, player, "O", matrix);
        
        if (checkWinner(matrix, player1) ==true){
            score1 ++;
            cout << name1 << " is the winner!";
            break;
        }
        
        if(checkWinner(matrix, player2)==false && mark >= 9 && checkWinner(matrix, player1)==false){
            //score2 ++;
            cout << "The game ended in a draw!" << endl;
            break;
        }
        
        Print(matrix);
        playerMove (name2, player2, matrix);
        mark += 1;
        
        if(checkWinner(matrix, player2) == true){
            score2++;
            cout <<name2 << " is the winner!";
            cout << endl;
            break;
        }
        Print(matrix);
    }
}

int main(){
    string name1,name2, player1, player2;
    int point1 = 0;
    int point2 = 0;
    string matrix[3][3] = {{" ", " ", " " }, {" ", " ", " " }, {" ", " ", " "}};
    cout << "Welcome to Tic-Tac-Toe!" << endl;
    cout << "Player 1, please enter your name: ";
    cin >>name1;
    cout << "Hello, " <<name1 << ". You are going to play with X" << endl;
    cout << "Player 2, please enter your name: ";
    cin >> name2;
    cout << "Hello, " << name2 <<". You are going to play with O" << endl << endl;
    //cout << "Starting a new game..." << endl;
    //Print(matrix);
    //string input;
    //cout << "move: ";
    //cin >> input;
    //if(checkFormat(input))
        //cout << "OK";
    
    playGame(name1, "X", name2, "O", point1, point2);
    cout << "Current Scores: " << endl;
    cout << name1 << ": " << point1 << "   " <<name2 << ": " << point2 <<endl;
    cout << endl;
   
    playGame(name2, "O", name1, "X", point2, point1);
    cout << "Current Scores: " << endl;
    cout << name1 << ": " << point1 << "   " << name2 << ": " << point2 <<endl;
    cout << endl;
   
   //playerMove (name2, name2, "O", matrix);
    cout << "Final Scores: " << endl;
    cout << name1 << ": " << point1 << "   " << name2 << ": " << point2 <<endl;
    
    if (point1 > point2){
        cout << name1 << " is the overall winner!" << endl;
    }
    if (point2 > point1){
        cout << name2 << " is the overall winner!"<< endl;;
    }
    if (point1 == point2){
        cout << "The overall game ended in a draw!" << endl;
    }
    return 0;
}
