package cryptoAnalyzer.gui;

import com.toedter.calendar.JDateChooser;
import cryptoAnalyzer.utils.AvailableCryptoList;
import cryptoAnalyzer.utils.DataVisualizationCreator;
import cryptoAnalyzer.utils.Processor;
import cryptoAnalyzer.utils.Result;
import cryptoAnalyzer.utils.Selector;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;


public class Main extends JFrame implements ActionListener{

	protected JFrame frame;
	private JPanel stats;
	
	private ArrayList<String> selectedList; // why is this an array list? 
	
	private JTextArea selectedCryptoList;
	private JComboBox <String> cryptoDropdown;
	private JComboBox metricDropdown;
	private JComboBox intervalDropdown;
	private JDateChooser dateChooser;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Main window = new Main();
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
	public Main() {
		initialize();
		
	}
	
	public JFrame getFrame() {
		return frame;
	}


	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
	
		frame = new JFrame();
		frame.setBounds(100, 100, 1500, 900);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		selectedList = new ArrayList<>();
		
		String[] cryptoNames = AvailableCryptoList.getInstance().getAvailableCryptos();
		cryptoDropdown = new JComboBox<String>(cryptoNames);
		// add back string
		cryptoDropdown.setBounds(190, 13, 211, 27);
		frame.getContentPane().add(cryptoDropdown);
		
		JLabel cryptoLabel = new JLabel("Choose a cryptocurrency:");
		cryptoLabel.setBounds(18, 17, 160, 16);
		frame.getContentPane().add(cryptoLabel);
		
		JButton addButton = new JButton("+");
		addButton.setBounds(398, 12, 44, 29);
		addButton.setActionCommand("add");
		addButton.addActionListener(this);
		frame.getContentPane().add(addButton);
		
		JButton subtractButton = new JButton("-");
		subtractButton.setBounds(431, 12, 44, 29);
		subtractButton.setActionCommand("subtract");
		subtractButton.addActionListener(this);
		frame.getContentPane().add(subtractButton);
		
		intervalDropdown = new JComboBox();
		intervalDropdown.setModel(new DefaultComboBoxModel(new String[] {"Daily", "Weekly", "Monthly", "Yearly"}));
		intervalDropdown.setBounds(986, 734, 160, 27);
		frame.getContentPane().add(intervalDropdown);
		
		metricDropdown = new JComboBox();
		metricDropdown.setModel(new DefaultComboBoxModel(new String[] {"Price", "Market Capitilization", "Volume", "Coins in Circulation", "% Change in Price", "% Change in Market Capitilization", "% Change in Volume", "% Change in Coins in Circulation"}));
		metricDropdown.setBounds(457, 734, 378, 27);
		frame.getContentPane().add(metricDropdown);
		
		JLabel metricLabel = new JLabel("Metric:");
		metricLabel.setBounds(414, 738, 61, 16);
		frame.getContentPane().add(metricLabel);
		
		JLabel intervalLabel = new JLabel("Interval:");
		intervalLabel.setBounds(930, 738, 61, 16);
		frame.getContentPane().add(intervalLabel);
		
		JButton refreshButton = new JButton("Refresh");
		refreshButton.setBounds(1178, 733, 245, 29);
		refreshButton.setActionCommand("refresh");
		refreshButton.addActionListener(this);
		frame.getContentPane().add(refreshButton);
		
		JLabel selectedCryptoListLabel = new JLabel("List of selected cryptocurrencies: ");
		selectedCryptoList = new JTextArea(16, 10);
		JScrollPane cryptoList = new JScrollPane(selectedCryptoList);
		cryptoList.setToolTipText("");
		cryptoList.setBounds(1178, 13, 245, 696);
		frame.getContentPane().add(cryptoList);
		
		dateChooser = new JDateChooser();
		dateChooser.setBounds(145, 734, 201, 26);
		frame.getContentPane().add(dateChooser);
		
		JLabel fromLabel = new JLabel("From:");
		fromLabel.setBounds(18, 738, 61, 16);
		frame.getContentPane().add(fromLabel);
		
		stats = new JPanel();
		stats.setBounds(100, 100, 1500, 900);
		stats.setLayout(new GridLayout(2, 2));
		frame.getContentPane().add(stats);
		
		
	}
	
	public void updateStats(JComponent component) {
		stats.add(component);
		stats.revalidate();
	}
	
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub
		String command = e.getActionCommand();
		if (command.contentEquals("refresh") ) {
			stats.removeAll();
			Selector newSelection = new Selector(selectedList, dateChooser.getDate(), intervalDropdown.getSelectedItem().toString(), metricDropdown.getSelectedItem().toString());
			Processor newProcessor = new Processor(newSelection);
			Result newResult = newProcessor.returnResult();
			
			//Double[][] array = newResult.getData();
			//for(int i = 0; i<array.length; i++)
			//{
			 //   for(int j = 0; j<array[0].length; j++)
			  //  {
			    //    System.out.print(array[i][j]);
			    //}
			    //System.out.println();
			//}
		
			DataVisualizationCreator newDataVis = new DataVisualizationCreator(newResult);
			newDataVis.createCharts();
		}
		
		if (command.contentEquals("add") ) {
			selectedList.add(cryptoDropdown.getSelectedItem().toString());
			String text = "";
			for (String crypto: selectedList)
				text += crypto + "\n";
			
			selectedCryptoList.setText(text);
		}
		
		if (command.contentEquals("subtract") ) {
			selectedList.remove(cryptoDropdown.getSelectedItem());
			String text = "";
			for (String crypto: selectedList)
				text += crypto + "\n";
			
			selectedCryptoList.setText(text);
		}
	}
}

