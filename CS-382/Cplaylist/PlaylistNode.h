#ifndef PLAYLIST_H
#define PLAYLIST_H

typedef struct PlaylistNode PlaylistNode;

struct PlaylistNode {
    char uniqueID[50];
    char songName[50];
    char artistName[50];
    int songLength;   
    PlaylistNode* nextNodeptr;
};

void SetPlaylistNode(PlaylistNode* thisnode, char idInit[], char songNameInit[], char artistNameInit[], int songLengthInit);
void PrintPlaylistNode(PlaylistNode* thisNode);
PlaylistNode* GetNextPlaylistNode(PlaylistNode* thisNode);

#endif
