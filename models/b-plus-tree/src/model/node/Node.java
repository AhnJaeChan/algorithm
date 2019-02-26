package model.node;

import java.io.Serializable;

import model.element.Element;
import model.tree.BPlusTree;
import util.Util;

public abstract class Node<T> implements Serializable {
	private static final long serialVersionUID = -3845814806462992515L;

	public int m = 0;
	public Element<T>[] p = null; // Wanted to use ArrayList but the constraints are to use array
	public Node r = null;

	public Node(int b) {
		this.p = new Element[b];
	}

	public Node(Element[] elements, int b) {
		this(b);

		System.arraycopy(elements, 0, this.p, 0, elements.length);
		this.m = elements.length;
	}

	public boolean isLeafNode() {
		return this instanceof LeafNode;
	}

	public boolean isValid() {
		return this.m < this.p.length;
	}

	public Element<T> find(int key) {
		int idx = Util.find(this.p, this.m, key);

		return idx == -1 ? null : this.p[idx];
	}

	public abstract void insert(int key, Integer value);

	public abstract Node split();

	public abstract void delete(int key);
}
