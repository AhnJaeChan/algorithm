package model.node;

import java.io.Serializable;
import java.util.Arrays;

import model.element.Element;
import util.Util;

public class NonLeafNode extends Node<Node> implements Serializable {
	private static final long serialVersionUID = 8733143208363358888L;

	public NonLeafNode(int b) {
		super(b);
	}

	public NonLeafNode(Element<Node>[] elements, int b) {
		super(elements, b);
	}

	@Override
	public void insert(int key, Integer value) {
		Node childNode = this.getChildNode(key);

		childNode.insert(key, value);

		if (!childNode.isValid()) {
			Node newNode = childNode.split();
			this.insertNode(newNode);
		}
	}

	private Node getChildNode(int key) {
		int idx = Util.binarySearch(this.p, this.m, key);
		return idx == this.m ? this.r : this.p[idx].value;
	}

	@Override
	public Node split() {
		int midIdx = this.m / 2;

		NonLeafNode right = new NonLeafNode(Arrays.copyOfRange(this.p, midIdx + 1, this.p.length), this.p.length);
		right.r = this.r;

		NonLeafNode middle = new NonLeafNode(this.p.length);
		middle.p[0] = new Element<Node>(this.p[midIdx].key, this);
		middle.m = 1;
		middle.r = right;

		this.m = midIdx;
		this.r = this.p[midIdx].value;
		for (int i = midIdx; i < this.p.length; i++) {
			this.p[i] = null;
		}

		return middle;
	}

	private void insertNode(Node node) {
		int idx = Util.binarySearch(this.p, this.m, node.p[0].key);

		if (idx != this.m) {
			Element<Node>[] newP = new Element[p.length];
			System.arraycopy(this.p, 0, newP, 0, idx);
			System.arraycopy(this.p, idx, newP, idx + 1, this.m - idx);
			newP[idx] = node.p[0];
			newP[idx + 1].value = node.r;
			this.p = newP;
		} else {
			this.p[idx] = new Element<Node>(node.p[0].key, (Node) node.p[0].value);
			this.r = node.r;
		}

		this.m++;
	}

	@Override
	public void delete(int key) {
		Node childNode = this.getChildNode(key);

		childNode.delete(key);

		if (!childNode.isValid()) {
//			Node leftSibling = 
		} else {
			this.deleteKey(key);
		}
	}
	
	private void deleteKey(int key) {
	}
}
