package hw3;

public class MultiplayerGame {
    private GameEntity[] index;
    private GameEntity turnTracker;
    
    public MultiplayerGame(int n) {
        index = new GameEntity[n]; 
        for (int i = 0; i < n; i++){
            index[i] = new GamePlayer(null, null, i);
        }
        for (int i = 0; i < n; i++){
            if (i == 0){
                index[i].next = index[i+1];
                index[i].prev = index[n-1];
            }else if (i == n-1){
                index[i].prev = index[i-1];
                index[i].next = index[0];
            }else{
            index[i].next = index[i+1];
            index[i].prev = index[i-1];
            }
        }
    }

    public void addGamePiece(int playerId, String name, int strength) {
        if (playerId < 0 || playerId > (index.length - 1)){
            throw new IllegalArgumentException("addGamePiece: no such player");
        }
        if (this.contains(playerId, name)){
            throw new IllegalArgumentException("addGamePiece: duplicate entity");
        }
        GameEntity current = index[playerId];
        GamePiece NewPiece = new GamePiece(null, null, name, strength);
        current = current.next;
        while (!current.isGamePlayer()){
            if (strength > ((GamePiece)current).getStrength()){
                break;
            }
            current = current.next;
        }
        NewPiece.prev = current.prev;
        current.prev.next = NewPiece;
        current.prev = NewPiece;
        NewPiece.next = current;    
    }

    public boolean contains(int playerId, String name){
        GameEntity current = index[playerId];
        current = current.next;
        while (!current.isGamePlayer()){
            if (current.getName() == name){
                return true;
            }
            current = current.next;
        }
        return false;
    }

    public void removeGamePiece(int playerId, String name) {
        // checks to see if the player exists
        if (playerId < 0 || playerId > (index.length - 1)){
            throw new IllegalArgumentException("removeGamePiece: no such player");
        }
        // checks to see if the player owns the piece
        if (!this.contains(playerId, name)){
            throw new IllegalArgumentException("removeGamePiece: entity does not exist");
        }
        GameEntity current = index[playerId];
        current = current.next;
        while (!current.isGamePlayer()){
            if (current.getName() == name){
                break;
            }
            current = current.next;
        }
        current.prev.next = current.next;
        current.next.prev = current.prev;
        current.next = null;
        current.prev = null;
    }

    public boolean hasGamePiece(String name){
        GameEntity current = index[0];
        current = current.next;
        while (current != index[0]){
            if (current.getName() == name && !current.isGamePlayer()){
                return true;
            }
            current = current.next;
        }
        return false;
    }

    public void removeAllGamePieces(int playerId) {
        if (playerId < 0 || playerId > (index.length - 1)){
            throw new IllegalArgumentException("removeAllGamePieces: no such player");
        }
        if (index.length - 1 == playerId){
            index[playerId].next = index[0];
            index[0].prev = index[playerId];
        } else {
        index[playerId].next = index[playerId + 1];
        index[playerId + 1].prev = index[playerId];
        }    
    }

    public void increaseStrength(int playerId, int n) {
        if (playerId < 0 || playerId > (index.length - 1)){
            throw new IllegalArgumentException("increaseStrength: no such player");
        }
        GameEntity current = index[playerId];
        current = current.next;
        while (!current.isGamePlayer()){
            ((GamePiece)current).updateStrength(n);
            current = current.next;
        }
    }

    public void removePlayer(int playerId) {
        if (playerId == 0) { 
            index[playerId + 1].prev = index[playerId].prev;
            index[playerId].prev.next = index[playerId + 1];
            index[playerId].next = index[1];
            ((GamePlayer) index[0]).setPlayerId(-1);
        } else if (playerId == index.length - 1) { 
            index[0].prev = index[index.length - 1].prev;
            index[index.length - 1].prev.next = index[0];
            index[playerId].next = index[0];
            ((GamePlayer) index[index.length - 1]).setPlayerId(-1);
        } else { // player in the middle
            index[playerId + 1].prev = index[playerId].prev;
            index[playerId].prev.next = index[playerId + 1];
            index[playerId].next = index[playerId + 1];
            ((GamePlayer) index[playerId]).setPlayerId(-1);
        }
    }

