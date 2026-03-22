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
    public City(int id, double x, double y){ this.id=id; this.x=x; this.y=y; }
}

public class GAPlotCompare {

    // tour colors
    static final Color COLOR_BEST  = new Color(0, 160, 0);       // সবুজ — GA best
    static final Color COLOR_ALT1  = new Color(220, 120, 0);      // কমলা — alternative 1
    static final Color COLOR_ALT2  = new Color(160, 0, 180);      // বেগুনি — alternative 2

    public static void main(String[] args) {
        ArrayList<City> cities = loadCities("cities.txt");
        ArrayList<Integer> bestTour = loadBestTour("results/ga_results.csv");
        System.out.println("Loaded "+cities.size()+" cities, tour "+bestTour.size()+" points");
        if(cities.isEmpty()||bestTour.isEmpty()){ System.err.println("Data missing!"); return; }

        // ── Alternative tours তৈরি ──────────────────────────────────
        // Alt 1: Nearest Neighbor greedy tour
        ArrayList<Integer> alt1 = nearestNeighborTour(cities);

        // Alt 2: Nearest Neighbor কিন্তু ভিন্ন starting city থেকে
        ArrayList<Integer> alt2 = nearestNeighborTourFrom(cities,
                cities.get(cities.size()/2).id);

        double bestDist = tourDistance(cities, bestTour);
        double alt1Dist = tourDistance(cities, alt1);
        double alt2Dist = tourDistance(cities, alt2);

        System.out.printf("GA Best   : %.2f%n", bestDist);
        System.out.printf("Alt 1 (NN): %.2f%n", alt1Dist);
        System.out.printf("Alt 2 (NN): %.2f%n", alt2Dist);

        // ── Dataset ─────────────────────────────────────────────────
        XYSeriesCollection dataset = new XYSeriesCollection();

        // Alt tours আগে add করো (পেছনে থাকবে)
        dataset.addSeries(buildSeries("Alt Route 1 (dist: "+String.format("%.1f",alt1Dist)+")", cities, alt1));
        dataset.addSeries(buildSeries("Alt Route 2 (dist: "+String.format("%.1f",alt2Dist)+")", cities, alt2));
        // Best tour সবার উপরে
        dataset.addSeries(buildSeries("GA Best (dist: "+String.format("%.1f",bestDist)+")", cities, bestTour));

        // ── Chart ───────────────────────────────────────────────────
        JFreeChart chart = ChartFactory.createXYLineChart(
            "TSP Tour Comparison — GA Best vs Alternatives",
            "X", "Y", dataset, PlotOrientation.VERTICAL, true, false, false);

        XYPlot plot = chart.getXYPlot();
        plot.setBackgroundPaint(new Color(248, 248, 248));
        plot.setDomainGridlinePaint(new Color(200,200,200));
        plot.setRangeGridlinePaint(new Color(200,200,200));
        ((NumberAxis)plot.getDomainAxis()).setRange(-5, 110);
        ((NumberAxis)plot.getRangeAxis()).setRange(-10, 110);

        // ── Renderer ────────────────────────────────────────────────
        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer(true, true);

        // Alt 1 — কমলা, dashed, পাতলা
        renderer.setSeriesPaint(0, COLOR_ALT1);
        renderer.setSeriesStroke(0, new BasicStroke(1.5f, BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_ROUND, 1f, new float[]{6f,4f}, 0f));
        renderer.setSeriesShapesVisible(0, true);
        renderer.setSeriesShape(0, new java.awt.geom.Ellipse2D.Double(-3,-3,6,6));

        // Alt 2 — বেগুনি, dashed, পাতলা
        renderer.setSeriesPaint(1, COLOR_ALT2);
        renderer.setSeriesStroke(1, new BasicStroke(1.5f, BasicStroke.CAP_ROUND,
            BasicStroke.JOIN_ROUND, 1f, new float[]{4f,4f}, 0f));
        renderer.setSeriesShapesVisible(1, true);
        renderer.setSeriesShape(1, new java.awt.geom.Ellipse2D.Double(-3,-3,6,6));

        // Best — সবুজ, solid, মোটা
        renderer.setSeriesPaint(2, COLOR_BEST);
        renderer.setSeriesStroke(2, new BasicStroke(3.0f));
        renderer.setSeriesShapesVisible(2, true);
        renderer.setSeriesShape(2, new java.awt.geom.Ellipse2D.Double(-5,-5,10,10));

        plot.setRenderer(renderer);

        // ── City ID labels (best tour এর জন্য) ──────────────────────
        HashSet<Integer> drawn = new HashSet<>();
        for(int id : bestTour){
            if(drawn.contains(id)) continue;
            City c = findCity(cities, id); if(c==null) continue;
            XYTextAnnotation ann = new XYTextAnnotation(String.valueOf(c.id), c.x+1.5, c.y+2.0);
            ann.setFont(new Font("SansSerif", Font.BOLD, 11));
            ann.setPaint(new Color(180,0,0));
            ann.setTextAnchor(TextAnchor.BOTTOM_LEFT);
            plot.addAnnotation(ann);
            drawn.add(id);
        }

        // ── ChartPanel — edge weight labels for best tour only ──────
        List<City[]> bestEdges = buildEdges(cities, bestTour);

        ChartPanel cp = new ChartPanel(chart, false){
            @Override public void paintComponent(Graphics g){
                super.paintComponent(g);
                Graphics2D g2 = (Graphics2D)g.create();
                g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
                    RenderingHints.VALUE_ANTIALIAS_ON);

                Rectangle2D area = getChartRenderingInfo().getPlotInfo().getDataArea();
                ValueAxis da = plot.getDomainAxis(), ra = plot.getRangeAxis();
                Font font = new Font("SansSerif", Font.BOLD, 10);
                g2.setFont(font);
                FontMetrics fm = g2.getFontMetrics(font);

                for(City[] edge : bestEdges){
                    City a=edge[0], b=edge[1];
                    double ax=da.valueToJava2D(a.x,area,plot.getDomainAxisEdge());
                    double ay=ra.valueToJava2D(a.y,area,plot.getRangeAxisEdge());
                    double bx=da.valueToJava2D(b.x,area,plot.getDomainAxisEdge());
                    double by_=ra.valueToJava2D(b.y,area,plot.getRangeAxisEdge());
                    double mx=(ax+bx)/2.0, my=(ay+by_)/2.0;
                    double dx=bx-ax, dy=by_-ay;
                    double edgeAngle=Math.abs(dy/(Math.abs(dx)+0.001));
                    double lx, ly;
                    if(edgeAngle > 1.5){ lx=mx+18; ly=my; }
                    else { lx=mx; ly=my-13; }

                    double dist=Math.sqrt(Math.pow(b.x-a.x,2)+Math.pow(b.y-a.y,2));
                    String label=String.format("%.1f",dist);
                    int tw=fm.stringWidth(label), th=fm.getAscent(), pad=2;
                    int bx2=(int)(lx-tw/2.0-pad), by2=(int)(ly-th/2.0-pad);
                    int bw=tw+pad*2, bh=th+pad*2;

                    g2.setColor(new Color(0,120,0,160));
                    g2.setStroke(new BasicStroke(1f,BasicStroke.CAP_ROUND,
                        BasicStroke.JOIN_ROUND,1f,new float[]{2f,2f},0f));
                    g2.drawLine((int)mx,(int)my,(int)lx,(int)ly);
                    g2.setStroke(new BasicStroke(1f));
                    g2.setColor(new Color(0,120,0));
                    g2.fillRoundRect(bx2,by2,bw,bh,4,4);
                    g2.setColor(Color.WHITE);
                    g2.drawString(label,bx2+pad,by2+th+pad/2);
                }
                g2.dispose();
            }
        };
        cp.setMouseWheelEnabled(false);
        cp.setDomainZoomable(false);
        cp.setRangeZoomable(false);

