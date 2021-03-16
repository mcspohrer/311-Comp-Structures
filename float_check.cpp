/*Matthew Spohrer
 * CS311
 * Floating point checker program
 *
 * This program reads in a string from an external data file 
 * and check if it is a floating point via a Deterministic
 * Finite Automata */
#include <iostream>
#include <fstream>
using namespace std;

//The states are all DFA[][0], [0][0] is initial state,
//[1][0],[4][0],[6][0], and [8][0] are accepting
//-1 represents the dead state
//column [0][1] represents 0-9
//column [0][2] reps a '.'
//column [0][3] reps a '+' or a '-'
//column [0][4] reps a 'e' or 'E'
const int DFA[9][5] = {
    {0, 1, 3, 2,-1},
    {1, 1, 4,-1, 5},
    {2, 1, 3,-1,-1},
    {3, 6,-1,-1,-1},
    {4, 4,-1,-1, 5},
    {5, 8,-1, 7,-1},
    {6, 6,-1,-1, 5},
    {7, 8,-1,-1,-1},
    {8, 8,-1,-1,-1},
};

const int SIZE = 100;//Max Size of the string

int check(char []);

int main(int argc, char * argv[]) {
    int state = 0;
    ifstream file_in;
    char to_check[100] = {'\0'};

    file_in.open(argv[1]);//opens the file with the name input by the user
    //checks if the file was opened
    if (!file_in) { 
        cout << "\n\nInvalid file name, please try again!\n\n";
        return 0; }
    
    //gets the first string to test
    if (file_in.peek() == '\n') {
        to_check[0] = '\0';
        file_in.ignore();
    } else {
        file_in.get(to_check, SIZE, '\n');
        file_in.ignore(100, '\n');
    }

    //reads in the rest of the file, one string at a time and checks 
    //which are strings and which are not 
    while(file_in && !file_in.eof()) {
        state = check(to_check);
        if (to_check[0] != '\0') cout << endl << to_check << ": ";
        else cout << endl << "Empty String: ";

        if(state == 1 || state == 4 || state == 6 || state == 8) cout << "accept\n";
        else cout << "reject\n";
        
        if (file_in.peek() == '\n') {
            to_check[0] = '\0';
            file_in.ignore();
            continue;
        }
        
        file_in.get(to_check, SIZE, '\n');
        file_in.ignore(100, '\n');
    }

    file_in.close();
    file_in.clear();

}

/*goes through each character of the string entered and uses the dfa table to determine
 * if the string should be accepted as a floating point */
int check(char to_check[]) {
    int cur_state = 0;

    for (int i = 0; to_check[i] != '\0'; ++i) {
        if (to_check[i] >= '0' && to_check[i] <= '9') cur_state = DFA[cur_state][1];
        else if (to_check[i] == '.') cur_state = DFA[cur_state][2];
        else if (to_check[i] == '+' || to_check[i] == '-') cur_state = DFA[cur_state][3];
        else if (to_check[i] == 'e' || to_check[i] == 'E') cur_state = DFA[cur_state][4];
        else cur_state = -1;
        if (cur_state == -1) return cur_state;
    }
    return cur_state;
}
