import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.annotations.XYTextAnnotation;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.plot.PlotOrientation;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import org.jfree.chart.ui.TextAnchor;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import javax.swing.*;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.io.*;
import java.util.*;
import java.util.List;

  class City {

        public double x, y; public int id;
        public City(int id, double x, double y){ this.id=id; this.x=x; this.y=y; }
  }

 public class GAPlotAll {

     public static void main(String[] args) {

        ArrayList<City> cities = loadCities("cities.txt");
        
        ArrayList<Integer> bestTour = loadBestTour("results/ga_results.csv");

        if(cities.isEmpty() || bestTour.isEmpty()){ 

                  System.err.println("Data missing! Check cities.txt and results/ga_results.csv"); 
                  return; 
        }
        
          System.out.println("Loaded " + cities.size() + " cities.");
          System.out.println("Best Tour Sequence: " + bestTour);

        
         List<City[]> edges = new ArrayList<>();

         for(int i=0; i < bestTour.size()-1; i++){

               City a = findCity(cities, bestTour.get(i));
               City b = findCity(cities, bestTour.get(i+1));
               if(a != null && b != null) edges.add(new City[]{a, b});
         }

        
         XYSeries s = new XYSeries("Tour", false, true);

         for(int id : bestTour){ 

              City c = findCity(cities, id); 
              if(c != null) s.add(c.x, c.y); 
         }
        
         XYSeriesCollection ds = new XYSeriesCollection(); 
         ds.addSeries(s);

         JFreeChart chart = ChartFactory.createXYLineChart(

               "Best GA Tour ", "X-Coordinate", "Y-Coordinate",
                ds, PlotOrientation.VERTICAL, false, true, false);

        XYPlot plot = chart.getXYPlot();
        plot.setBackgroundPaint(new Color(245, 245, 245));
        
        
        NumberAxis domain = (NumberAxis) plot.getDomainAxis();
        domain.setRange(-10, 110);
        NumberAxis range = (NumberAxis) plot.getRangeAxis();
        range.setRange(-10, 110);

        
        XYLineAndShapeRenderer r = new XYLineAndShapeRenderer(true, true);
        r.setSeriesPaint(0, new Color(0, 150, 0)); 
        r.setSeriesStroke(0, new BasicStroke(2.5f));
        r.setSeriesShape(0, new java.awt.geom.Ellipse2D.Double(-4, -4, 8, 8));
        plot.setRenderer(r);

    
        HashSet<Integer> drawn = new HashSet<>();

        for(int id : bestTour){

            if(drawn.contains(id)){
                   continue;
            }
            City c = findCity(cities, id); 

            if(c == null) {
                 continue;
            }

            XYTextAnnotation ann = new XYTextAnnotation(" " + c.id, c.x, c.y + 2.5);
            ann.setFont(new Font("SansSerif", Font.BOLD, 13));
            ann.setPaint(Color.RED);
            ann.setTextAnchor(TextAnchor.BOTTOM_CENTER);
            plot.addAnnotation(ann); 
            drawn.add(id);
        }

        
        ChartPanel cp = new ChartPanel(chart, false) {
            
            @Override public void paintComponent(Graphics g){

                super.paintComponent(g);
                Graphics2D g2 = (Graphics2D) g.create();
                g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

                Rectangle2D area = getChartRenderingInfo().getPlotInfo().getDataArea();
                ValueAxis da = plot.getDomainAxis(), ra = plot.getRangeAxis();
                g2.setFont(new Font("SansSerif", Font.PLAIN, 10));

                for(City[] edge : edges){

                    City a = edge[0], b = edge[1];
                    double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
                    double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
                    double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
                    double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

                    double mx = (ax + bx) / 2.0, my = (ay + by) / 2.0;
                    double dist = Math.sqrt(Math.pow(b.x - a.x, 2) + Math.pow(b.y - a.y, 2));
                    
                    String label = String.format("%.1f", dist);
                    g2.setColor(new Color(30, 100, 200));
                    g2.drawString(label, (int)mx + 5, (int)my - 5);
                }

                    g2.dispose();
            }
        };

            JFrame frame = new JFrame("GA TSP Solver - Corrected Plot");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(cp);
            frame.setSize(850, 850);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
     }

       static City findCity(ArrayList<City> cities, int id){

             for(City c : cities) 

              if(c.id == id) {

                   return c; 

              }
              return null;
     }

     static ArrayList<City> loadCities(String f){

        ArrayList<City> cities = new ArrayList<>();
        try(BufferedReader br = new BufferedReader(new FileReader(f))){
            String line; 
            boolean first = true;
            while((line = br.readLine()) != null){
                line = line.trim(); 
                if(line.isEmpty()) {
                     continue;
                }
                if(first && (line.contains(",") || line.split("\\s+").length < 3)){ 
                     first = false; 
                     continue;
              }
                String[] p = line.split("\\s+");
                if(p.length >= 3) {
                     cities.add(new City(Integer.parseInt(p[0]), Double.parseDouble(p[1]), Double.parseDouble(p[2])));
                }
            }
        } catch(Exception e){ 

                System.err.println("City Load Error: " + e.getMessage()); 
         }
        return cities;
    }

     static ArrayList<Integer> loadBestTour(String f) {

        ArrayList<Integer> tour = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
              String line;
            while ((line = br.readLine()) != null) {

                if (line.contains("Final Best Tour")) {
                    
                    String tourData = line.substring(line.lastIndexOf("Tour:") + 5).split("\\|")[0].trim();
                    String[] ids = tourData.split("->");

                    for (String s : ids) {

                         if (!s.trim().isEmpty()) tour.add(Integer.parseInt(s.trim()));
                    }
                        break;
                 }
             }
         } 
         catch (Exception e) { 
            System.err.println("Tour Load Error: " + e.getMessage()); 
         }
          return tour;
      }
 }