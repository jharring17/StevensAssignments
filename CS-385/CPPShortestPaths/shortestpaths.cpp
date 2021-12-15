/*******************************************************************************
 * Name          : shortestpaths.cpp
 * Author        : Zachary Scarpati && Jack Harrington
 * Date          : December 5, 2020
 * Description   : Program to detect the shortest paths between pairs of vertices.
 * Pledge 		 : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int num_vertices;
long** intermediates;
long** distances;
long** paths;
long INF = LONG_MAX;

int len(long integ){
	int digits = 0;
	while(integ != 0){
		integ /= 10;
		digits++;
	}
	return digits;
}


void display_table(long** const matrix, const string &label, const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i=0; i < num_vertices; i++) {
		for (int j=0; j < num_vertices; j++) {
		 	long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
		 		max_val = matrix[i][j];
		 	}
		}
	}
	int max_cell_width;
	if(use_letters) {
		max_cell_width = 1;
	}
	else { 
		max_cell_width = len(max(static_cast<long>(num_vertices), max_val));
    }    
    cout << ' ';
	for (int j=0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for(int i=0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
	    for(int j=0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if(!use_letters && i == j) {
				cout << "0";
			}
			else if(use_letters && i == j) {
				cout << "-";
			}
			else if (matrix[i][j] == INF) {
			    cout << "-";
			} 
            else if (use_letters) {
			    cout << static_cast<char>(matrix[i][j] + 'A');
			} 
            else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}


long** makePaths(int length) {
	long **path = new long*[length];
	num_vertices = length;
	for(int i=0; i < length; i++) {
		path[i] = new long[length];
		for(int j=0; j < length; j++) {
			path[i][j] = INF;
		}
	}
	return path;
}


long** floydsAlgorithm(long** paths) {
	for(int k=0; k < num_vertices; k++) {
		for(int i=0; i < num_vertices; i++) {
			for(int j=0; j < num_vertices; j++) {
				if(paths[i][k] != INF && paths[k][j] != INF) {
					if((paths[i][k] + paths[k][j]) < paths[i][j]) {
						intermediates[i][j] = k;
					}
					paths[i][j] = min(paths[i][j], paths[i][k] + paths[k][j]);
				}
			}
		}
	}
	distances = paths;
	return paths;
}

void fillTable(long** paths, int startVert, int endVert, int weight) {
	if(startVert == endVert) {
		paths[startVert][endVert] = 0;
	}
	else {
		paths[startVert][endVert] = weight;
	}
}

void get_path(int i, int j) {
	if(intermediates[i][j] == INF) {
		cout << char (i+65) << " -> " ;
	}
	else {
		get_path(i, intermediates[i][j]);
		get_path(intermediates[i][j], j);
	}
}

void printPath(long** pather) {
	for(int i=0; i < num_vertices; i++) {
		for(int j=0; j < num_vertices; j++) {
			if(i == j) {
				cout << (char)(i+65) << " -> " << (char)(j+65) << ", distance: 0, path: " << (char)(i+65) << endl;
			}
			else if(pather[i][j] == INF) {
				cout << (char)(i+65) << " -> " << (char)(j+65) << ", distance: infinity, path: none" << endl;
			}
			else if(pather[i][j] != INF) {
				cout << (char)(i+65) << " -> " << (char)(j+65) << ", distance: " << paths[i][j] << ", path: ";
				get_path(i, j);
				cout <<  (char)(j+65) << endl;
			}
		}
	}
}

void del() {
	for(int i = 0; i < num_vertices;i++) {
		delete [] paths[i];
		delete [] intermediates[i];
	}
	delete [] paths;
	delete [] intermediates;
}

int main(int argc, char* const argv[]) {
	long number;
	int linenum = 1;
	string startVert;
	string endVert;
	int weight = 0;
	string weightNum;
	long vertCounter = 0;
	string alph[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};


	if (argc != 2) {
	    cerr << "Usage: " << argv[0] << " <filename>" << endl;
	    for(int i=0; i < num_vertices;i++){
	        	delete [] paths[i];
	        	delete [] intermediates[i];
	        }
	        delete [] paths;
	        delete [] intermediates;
	    return 1;
	}
	ifstream filereader(argv[1]);
	if(!filereader) {
	    cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
	    for(int i=0; i < num_vertices;i++) {
	        	delete [] paths[i];
	        	delete [] intermediates[i];
	        }
	        delete [] paths;
	        delete [] intermediates;
	    return 1;
	}
	filereader.exceptions(ifstream::badbit);
	string line;
	try {
	    getline(filereader, line);
	    istringstream iss;
	    iss.str(line);
	    iss >> number;
	    if(number < 1 || number > 26) {
	        cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
	        for(int i=0; i < num_vertices;i++) {
	        	delete [] paths[i];
	        	delete [] intermediates[i];
	        }
	        delete [] paths;
	        delete [] intermediates;
	        return 1;
	    }
	    paths = makePaths(number);
	    intermediates = makePaths(number);
	    while(getline(filereader, line)) {
	        bool found = false;
	        bool start = false;
	        bool end = false;
	        int spaceCount = 0;
	        linenum++;
	        for(unsigned int i=0; i < line.length(); i++) {
	        	if(isspace(line[i])){
                    spaceCount++;
                    if(!start) {
                        start = true;
                        startVert = line.substr(0, i);
                        vertCounter = i;
                    }
                    else if(!end) {
                        end = true;
                        endVert = line.substr(vertCounter + 1, i - 2);
                        vertCounter = i;
                    }
	            }
                if(end) {
                    weightNum = line.substr(vertCounter + 1);
                }
	        }
	        stringstream numCheck(weightNum);
	        if(!(numCheck >> weight)) {
	        	cerr << "Error: Invalid edge weight '" << weightNum << "' on line " << linenum << "." << endl;
	        	for(int i=0; i < num_vertices;i++) {
	        	    delete [] paths[i];
	        		delete [] intermediates[i];
	        	}
	        	delete [] paths;
	        	delete [] intermediates;
	        	return 1;
	        }
	        else if(weight <= 0) {
	        	cerr << "Error: Invalid edge weight '" << weightNum << "' on line " << linenum << "." << endl;
	        	for(int i=0; i < num_vertices;i++) {
	        		delete [] paths[i];
	        		delete [] intermediates[i];
	        	}
	        	delete [] paths;
	        	delete [] intermediates;
	        	return 1;
	        }
	        if(spaceCount != 2) {
	        	cerr << "Error: Invalid edge data '" << line << "' on line " << linenum << "." << endl;
	        	for(int i=0; i < num_vertices;i++) {
	        		delete [] paths[i];
	        		delete [] intermediates[i];
	        	}
	        	delete [] paths;
	        	delete [] intermediates;
	       		return 1;
	       	}
	        for(int i=0; i < number; i++) {
	        	if(alph[i].compare(startVert) == 0) {
	        		found = true;
	        		break;
	        	}
	       	}

	        if(!found) {
	        	cerr << "Error: Starting vertex '" << startVert << "' on line " << linenum << " is not among valid values A-" << alph[number - 1] << "." << endl;
	        	for(int i=0; i < num_vertices;i++) {
	        		delete [] paths[i];
	        		delete [] intermediates[i];
	        	}
	        	delete [] paths;
	        	delete [] intermediates;
	        	return 1;
	        }
	        found = false;
	        for(int i=0; i < number; i++) {
	        	if(alph[i].compare(endVert) == 0) {
	        		found = true;
	        		break;
	        	}
	       	}
            if(!found) {
	        	cerr << "Error: Ending vertex '" << endVert << "' on line " << linenum << " is not among valid values A-" << alph[number - 1] << "." << endl;
	        	for(int i=0; i < num_vertices;i++) {
	        		delete [] paths[i];
	        		delete [] intermediates[i];
	        	}
	        	delete [] paths;
	        	delete [] intermediates;
	       		return 1;
	       	}
	        int startInt = (int) startVert[0]-65;
	        int endInt = (int) endVert[0]-65;
            fillTable(paths, startInt, endInt, weight);

	    }
	    filereader.close();
	} 
    catch (const ifstream::failure &f) {
	        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
	        return 1;
	}

	display_table(paths, "Distance matrix:", false);
	display_table(floydsAlgorithm(paths), "Path lengths:", false);
	display_table(intermediates, "Intermediate vertices:", true);
	printPath(floydsAlgorithm(paths));
	del();
	return 0;
}
