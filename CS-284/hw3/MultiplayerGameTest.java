package hw3;
//import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertTrue;

import org.junit.Test;   

public class MultiplayerGameTest {
        
    @Test
    public void testAddGamePiece() {
        MultiplayerGame g1 = new MultiplayerGame(3);
        g1.addGamePiece(2, "BluePiece", 5);
        g1.addGamePiece(1, "PurplePiece", 2);
        g1.addGamePiece(1, "OrangePiece", 17);

        assertTrue(g1.contains(1, "PurplePiece"));
    }

    @Test
    public void testRemoveGamePiece() {
        MultiplayerGame g1 = new MultiplayerGame(3);
        g1.addGamePiece(2, "BluePiece", 5);
        g1.addGamePiece(1, "PurplePiece", 2);
        g1.addGamePiece(1, "OrangePiece", 17);
        g1.removeGamePiece(1, "PurplePiece");
        
        assertFalse(g1.contains(1, "PurplePiece"));
    }

    @Test
    public void testContainsPiece() {
        MultiplayerGame g1 = new MultiplayerGame(3);
        g1.addGamePiece(2, "BluePiece", 5);
        g1.addGamePiece(1, "PurplePiece", 2);
        g1.addGamePiece(1, "OrangePiece", 17);
        
        assertFalse(g1.contains(1, "RedPiece"));
    }

}
    