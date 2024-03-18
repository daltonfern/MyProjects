package loginTest;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

public class login extends JFrame {

	private static login instance;

	private static JLabel chooseUser;
	private static JLabel choosePass;
	private static JTextField userText;
	private static JTextField passText;
	private static JButton logins;

	public static login getInstance() {
		if (instance == null)
			instance = new login();

		return instance;
	}

	private login() {

		super("Login");

		chooseUser = new JLabel("Username: ");
		choosePass = new JLabel("Password: ");
		userText = new JTextField(20);
		passText = new JTextField(20);
		logins = new JButton("Login");
		logins.setActionCommand("login");
		// logins.addActionListener(this);

		choosePass.setBounds(100, 80, 80, 80);
		chooseUser.setBounds(100, 50, 80, 80);
		userText.setBounds(175, 80, 200, 20);
		passText.setBounds(175, 110, 200, 20);
		logins.setBounds(230, 150, 80, 20);
	}

	public static void main(String[] args) {
		JFrame frame = login.getInstance();
		frame.setSize(500, 300);
		frame.add(chooseUser);
		frame.add(choosePass);
		frame.setLayout(null);
		frame.add(userText);
		frame.add(passText);
		frame.add(logins);
		frame.setVisible(true);
	}

}