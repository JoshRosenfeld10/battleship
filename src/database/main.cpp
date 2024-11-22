#include "database.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(){
    Database db;

    try{
        db.load();
    } catch(DatabaseException &message) {
        cerr << message.getMessage() << endl;
        return 1;
    }

    string username = "user1";
    string password = "password1";
    int totalWin = 10;
    int totalLoss = 5;
    int totalGame = 15;
    int hits = 100;
    int turns = 200;

    if (!db.addBaseUser(username, password, IconColour::BLUE)) {
        cerr << "User already exists" << endl;
        return 1;
    }

    if (!db.changeUserAllStats(username, password, totalWin, totalLoss, totalGame, hits, turns)) {
        cerr << "User not found" << endl;
        return 1;
    } else {
        db.pushToFile();
        cout << "User entered" << endl;
    }

    cout << "User entered" << endl;

    string username2 = "user2";
    string password2 = "password2";
    int totalWin2 = 20;
    int totalLoss2 = 10;
    int totalGame2 = 30;
    int hits2 = 200;
    int turns2 = 400;

    if (!db.addBaseUser(username2, password2, IconColour::RED)) {
        cerr << "User already exists" << endl;
        return 1;
    }

    if (!db.changeUserAllStats(username2, password2, totalWin2, totalLoss2, totalGame2, hits2, turns2)) {
        cerr << "User not found" << endl;
        return 1;
    }
    else {
        db.pushToFile();
        cout << "User entered" << endl;
    }

    
    string username3 = "user3";
    string password3 = "password3";

    if (!db.addBaseUser(username3, password3, IconColour::RED)) {
        cerr << "User already exists" << endl;
        return 1;
    }else {
        db.pushToFile();
        cout << "User entered" << endl;
    }

    totalWin2 = 20 + 1;
    totalLoss2 = 10 + 2;
    totalGame2 = 30 + 3;
    hits2 = 200;
    turns2 = 400;
    
    if (!db.changeUserAllStats(username2, password2, totalWin2, totalLoss2, totalGame2, hits2, turns2)) {
        cerr << "User not found" << endl;
        return 1;
    }
    else {
        db.pushToFile();
        cout << "User entered" << endl;
    }
}