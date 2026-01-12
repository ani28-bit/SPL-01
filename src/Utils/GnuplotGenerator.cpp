#include "GnuplotGenerator.h"
#include <fstream>
#include <iostream>
#include <cstdlib>

bool GnuplotGenerator::executeGnuplot(const std::string& scriptFile) {
    std::string command = "gnuplot " + scriptFile + " 2>&1";
    int result = system(command.c_str());
    if (result != 0) {
        std::cerr << "Warning: gnuplot execution failed or not installed\n";
        std::cerr << "Install gnuplot: sudo apt-get install gnuplot\n";
        return false;
    }
    return true;
}

// -------------------- Evolution Graphs --------------------

void GnuplotGenerator::generateGraph(const Logger& logger,
                                     const std::string& dataFile,
                                     const std::string& outputImage) {

    const auto& data = logger.getData();
    if (data.empty()) return;

    std::ofstream script("results/graph_data/plot_script.gnu");
    if (!script.is_open()) return;

    double initialBest = data.front().bestDistance;
    double finalBest = data.back().bestDistance;
    double improvement = ((initialBest - finalBest) / initialBest) * 100.0;

    script << "set terminal pngcairo enhanced font 'Arial,12' size 1200,800\n";
    script << "set output '" << outputImage << "'\n";
    script << "set title 'TSP Genetic Algorithm Evolution' font 'Arial,16'\n";
    script << "set xlabel 'Generation'\nset ylabel 'Distance'\n";
    script << "set grid\nset key left top box\n";
    script << "set style line 1 lc rgb '#2ecc71' lt 1 lw 3 pt 7 ps 0.5\n";
    script << "set style line 2 lc rgb '#3498db' lt 1 lw 2 pt 5 ps 0.5\n";
    script << "set style line 3 lc rgb '#e74c3c' lt 1 lw 2 pt 9 ps 0.5\n";
    script << "set label 1 sprintf('Improvement: %.1f%%', " << improvement << ") at graph 0.65,0.95\n";
    script << "set label 2 sprintf('Initial: %.2f', " << initialBest << ") at graph 0.65,0.90\n";
    script << "set label 3 sprintf('Final: %.2f', " << finalBest << ") at graph 0.65,0.85\n";

    script << "plot '" << dataFile << "' using 1:2 every ::1 with linespoints ls 1 title 'Best Distance', \\\n";
    script << "     '' using 1:3 every ::1 with linespoints ls 2 title 'Average Distance', \\\n";
    script << "     '' using 1:4 every ::1 with linespoints ls 3 title 'Worst Distance'\n";

    script.close();
    executeGnuplot("results/graph_data/plot_script.gnu");
}

void GnuplotGenerator::generateBestGraph(const Logger& logger,
                                         const std::string& dataFile,
                                         const std::string& outputImage) {

    const auto& data = logger.getData();
    if (data.empty()) return;

    std::ofstream script("results/graph_data/plot_best.gnu");
    if (!script.is_open()) return;

    double initialBest = data.front().bestDistance;
    double finalBest = data.back().bestDistance;
    double improvement = ((initialBest - finalBest) / initialBest) * 100.0;

    script << "set terminal pngcairo enhanced font 'Arial,12' size 1200,600\n";
    script << "set output '" << outputImage << "'\n";
    script << "set title 'Best Solution Evolution'\nset xlabel 'Generation'\nset ylabel 'Best Distance'\n";
    script << "set grid\nset key off\nset style line 1 lc rgb '#2ecc71' lt 1 lw 4\n";
    script << "plot '" << dataFile << "' using 1:2 every ::1 with filledcurves x1 ls 1 notitle, \\\n";
    script << "     '' using 1:2 every ::1 with lines ls 1 lw 3 notitle\n";

    script.close();
    executeGnuplot("results/graph_data/plot_best.gnu");
}

void GnuplotGenerator::generateMultiLineGraph(const Logger& logger,
                                              const std::string& dataFile,
                                              const std::string& outputImage) {
    const auto& data = logger.getData();
    if (data.empty()) return;

    std::ofstream script("results/graph_data/plot_multi.gnu");
    if (!script.is_open()) return;

    double minBest = data[0].bestDistance;
    double maxBest = data[0].bestDistance;
    for (const auto& d : data) {
        if (d.bestDistance < minBest) minBest = d.bestDistance;
        if (d.bestDistance > maxBest) maxBest = d.bestDistance;
    }
    double margin = (maxBest - minBest) * 0.1;

    script << "set terminal pngcairo enhanced font 'Arial,12' size 1200,1000\n";
    script << "set output '" << outputImage << "'\n";
    script << "set multiplot layout 2,1 title 'TSP GA Comprehensive Analysis' font 'Arial,16'\n";

    // Top: All metrics
    script << "set xlabel 'Generation'\nset ylabel 'Distance'\nset grid\nset key left top box\n";
    script << "set title 'All Metrics Evolution'\n";
    script << "set style line 1 lc rgb '#2ecc71' lt 1 lw 3\n";
    script << "set style line 2 lc rgb '#3498db' lt 1 lw 2\n";
    script << "set style line 3 lc rgb '#e74c3c' lt 1 lw 2\n";
    script << "plot '" << dataFile << "' using 1:2 every ::1 with lines ls 1 title 'Best', \\\n";
    script << "     '' using 1:3 every ::1 with lines ls 2 title 'Average', \\\n";
    script << "     '' using 1:4 every ::1 with lines ls 3 title 'Worst'\n";

    // Bottom: Best only zoomed
    script << "set xlabel 'Generation'\nset ylabel 'Best Distance'\nset title 'Best Solution Progress (Zoomed)'\nset key off\n";
    script << "set yrange [" << (minBest - margin) << ":" << (maxBest + margin) << "]\n";
    script << "plot '" << dataFile << "' using 1:2 every ::1 with linespoints ls 1 pt 7 ps 0.5\n";

    script << "unset multiplot\n";
    script.close();
    executeGnuplot("results/graph_data/plot_multi.gnu");
}

// -------------------- Route Graph --------------------

void GnuplotGenerator::generateRouteGraph(const std::vector<City>& cities,
                                          const std::vector<int>& bestTour,
                                          const std::string& outputImage) {

    std::ofstream routeFile("results/graph_data/route.dat");
    if (!routeFile.is_open()) {
        std::cerr << "Error: Cannot create route.dat\n";
        return;
    }

    for (int idx : bestTour)
        routeFile << cities[idx].getX() << "," << cities[idx].getY() << "\n";

    int first = bestTour[0];
    routeFile << cities[first].getX() << "," << cities[first].getY() << "\n"; // close loop
    routeFile.close();

    std::ofstream script("results/graph_data/plot_route.gnu");
    if (!script.is_open()) return;

    script << "set terminal pngcairo enhanced font 'Arial,12' size 800,800\n";
    script << "set datafile separator ','\n";
    script << "set output '" << outputImage << "'\n";
    script << "set title 'TSP Best Route' font 'Arial,16'\n";
    script << "set xlabel 'X'\nset ylabel 'Y'\nset grid\nset key off\n";
    script << "plot 'results/graph_data/route.dat' using 1:2 with linespoints lc rgb '#e74c3c' pt 7 ps 1 lw 2\n";

    script.close();
    executeGnuplot("results/graph_data/plot_route.gnu");
}
