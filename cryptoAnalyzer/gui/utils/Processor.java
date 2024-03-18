package utils;


import java.text.SimpleDateFormat;
import java.time.Duration;
import java.util.ArrayList;
import java.util.Date;
import static java.lang.Math.abs;

public class Processor {

    private Selector selections;
    private ArrayList<String> dates;
    private Double[][] result;
    private DataFetcher fetcher = new DataFetcher();
    private ArrayList<Date> allDates = new ArrayList<Date>();

    public Processor(Selector selections) {
        this.selections = selections;
    }

    public Double[][] basicAnalysis() {
        ArrayList<String> cryptos = selections.getSelectedCryptos();
       
        System.out.println("ArrayList" + cryptos);
        System.out.println(cryptos.get(0));
        
        Date startDate = selections.getStartDate(); 
        System.out.println("StartDate" + startDate);
        
        String interval = selections.getInterval();
        String analysis = selections.analysisType();
        dates = new ArrayList<String>();
        
        Date currentDate = new Date();
        currentDate.setDate(currentDate.getDate());
        
        long diff = currentDate.getTime() - startDate.getTime();
        diff = (diff / (1000 * 60 * 60 * 24)) + 1;
        System.out.println(diff);
        
        // add if statements for daily, weekly, monthly, yearly 
        
        result = new Double[cryptos.size()][(int) diff];
        
        Date tempDate = new Date(startDate.getDate());
        tempDate.setDate(startDate.getDate());
        tempDate.setMonth(startDate.getMonth());
        tempDate.setYear(startDate.getYear());

        
        Date changeTemp = new Date();
        changeTemp.setDate(startDate.getDate());
        
        String tempDates = "";
        String tempDatesTwo = "";
        SimpleDateFormat formatter = new SimpleDateFormat("dd-MM-yyyy");
        int index = 0;

        if (interval == "Daily") {
           changeTemp.setDate(changeTemp.getDate() + 1);
        }
        else if (interval == "Weekly") {
            if (changeTemp.getDate() > 24) {                                          //Check if incrementing date by 7 days would produce out of range date (Ex. 25th day of the month + 7 days cannot equal 32nd day of the month)
                int newDay = (changeTemp.getDate() + 7) - 31;                         //Get day considering next month
                changeTemp.setMonth(changeTemp.getMonth() + 1);                         //Set next month
                changeTemp.setDate(newDay);
            }
            else {
                changeTemp.setDate(changeTemp.getDate() + 7);
            }
        }
        else if (interval == "Monthly") {
            changeTemp.setMonth(changeTemp.getMonth() + 1);
        }
        else {
            changeTemp.setYear(changeTemp.getYear() + 1);
        }

        for (int j = 0; j < cryptos.size(); j++) {
        	
        	tempDate.setDate(startDate.getDate());
            tempDate.setMonth(startDate.getMonth());
            tempDate.setYear(startDate.getYear());
        	
            while(tempDate.before(currentDate)) {
                //Loop from selected start date to current date at selected interval rate
                    allDates.add(tempDate);
                    System.out.println("Temp Date" + tempDate);
                    tempDates = formatter.format(tempDate);
                    System.out.println("Dates" + tempDates);
                    tempDatesTwo = formatter.format(changeTemp);                                     //Format date at current interval
                    dates.add(tempDates);

                    if (analysis == "Price") {
                        result[j][index] = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        System.out.println(result[j][index]);
                    }
                    else if (analysis == "Market Capitilization") {
                        result[j][index] = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDates);
                    }
                    else if (analysis == "Volume") {
                        result[j][index] = fetcher.getVolumeForCoin(cryptos.get(j).toLowerCase(), tempDates);
                    }
                    else if (analysis == "Coins in Circulation") {
                        double price = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double marketCap = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        result[j][index] = marketCap/price;
                    }

                    else if (analysis == "% Change in Price") {
                        if (changeTemp.after(changeTemp)){
                            break;
                        }
                        double n = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double next_n = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDatesTwo);
                        result[j][index] = ((next_n - n) / abs(n))*100;
                    }

                    else if (analysis == "% Change in Market Capitilization") {
                        if (changeTemp.after(changeTemp)){
                            break;
                        }
                        double n = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double next_n = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDatesTwo);
                        result[j][index] = ((next_n - n) / abs(n))*100;
                    }

                    else if (analysis == "% Change in Volume") {
                        if (changeTemp.after(changeTemp)){
                            break;
                        }
                        double n = fetcher.getVolumeForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double next_n = fetcher.getVolumeForCoin(cryptos.get(j).toLowerCase(), tempDatesTwo);
                        result[j][index] = ((next_n - n) / abs(n))*100;
                    }

                    else if (analysis == "% Change in Coins in Circulation") {
                        if (changeTemp.after(changeTemp)){
                            break;
                        }
                        double n_price = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double next_n_price = fetcher.getPriceForCoin(cryptos.get(j).toLowerCase(), tempDatesTwo);
                        double n_marketCap = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDates);
                        double next_n_marketCap = fetcher.getMarketCapForCoin(cryptos.get(j).toLowerCase(), tempDatesTwo);
                        double n = n_marketCap / n_price;
                        double next_n = next_n_marketCap / next_n_price;
                        result[j][index] = ((next_n - n) / abs(n))*100;
                    }

                index = index + 1;

                    if (interval == "Daily") {
                        tempDate.setDate(tempDate.getDate() + 1);
                        changeTemp.setDate(changeTemp.getDate() + 1);
                    }
                    else if (interval == "Weekly") {
                        if (tempDate.getDate() > 24) {                                          //Check if incrementing date by 7 days would produce out of range date (Ex. 25th day of the month + 7 days cannot equal 32nd day of the month)
                            int newDay = (tempDate.getDate() + 7) - 31;                         //Get day considering next month
                            tempDate.setMonth(tempDate.getMonth() + 1);                         //Set next month
                            tempDate.setDate(newDay);
                        }
                        else {
                            tempDate.setDate(tempDate.getDate() + 7);
                        }
                        if (changeTemp.getDate() > 24) {                                          //Check if incrementing date by 7 days would produce out of range date (Ex. 25th day of the month + 7 days cannot equal 32nd day of the month)
                            int newDay = (changeTemp.getDate() + 7) - 31;                         //Get day considering next month
                            changeTemp.setMonth(changeTemp.getMonth() + 1);                         //Set next month
                            changeTemp.setDate(newDay);
                        }
                        // FIX****
                        
                        else {
                            changeTemp.setDate(changeTemp.getDate() + 7);
                        }
                    }
                    else if (interval == "Monthly") {
                        tempDate.setMonth(tempDate.getMonth() + 1);
                        changeTemp.setMonth(changeTemp.getMonth() + 1);
                    }
                    else {
                        tempDate.setYear(tempDate.getYear() + 1);
                        changeTemp.setYear(changeTemp.getYear() + 1);
                    }
                }
        }
        return result;
    }



    public Result returnResult() {
    	Double[][] dataValues = basicAnalysis();
        ArrayList<String> cryptos = selections.getSelectedCryptos();
        String[] cryptoNames = cryptos.toArray(new String[cryptos.size()]);
        String[] intervalDates = dates.toArray(new String[dates.size()]);
        Result analysisResults = new Result(cryptoNames, dataValues, intervalDates, allDates, selections.getInterval());
        return analysisResults;
    }

}