        // ── Info panel নিচে ─────────────────────────────────────────
        JPanel info = new JPanel(new FlowLayout(FlowLayout.CENTER, 30, 5));
        info.setBackground(Color.WHITE);
        info.setBorder(new EmptyBorder(4,4,4,4));

        info.add(makeLabel("■ GA Best Tour  dist: "+String.format("%.2f",bestDist), COLOR_BEST, true));
        info.add(makeLabel("- - Alt Route 1  dist: "+String.format("%.2f",alt1Dist), COLOR_ALT1, false));
        info.add(makeLabel("- - Alt Route 2  dist: "+String.format("%.2f",alt2Dist), COLOR_ALT2, false));

        SwingUtilities.invokeLater(()->{
            JFrame frame = new JFrame("GA TSP - Best vs Alternative Tours");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setLayout(new BorderLayout());
            frame.add(cp, BorderLayout.CENTER);
            frame.add(info, BorderLayout.SOUTH);
            frame.setSize(980, 950);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }

    static JLabel makeLabel(String text, Color color, boolean bold){
        JLabel l = new JLabel(text);
        l.setForeground(color);
        l.setFont(new Font("SansSerif", bold ? Font.BOLD : Font.PLAIN, 13));
        return l;
    }

    static XYSeries buildSeries(String name, ArrayList<City> cities, ArrayList<Integer> tour){
        XYSeries s = new XYSeries(name);
        for(int id : tour){ City c=findCity(cities,id); if(c!=null) s.add(c.x,c.y); }
        return s;
    }

    static List<City[]> buildEdges(ArrayList<City> cities, ArrayList<Integer> tour){
        List<City[]> edges = new ArrayList<>();
        for(int i=0;i<tour.size()-1;i++){
            City a=findCity(cities,tour.get(i));
            City b=findCity(cities,tour.get(i+1));
            if(a!=null&&b!=null) edges.add(new City[]{a,b});
        }
        return edges;
    }

    // Nearest Neighbor tour from city index 0
    static ArrayList<Integer> nearestNeighborTour(ArrayList<City> cities){
        return nearestNeighborTourFrom(cities, cities.get(0).id);
    }

    // Nearest Neighbor tour from specific start city
    static ArrayList<Integer> nearestNeighborTourFrom(ArrayList<City> cities, int startId){
        ArrayList<Integer> tour = new ArrayList<>();
        HashSet<Integer> visited = new HashSet<>();
        City current = findCity(cities, startId);
        if(current == null) current = cities.get(0);
        tour.add(current.id);
        visited.add(current.id);
        while(visited.size() < cities.size()){
            City nearest = null;
            double minDist = Double.MAX_VALUE;
            for(City c : cities){
                if(visited.contains(c.id)) continue;
                double d = Math.sqrt(Math.pow(c.x-current.x,2)+Math.pow(c.y-current.y,2));
                if(d < minDist){ minDist=d; nearest=c; }
            }
            if(nearest==null) break;
            tour.add(nearest.id);
            visited.add(nearest.id);
            current = nearest;
        }
        tour.add(tour.get(0)); // loop close
        return tour;
    }

    static double tourDistance(ArrayList<City> cities, ArrayList<Integer> tour){
        double total=0;
        for(int i=0;i<tour.size()-1;i++){
            City a=findCity(cities,tour.get(i));
            City b=findCity(cities,tour.get(i+1));
            if(a!=null&&b!=null)
                total+=Math.sqrt(Math.pow(b.x-a.x,2)+Math.pow(b.y-a.y,2));
        }
        return total;
    }

    static City findCity(ArrayList<City> cities, int id){
        for(City c:cities) if(c.id==id) return c; return null;
    }

    static ArrayList<City> loadCities(String f){
        ArrayList<City> cities=new ArrayList<>();
        try(BufferedReader br=new BufferedReader(new FileReader(f))){
            String line; boolean first=true;
            while((line=br.readLine())!=null){
                line=line.trim(); if(line.isEmpty()) continue;
                if(first){first=false;continue;}
                String[] p=line.split("\\s+"); if(p.length<3) continue;
                try{ cities.add(new City(Integer.parseInt(p[0]),
                    Double.parseDouble(p[1]),Double.parseDouble(p[2]))); }
                catch(NumberFormatException e){}
            }
        }catch(IOException e){ System.err.println("Error: "+e.getMessage()); }
        return cities;
    }

    static ArrayList<Integer> loadBestTour(String f){
        ArrayList<Integer> tour=new ArrayList<>();
        try(BufferedReader br=new BufferedReader(new FileReader(f))){
            String line;
            while((line=br.readLine())!=null){
                if(!line.startsWith("Final Best Tour")) continue;
                int t1=line.indexOf("Tour:"),t2=line.indexOf("Tour:",t1+5),pipe=line.indexOf("|");
                if(t2>=0&&pipe>t2){
                    for(String c:line.substring(t2+5,pipe).trim().split("->")){
                        c=c.trim(); if(c.isEmpty()) continue;
                        try{ tour.add(Integer.parseInt(c)); }catch(NumberFormatException e){}
                    }
                    if(!tour.isEmpty()&&!tour.get(0).equals(tour.get(tour.size()-1)))
                        tour.add(tour.get(0));
                    break;
                }
            }
        }catch(IOException e){ System.err.println("Error: "+e.getMessage()); }
        if(tour.isEmpty()) System.err.println("No tour found in "+f);
        return tour;
    }
}