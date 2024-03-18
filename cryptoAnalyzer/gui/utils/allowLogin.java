package utils;


import cryptoAnalyzer.gui.Main;
import cryptoAnalyzer.gui.LoginUI;

public class allowLogin extends Login{

	@Override
	public void startUI() {
		LoginUI.getFrame().dispose(); // how to get the frame? 
		
		Main main = new Main();
		main.getFrame().setVisible(true);
	}
	
	

}
