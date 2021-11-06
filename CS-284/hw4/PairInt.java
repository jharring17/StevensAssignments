package hw4;

public class PairInt {
    private int x;
    private int y;

    public PairInt(int x, int y) {
        this.x = x;
        this.y = y;
    }

    // getter methods getX && getY
    public int getX() {
        return this.x;
    }

    public int getY() {
        return this.y;
    }

    // setter methods setX && setY
    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public boolean equals(Object P) {
        Object temp = this;
        return temp.equals(P);
    }

    public String toString() {
        String point = "(" + x + "," + y + ")";
        return point; 
    }

    public PairInt copy() {
        return new PairInt(this.x, this.y);
    }

    public static void main(String[] args) {
        PairInt p1 = new PairInt(1,2);
        PairInt p2 = new PairInt(2,3);
        // System.out.println(p1.equals(p2));
        System.out.println(p1);
        System.out.println(p2);
    }
}
