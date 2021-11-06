package assignmentTwo;

public class Complexity {
	
	// time complexity of n^2
	public static void method1(int n) {
		int counter = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				System.out.println("Counter: " + counter);
				counter ++; 
			}
		}
	}
	
	// time complexity of n^3
	public static void method2(int n) {
		int counter = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				 for (int k = 0; k < n; k++) {
					 System.out.println("Counter: " + counter);
					counter ++;
				 }
			}
		}
	}

	// time complexity of log(n)
	public static void method3(int n) {
		int counter = 0;
		for(int i = 1; i <= n; i = i * 2) {
			System.out.println("Counter: " + counter);
			counter ++;
		}
	}

	// time complexity of nlogn
	public static void method4(int n) {
		int counter = 0;
		for (int i = 0; i < n; i++) {
			for(int k = 1; k <= n; k = k * 2) {
				System.out.println("Counter: " + counter);
				counter ++;
			}
		}
	}
	
	// time complexity of log(log(n))
	public static void method5(int n) {
		int counter = 0;
		for (int i = 2; i <=n; i = i * i) { 
			System.out.println("Counter: " + counter);
			counter ++;
		   }
	}	
}
