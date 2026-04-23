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

    public double x, y;
    public int id;

    public City(int id, double x, double y) {

        this.id = id;
        this.x = x;
        this.y = y;
    }
}

public class GAPlotGAvsCPLEX {


    static final Color COLOR_GA = new Color(0, 160, 0);
    static final Color COLOR_CPLEX = new Color(0, 80, 200);

    public static void main(String[] args) {

        ArrayList<City> cities = loadCities("cities.txt");
        System.out.println("Loaded " + cities.size() + " cities");

        ArrayList<Integer> gaTour = loadTourFromSummary("CPLEX/Summary.txt", false);
        ArrayList<Integer> cplexTour = loadTourFromSummary("CPLEX/Summary.txt", true);

        if (gaTour.isEmpty()) {

                gaTour = loadBestTourFromCSV("results/ga_results.csv");
        }

        if (cplexTour.isEmpty()) {

                System.out.println("CPLEX tour missing! Using empty tour.");
                cplexTour = new ArrayList<>();
         }
       
        double gaDist = tourDistance(cities, gaTour);
        double cplexDist = tourDistance(cities, cplexTour);
        double gap = Math.abs(gaDist - cplexDist) / cplexDist * 100;
        boolean optimal = gap < 0.01;

        System.out.printf("GA    : %.2f%n", gaDist);
        System.out.printf("CPLEX : %.2f%n", cplexDist);
        System.out.printf("Gap   : %.2f%%%n", gap);

        
        XYSeriesCollection dataset = new XYSeriesCollection();
        dataset.addSeries(buildSeries("CPLEX Optimal (dist: " + String.format("%.2f", cplexDist) + ")", cities, cplexTour));
        dataset.addSeries(buildSeries("GA Best (dist: " + String.format("%.2f", gaDist) + ")", cities, gaTour));

        String title;

          if (optimal) {

                  title = "GA vs CPLEX  |  GA found OPTIMAL solution!  Gap: 0.00%";
           } 
           else {

                  title = String.format("GA vs CPLEX  |  Optimality Gap: %.2f%%  (CPLEX optimal)", gap);
             }
               
        JFreeChart chart = ChartFactory.createXYLineChart(
                           title, "X", "Y", dataset, PlotOrientation.VERTICAL, true, false, false);

        XYPlot plot = chart.getXYPlot();
        plot.setBackgroundPaint(new Color(245, 248, 245));
        plot.setDomainGridlinePaint(new Color(200, 200, 200));
        plot.setRangeGridlinePaint(new Color(200, 200, 200));
        ((NumberAxis) plot.getDomainAxis()).setRange(-10, 115);
        ((NumberAxis) plot.getRangeAxis()).setRange(-10, 115);

        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer(true, true);

       
        renderer.setSeriesPaint(0, COLOR_CPLEX);
        renderer.setSeriesStroke(0, new BasicStroke(2.0f, BasicStroke.CAP_ROUND,
                 BasicStroke.JOIN_ROUND, 1f, new float[]{8f, 5f}, 0f));
        renderer.setSeriesShape(0, new java.awt.geom.Ellipse2D.Double(-5, -5, 10, 10));

        renderer.setSeriesPaint(1, COLOR_GA);
        renderer.setSeriesStroke(1, new BasicStroke(3.0f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND));
        renderer.setSeriesShape(1, new java.awt.geom.Ellipse2D.Double(-6, -6, 12, 12));

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

            
            XYTextAnnotation cityIdAnn = new XYTextAnnotation(String.valueOf(c.id), c.x + 1.5, c.y + 3.5);
            cityIdAnn.setFont(new Font("SansSerif", Font.BOLD, 13));
            cityIdAnn.setPaint(new Color(200, 0, 0));
            cityIdAnn.setTextAnchor(TextAnchor.BOTTOM_LEFT);
            plot.addAnnotation(cityIdAnn);

            XYTextAnnotation gaSeqAnn = new XYTextAnnotation("GA:(" + (i + 1) + ")", c.x - 2, c.y - 3.5);
            gaSeqAnn.setFont(new Font("SansSerif", Font.PLAIN, 10));
            gaSeqAnn.setPaint(new Color(0, 130, 0));
            gaSeqAnn.setTextAnchor(TextAnchor.TOP_RIGHT);
            plot.addAnnotation(gaSeqAnn);

           

            int cplexOrder = -1;
            for (int j = 0; j < cplexTour.size(); j++) {
              if (cplexTour.get(j) == id) {
                         cplexOrder = j + 1;
                         break;
                     }
                }
            if (cplexOrder > 0) {
                XYTextAnnotation cplexSeqAnn = new XYTextAnnotation("CPX:(" + cplexOrder + ")", c.x - 2, c.y - 6.5);
                cplexSeqAnn.setFont(new Font("SansSerif", Font.PLAIN, 10));
                cplexSeqAnn.setPaint(new Color(0, 70, 180));
                cplexSeqAnn.setTextAnchor(TextAnchor.TOP_RIGHT);
                plot.addAnnotation(cplexSeqAnn);
            }

          
            if (i == 0) {
                XYTextAnnotation startLabel = new XYTextAnnotation("START", c.x + 1.5, c.y + 7);
                startLabel.setFont(new Font("SansSerif", Font.BOLD, 12));
                startLabel.setPaint(new Color(0, 150, 0));
                startLabel.setTextAnchor(TextAnchor.BOTTOM_LEFT);
                plot.addAnnotation(startLabel);
            }

            if (!cplexTour.isEmpty() && id == cplexTour.get(0)) {

                    XYTextAnnotation cplexStart = new XYTextAnnotation(
                             "CPLEX START", c.x + 1.5, c.y + 10
                            );
     cplexStart.setFont(new Font("SansSerif", Font.BOLD, 12));
     cplexStart.setPaint(new Color(0, 70, 180));
     cplexStart.setTextAnchor(TextAnchor.BOTTOM_LEFT);
     plot.addAnnotation(cplexStart);
  }


            drawn.add(id);
        }

        
        List<City[]> gaEdges = buildEdges(cities, gaTour);
        List<City[]> cplexEdges = buildEdges(cities, cplexTour);

