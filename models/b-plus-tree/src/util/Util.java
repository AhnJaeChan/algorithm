package util;

import model.element.Element;

public class Util {

	/***
	 * Finds the index for the key to be placed.
	 * If the key already exists, returns the right side index.
	 * 
	 * [Example]
	 * arr = {1, 3, 5} => binarySearch(arr, 3, 2) => returns 1
	 * arr = {1, 3, 5} => binarySearch(arr, 3, 3) => returns 2
	 * 
	 * @param arr	Array of Element
	 * @param size	Size of the search region (from 0 to index)
	 * @param key	Key to be searched
	 * @return
	 */
	public static int binarySearch(Element[] arr, int size, int key) {
		int start = 0;
		int end = size - 1;

		while (start <= end) {
			int mid = (start + end) / 2;

			if (key > arr[mid].key) {
				start = mid + 1;
			} else if (key < arr[mid].key) {
				end = mid - 1;
			} else {
				return mid + 1;
			}
		}

		return start;
	}

	/***
	 * Tries to find the key from the given array.
	 * If the match is found, index is returned,
	 * Else if it's not found -1 is returned.
	 * 
	 * @param arr
	 * @param size
	 * @param key
	 * @return
	 */
	public static int find(Element[] arr, int size, int key) {
		int start = 0;
		int end = size - 1;

		while (start <= end) {
			int mid = (start + end) / 2;

			if (key < arr[mid].key) {
				end = mid - 1;
			} else if (key > arr[mid].key) {
				start = mid + 1;
			} else if (key == arr[mid].key) {
				return mid;
			}
		}
		return -1;
	}
}
