 import org.jfree.chart.ChartFactory;
 import org.jfree.chart.ChartPanel;
 import org.jfree.chart.JFreeChart;
 import org.jfree.chart.annotations.XYTextAnnotation;
 import org.jfree.chart.plot.PlotOrientation;
 import org.jfree.chart.plot.XYPlot;
 import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
 import org.jfree.data.xy.XYSeries;
 import org.jfree.data.xy.XYSeriesCollection;

 import javax.swing.*;
 import java.awt.*;
 import java.io.*;
 import java.util.ArrayList;
 import java.util.HashSet;

 class City {

      public double x, y;
      public int id;
      public City(int id, double x, double y) { 
          this.id = id; 
           this.x = x; 
            this.y = y; 

       }
    }

   public class GAPlotAll {

          public static void main(String[] args) {

               ArrayList<City> cities = loadCities("cities.txt");
                    System.out.println("Loaded " + cities.size() + " cities from cities.txt");
        
               ArrayList<Integer> bestTour = loadBestTour("results/ga_results.csv");
                     System.out.println(" Loaded tour with " + bestTour.size() + " points");

                     if (cities.isEmpty()) {

                              System.err.println("ERROR: No cities loaded! Check cities.txt");
                                  return;

                       }

                       if (bestTour.isEmpty()) {

                                System.err.println("ERROR: No tour loaded! Check ga_results.csv");
                                  return;

                           }

       
                          XYSeries tourSeries = new XYSeries("Best Tour");

                              for (int i = 0; i < bestTour.size(); i++) {
                               int cityId = bestTour.get(i);
            
           
                           City c = null;

                            for (City city : cities) {

                               if (city.id == cityId) {
                                  c = city;
                                   break;

                               }
                            }
            
                             if (c != null) {

                                     tourSeries.add(c.x, c.y);

                              } 
                              
                              else {

                                    System.err.println(" City ID " + cityId + " not found in cities list!");
                                 }
                              }

                              XYSeriesCollection tourDataset = new XYSeriesCollection();
                               tourDataset.addSeries(tourSeries);

                              JFreeChart tourChart = ChartFactory.createXYLineChart(

                                "Best GA Tour (" + cities.size() + " cities)",
                                 "X coordinate",
                                  "Y coordinate",
                                   tourDataset,
                                    PlotOrientation.VERTICAL,
                                     true, true, false
                                  );

                                  XYPlot plot = tourChart.getXYPlot();

       
                                XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer(true, true);
                                 renderer.setSeriesPaint(0, Color.GREEN.darker());
                                  renderer.setSeriesStroke(0, new BasicStroke(2.5f));
                                    renderer.setSeriesShapesVisible(0, true);
                                       renderer.setSeriesShape(0, new java.awt.geom.Ellipse2D.Double(-5, -5, 10, 10));
                                         plot.setRenderer(renderer);

       
                                        HashSet<Integer> drawnCities = new HashSet<>();

                                          for (int i = 0; i < bestTour.size(); i++) {

                                               int cityId = bestTour.get(i);
            
           
                                               City c = null;
                                                 for (City city : cities) {

                                                if (city.id == cityId) {

                                                        c = city;
                                                         break;

                                                 }
                                             }
            
                                 if (c != null && !drawnCities.contains(c.id)) {

                                    XYTextAnnotation annotation = new XYTextAnnotation(
                                             String.valueOf(c.id), c.x + 0.5, c.y + 0.5 );

                                       annotation.setFont(new Font("Arial", Font.BOLD, 12));
                                         annotation.setPaint(Color.RED);
                                           plot.addAnnotation(annotation);
                                                drawnCities.add(c.id);

                                 }
                             }

                         System.out.println("Graph created with " + drawnCities.size() + " unique cities");

        
                                 SwingUtilities.invokeLater(() -> {


                                              JFrame frame = new JFrame("GA TSP - Best Tour with City IDs");
                                               frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
                                                 frame.setLayout(new BorderLayout());
                                                   frame.add(new ChartPanel(tourChart), BorderLayout.CENTER);
                                                     frame.setSize(900, 900);
                                                        frame.setLocationRelativeTo(null);
                                                           frame.setVisible(true);
                                                        });

                                                    }

   
                         private static ArrayList<City> loadCities(String filename) {

                                  ArrayList<City> cities = new ArrayList<>();
                         try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
                                       String line;
                                        boolean firstLine = true;
                                         int lineNum = 0;
            
                              while ((line = br.readLine()) != null) {
                                        lineNum++;
                                        line = line.trim();
                                  if (line.isEmpty()){

                                        continue;
                                  }

                                  if (firstLine) { 

                                        firstLine = false; 
                                         continue; 
                                 }

                                  String[] parts = line.split("\\s+");

                                   if (parts.length < 3) {

                                        System.err.println("WARNING: Line " + lineNum + " has less than 3 columns, skipping");
                                          continue;

                                  }

                            try {

                                   int id = Integer.parseInt(parts[0]);
                                    double x = Double.parseDouble(parts[1]);
                                     double y = Double.parseDouble(parts[2]);
                                       cities.add(new City(id, x, y));

                             }
                              catch (NumberFormatException e) {

                                          System.err.println(" Could not parse line " + lineNum + ": " + line);
                                     }
                                  }
                               } 
                               
                                catch (IOException e) { 

                                          System.err.println("reading cities.txt: " + e.getMessage());
                                           e.printStackTrace(); 

                                 }
                                  return cities;
                              }

    
              private static ArrayList<Integer> loadBestTour(String filename) {
                            ArrayList<Integer> tour = new ArrayList<>();

                       try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
                                  String line;

                              while ((line = br.readLine()) != null) {

                                 if (line.startsWith("Final Best Tour")) {
                    
                   
                                     int tourStart = line.indexOf("Tour:");
                                      int pipe = line.indexOf("|");
                    
                                       if (tourStart >= 0 && pipe > tourStart) {
                       
                                         String tourStr = line.substring(tourStart + 5, pipe).trim();
                        
                        
                                          if (tourStr.startsWith("Tour:")) {

                                              tourStr = tourStr.substring(5).trim();
                                         }
                        
                                               String[] cityParts = tourStr.split("->");
                        
                                                  for (String c : cityParts) {
                                                      c = c.trim();

                                                       if (c.isEmpty()){

                                                           continue;
                                                       }
                                        try {

                                                 int cityId = Integer.parseInt(c);
                                                 tour.add(cityId);
                                       }
                                       
                                        catch (NumberFormatException e) {


                                                 System.err.println("Failed to parse city ID: '" + c + "'");
                            }
                        }
                        
                       
                                if (!tour.isEmpty() && !tour.get(0).equals(tour.get(tour.size() - 1))) {

                                               tour.add(tour.get(0));
                             }
                        
                                                break;
                       }
                    }
                 }
              } 
              
                catch (IOException e) { 

                                    System.err.println("Error reading ga_results.csv: " + e.getMessage());
                                    e.printStackTrace(); 
                             }
        
                    if (tour.isEmpty()) {

                                    System.err.println("WARNING: No tour found in " + filename);
                               }
        
                                    return tour;
                         }
                       }