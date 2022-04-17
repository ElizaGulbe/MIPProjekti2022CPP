#include <iostream>
#include <string>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
using namespace std;

string passwordChecker(string password){
    bool containsLetter = false;
    bool containsCapital = false;
    bool containsDigit = false; 
    bool containsSpecial = false; 
    string specialChars = "!@#$%^&*()_+-";
    for (int i = 0; i  < password.length() ; i++){ 
        char currChar = password[i];
        if(!containsLetter) containsLetter = isalpha(currChar);
        if(!containsCapital) containsCapital = isupper(currChar);
        if(!containsDigit) containsDigit = isdigit(currChar);
        if(!containsSpecial) containsSpecial = specialChars.find(currChar) != string::npos;
    }
    if(!containsLetter) throw ("Parolei jāsatur vismaz viens burts");
    if(!containsCapital) throw ("Parolei jāsatur vismaz viens lielais burts");
    if(!containsDigit) throw ("Parolei jāsatur vismaz viens cipars");
    if(!containsSpecial) throw ("Parolei jāsatur speciālais simbols - “!@#$%^&*()_+-");
    if (!(password.length() >= 8 && password.length() <= 12)) throw ("Parolei jābūt vismaz 8-12 simbolu garai");
    return password;
}

int main(){
    string password = "";
    while (true){
        cout << "Ievadiet paroli: ";
        cin >> password;
        try {
            password = passwordChecker(password);
        } 
        catch(char const* param) {
            cout << param << endl;
            cout << "Parole nav pietiekami stipra. Ievadiet jaunu paroli!" << endl; 
            continue;
        }
        system(CLEAR);
        break; 
    }
    cout << "Parole '" << password << "' ir pietiekami stipra" << endl;
    return 0; 
}