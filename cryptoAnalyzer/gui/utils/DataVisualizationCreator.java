package utils;



import cryptoAnalyzer.gui.MainUI;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.CategoryAxis;
import org.jfree.chart.axis.DateAxis;
import org.jfree.chart.axis.LogAxis;
import org.jfree.chart.plot.CategoryPlot;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.category.BarRenderer;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.renderer.xy.XYSplineRenderer;
import org.jfree.data.Range;
import org.jfree.data.category.DefaultCategoryDataset;
import org.jfree.data.time.Day;
import org.jfree.data.time.TimeSeries;
import org.jfree.data.time.TimeSeriesCollection;

import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.util.ArrayList;
import java.util.Date;

public class DataVisualizationCreator {

	private Result fetchedData;

	public DataVisualizationCreator(Result fetchedData) {
		this.fetchedData = fetchedData;
	}

	private Object[] formatColumnNames() {
		String[] dates = fetchedData.getDates();
		Object[] columnNames = new Object[dates.length + 1];
		columnNames[0] = "Cryptocurrency";
		int index = 0;

		for (int i = 1; i < columnNames.length; i++) {
			columnNames[i] = dates[index];
			index++;
		}

		return columnNames;
	}

	private Object[][] formatData() {
		String[] cryptos = fetchedData.getCryptos();
		Double[][] cryptoData = fetchedData.getData();
		Object[][] data = new Object[cryptos.length][fetchedData.getDates().length];

		for (int i = 0; i < cryptos.length; i++) {
			data[i][0] = cryptos[i];
			for (int j = 1; j < (cryptoData[0].length + 1); j++) {
				data[i][j] = cryptoData[i][j-1];
			}
		}
		return data;
	}

	private TimeSeries[] formatTimeSeries() {
		String[] cryptos = fetchedData.getCryptos();
		Double[][] data = fetchedData.getData();
		ArrayList<Date> allDates = fetchedData.getAllDates();

		TimeSeries[] allSeries = new TimeSeries[cryptos.length];
		for (int j = 0; j < cryptos.length; j++) {
			String seriesName = cryptos[j] + " - " + fetchedData.getInterval();
			allSeries[j] = new TimeSeries(seriesName);
			for (int i = 0; i < allDates.size(); i++) {
				Date currentDateVal = allDates.get(i);
				allSeries[j].add(new Day(currentDateVal.getDate(), currentDateVal.getMonth() + 1, currentDateVal.getYear() + 1900), data[j][i]);
			}
		}

		return allSeries;
	}

	public void createCharts() {
		createTableOutput();
		createTimeSeries();
		createScatter();
		createBar();
	}

	private void createTableOutput() {
		// These come from selection menu
		Object[] columnNames = formatColumnNames();
		// These come from fetcher
		Object[][] data = formatData();
		JTable table = new JTable(data, columnNames);
		//table.setPreferredSize(new Dimension(600, 300));
		JScrollPane scrollPane = new JScrollPane(table);
		scrollPane.setBorder (BorderFactory.createTitledBorder (BorderFactory.createEtchedBorder (),
                "Daily Price Summary Table",
                TitledBorder.CENTER,
                TitledBorder.TOP));
		
		scrollPane.setPreferredSize(new Dimension(600, 300));
		table.setFillsViewportHeight(true);;
		
		MainUI.getInstance().updateStats(scrollPane);
	}

	private void createTimeSeries() {
		TimeSeries[] allSeries = formatTimeSeries();

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		for (int i = 0; i < allSeries.length; i++) {
			dataset.addSeries(allSeries[i]);
		}

		XYPlot plot = new XYPlot();
		XYSplineRenderer splinerenderer1 = new XYSplineRenderer();
		
		plot.setDataset(0, dataset);
		plot.setRenderer(0, splinerenderer1);
		DateAxis domainAxis = new DateAxis("");
		plot.setDomainAxis(domainAxis);
		plot.setRangeAxis(new LogAxis("Price(USD)"));

		//plot.mapDatasetToRangeAxis(0, 0);// 1st dataset to 1st y-axis
		//plot.mapDatasetToRangeAxis(1, 1); // 2nd dataset to 2nd y-axis
		//plot.mapDatasetToRangeAxis(2, 2);// 3rd dataset to 3rd y-axis
		
		JFreeChart chart = new JFreeChart("Daily Price Line Chart", new Font("Serif", java.awt.Font.BOLD, 18), plot,
				true);

		ChartPanel chartPanel = new ChartPanel(chart);
		chartPanel.setPreferredSize(new Dimension(600, 300));
		chartPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		chartPanel.setBackground(Color.white);
		
		MainUI.getInstance().updateStats(chartPanel);
	}

