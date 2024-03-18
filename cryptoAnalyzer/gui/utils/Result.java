package cryptoAnalyzer.utils;

import java.util.ArrayList;
import java.util.Date;

public class Result {

    private String[] cryptos;
    private Double[][] data;
    private String[] dates;
    private ArrayList<Date> allDates;
    private String interval;

    public Result(String[] cryptos, Double[][] data, String[] dates, ArrayList<Date> allDates, String interval) {
        this.cryptos = cryptos;
        this.data = data;
        this.dates = dates;
        this.allDates = allDates;
        this.interval = interval;
    }

    public String[] getCryptos() {
        return cryptos;
    }

    public Double[][] getData() {
        return data;
    }

    public String[] getDates() {
        return dates;
    }

    public ArrayList<Date> getAllDates() { return allDates; }

    public String getInterval() { return  interval; }
}
