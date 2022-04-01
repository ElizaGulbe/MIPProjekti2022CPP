#include <iostream>
#include <string>
#include <string.h>
#include <regex>
#include <iomanip>  
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
using namespace std;
struct PlayerData {
    string playerName;
    int gamesWon;
    int drawGames; 
    int gamesLost;
};

struct Game {
    int totalGames;
    int drawGames;
    PlayerData &player1;
    PlayerData &player2;
};
PlayerData player1 = {"", 0, 0, 0};
PlayerData player2 = {"", 0, 0, 0};
Game theGame = {0, 0, player1, player2};

string outputChar(int element){
    switch (element){
    case -1:
        return " ";
    case 0:
        return "O";
    case 1:
        return "X";
    default:
        cout << "Programmas darbība pārtrāukta iekšējās kļūdas dēļ!" << endl;
        exit(-1); 
    }
}

void drawGraphics(int listOfFigures[9]){
     system(CLEAR);
    cout
        << setfill(' ')
        << setw(20)
        << "Kollona1"
        << setfill(' ')
        << setw(10)
        << "Kollona2"
        << setfill(' ')
        << setw(10)
        << "Kollona3"
        << endl;
    for (int i = 0; i < 3; i++)
    {
        cout
            << "Rinda" << i + 1
            << setfill(' ')
            << setw(10)
            << outputChar(listOfFigures[i*3]) // outputChar pārveido listOfFigure vērtības par tradicionāli pieņemtajiem simboliem spēlē desas
            << setfill(' ')
            << setw(10)
            << outputChar(listOfFigures[i*3+1])
            << setfill(' ')
            << setw(10)
            << outputChar(listOfFigures[i*3+2])
            << endl;
    }
}

int figurePlacement(){  // pārbauda vai spēlētājs ir atzīmējis pareizi rindu un kollonu 
    int row = 0;
    int column = 0;
    regex integer_expr("[1-3]");
    while (true){
        string row_s;
        cout << "Ievadiet skaitli rindas vērtību no 1 līdz 3: ";
        cin >> row_s;
        if (!cin) exit(-1);
        if (regex_match(row_s, integer_expr)) {
            row = stoi(row_s);
            break;
        }
         cout << "Kļūda.Ievadiet skaitli no 1 līdz 3." << endl; 
    }
    while (true){
        cout << "Ievadiet skaitli kollonas vērtību no 1 līdz 3: ";
        string column_s;
        cin >> column_s;
        if (!cin) exit(-1);
        if (regex_match(column_s, integer_expr)) {
            column = stoi(column_s);
            break;
        } 
        cout << "Kļūda. Kollonas vērtībai jābūt skaitlim no 1 līdz 3." << endl;
    }
    return (row-1)*3 + column-1; // atgriež spēlētāja izvēlēto lokāciju 
}
int checkIfWinner(int listOfFigures[9]){
    int winner;
    for (int i = 0 ; i < 3 ; i++){
        if((listOfFigures[i] == listOfFigures[i+3] && listOfFigures[i+3] == listOfFigures[i+6]) && listOfFigures[i] != -1){ // iet cauri kollonām
            winner = listOfFigures[i]; // atgriež uzvarētāja indeksu masīvā "allPlayers" funkcijā "launchGame"
            return winner;
        }
        if((listOfFigures[i*3] == listOfFigures[i*3+1] && listOfFigures[i*3+1] == listOfFigures[i*3+2]) && listOfFigures[i*3] != -1){ // iet cauri rindām
            winner = listOfFigures[i*3];
            return winner;
        }
    }
    if((listOfFigures[0] == listOfFigures[4] && listOfFigures[4] == listOfFigures[8]) && listOfFigures[0] != -1){ // pārbauda diognāli
        winner = listOfFigures[0];
        return winner; 
    } else if((listOfFigures[2] == listOfFigures[4] && listOfFigures[4] == listOfFigures[6]) && listOfFigures[2] != -1){ // pārbauda diognāli
        winner = listOfFigures[2];
        return winner; 
    } else { 
         return -1;
    }
}

void printStatistics(){ 
    system(CLEAR);
    cout << "\nDati par spēli:" << endl;
    cout << "Kopējais spēļu skaits:  " << theGame.totalGames << endl;
    cout << "Neizšķirto spēļu skaits:  " << theGame.drawGames << endl;
    cout << "\nSpēlētāju dati: " << endl;
    cout <<  endl <<theGame.player1.playerName << endl; 
    cout << "Uzvarēto spēļu skaits: " << theGame.player1.gamesWon << endl; 
    cout << "Zaudēto spēļu skaits: " << theGame.player1.gamesLost << endl;
    cout << "Neizšķirto spēļu skaits:" << theGame.player1.drawGames << endl; 
    cout << endl <<theGame.player2.playerName << endl; 
    cout << "Uzvarēto spēļu sk1aits: " << theGame.player2.gamesWon << endl; 
    cout << "Zaudēto spēļu skaits: " << theGame.player2.gamesLost << endl;
    cout << "Neizšķirto spēļu skaits:" << theGame.player2.drawGames << endl;
    sleep(6);
    system(CLEAR);
}

void delelteAllPlayerData(){
     player1.gamesLost = 0;
     player1.drawGames = 0;
     player1.gamesWon = 0;
     player2.gamesLost = 0;
     player2.drawGames = 0;
     player2.gamesWon = 0;
     theGame.totalGames = 0;
     theGame.drawGames = 0;
}

