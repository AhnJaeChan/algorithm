package model.element;

import java.io.Serializable;

public class Element<T> implements Serializable {
	public int key;
	public T value;

	public Element(int key, T value) {
		this.key = key;
		this.value = value;
	}
	
	@Override
	public String toString() {
		return String.format("%d, %d", key, value);
	}
}
