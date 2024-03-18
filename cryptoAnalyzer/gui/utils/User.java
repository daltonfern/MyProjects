package utils;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class User{

	protected String username;
	protected String password;
	File database = new File("C:\\Users\\aweso\\IdeaProjects\\group\\cryptoAnalyzer\\src\\main\\java\\cryptoAnalyzer\\cs2212_userDatabase.txt");

	public User(String user, String pass) {
		username = user;
		password = pass;
	}

	public String getUser() {
		return username;
	}

	public String getPass() {
		return password;
	}

	public void setUser(String user) {
		this.username = user;
	}

	public void setPass(String pass) {
		this.password = pass;
	}

	public boolean validate(User user) {
		try {
			Scanner myReader = new Scanner(database);
			while (myReader.hasNextLine()) {
				String userInfo = myReader.nextLine();
				String[] parts = userInfo.split(", ", 2);
				if (parts[0].equals(user.getUser()) & parts[1].equals(user.getPass())) {
					myReader.close();
					return true;
				}
			}
			myReader.close();
		} catch (FileNotFoundException e) {
		}

		return false;
	}
}