//
//  main.cpp
//  Locate-me
//
//  Created by Wooldridge, Jesse on 12/8/18.
//  Copyright © 2018 Wooldridge, Jesse. All rights reserved.
//

#include <iostream>

using namespace std;

void displayPlayer(int player_num, char (&player_arr)[15][15]){
    cout << "** Player " << player_num << endl;
    for(int i = 0; i<15; i++){
        for(int j = 0; j<15; j++){
            cout << player_arr[i][j];
        }
        cout << endl;
    }
    
}

void initArray(char (&player_arr)[15][15]){
    for(int i = 0; i< 15; i ++){
        for(int j = 0; j < 15; j++){
            player_arr[i][j]='*';
        }
    }
}

void pickPoints(int player_num,  char (&player_arr)[15][15], int num_points){
    int x;
    int y;
    
    cout << "Picking points for Player "<< player_num << endl;
    for(int i = 0; i< num_points; i++){
        int this_point = num_points - i;
        cout << "Add your secret grid points -> x,y coordinates. You have -" << this_point << "- left" << endl;
        cout << "Input X Coord of secret point # " << this_point << " ";
        cin >> x;
        cout << "Input Y Coord of secret point # " << this_point << " ";
        cin >> y;
        player_arr[x][y] = 'x';
        displayPlayer(player_num, player_arr);
        
    }
    cout << "All Done!" << endl;
    
}

int guessPoints(int player_num, char(&enemy_arr)[15][15], int num_right){
    bool guessed_wrong = false;
    int x;
    int y;
    
    while(!guessed_wrong){
        cout << "Player "<< player_num << ": Guess a point!" << endl;
        cout << "Input X coordinate of guess: ";
        cin >> x;
        cout << "Input Y coordinate of guess: ";
        cin >> y;
        cout << "Checking your opponent's grid..." << endl;
        if(enemy_arr[x][y] == 'x'){
            cout << "You guessed wisely! Get another turn!" << endl;
            enemy_arr[x][y] = 'P';
            num_right++;
            guessed_wrong = false;
        } else {
            cout << "You guessed incorrectly. Your turn is over!" << endl;
            guessed_wrong = true;
        }
    }

    return num_right;
}
int main() {
    char player1[15][15];
    char player2[15][15];
    int player1_num = 1;
    int player2_num = 2;
    int num_to_win = 1;
    int player1_right=0;
    int player2_right=0;
    bool somebody_won = false;
    bool picking_points = true;
    
    
    // start game
    cout << "Welcome to Locate Me!" << endl;
    initArray(player1);
    initArray(player2);
    
    while(!somebody_won){
        // pick the player points
        if(picking_points){
            cout << "** Choosing Points Round **" << endl;
            pickPoints(player1_num, player1, num_to_win);
            pickPoints(player2_num, player2, num_to_win);
            picking_points = false;
        }
        // guess the player points
        cout << "** Guessing Points Round **" << endl;
        if(!somebody_won){
            player1_right = guessPoints(player1_num, player2, player1_right);
            if(player1_right >= num_to_win) {
                somebody_won = true;
            }
        }
        // check again because player 1 might have guessed all the points of player 2
        if(!somebody_won){
            player2_right = guessPoints(player2_num, player1, player1_right);
            if(player2_right >= num_to_win){
                somebody_won = true;
            }
        }
        
    }
    
    // end game
    cout << "Player 1 had " << player1_right << " correct guesses" << endl;
    cout << "Player 2 had " << player2_right << " correct guesses" << endl;
    
    if(player1_right > player2_right) {
        cout << "Player 1 Wins!" << endl;
    } else {
        cout << "Player 2 Wins1" << endl;
    }
    
    return 0;
}
