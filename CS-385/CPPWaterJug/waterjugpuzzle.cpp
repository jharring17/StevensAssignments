/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Jack Harrington && Zach Scarpati
 * Date        : October 16, 2021
 * Description : Solving Water Jug puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// State Struct used to represent the states of the waterjugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

/**
 * * display
 * Displays the state of the water jugs.
 * 
 * @param State *final
 */
void display(State *final) {
    stack<string> jugs;
    string temp;
    State *current = final;
    while(current->parent != nullptr) {
        temp = current->directions + current->to_string(); 
        jugs.push(temp);
        current = current->parent;
    }
    temp = current->directions + current->to_string(); 
    jugs.push(temp);

    while(!jugs.empty()) {
        cout << jugs.top() << endl ;
        jugs.pop();
    }
}

/**
 * * PourCheck
 * Checks to see if the pours will exceed capacity of the jugs.
 * 
 * @param toCap
 * @param toVal
 * @param fromVal 
 * @return true || false
 */
bool PourCheck(int toCap, int toVal, int fromVal) {
    // Checks if pour will make a change to the levels in each jug.
    if (toVal == toCap) {
        return false;
    }
    if (fromVal == 0) {
        return false;
    }
    return true;
}

/**
 * * simplePour
 * Returns the amount being transferred from the bucket before and 
 * after a pour.
 * 
 * @param fromVal
 * @param toVal
 * @param toCap 
 * @return vector<int> result
 */
vector<int> simplePour(int fromVal, int toVal, int toCap) {
    vector<int> results;
    int amountTransferred;
    int fromAfter;
    int toAfter;
    if(fromVal <= (toCap-toVal)) {
        toAfter = toVal + fromVal;
        fromAfter = 0;
        amountTransferred = fromVal;
    }
    else {
        toAfter = toCap;
        fromAfter = fromVal - (toCap-toVal);
        amountTransferred = toCap - toVal;
    }
    // results[] = [amountTransferred, toAfter, fromAfter]
    results.push_back(amountTransferred);
    results.push_back(toAfter);
    results.push_back(fromAfter);
    return results;
}

/**
 * * pastValCheck
 * Checks states of the variables.
 * 
 * @param vector<vector<state *>> &M 
 * @param State *state
 * @return true || false
 */
bool pastValCheck(vector<vector<State *>> &M, State *state) {
    if(M[state->a][state->b] != nullptr) {
        // Already checked
        return false;
    }
    else {
        // Continue with path and mark that we're here
        M[state->a][state->b] = state;
        return true;
    }    
}
/**
 * * pour
 * Completes Breadth First Search (BFS) algorithm.
 * 
 * @param int caps[]
 * @param vector<vector<State *>> &pastVals
 * @param queue<State *> &q
 * @return true || false
 */
