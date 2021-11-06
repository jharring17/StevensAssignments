package hw5;

import java.util.ArrayList;
import java.util.Random;

public class Treap<E extends Comparable<E>> {
	
	private static class Node<E> {
		// establishes data in node class 
		public E data;
		public int priority;
		public Node<E> left;
		public Node<E> right;
	
		public Node(E data, int priority) {
			this.data = data;
			this.priority = priority;
			left = null;
			right = null;
		}
		
		//  rotates left around pivot point 
		public Node<E> rotateLeft() {
			Node<E> temp = this.right;
			Node<E> x = temp.left;
			temp.left = this;
			this.right = x;
			return temp;
		}
		
		// rotates right around pivot point 
		public Node<E> rotateRight() {
			Node<E> temp = this.left;
			Node<E> x = temp.right; 
			temp.right = this;
			this.left = x;
			return temp;
		}		
	}

	private Random priorityGenerator;
	private Node<E> root;

	// creates a treap of null size
	public Treap() {
		this.priorityGenerator = new Random();
		root = null;
	}

	// generates random seed
	public Treap(long seed) {
		this.priorityGenerator = new Random(seed);
		root = null;
	}

	// adds new node to treap
    boolean add(E key, int priority) {
        // keeps track of current place in treap
		ArrayList<String> stack = new ArrayList<String>();
        // makes node in treap
		Node<E> node = new Node<E>(key, priority);
		// keeps place of current node in the treap 
		Node<E> current = root;
        
		// establishes new root if current treap is null 
		if (root == null) {
            root = node;
            return true;
        } else if (root.data.equals(node.data)) {
            return false;
        }

        while (true) {
            if (current.data.compareTo(node.data) > 0) {
                // checks left for null data 
				if (current.left != null) {
                    current = current.left;
                    stack.add("L");
                } else {
                    current.left = node;
                    reheap(stack);
                    return true;
                }
            } else if (current.data.compareTo(node.data) < 0) {
				// checks right for null data 
                if (current.right != null) {
                    current = current.right;
                    stack.add("R");
                } else {
                    current.right = node;
                    reheap(stack);
                    return true;
                }
            } else {
                return false;
            }
        }
    }

	// parent function of add
    boolean add(E key) {
        return add(key, priorityGenerator.nextInt());
    }

	// helper function to rotate treap into correct orientation
    private void reheap(ArrayList<String> stack) {
        Node<E> current = root;
        // iterates through treap
		for (String string : stack) {
            if (string.equals("L")) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        if (current.left != null && current.priority < current.left.priority) {
            current = current.rotateRight();
            if (stack.isEmpty()) {
                root = current;
                return;
            } else {
                String values = stack.remove(stack.size() - 1);

                Node<E> current2 = root;
                for (String string : stack) {
                    if (string.equals("L")) {
                        current2 = current2.left;
                    } else {
                        current2 = current2.right;
                    }
                }
                if (values.equals("L")) {
                    current2.left = current;
                } else {
                    current2.right = current;
                }
                reheap(stack);
            }
        } else if (current.right != null && current.priority < current.right.priority) {
            current = current.rotateLeft();
            if (stack.isEmpty()) {
                root = current;
                return;
            } else {
                String values = stack.remove(stack.size() - 1);

                Node<E> current2 = root;
                for (String string : stack) {
                    if (string.equals("L")) {
                        current2 = current2.left;
                    } else {
                        current2 = current2.right;
                    }
                }
                if (values.equals("L")) {
                    current2.left = current;
                } else {
                    current2.right = current;
                }
                reheap(stack);
            }
        }
    }

	// moves node to the bottom of the treap
    boolean delete(E key) {
        Node<E> node = root;
		
		// checks if node exists 
		if (!find(key)) {
            return false;
        }
		// checks if root is key
        if (root.data == key) {
            if (root.left != null && root.right != null) {
                if (root.left.priority > root.right.priority) {
                    root = root.rotateLeft();
                } else {
                    root = root.rotateRight();
                }
            } else if (root.left == null) {
                root = root.rotateLeft();
            } else if (root.right == null) {
                root = root.rotateRight();
            } else {
                root = null;
            }
        }

        while (true) {
            if ((node.left != null && node.left.data == key) || (node.right != null && node.right.data == key)) {
                break;
            } else {
                if (find(node.left, key)) {
                    node = node.left;
                } else {
                    node = node.right;
                }
            }
        }
        while (true) {
            if (node.left != null && node.left.data == key) {
                if (node.left.left != null && node.left.right != null) {
                    if (node.left.left.priority < node.left.right.priority) {
                        node.left = node.left.rotateLeft();
                    } else {
                        node.left = node.left.rotateRight();
                    }
                } else if (node.left.left == null && node.left.right == null) {
                    node.right = null;
                    return true;
                } else if (node.left.left == null) {
                    node.left = node.left.rotateLeft();
                } else if (node.left.right == null) {
                    node.left = node.left.rotateRight();
                }
                node = node.left;
            } else {
                if (node.right.left != null && node.right.right != null) {
                    if (node.right.left.priority < node.right.right.priority) {
                        node.right = node.right.rotateLeft();
                    } else {
                        node.right = node.right.rotateRight();
                    }
                } else if (node.right.left == null && node.right.right == null) {
                    node.right = null;
                    return true;
                } else if (node.right.left == null) {
                    node.right = node.right.rotateLeft();
                } else if (node.right.right == null) {
                    node.right = node.right.rotateRight();
                }
                node = node.right;
            }
        }

    }

	// looks through treap and finds node in treap 
    private boolean find(Node<E> root, E key) {
        // checks if root is null
		if (root == null) {
            return false;
        }
		// checks if root is find() value 
        if (root.data == key) {
            return true;
        }
		// checks left of current node for find() value
        if (find(root.left, key)) {
            return true;
        }
        return find(root.right, key);
    }

	// parent function of find 
    public boolean find(E key) {
        return find(root, key);
    }

	// creates a string representation of treap
    private String toString(Node<E> current, int level) {
		StringBuilder s = new StringBuilder();
		for (int i=0; i<level;i++) {
			s.append("-");
		}
		if (current==null) {
			s.append("null\n");
		} else {
			s.append(current.toString()+"\n");
			s.append(toString(current.left, level+1));
			s.append(toString(current.right,level+1));
		}
		return s.toString();
		
	}

	// parent function of toString()
	public String toString() {
		return toString(root,0);
	}
}