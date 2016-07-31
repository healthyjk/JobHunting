import java.util.*;
public class InsertionSort {
	private int[] array;

	public InsertionSort() {
		this.inputArray();
	}

	public void inputArray() {
		Scanner scanner = new Scanner(System.in);
		System.out.print("Please input the length:");
		int len = scanner.nextInt();
		if (len > 0)
			array = new int[len];
		System.out.print("Please input the numbers:");
		for (int i = 0; i < len; ++i) {
			array[i] = scanner.nextInt();
		}
	}

	public void printArray() {
		for (int i = 0; i < array.length; ++i) {
			System.out.print(array[i] + "\t");
		}
		System.out.print("\n");
	}

	public void startSort() {
		int len = array.length;
		int j;
		for (int i = 1; i < len; ++i) {
			int temp = array[i];
			j = i - 1;
			while ((j >= 0) && (array[j] > temp)) {
				array[j+1] = array[j];
				j--;	
			}
			if (j != (i-1)) {
				array[j+1] = temp;
			}
		}
	}

	public static void main(String[] args) {
		InsertionSort insertionSort = new InsertionSort();
		insertionSort.startSort();
		insertionSort.printArray();
	}
}
