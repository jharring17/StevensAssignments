#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "PlaylistNode.h"

// PrintMenu() - Outputs the options to manipulate the playlist.
void PrintMenu(char playlistName[50]) {
    printf("%s PLAYLIST MENU\n", playlistName);
    printf("a - Add song\n");
    printf("r - Remove song\n");
    printf("o - Output full playlist\n");
    printf("q - Quit\n\n");
}


// ExecuteMenu() - Excutes valid user inputted option.
PlaylistNode* ExecuteMenu(char userOption, char playlistName[50], PlaylistNode* headNode) {
    PlaylistNode* newNode;
    newNode = (PlaylistNode*) malloc(sizeof(PlaylistNode));
    switch (userOption) {
        
        case 'a' :
            printf("ADD SONG\n");
            printf("Enter song's unique ID:\n");
            scanf("%s\n", (newNode->uniqueID));
            
            printf("Enter song's name:\n");
            scanf("%s\n", (newNode->songName));
            
            printf("Enter artist's name:\n");
            scanf("%s\n", (newNode->artistName));
            
            printf("Enter song's length (in seconds):\n");
            scanf("%d\n", &(newNode->songLength));
            PrintMenu(playlistName);
        break;
        
        case 'r' :
        // statements;
        break;
            
        case 'o' :
        // Statements
        if (headNode == NULL) {
            printf("%s - OUTPUT FULL PLAYLIST\n", playlistName);
            printf("Playlist is empty\n\n");
            PrintMenu(playlistName);
            
            printf("Choose an option:\n");
            scanf("%s", &userOption);
        }
        
        else {
            printf("%s OUTPUT FULL PLAYLIST\n", playlistName);
        }
        break;
            
        case 'q' :
        exit(0);
    }
    return headNode;
}
 


int main () {
    
    
    PlaylistNode* headNode = NULL;
    char playlistName[50];
    char userOption;
    
    // Get user input for the playlist title
    printf("Enter playlist's title:\n\n");
    scanf("%[^\n]s", playlistName), 
    
    // Call to the PrintMenu Function
    PrintMenu(playlistName);
    
    // Prompts user for userOption
    printf("Choose an option:\n");
    scanf("%s", &userOption);
    
    // Call to the Execute Menu Function
    ExecuteMenu(userOption, playlistName, headNode);
}