    public void swapPieces(int PlayerId1, int PlayerId2) {
        if (PlayerId1 < 0 || PlayerId1 > index.length - 1  || PlayerId2 < 0  || PlayerId2 > index.length - 1 
                || ((GamePlayer) index[PlayerId1]).getPlayerId() == -1
                || ((GamePlayer) index[PlayerId2]).getPlayerId() == -1) {
            throw new IllegalArgumentException("swapPieces: no such player");
        }

        GameEntity playerOne = index[PlayerId1];
        GameEntity playerOneIteratorF = playerOne;
        GameEntity playerOneIteratorL = playerOneIteratorF;
        if (playerOneIteratorF.next.isGamePlayer() == false) { 
            playerOneIteratorF = playerOneIteratorF.next;
            playerOneIteratorL = playerOneIteratorF;

            while (playerOneIteratorL.isGamePlayer() == false) {
                playerOneIteratorL = playerOneIteratorL.next;
            }
            playerOneIteratorL = playerOneIteratorL.prev;
        }

        GameEntity playerTwo = index[PlayerId2];
        GameEntity playerTwoIteratorF = playerTwo;
        GameEntity playerTwoIteratorL = playerTwoIteratorF;
        if (playerTwoIteratorF.next.isGamePlayer() == false) { 
            playerTwoIteratorF = playerTwoIteratorF.next;
            playerTwoIteratorL = playerTwoIteratorF;

            while (playerTwoIteratorL.isGamePlayer() == false) {
                playerTwoIteratorL = playerTwoIteratorL.next;
            }
            playerTwoIteratorL = playerTwoIteratorL.prev;
        }
    }

    public String toString() {
        GameEntity current = index[0];
        String Game = "";
        while (current.next != index[0]){
            Game += current.toString();
            Game += "\n";
            current = current.next;
        }
        Game += current.toString();
        Game += "\n";
        return Game;
    }


    // Beginning of turnTracker
    public void initializeTurnTracker() {
        GameEntity firstPlayer = index[0];
        while (((GamePlayer) firstPlayer).getPlayerId() == -1 || firstPlayer.isGamePlayer() == false) {
            firstPlayer = firstPlayer.next;
        }
        turnTracker = firstPlayer;
    }

    public void nextPlayer() {
        turnTracker = turnTracker.next;
        while (!turnTracker.isGamePlayer()){
            turnTracker = turnTracker.next;
        }
    }

    public void nextEntity() {
        turnTracker = turnTracker.next;
    }

    public void prevPlayer() {
        turnTracker = turnTracker.prev;
        while (!turnTracker.isGamePlayer()){
            turnTracker = turnTracker.prev;
        }
    }

    public String currentEntityToString() {
        return turnTracker.toString();
    }

    public static void main(String[] args) {
        MultiplayerGame g1 = new MultiplayerGame(3);
        System.out.println(g1.toString());
        g1.addGamePiece(2, "BluePiece", 5);
        g1.addGamePiece(1, "PurplePiece", 2);
        g1.addGamePiece(1, "OrangePiece", 17);
        System.out.println(g1.toString());
        g1.increaseStrength(1, -18);
        System.out.println(g1.toString());

    
        //Expected output: 
    //[Player0; Player1; GamePiece: OrangePiece strength: 17; GamePiece: 
    //PurplePiece strength: 2; Player2; GamePiece: BluePiece strength: 5]

        MultiplayerGame g2 = new MultiplayerGame(3);
        g2.addGamePiece(2, "BluePiece", 5);
        g2.addGamePiece(1, "PurplePiece", 2);
        g2.addGamePiece(1, "OrangePiece", 17);
        g2.removePlayer(1);
        g2.increaseStrength(2,3);
        System.out.println(g2.toString());

    //Expected output:
    //[Player0; Player2; GamePiece: BluePiece strength: 8]

        MultiplayerGame g3 = new MultiplayerGame(3);
        g3.addGamePiece(2, "BluePiece", 5);
        g3.addGamePiece(1, "PurplePiece", 2);
        g3.addGamePiece(1, "OrangePiece", 17);
        g3.removeGamePiece(1, "PurplePiece");
        System.out.println(g3.toString());

    //Expected output:
    //[Player0; Player1; GamePiece: OrangePiece strength: 17; Player2; 
    //GamePiece: BluePiece strength: 5]
    
    }

}
