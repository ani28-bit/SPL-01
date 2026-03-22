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
        System.out.println("Loaded "+cities.size()+" cities, tour "+bestTour.size()+" points");
        if(cities.isEmpty()||bestTour.isEmpty()){ System.err.println("Data missing!"); return; }

        List<City[]> edges = new ArrayList<>();
        for(int i=0;i<bestTour.size()-1;i++){
            City a=findCity(cities,bestTour.get(i));
            City b=findCity(cities,bestTour.get(i+1));
            if(a!=null&&b!=null) edges.add(new City[]{a,b});
        }

        XYSeries s = new XYSeries("Tour");
        for(int id:bestTour){ City c=findCity(cities,id); if(c!=null) s.add(c.x,c.y); }
        XYSeriesCollection ds = new XYSeriesCollection(); ds.addSeries(s);

        JFreeChart chart = ChartFactory.createXYLineChart(
            "Best GA Tour ("+cities.size()+" cities)","X","Y",
            ds,PlotOrientation.VERTICAL,false,false,false);

        XYPlot plot = chart.getXYPlot();
        plot.setBackgroundPaint(new Color(245,245,245));
        ((NumberAxis)plot.getDomainAxis()).setRange(-5,110);
        ((NumberAxis)plot.getRangeAxis()).setRange(-10,110);

        XYLineAndShapeRenderer r = new XYLineAndShapeRenderer(true,true);
        r.setSeriesPaint(0,new Color(0,150,0));
        r.setSeriesStroke(0,new BasicStroke(2.0f));
        r.setSeriesShapesVisible(0,true);
        r.setSeriesShape(0,new java.awt.geom.Ellipse2D.Double(-5,-5,10,10));
        plot.setRenderer(r);

        HashSet<Integer> drawn = new HashSet<>();
        for(int id:bestTour){
            if(drawn.contains(id)) continue;
            City c=findCity(cities,id); if(c==null) continue;
            XYTextAnnotation ann=new XYTextAnnotation(String.valueOf(c.id),c.x+1.5,c.y+2.0);
            ann.setFont(new Font("SansSerif",Font.BOLD,12));
            ann.setPaint(Color.RED);
            ann.setTextAnchor(TextAnchor.BOTTOM_LEFT);
            plot.addAnnotation(ann); drawn.add(id);
        }

        ChartPanel cp = new ChartPanel(chart,false){
            @Override public void paintComponent(Graphics g){
                super.paintComponent(g);
                Graphics2D g2=(Graphics2D)g.create();
                g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);

                Rectangle2D area=getChartRenderingInfo().getPlotInfo().getDataArea();
                ValueAxis da=plot.getDomainAxis(), ra=plot.getRangeAxis();
                Font font=new Font("SansSerif",Font.BOLD,11);
                g2.setFont(font);
                FontMetrics fm=g2.getFontMetrics(font);

                for(City[] edge:edges){
                    City a=edge[0], b=edge[1];

                    // data → pixel
                    double ax=da.valueToJava2D(a.x,area,plot.getDomainAxisEdge());
                    double ay=ra.valueToJava2D(a.y,area,plot.getRangeAxisEdge());
                    double bx=da.valueToJava2D(b.x,area,plot.getDomainAxisEdge());
                    double by=ra.valueToJava2D(b.y,area,plot.getRangeAxisEdge());

                    // pixel midpoint
                    double mx=(ax+bx)/2.0, my=(ay+by)/2.0;

                    // pixel space edge vector
                    double dx=bx-ax, dy=by-ay;

                    // edge কতটা vertical সেটা বুঝে label position ঠিক করো
                    double edgeAngle=Math.abs(dy/(Math.abs(dx)+0.001));
                    double lx, ly;
                    if(edgeAngle > 1.5){
                        // vertical edge → ডানে 18px
                        lx=mx+18; ly=my;
                    } else {
                        // horizontal/diagonal → উপরে 14px
                        lx=mx; ly=my-14;
                    }

                    double dist=Math.sqrt(Math.pow(b.x-a.x,2)+Math.pow(b.y-a.y,2));
                    String label=String.format("%.1f",dist);
                    int tw=fm.stringWidth(label), th=fm.getAscent(), pad=3;
                    int bx2=(int)(lx-tw/2.0-pad), by2=(int)(ly-th/2.0-pad);
                    int bw=tw+pad*2, bh=th+pad*2;

                    // dashed leader line
                    g2.setColor(new Color(0,80,180,150));
                    g2.setStroke(new BasicStroke(1.0f,BasicStroke.CAP_ROUND,
                        BasicStroke.JOIN_ROUND,1f,new float[]{3f,2f},0f));
                    g2.drawLine((int)mx,(int)my,(int)lx,(int)ly);

                    // নীল box
                    g2.setStroke(new BasicStroke(1.0f));
                    g2.setColor(new Color(30,100,200));
                    g2.fillRoundRect(bx2,by2,bw,bh,5,5);

                    // সাদা text
                    g2.setColor(Color.WHITE);
                    g2.drawString(label,bx2+pad,by2+th+pad/2);
                }
                g2.dispose();
            }
        };

        cp.setMouseWheelEnabled(false);
        cp.setDomainZoomable(false);
        cp.setRangeZoomable(false);

        SwingUtilities.invokeLater(()->{
            JFrame frame=new JFrame("GA TSP - Best Tour");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.add(cp);
            frame.setSize(900,900);
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }

    static City findCity(ArrayList<City> cities,int id){
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