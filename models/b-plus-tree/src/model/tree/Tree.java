package model.tree;

public interface Tree {

	/***
	 * Insertion of the <key, value>.
	 * 
	 * @param element
	 */
	public void insert(int key, Integer value);

	/***
	 * Deletion of the key.
	 * 
	 * @param key
	 */
	public void delete(int key);

	/***
	 * Single search of the specific key.
	 * 
	 * @param key
	 */
	public void search(int key);

	/***
	 * Range search of keys between from and to.
	 * 
	 * @param from
	 * @param to
	 */
	public void search(int from, int to);
}