bool pour(int caps[], int goals[], vector<vector<State *>> &pastVals, queue<State *> &q) {
    // Checks for: goal, unchanged, and if state has been visited before.
    // Will only enter if statement when the pouring changes.
    State *jug;
    vector<int> simplePourResults;
    while(!(q.empty())) {
        // C to A
        if(PourCheck(caps[0], q.front()->a, q.front()->c)) {
            simplePourResults = simplePour(q.front()->c, q.front()->a, caps[0]);
            string directionCA = "Pour ";
            directionCA += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionCA += " gallon from C to A. ";
            }
            else {
                directionCA += " gallons from C to A. ";
            }
            jug = new State(simplePourResults[1], q.front()->b, simplePourResults[2], directionCA);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else {
                delete jug;
            }
        }
        
        // B to A
        if(PourCheck(caps[0], q.front()->a, q.front()->b)) {
            simplePourResults = simplePour(q.front()->b, q.front()->a, caps[0]);
            string directionBA = "Pour ";
            directionBA += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionBA += " gallon from B to A. ";
            }
            else {
                directionBA += " gallons from B to A. ";
            }
            jug = new State(simplePourResults[1], simplePourResults[2], q.front()->c, directionBA);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else {
                delete jug;
            }
        }

        // C to B
        if(PourCheck(caps[1], q.front()->b, q.front()->c)) {
            vector<int> simplePourResults;
            simplePourResults = simplePour(q.front()->c, q.front()->b, caps[1]);
            string directionCB = "Pour ";
            directionCB += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionCB += " gallon from C to B. ";
            }
            else {
                directionCB += " gallons from C to B. ";
            }
            jug = new State(q.front()->a, simplePourResults[1], simplePourResults[2], directionCB);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else {
                delete jug;
            }
        }

        // A to B
        if(PourCheck(caps[1], q.front()->b, q.front()->a)) {
            simplePourResults = simplePour(q.front()->a, q.front()->b, caps[1]);
            string directionAB = "Pour ";
            directionAB += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionAB += " gallon from A to B. ";
            }
            else {
                directionAB += " gallons from A to B. ";
            }
            jug = new State(simplePourResults[2], simplePourResults[1], q.front()->c, directionAB);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else{
                delete jug;
            }
        }
        
        // B to C
        if(PourCheck(caps[2], q.front()->c, q.front()->b)) {
            simplePourResults = simplePour(q.front()->b, q.front()->c, caps[2]);
            string directionBC = "Pour ";
            directionBC += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionBC += " gallon from B to C. ";
            }
            else {
                directionBC += " gallons from B to C. ";
            }
            jug = new State(q.front()->a, simplePourResults[2], simplePourResults[1], directionBC);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else {
                delete jug;
            }
        }
        
        // A to C
        if(PourCheck(caps[2], q.front()->c, q.front()->a)) {
            simplePourResults = simplePour(q.front()->a, q.front()->c, caps[2]);
            string directionAC = "Pour ";
            directionAC += to_string(simplePourResults[0]); 
            if(simplePourResults[0] == 1) {
                directionAC += " gallon from A to C. ";
            }
            else {
                directionAC += " gallons from A to C. ";
            }
            jug = new State(simplePourResults[2], q.front()->b, simplePourResults[1], directionAC);
            if(pastValCheck(pastVals, jug)) {
                jug->parent = q.front();
                if(jug->a == goals[0] && jug->b == goals[1]) {
                    display(jug);
                    return true;
                }
                else {
                    q.push(jug);
                }
            }
            else {
                delete jug;
            }
        }
        q.pop();
    }
    cout << "No solution." << endl;
    return false;
}

/**
 * * solve
 * Completes the pour between jugs.
 * 
 * @param int caps[]
 * @param int goals[]
 * @return int
 */
int solve(int caps[], int goals[]) {
    vector<vector<State *>> pastValues;
    vector<State*> result;
    // Fill vector with theta(n) efficiency.
    for(int j=0; j<=(caps[1]+1); j++) {
        result.push_back(nullptr);
    }
    for(int i=0; i<=(caps[0]+1); i++) {
        pastValues.push_back(result);
    }
    // Problem Starts with jug c full and others are empty.
    State *initial = new State(0, 0, caps[2], "Initial state. ");
    pastValCheck(pastValues, initial);
    // Tracker variable keeps track of if the goal state was found.
    if(initial->a == goals[0] && initial->b == goals[1]) {
        cout << initial->directions << initial->to_string() << endl;
        delete initial;
        return 0;
    }
    queue<State *> explore;
    explore.push(initial);
    pour(caps, goals, pastValues, explore);
    for(int i=0; i<=(caps[0]+1); i++) {
        for(int j=0; j<=(caps[1]+1); j++) {
            delete pastValues[i][j];
        }
    }
    return 0;
}


int main(int const argc, char * const argv[]) {
    int values[6];
    istringstream iss;
    
    // Checks the number of arguments. 
    if(argc != 7) {
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    // Checks to see if the user input is a valid integer.
    string letters[] = {"A", "B", "C", "A", "B", "C" };
    for(int i=1; i <= 6; i++){
        iss.str(argv[i]);
        if(!(iss>> values[i-1]) || (values[i-1] < 0) || (i <= 3 && values[i-1] == 0)) {
            string gORc;
            if (i > 3){
                gORc = "goal";
            }
            else {
                gORc = "capacity";
            }             
            cout << "Error: Invalid " << gORc << " '" <<  argv[i] <<"' for jug " << letters[i-1] << "."<< endl;
            return 1;
        }
        iss.clear();
    }

    for(int i=0; i<=2; i++) {
        // Checks to see if goal state is larger than capacity.
        if(values[i] < values[i+3]) {
            cout << "Error: Goal cannot exceed capacity of jug " << letters[i]<< "." << endl;
            return 1;
        }
    }

    // Checks to see the total number of gallons of the goal state is equal to C.
    if((values[5] + values[4] + values[3]) != values[2]) {
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." <<endl;
        return 1;
    }
    int caps[3] = {values[0], values[1], values[2]};
    int goals[3]= {values[3], values[4], values[5]};
    
    // Solves the waterjug puzzle.
    solve(caps, goals);
    return 0;
}