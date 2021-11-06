package hw6;

import java.util.Stack;

public class Sort {
	public static <T extends Comparable<T>> void sort(T[] array) {
		
	}
	
	private static class Interval {
		private int lower;
		private int upper;
	
		public Interval(int lower, int upper) {
			this.lower = lower;
			this.upper = upper;
		}
		
		public int getLower() {
			return this.lower;
		}
	
		public int getUpper() {
			return this.upper;
		}
		
		public boolean equals(Object o) {
			return o.equals(this);
		}
		
		public int hashCode() {
			return (lower * lower) + upper;
		}
	}
	
	private <T> void swap(T[] array, int index1, int index2) {
		// swaps the elements in an array 
		T temp = array[index1];
		array[index1] = array[index2];
		array[index2] = temp;
	}
	
	
	private <T extends Comparable<T>> int partition(int first, int middle, int last, T[] array) {
		// Middle and first comparison
		if (array[middle].compareTo(array[first]) < 0) {
			swap(array, first, middle);
		}
		
		// Middle and last comparison 
		if (array[middle].compareTo(array[last]) > 0) {
			swap(array, middle, last);
		}
		
		// First and last comparison
		if (array[first].compareTo(array[last]) > 0) {
			swap(array, first, last);
		}
		
		swap(array, middle, first);
		
		int up = first;
		int down = last;
		
		do {
			while (array[up].compareTo(array[middle]) <= 0 || up != last) {
				up++;
			}
			
			while (array[down].compareTo(array[middle]) > 0 || down != first) {
				down--;
			}
			
			if (up < down) {
				swap(array, up, down);
			}
		} while (up < down);
		swap(array, up, down);
		return down;
		
	}

	public static <T extends Comparable<T>> T[] bubblesort(T[] arr, int first, int middle, int last) {
		
		// First and middle comparison
		if (arr[first].compareTo(arr[middle]) > 0) {
			T temp = arr[first];
			arr[first] = arr[middle];
			arr[middle] = temp;
		}

		// Middle and last comparison
		if (arr[middle].compareTo(arr[last]) > 0) {
			T temp = arr[middle];
			arr[middle] = arr[last];
			arr[last] = temp;
		}
		
		// First and middle comparison
		if (arr[first].compareTo(arr[middle]) > 0) {
			T temp = arr[first];
			arr[first] = arr[middle];
			arr[middle] = temp;
		}
		return arr;
	}
}
public static void main(String[] args) {
	Sort sort1 = new Sort([1 , 5, 3, 10]);
	
}


