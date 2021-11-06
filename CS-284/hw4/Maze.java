package hw4;

import java.util.ArrayList;
import java.util.Stack;

/**
 * Class that solves maze problems with backtracking.
 * @author Koffman and Wolfgang
 **/
public class Maze implements GridColors {

    /** The maze */
    private TwoDimGrid maze;

    public Maze(TwoDimGrid m) {
        maze = m;
    }

    /** Wrapper method. */
    public boolean findMazePath() {
        return findMazePath(0, 0); // (0, 0) is the start point.
    }

    /**
     * Attempts to find a path through point (x, y).
     * @pre Possible path cells are in BACKGROUND color;
     *      barrier cells are in ABNORMAL color.
     * @post If a path is found, all cells on it are set to the
     *       PATH color; all cells that were visited but are
     *       not on the path are in the TEMPORARY color.
     * @param x The x-coordinate of current point
     * @param y The y-coordinate of current point
     * @return If a path through (x, y) is found, true;
     *         otherwise, false
     */
    public boolean findMazePath(int x, int y) {
        // out of bounds case
        if (x > (maze.getNCols()-1) || x < 0 || y > maze.getNRows() || y < 0){
            return false;
        }

        // incorrect color case
        if (maze.getColor(x , y) != NON_BACKGROUND) {
            return false;
        }

        // exit cell case
        if (x == maze.getNCols() - 1 && y == maze.getNRows() - 1) {
            maze.recolor(x, y, PATH);
            return true;
        }

        // recursive calls 
        maze.recolor(x, y, PATH);
        if (findMazePath(x - 1, y) || findMazePath(x + 1, y) || findMazePath(x, y + 1) || findMazePath(x, y - 1)) {
            return true;
        } else {
            maze.recolor(x, y, TEMPORARY);
            return false;
        }
    }    

    public ArrayList<ArrayList<PairInt>> findAllMazePaths(int x, int y) {
        ArrayList <ArrayList <PairInt>> result = new ArrayList<>();
        Stack <PairInt> trace =new Stack<>();
        findMazePathStackBased (0, 0, result, trace);
        if (result.size() == 0) {
            ArrayList<PairInt> temp = new ArrayList<>();
            result.add(temp);
        }
        return result;
    }

    public void findMazePathStackBased(int x, int y, ArrayList<ArrayList<PairInt>> result, Stack<PairInt> trace) {
        // out of bounds case
        if (x > (maze.getNCols()-1) || x < 0 || y > maze.getNRows() || y < 0){
            return;
        }

        // incorrect color case
        if (maze.getColor(x , y) != NON_BACKGROUND) {
            return;
        }

        // adding to the stack 
        PairInt currentPair = new PairInt(x,y);
        trace.push(currentPair);

        // exit cell case
        if (x == maze.getNCols() - 1 && y == maze.getNRows() - 1) {
            ArrayList<PairInt> temp = new ArrayList<>();
            temp.addAll(trace);
            // adds current path to result 
            result.add(temp);
            trace.pop();
            return;
        }

        // recursive calls 
        maze.recolor(x, y, PATH);
        findMazePathStackBased(x - 1, y, result, trace);
        findMazePathStackBased(x + 1, y, result, trace);
        findMazePathStackBased(x, y + 1, result, trace);
        findMazePathStackBased(x, y - 1, result, trace);
        maze.recolor(x, y, NON_BACKGROUND);

        // popping from the stack 
        trace.pop();
    }
    
    public ArrayList<PairInt> findMazePathMin(int x,int y) {
        ArrayList<ArrayList<PairInt>> allPaths = findAllMazePaths(x, y); 
        ArrayList<PairInt> min =  allPaths.get(0);
        for (int i = 0; i < allPaths.size(); i++) {
            if (min.size() > allPaths.get(i).size()) {
                min = allPaths.get(i);
            }
        }
        return min;
    }
    
    public void resetTemp() {
        maze.recolor(TEMPORARY, BACKGROUND);
    }

    public void restore() {
        resetTemp();
        maze.recolor(PATH, BACKGROUND);
        maze.recolor(NON_BACKGROUND, BACKGROUND);
    }
}
/*</listing>*/
