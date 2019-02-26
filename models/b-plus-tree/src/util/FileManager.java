package util;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import model.element.Element;

public class FileManager {
	public static void writeObjectToFile(Object obj, String fileName) throws IOException {
		FileOutputStream fos = null;
		ObjectOutputStream oos = null;

		fos = new FileOutputStream(fileName);
		oos = new ObjectOutputStream(fos);

		oos.writeObject(obj);

		if (oos != null) {
			oos.close();
		}

		if (fos != null) {
			fos.close();
		}
	}

	public static Object readObjectFromFile(String fileName) throws IOException, ClassNotFoundException {
		FileInputStream fis = new FileInputStream(fileName);
		ObjectInputStream ois = new ObjectInputStream(fis);

		Object obj = ois.readObject();

		if (ois != null) {
			ois.close();
		}

		if (fis != null) {
			fis.close();
		}

		return obj;
	}

	public static ArrayList<Element<Integer>> readDataFromFile(String fileName)
			throws IOException, ClassNotFoundException {
		FileReader fr = new FileReader(fileName);
		BufferedReader br = new BufferedReader(fr);

		String line;
		ArrayList<Element<Integer>> data = new ArrayList<Element<Integer>>();
		while ((line = br.readLine()) != null) {

			// use comma as separator
			String[] strValues = line.split(", ");

			Integer key = Integer.parseInt(strValues[0]);
			Integer value = Integer.parseInt(strValues[1]);
			
			data.add(new Element<Integer>(key, value));
		}
		
		return data;
	}
}
