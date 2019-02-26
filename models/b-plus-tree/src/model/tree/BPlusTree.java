package model.tree;

import java.io.Serializable;

import model.element.Element;
import model.node.LeafNode;
import model.node.Node;
import util.Util;

public class BPlusTree implements BalancedTree, Serializable {
	private static final long serialVersionUID = -1255887161361602083L;

	public int b = 0; // size of each node (max # of child nodes)

	private Node rootNode = null;

	public BPlusTree(int b) {
		this.b = b;

		this.rootNode = new LeafNode(this.b);
	}

	@Override
	public void insert(int key, Integer value) {
		this.rootNode.insert(key, value);

		if (!this.rootNode.isValid()) {
			this.rootNode = this.rootNode.split();
		}
	}

	@Override
	public void delete(int key) {
		this.rootNode.delete(key);
	}

	@Override
	public void search(int key) {
		LeafNode leafNode = this.findLeaf(key, true);

		// Currently at the leaf node
		Element<Integer> result = leafNode.find(key);
		if (result == null) {
			System.out.println("NOT FOUND");
		} else {
			System.out.println(result.value);
		}
	}

	@Override
	public void search(int from, int to) {
		if (from > to) {
			return;
		}

		LeafNode fromNode = this.findLeaf(from, false);
		LeafNode toNode = this.findLeaf(to, false);

		LeafNode currentNode = fromNode;
		int idx = Util.binarySearch(currentNode.p, currentNode.m, from);

		// Util.binarySearch() gives the right side of the array if the element is a
		// perfect match.
		// Therefore, if the content is same, start from idx - 1
		if (currentNode.p[idx - 1].key == from) {
			idx--;
		}

		while (currentNode != toNode) {
			for (; idx < currentNode.m; idx++) {
				System.out.println(currentNode.p[idx]);
			}
			idx = 0;
			currentNode = (LeafNode) currentNode.r;
		}

		idx = Util.binarySearch(currentNode.p, currentNode.m, to);
		for (int i = 0; i < idx; i++) {
			System.out.println(currentNode.p[i]);
		}
	}

	private LeafNode findLeaf(int key, boolean printPath) {
		Node currentNode = this.rootNode;

		// Trail down the tree
		while (!currentNode.isLeafNode()) {
			int idx = Util.binarySearch(currentNode.p, currentNode.m, key);
			int pathValue = idx != currentNode.m ? currentNode.p[idx].key : currentNode.p[idx - 1].key;

			if (printPath) {
				System.out.print(String.format("%d, ", pathValue));
			}

			currentNode = idx == currentNode.m ? currentNode.r : (Node) currentNode.p[idx].value;
		}

		return (LeafNode) currentNode;
	}

	@Override
	public boolean isBalanced() {
		// Didn't have time to implement this.
		return false;
	}

	@Override
	public String toString() {
		Node node = this.rootNode;

		while (!node.isLeafNode()) {
			node = (Node) node.p[0].value;
		}

		String str = String.format("B: %d\n", this.b);
		do {
			for (int i = 0; i < node.m; i++) {
				str += node.p[i].key + " , ";
			}
			str += "-> ";
			node = node.r;
		} while (node != null);
		str = str.substring(0, str.length() - 3);

		return str;
	}
}
