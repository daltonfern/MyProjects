package utils;


import java.util.ArrayList;
import java.util.Date;

//This class stores the selections the user makes
public class Selector {
	
	private ArrayList<String> selectedCryptos;
	private Date startDate;
	private String interval;
	private String analysisType;
	
	public Selector(ArrayList<String> selectedCryptos, Date startDate, String interval, String analysisType) {
		this.selectedCryptos = selectedCryptos;
		this.startDate = startDate;
		this.interval = interval;
		this.analysisType = analysisType;
	}
	
	public ArrayList<String> getSelectedCryptos() {
		return selectedCryptos;
	}
	
	public Date getStartDate() {
		return startDate;
	}
	
	public String getInterval() {
		return interval;
	}
	
	public String analysisType() {
		return analysisType;
	}
	
	public void setSelectedCryptos(ArrayList<String> cryptos) {
		selectedCryptos = cryptos;
	}
	
	public void setStartDate(Date date) {
		startDate = date;
	}
	
	public void setInterval(String intv) {
		interval = intv;
	}
	
	public void setAnaylsisType(String anaType) {
		analysisType = anaType;
	}
}