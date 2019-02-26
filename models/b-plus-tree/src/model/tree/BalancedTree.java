package model.tree;

public abstract interface BalancedTree extends Tree {
	/***
	 * Checks if the tree is balanced or not.
	 * 
	 * @return True if the tree is balanced, False if the tree is not balanced.
	 */
	public boolean isBalanced();
}
