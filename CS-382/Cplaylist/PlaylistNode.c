#include <stdio.h>
#include <string.h>
#include "PlaylistNode.h"

void SetPlaylistNode(PlaylistNode* thisnode, char idInit[], char songNameInit[], char artistNameInit[], int songLengthInit) {
    // Puts all the information into the node.
    strcpy(thisnode->uniqueID, idInit);
    strcpy(thisnode->songName, songNameInit);
    strcpy(thisnode->artistName, artistNameInit);
    thisnode->songLength = songLengthInit;
    thisnode->nextNodeptr = NULL;
}

void PrintPlaylistNode(PlaylistNode* thisnode) {
    // Prints all of the data in thisnode.
    printf("Unique ID: %s\n", thisnode->uniqueID);
    printf("Song Name: %s\n", thisnode->songName);
    printf("Artist Name: %s\n", thisnode->artistName);
    printf("Song Length (in seconds): %d\n", thisnode->songLength);
}

PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisnode) {
    // Returns a pointer to the next node. 
    return thisnode->nextNodeptr;
}
