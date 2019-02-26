package model.node;

import java.io.Serializable;
import java.util.Arrays;

import model.element.Element;
import util.Util;

public class LeafNode extends Node<Integer> implements Serializable {
	private static final long serialVersionUID = 1169886521119023954L;

	public LeafNode(int b) {
		super(b);
	}

	public LeafNode(Element<Integer>[] elements, int b) {
		super(elements, b);
	}

	@Override
	public void insert(int key, Integer value) {
		int idx = Util.binarySearch(this.p, this.m, key);
		System.arraycopy(this.p, idx, this.p, idx + 1, this.m - idx);

		this.p[idx] = new Element<Integer>(key, value);
		this.m++;
	}

	@Override
	public Node split() {
		int midIdx = this.m / 2;

		// Split right node
		LeafNode right = new LeafNode(Arrays.copyOfRange(this.p, midIdx, this.p.length), this.p.length);
		right.r = this.r;

		// Use this as left node
		for (int i = midIdx; i < this.p.length; i++) {
			this.p[i] = null;
		}
		this.r = right;
		this.m = midIdx;

		// Set middle node, connect it to this and right.
		NonLeafNode middle = new NonLeafNode(this.p.length);
		middle.p[0] = new Element<Node>(right.p[0].key, this);
		middle.m++;
		middle.r = right;

		return middle;
	}

	@Override
	public void delete(int key) {
		int idx = Util.find(this.p, this.m, key);

		if (idx == -1) {
			System.out.println(String.format("[Error]: Key %d does not exist.", key));
			return;
		}

		System.arraycopy(this.p, idx + 1, this.p, idx, this.m - idx - 1);
		this.m--;

		this.p[this.m] = null;
	}
}