	private void createScatter() {
		TimeSeries[] allSeries = formatTimeSeries();

		TimeSeriesCollection dataset = new TimeSeriesCollection();
		for (int i = 0; i < allSeries.length; i++) {
			dataset.addSeries(allSeries[i]);
		}

		XYPlot plot = new XYPlot();
		XYItemRenderer itemrenderer1 = new XYLineAndShapeRenderer(false, true);

		plot.setDataset(0, dataset);
		plot.setRenderer(0, itemrenderer1);
		DateAxis domainAxis = new DateAxis("");
		plot.setDomainAxis(domainAxis);
		plot.setRangeAxis(new LogAxis("Price(USD)"));

		//plot.mapDatasetToRangeAxis(0, 0);// 1st dataset to 1st y-axis
		//plot.mapDatasetToRangeAxis(1, 1); // 2nd dataset to 2nd y-axis
		
		JFreeChart scatterChart = new JFreeChart("Daily Price Scatter Chart",
				new Font("Serif", java.awt.Font.BOLD, 18), plot, true);

		ChartPanel chartPanel = new ChartPanel(scatterChart);
		chartPanel.setPreferredSize(new Dimension(600, 300));
		chartPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		chartPanel.setBackground(Color.white);
		MainUI.getInstance().updateStats(chartPanel); // get frame not instance
	}

	private String theMonth(int month) {
		String[] months = {"Jan", "Feb", "Mar", "April", "May", "June", "July", "Aug", "Sept", "Oct", "Nov", "Dec"};
		return months[month];
	}

	private DefaultCategoryDataset formatDataset() {
		DefaultCategoryDataset dataset = new DefaultCategoryDataset();
		String[] cryptos = fetchedData.getCryptos();
		Double[][] data = fetchedData.getData();
		ArrayList<Date> allDates = fetchedData.getAllDates();
		for (int i = 0; i < cryptos.length; i++) {
			for (int j = 0; j < allDates.size(); j++) {
				String curDate = allDates.get(j) + "-" + theMonth(allDates.get(j).getMonth());
				dataset.setValue(data[i][j], cryptos[i], curDate);
			}
		}
		return dataset;
	}

	private void createBar() {
		
		DefaultCategoryDataset dataset = formatDataset();

		CategoryPlot plot = new CategoryPlot();
		BarRenderer barrenderer1 = new BarRenderer();

		plot.setDataset(0, dataset);
		plot.setRenderer(0, barrenderer1);
		CategoryAxis domainAxis = new CategoryAxis("Date");
		plot.setDomainAxis(domainAxis);
		LogAxis rangeAxis = new LogAxis("Price(USD)");
		rangeAxis.setRange(new Range(1.0, 70000.0));
		plot.setRangeAxis(rangeAxis);

		//plot.mapDatasetToRangeAxis(0, 0);// 1st dataset to 1st y-axis
		//plot.mapDatasetToRangeAxis(1, 1); // 2nd dataset to 2nd y-axis

		JFreeChart barChart = new JFreeChart("Daily Price Bar Chart", new Font("Serif", java.awt.Font.BOLD, 18), plot,
				true);

		ChartPanel chartPanel = new ChartPanel(barChart);
		chartPanel.setPreferredSize(new Dimension(600, 300));
		chartPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		chartPanel.setBackground(Color.white);
		MainUI.getInstance().updateStats(chartPanel);
	}

}
