package hw5;
import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;  
    
public class TreapTest {
    @Test
    void testAdd() {
        Treap<Integer> t = new Treap<Integer>();
        t.add(5, 19);
        t.add(2, 31);
        t.add(46, 70);
        t.add(85, 32);
        t.add(10, 16);
        t.add(1, 8);
        assertTrue(t.find(2));
        assertTrue(t.find(5));
        assertTrue(t.find(46));
        assertFalse(t.find(12));
        assertFalse(t.find(13));
        assertTrue(t.delete(2));
        assertTrue(t.delete(85));
        assertFalse(t.delete(45));
        assertFalse(t.delete(3));

    }

}
    