void launchGame(){
    int startingPlayer = theGame.totalGames % 2; 
    // nosaka kurš spēlētājs sāks spēli atkarībā no izspēlēto spēļu skaita
    PlayerData* allPlayers[2];
    if(startingPlayer){
        allPlayers[0]  = &player2;
        allPlayers[1]  = &player1;
    } else {
        allPlayers[0]  = &player1;
        allPlayers[1] = &player2;
    }
    int totalMovements = 0;
    int gameLayout[9]; // glabā spēlētāju gājienus
    for (int i = 0; i < 9 ; i++) gameLayout[i] = -1;
    // masīvā gameLayout -1 reprezentē tukšās vietas, savukārt 0 reprezentēs pirmā spēlētāja gājienus, 1 - otrā spēlētāja gājienus
    for(int i = 0; i < 9 ; i++){
        drawGraphics(gameLayout); // funkcijas, kas izsauc spēles uzzīmēšanu 
        cout << endl <<allPlayers[0]->playerName << " - " << "O   ";
        cout << allPlayers[1]->playerName << " - " << "X" << endl;
        cout <<  "Spēlētāj," << allPlayers[i % 2]->playerName << ", lūdzu, veiciet gājienu!" << endl; 
        while (true){
            int location  = figurePlacement(); // funkcija kas apstrāda ievadi, atgriež spēlētāja izvēlēto lokāciju
            if (gameLayout[location] > -1 ){ // ja lokācija jau ir aizņemta, spēlētājam jāievada jauna ievade
                cout << "šis lauks jau ir aizņemts. Izvēlieties citu." << endl;
            } else {
                int currentTurn = i % 2; // nosaka, kura spēlētāja kārta šobrīd ir
                gameLayout[location] = currentTurn; // pievieno spēlētāja gājienu spēles datu masīvā
                break;
            }
        }
        totalMovements++;
        int winner = -1; 
        if (totalMovements >= 5){ // spēlētājam iespējams vinnēt tikai tad, ja spēlē kopā ir bijuši vismaz 5 gājieni
            winner = checkIfWinner(gameLayout); // pārbauda vai kāds no spēlētājiem ir uzvarējis, atgriež, uzvarējošā spēlētāju lokāciju masīvā "allPlayers"
            if (winner > -1){ // j
            theGame.totalGames++;
            PlayerData* winningPlayer = allPlayers[winner]; 
            drawGraphics(gameLayout);
            cout << "Apsveicam spēlētāju " <<winningPlayer->playerName << " ar uzvaru" << endl;
            winningPlayer->gamesWon++;
            int loser = winner == 1 ? 0 : 1; // nosaka zaudētāja adresi 
            PlayerData* losingPlayer = allPlayers[loser];
            losingPlayer->gamesLost++;
            sleep(3);
            return; 
            }
            if (totalMovements == 9){ // ja kopā bijuši jau 9 gājieni un neviens nav uzvarējis, tiek paziņots neizšķirts
            drawGraphics(gameLayout);
            cout << "Neizšķirts spēles rezultāts" << endl;
            theGame.totalGames++;
            theGame.drawGames++; 
            allPlayers[0]->drawGames++;
            allPlayers[1]->drawGames++;
            sleep(3);
            return; 
            }
        } 

        

    }
}

int launchConsole(){
    cout << "\nIzvēlne:" << endl; 
    cout << "1 - turpināt spēli" << endl;
    cout << "2 - izdzēst līdzšinējos spēles datus" << endl; 
    cout << "3 - beigt spēli" << endl; 
    int userChoice = 0;
    regex integer_expr("[1-3]");
    while (true){ // pārbauda, vai lietotāji ievadījuši pareizo izvēli
        string input;
        cout << "Ievadiet skaitli no 1 līdz 3: ";
        cin >> input;
        if (!cin) break;
        if (regex_match(input, integer_expr)){
            userChoice = stoi(input);
            break;
        }
        cout << "Kļūda.Ievadiet skaitli no 1 līdz 3." << endl; 
    }
    return userChoice; // atgriež lietotāju izvēli 
}

string addUsername(){
    string input;
    regex integer_expr("[A-Za-z]+"); // spēlētāja segvārds var sastāvēt tikai no lielajiem vai mazajiem burtiem + segvārda garums 2-10 zīmes
    while (true){
        cout << "Ievadiet segvārdu: ";
        cin >> input;
        if (!cin) break;
        if (regex_match(input, integer_expr) && input.length() >= 2 && input.length() <= 10) break; 
        cout << "segvārdam jābūt 2-10 zīmes garam un var tikt ievietoti tikai burti\n";
    }
    return input;
}

void launchIntro(){ // pievieno struct game speletāju segvārdus
    printf("Esiet sveicināti spēlē desas!\n");
    printf("Ievadiet 1. spēlētāja segvārdu!\n (segvārdam jābūt 2-10 zīmes garam, un var tikt ievietoti tikai burti)\n");
    string nicknamePlayer1 = addUsername();
    player1.playerName = nicknamePlayer1;
    system(CLEAR);
    printf("Ievadiet 2. spēlētāja segvārdu!\n (segvārdam jābūt 2-10 zīmes garam, un var tikt ievietoti tikai burti)\n");
    string nicknamePlayer2 = addUsername();
    player2.playerName = nicknamePlayer2;
}

int main() {
     launchIntro();
     system(CLEAR);
     while (true) {
         int userChoice = launchConsole(); 
         switch (userChoice)
         {
         case 1:
            launchGame();
            printStatistics(); // pēc katras partijas parādās kopējie spēles dati 
            break;
         case 2:
            delelteAllPlayerData(); // izdzēš līdzšinējo statistiku, atstāj tikai segvārdus
            break;
         case 3:
            cout << "Spēles darbība pārtraukta" << endl;
            exit(0);
            break; 
         default:
             exit(-1);
             break;
         }

     }
}
