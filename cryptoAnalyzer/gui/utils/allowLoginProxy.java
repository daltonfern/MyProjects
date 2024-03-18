package utils;


import javax.swing.JFrame;
import javax.swing.JOptionPane;
import cryptoAnalyzer.gui.LoginUI;

public class allowLoginProxy extends Login{
	
	private User user;
	private Login login;
	//private JFrame newFrame = new JFrame();
	//newFrame = LoginUI.getFrame();
	
	public allowLoginProxy(User user) {
		this.user = user;
		this.login = new allowLogin();
	}

	@Override
	public void startUI() {
		// TODO Auto-generated method stub
		if (user.validate(user) == true) {
			login.startUI();
		}
		
		else if (user.validate(user) == false) {
			// how to get the frame?  
			JOptionPane.showMessageDialog(LoginUI.getFrame(), "The login credentials were incorrect");
			System.exit(0);
		}
	}
	
	

}
