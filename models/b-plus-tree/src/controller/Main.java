package controller;

import java.io.IOException;
import java.util.ArrayList;

import model.element.Element;
import model.tree.BPlusTree;
import util.FileManager;

public class Main {

	public static void main(String[] args) throws IOException, ClassNotFoundException {

		if (args.length < 1) {
			System.out.println("Arguments are not given.");
			return;
		}

		if (args[0].charAt(0) != '-') {
			System.out.println("Please provide an option for the first argument.");
			return;
		}

		String indexFile = args[1];
		int argIdx = 2; // 0: option, 1: index_file so 2 should be the starting point.
		BPlusTree tree;

		switch (args[0]) {
		case "-c":
			int b = Integer.parseInt(args[argIdx++]);

			tree = new BPlusTree(b);

			FileManager.writeObjectToFile(tree, indexFile);
			break;
		case "-i":
			String dataFile = args[argIdx++];

			tree = (BPlusTree) FileManager.readObjectFromFile(indexFile);

			ArrayList<Element<Integer>> dataList = FileManager.readDataFromFile(dataFile);
			if (dataList != null) {
				dataList.forEach((data) -> {
					tree.insert(data.key, data.value);
				});
			}

			FileManager.writeObjectToFile(tree, indexFile);
			break;
		case "-d":
			System.out.println("Delete");
			break;
		case "-s":
			int key = Integer.parseInt(args[argIdx++]);

			tree = (BPlusTree) FileManager.readObjectFromFile(indexFile);

			tree.search(key);
			break;
		case "-r":
			int from = Integer.parseInt(args[argIdx++]);
			int to = Integer.parseInt(args[argIdx++]);

			tree = (BPlusTree) FileManager.readObjectFromFile(indexFile);

			tree.search(from, to);
			break;
		default:
			System.out.println(String.format("The option %s is not supported.", args[0]));
			return;
		}

	}

}