        ChartPanel cp = new ChartPanel(chart, false) {
            @Override
            public void paintComponent(Graphics g) {

                super.paintComponent(g);
                Graphics2D g2 = (Graphics2D) g.create();
                g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
                Rectangle2D area = getChartRenderingInfo().getPlotInfo().getDataArea();
                ValueAxis da = plot.getDomainAxis(), ra = plot.getRangeAxis();
                Font font = new Font("SansSerif", Font.BOLD, 10);
                g2.setFont(font);
                FontMetrics fm = g2.getFontMetrics(font);

               
                for (City[] edge : gaEdges) {

                    City a = edge[0], b = edge[1];
                    double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
                    double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
                    double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
                    double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());
                    double mx = (ax + bx) / 2.0, my = (ay + by) / 2.0;
                    double edgeAngle = Math.abs((by - ay) / (Math.abs(bx - ax) + 0.001));
                    double lx,ly;
                   

                      if (edgeAngle > 1.5) {
                               lx = mx + 20;
                                 ly = my;

                           } 
                           else {
                                    lx = mx;
                                    ly = my - 14;
                                 }
                    double dist = Math.hypot(b.x - a.x, b.y - a.y);

                    
                    String label = String.format("%.1f", dist);
                    int tw = fm.stringWidth(label), th = fm.getAscent(), pad = 2;
                    int bx2 = (int) (lx - tw / 2.0 - pad), by2 = (int) (ly - th / 2.0 - pad);

                    g2.setColor(new Color(0, 100, 0, 150));
                    g2.setStroke(new BasicStroke(1f, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND, 1f, new float[]{2f, 2f}, 0f));
                    g2.drawLine((int) mx, (int) my, (int) lx, (int) ly);
                    g2.setStroke(new BasicStroke(1f));
                    g2.setColor(new Color(0, 110, 0));
                    g2.fillRoundRect(bx2, by2, tw + pad * 2, th + pad * 2, 4, 4);
                    g2.setColor(Color.WHITE);
                    g2.drawString(label, bx2 + pad, by2 + th + pad / 2);

                   
                    drawArrow(g2, ax, ay, bx, by, COLOR_GA);
                 }

               
                for (City[] edge : cplexEdges) {
                    City a = edge[0], b = edge[1];
                    double ax = da.valueToJava2D(a.x, area, plot.getDomainAxisEdge());
                    double ay = ra.valueToJava2D(a.y, area, plot.getRangeAxisEdge());
                    double bx = da.valueToJava2D(b.x, area, plot.getDomainAxisEdge());
                    double by = ra.valueToJava2D(b.y, area, plot.getRangeAxisEdge());

                    drawArrow(g2, ax, ay, bx, by, COLOR_CPLEX);
                }

                g2.dispose();
            }
        };
        cp.setMouseWheelEnabled(false);
        cp.setDomainZoomable(false);
        cp.setRangeZoomable(false);

        JPanel info = new JPanel(new FlowLayout(FlowLayout.CENTER, 30, 6));
        info.setBackground(Color.WHITE);
        info.setBorder(new EmptyBorder(6, 4, 6, 4));

        String gaTag; 

        if (optimal) {
                gaTag = "  ★ OPTIMAL";

             }
         else {
                gaTag = String.format("  [Gap: %.2f%%]", gap);

              }

        info.add(makeLabel(" GA Best   dist: " + String.format("%.2f", gaDist) + gaTag, COLOR_GA, true));
        info.add(makeLabel("CPLEX Optimal   dist: " + String.format("%.2f", cplexDist) + "  ★ OPTIMAL", COLOR_CPLEX, false));

        String speedInfo = readSpeedRatio("CPLEX/Summary.txt");

        if (!speedInfo.isEmpty()) {
                info.add(makeLabel(speedInfo, new Color(80, 80, 80), false));
        }

        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("GA TSP — GA vs CPLEX (Enhanced)");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLayout(new BorderLayout());
            frame.add(cp, BorderLayout.CENTER);
            frame.add(info, BorderLayout.SOUTH);
            frame.setSize(1100, 1000);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }

    static void drawArrow(Graphics2D g2, double ax, double ay, double bx, double by, Color color) {
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

        double arrowSize;


                 if (color.equals(COLOR_GA)) {

                        arrowSize = 10;
                  } 
                  else {
                         arrowSize = 7;
                      }

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

    static String readSpeedRatio(String f) {

        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            String line;
            while ((line = br.readLine()) != null) {

                if (line.contains("Speed Ratio")) {
                        return "~" + line.trim();
                }
            }
        } 
           catch (IOException ignored) {}
             return "";
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
            while ((line = br.readLine()) != null) {
                if (line.contains(marker)) {
                     inSection = true;
                     continue;
                }
                if (inSection && line.trim().startsWith("Tour:")) {

                    String routePart = line.trim().substring(5).trim();
                    for (String t : routePart.split("->")) {
                        t = t.trim();

                        if (t.isEmpty()) {
                             continue;
                        }
                        try {
                              tour.add(Integer.parseInt(t));
                        }
                         catch (NumberFormatException ignored) {}
                    }
                         break;
                }
                if (inSection && line.contains("Comparison")) {
                     break;
                }
            }
        } catch (IOException e) {
            System.out.println("Cannot read " + f);
        }
        if (!tour.isEmpty() && !tour.get(0).equals(tour.get(tour.size() - 1))){
               tour.add(tour.get(0));
       }


    if (tour.size() < 2) {
            System.out.println(" Tour parsing failed from " + f);
    }
        return tour;
    }

    static ArrayList<Integer> loadBestTourFromCSV(String f) {
        ArrayList<Integer> tour = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new FileReader(f))) {
            String line;

            while ((line = br.readLine()) != null) {

                if (!line.contains("Final Best Tour")) {
                      continue;
                }
                int idx = line.lastIndexOf("Tour:");

                if (idx < 0) {
                      continue;
                }
                String part = line.substring(idx + 5);
                int pipe = part.indexOf('|');
                if (pipe >= 0) {
                       part = part.substring(0, pipe);
                }
                for (String t : part.split("->")) {
                    t = t.trim();

                    if (t.isEmpty()) {
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
        if (!tour.isEmpty() && !tour.get(0).equals(tour.get(tour.size() - 1))) {
              tour.add(tour.get(0));
        }
        return tour;
    }

    static double tourDistance(ArrayList<City> cities, ArrayList<Integer> tour) {
        double total = 0;
        for (int i = 0; i < tour.size() - 1; i++) {

            City a = findCity(cities, tour.get(i)), b = findCity(cities, tour.get(i + 1));
            if (a != null && b != null) {
                total += Math.hypot(b.x - a.x, b.y - a.y);
            }
        }
         return total;
    }

    static XYSeries buildSeries(String name, ArrayList<City> cities, ArrayList<Integer> tour) {
        XYSeries s = new XYSeries(name, false, true);
        for (int id : tour) {
            City c = findCity(cities, id);

            if (c != null) {
                s.add(c.x, c.y);
            }
        }
              return s;
    }

    static List<City[]> buildEdges(ArrayList<City> cities, ArrayList<Integer> tour) {
        List<City[]> edges = new ArrayList<>();

        for (int i = 0; i < tour.size() - 1; i++) {
            City a = findCity(cities, tour.get(i)), b = findCity(cities, tour.get(i + 1));

            if (a != null && b != null) {

                    edges.add(new City[]{a, b});
            }
        }
                    return edges;
    }

    static City findCity(ArrayList<City> cities, int id) {
        for (City c : cities){
               if (c.id == id) {
                      return c;
                 }
             }
                   return null;
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
                } catch (NumberFormatException ignored) {}
            }
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
        return cities;
    }
}