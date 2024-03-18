import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPasswordField;
import javax.swing.JTextField;

import utils.Login;
import utils.User;
import utils.allowLoginProxy;

public class LoginUI extends JFrame implements ActionListener {

	private static JFrame frame;
	private JTextField usernameEntered;
	private JPasswordField passwordField;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					LoginUI window = new LoginUI();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public LoginUI() {
		initialize();
	}

	public static JFrame getFrame() {
		return frame;
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 450, 192);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);

		JLabel usernameLabel = new JLabel("Username:");
		usernameLabel.setBounds(25, 36, 78, 16);
		frame.getContentPane().add(usernameLabel);

		JLabel passwordLabel = new JLabel("Password:");
		passwordLabel.setBounds(25, 64, 78, 16);
		frame.getContentPane().add(passwordLabel);

		usernameEntered = new JTextField();
		usernameEntered.setBounds(138, 31, 278, 26);
		frame.getContentPane().add(usernameEntered);
		usernameEntered.setColumns(10);

		passwordField = new JPasswordField();
		passwordField.setBounds(138, 59, 278, 26);
		frame.getContentPane().add(passwordField);

		JButton loginButton = new JButton("LOGIN");
		loginButton.setBounds(299, 109, 117, 29);
		loginButton.addActionListener(this);
		frame.getContentPane().add(loginButton);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		String user = usernameEntered.getText();
		String pass = passwordField.getText();

		User newUser = new User(user, pass);

		Login loginAttempt = new allowLoginProxy(newUser);
		loginAttempt.startUI();
	}
}
