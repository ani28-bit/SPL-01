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
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.geom.Rectangle2D;
import java.io.*;
import java.util.*;
import java.util.List;

 class City {

       public double x, y; public int id;
       public City(int id, double x, double y){
                     this.id=id; this.x=x; this.y=y; 
       }
    }

  public class GAPlotCompare {

     static final Color COLOR_GA   = new Color(0, 160, 0);
     static final Color COLOR_ALT1 = new Color(220, 120, 0);
     static final Color COLOR_ALT2 = new Color(160, 0, 180);
     static final Color COLOR_ALT3 = new Color(0, 160, 200);

    public static void main(String[] args) {

        ArrayList<City> cities = loadCities("cities.txt");
        System.out.println("Loaded " + cities.size() + " cities");

        ArrayList<Integer> gaTour = loadTourFromSummary("CPLEX/Summary.txt", false);


        if (gaTour.isEmpty()) {
                gaTour = loadBestTourFromCSV("results/ga_results.csv");
            }
        if (cities.isEmpty() || gaTour.isEmpty()) {

                System.out.println("Error: data missing!");
                return;
        }

       
        ArrayList<Integer> alt1 = nearestNeighborTourFrom(cities, cities.get(0).id);
        ArrayList<Integer> alt2 = nearestNeighborTourFrom(cities, cities.get(cities.size()/2).id);
        ArrayList<Integer> alt3 = nearestNeighborTourFrom(cities, cities.get(cities.size()/4).id);

        double gaDist   = tourDistance(cities, gaTour);
        double alt1Dist = tourDistance(cities, alt1);
        double alt2Dist = tourDistance(cities, alt2);
        double alt3Dist = tourDistance(cities, alt3);

        System.out.printf("GA Best   : %.2f%n", gaDist);
        System.out.printf("Alt 1 (NN): %.2f%n", alt1Dist);
        System.out.printf("Alt 2 (NN): %.2f%n", alt2Dist);
        System.out.printf("Alt 3 (NN): %.2f%n", alt3Dist);

        
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(buildSeries("Alt 1 - NN from city " + cities.get(0).id +
            " (dist: " + String.format("%.1f", alt1Dist) + ")", cities, alt1));
        dataset.addSeries(buildSeries("Alt 2 - NN from city " + cities.get(cities.size()/2).id +
            " (dist: " + String.format("%.1f", alt2Dist) + ")", cities, alt2));
        dataset.addSeries(buildSeries("Alt 3 - NN from city " + cities.get(cities.size()/4).id +
            " (dist: " + String.format("%.1f", alt3Dist) + ")", cities, alt3));
        dataset.addSeries(buildSeries("GA Best (dist: " + String.format("%.1f", gaDist) + ")", cities, gaTour));

      
        double bestAlt = Math.min(alt1Dist, Math.min(alt2Dist, alt3Dist));
        double improvement = (bestAlt - gaDist) / bestAlt * 100;
        String title = String.format(
                    "GA vs Alternative Heuristics  |  GA is %.2f%% better than best alternative", improvement);

        JFreeChart chart = ChartFactory.createXYLineChart(
            title, "X", "Y", dataset, PlotOrientation.VERTICAL, true, false, false);

        XYPlot plot = chart.getXYPlot();
        plot.setBackgroundPaint(new Color(248, 248, 248));
        plot.setDomainGridlinePaint(new Color(200, 200, 200));
        plot.setRangeGridlinePaint(new Color(200, 200, 200));
        ((NumberAxis) plot.getDomainAxis()).setRange(-10, 115);
        ((NumberAxis) plot.getRangeAxis()).setRange(-10, 115);

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer(true, true);

       
        renderer.setSeriesPaint(0, COLOR_ALT1);
        renderer.setSeriesStroke(0, new BasicStroke(1.5f, BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_ROUND, 1f, new float[]{8f, 5f}, 0f));
        renderer.setSeriesShape(0, new java.awt.geom.Ellipse2D.Double(-3,-3,6,6));

      
        renderer.setSeriesPaint(1, COLOR_ALT2);
        renderer.setSeriesStroke(1, new BasicStroke(1.5f, BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_ROUND, 1f, new float[]{5f, 4f}, 0f));
        renderer.setSeriesShape(1, new java.awt.geom.Ellipse2D.Double(-3,-3,6,6));

       
        renderer.setSeriesPaint(2, COLOR_ALT3);
        renderer.setSeriesStroke(2, new BasicStroke(1.5f, BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_ROUND, 1f, new float[]{3f, 4f}, 0f));
        renderer.setSeriesShape(2, new java.awt.geom.Ellipse2D.Double(-3,-3,6,6));

       
        renderer.setSeriesPaint(3, COLOR_GA);
        renderer.setSeriesStroke(3, new BasicStroke(3.5f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        renderer.setSeriesShape(3, new java.awt.geom.Ellipse2D.Double(-6,-6,12,12));

        plot.setRenderer(renderer);

        HashSet<Integer> drawn = new HashSet<>();

        for (int i = 0; i < gaTour.size(); i++) {

                     int id = gaTour.get(i);

                     if (drawn.contains(id)) {
                            continue;
                        }

                     City c = findCity(cities, id);

                      if (c == null) {
                            continue;
                        }

    
    XYTextAnnotation ann = new XYTextAnnotation(
            String.valueOf(c.id),
            c.x + 1.5,
            c.y + 2.0
    );
    ann.setFont(new Font("SansSerif", Font.BOLD, 12));
    ann.setPaint(new Color(180, 0, 0));
    ann.setTextAnchor(TextAnchor.BOTTOM_LEFT);
    plot.addAnnotation(ann);

   
    XYTextAnnotation seq = new XYTextAnnotation(
            "GA:(" + (i + 1) + ")",
            c.x - 2,
            c.y - 3.0
    );
    seq.setFont(new Font("SansSerif", Font.PLAIN, 10));
    seq.setPaint(new Color(0, 130, 0));
    seq.setTextAnchor(TextAnchor.TOP_RIGHT);
    plot.addAnnotation(seq);

   
    if (i == 0) {
        XYTextAnnotation startLabel = new XYTextAnnotation(
                "START",
                c.x + 1.5,
                c.y + 7
        );
        startLabel.setFont(new Font("SansSerif", Font.BOLD, 12));
        startLabel.setPaint(new Color(0, 150, 0));
        startLabel.setTextAnchor(TextAnchor.BOTTOM_LEFT);
        plot.addAnnotation(startLabel);
    }

       drawn.add(id);
  }

        
        List<City[]> gaEdges = buildEdges(cities, gaTour);
        List<City[]> alt1Edges = buildEdges(cities, alt1);
        List<City[]> alt2Edges = buildEdges(cities, alt2);
        List<City[]> alt3Edges = buildEdges(cities, alt3);

       
        ChartPanel cp = new ChartPanel(chart, false) {

    @Override
    public void paintComponent(Graphics g) {

         super.paintComponent(g);

        Graphics2D g2 = (Graphics2D) g.create();
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);

        Rectangle2D area = getChartRenderingInfo().getPlotInfo().getDataArea();
        ValueAxis da = plot.getDomainAxis();
        ValueAxis ra = plot.getRangeAxis();

        Font font = new Font("SansSerif", Font.BOLD, 10);
        g2.setFont(font);
        FontMetrics fm = g2.getFontMetrics(font);

        
        for (City[] edge : gaEdges) {

              City a = edge[0], b = edge[1];

            double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
            double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
            double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
            double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

            double mx = (ax + bx) / 2.0;
            double my = (ay + by) / 2.0;

            double dist = Math.hypot(b.x - a.x, b.y - a.y);
            String label = String.format("%.1f", dist);

            int tw = fm.stringWidth(label);
            int th = fm.getAscent();
            int pad = 2;

            int bx2 = (int)(mx - tw/2.0 - pad);
            int by2 = (int)(my - th/2.0 - pad);

            g2.setColor(new Color(0,120,0,150));
            g2.drawLine((int)mx, (int)my, bx2, by2);

            g2.setColor(new Color(0,110,0));
            g2.fillRoundRect(bx2, by2, tw + pad*2, th + pad*2, 4, 4);

            g2.setColor(Color.WHITE);
            g2.drawString(label, bx2 + pad, by2 + th);

            drawArrow(g2, ax, ay, bx, by, COLOR_GA);
        }

        for (City[] edge : alt1Edges) {

              City a = edge[0], b = edge[1];

            double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
            double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
            double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
            double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

            drawArrow(g2, ax, ay, bx, by, COLOR_ALT1);
        }

        
        for (City[] edge : alt2Edges) {

              City a = edge[0], b = edge[1];

            double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
            double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
            double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
            double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

            drawArrow(g2, ax, ay, bx, by, COLOR_ALT2);
        }

        
        for (City[] edge : alt3Edges) {

               City a = edge[0], b = edge[1];

            double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
            double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
            double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
            double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

            drawArrow(g2, ax, ay, bx, by, COLOR_ALT3);
          }

           g2.dispose();
      }
  };
 


         cp.setMouseWheelEnabled(false); 
          cp.setDomainZoomable(false);
           cp.setRangeZoomable(false);

      
        JPanel info = new JPanel(new FlowLayout(FlowLayout.CENTER, 20, 6));
        info.setBackground(Color.WHITE);
        info.setBorder(new EmptyBorder(6,4,6,4));
        info.add(makeLabel(" GA Best  dist: " + String.format("%.2f", gaDist) + "  ★ BEST", COLOR_GA, true));
        info.add(makeLabel(" Alt 1 (NN)  dist: " + String.format("%.2f", alt1Dist), COLOR_ALT1, false));
        info.add(makeLabel(" Alt 2 (NN)  dist: " + String.format("%.2f", alt2Dist), COLOR_ALT2, false));
        info.add(makeLabel(" Alt 3 (NN)  dist: " + String.format("%.2f", alt3Dist), COLOR_ALT3, false));

        SwingUtilities.invokeLater(() -> {

            JFrame frame = new JFrame("GA TSP — GA vs Alternative Heuristics");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLayout(new BorderLayout());
            frame.add(cp, BorderLayout.CENTER);
            frame.add(info, BorderLayout.SOUTH);
            frame.setSize(1050, 950);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }

    static ArrayList<Integer> loadTourFromSummary(String f, boolean isCplex) {

        ArrayList<Integer> tour = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {

            String line; 
            boolean inSection = false;
            String marker;
           
            if (isCplex) {
                  marker = "CPLEX (optimal)";
             }
              else {

                    marker = "Genetic Algorithm Result";
               }

               while ((line = br.readLine()) != null){

                if (line.contains(marker)) {
                       inSection = true; 
                       continue;

                }
                if (inSection && line.trim().startsWith("Tour:")) {

                    String routePart = line.trim().substring(5).trim();

                    for (String t : routePart.split("->")) {

                        t = t.trim(); 

                        if (t.isEmpty()){ 
                               continue;
                        }
                        try { 
                              tour.add(Integer.parseInt(t));

                        } catch (NumberFormatException ignored) {}
                    }
                       break;
                }

                if (inSection && line.contains("Comparison")) 
                     break;
            }
         } 
           catch (IOException e) { 
            
                     System.out.println("Cannot read " + f);    
                 }

        if (!tour.isEmpty() && !tour.get(0).equals(tour.get(tour.size()-1))){
 
              tour.add(tour.get(0));
         }
              return tour;
        }

    static ArrayList<Integer> loadBestTourFromCSV(String f) {

        ArrayList<Integer> tour = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {

            String line;
            while ((line = br.readLine()) != null) {

                if (!line.contains("Final Best Tour")){

                        continue;
                }

                int idx = line.lastIndexOf("Tour:");

                if (idx < 0){

                     continue;
                }
                String part = line.substring(idx+5);
                int pipe = part.indexOf('|');

                 if (pipe >= 0) {
                        part = part.substring(0, pipe);
                 } 
                for (String t : part.split("->")) {
                     t = t.trim(); 

                     if (t.isEmpty()){ 
                           continue;
                     }

                    try { 
                           tour.add(Integer.parseInt(t)); 
                        
                    } catch (NumberFormatException ignored) {}
                }
                break;
            }
         } catch (IOException e) { 
            
                  System.out.println("Error: " + e.getMessage()); 
        
              }
        if (!tour.isEmpty() && !tour.get(0).equals(tour.get(tour.size()-1)))
              tour.add(tour.get(0));
               return tour;
    }

    static ArrayList<Integer> nearestNeighborTourFrom(ArrayList<City> cities, int startId) {

        ArrayList<Integer> tour = new ArrayList<>();
        HashSet<Integer> visited = new HashSet<>();
        City current = findCity(cities, startId);

        if (current == null){

              current = cities.get(0);
        }

        tour.add(current.id); visited.add(current.id);

        while (visited.size() < cities.size()) {

            City nearest = null; double minDist = Double.MAX_VALUE;

            for (City c : cities) {

                if (visited.contains(c.id)){ 
                      continue;
                }
                  double d = Math.hypot(c.x-current.x, c.y-current.y);

                if (d < minDist) { 
                       minDist=d; nearest=c; 
                }
             }
              if (nearest == null) {
                     break;
              }
                tour.add(nearest.id); 
                visited.add(nearest.id);
                current = nearest;
        }
             tour.add(tour.get(0));
             return tour;
    }

     static double tourDistance(ArrayList<City> cities, ArrayList<Integer> tour) {
            double total = 0;

        for (int i = 0; i < tour.size()-1; i++) {

            City a = findCity(cities, tour.get(i)), b = findCity(cities, tour.get(i+1));
            
            if (a != null && b != null) {
                
                    total += Math.hypot(b.x-a.x, b.y-a.y);
            }
        }
                return total;
    }

    static XYSeries buildSeries(String name, ArrayList<City> cities, ArrayList<Integer> tour) {

        XYSeries s = new XYSeries(name, false, true);
        for (int id : tour) { 
            
              City c = findCity(cities, id); 

            if (c != null){ 

                 s.add(c.x, c.y); 
             }
            
         }
          return s;
     }

    static List<City[]> buildEdges(ArrayList<City> cities, ArrayList<Integer> tour) {

        List<City[]> edges = new ArrayList<>();

        for (int i = 0; i < tour.size()-1; i++) {

                 City a = findCity(cities, tour.get(i)), b = findCity(cities, tour.get(i+1));
                 if (a != null && b != null) {
                 
                      edges.add(new City[]{a,b});
                  }
            }
                 return edges;
      }

     static City findCity(ArrayList<City> cities, int id) {

           for (City c : cities) 
               if (c.id == id) {
            
                  return c; 
        }
                 return null;
    }

    static void drawArrow(Graphics2D g2,
                      double ax, double ay,
                      double bx, double by,
                      Color color) {

    double dx = bx - ax;
    double dy = by - ay;
    double len = Math.sqrt(dx * dx + dy * dy);

    if (len < 5) {
          return;
    }

    dx /= len;
    dy /= len;

    double arrowPos = 0.65;
    double arrowX = ax + dx * len * arrowPos;
    double arrowY = ay + dy * len * arrowPos;

    double arrowSize = 10;

    double perpX = -dy;
    double perpY = dx;

    int[] xPoints = {
            (int) (arrowX + dx * arrowSize),
            (int) (arrowX + perpX * arrowSize * 0.5),
            (int) (arrowX - perpX * arrowSize * 0.5)
    };

    int[] yPoints = {
            (int) (arrowY + dy * arrowSize),
            (int) (arrowY + perpY * arrowSize * 0.5),
            (int) (arrowY - perpY * arrowSize * 0.5)
       };

        g2.setColor(color);
        g2.fillPolygon(xPoints, yPoints, 3);
     }

    static JLabel makeLabel(String text, Color color, boolean bold) {
          JLabel l = new JLabel(text);
          l.setForeground(color);
          l.setFont(new Font("SansSerif", bold ? Font.BOLD : Font.PLAIN, 13));
          return l;
    }

     static ArrayList<City> loadCities(String f) {

        ArrayList<City> cities = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {

            String line;
            while ((line = br.readLine()) != null) {

                line = line.trim();
                 if (line.isEmpty()) {
                       continue;
               }
                String[] p = line.split("\\s+");
                if (p.length < 3) {
                       continue;
            }
                try {
                      cities.add(new City(Integer.parseInt(p[0]),
                      Double.parseDouble(p[1]), Double.parseDouble(p[2]))); 
                }
                  catch (NumberFormatException ignored) {}
            }
        }      catch (IOException e) {
             
                   System.err.println("Error: " + e.getMessage()); 
                
              }
                return cities;
     }
  }
  