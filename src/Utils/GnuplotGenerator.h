#ifndef GNUPLOTGENERATOR_H
#define GNUPLOTGENERATOR_H

#include <string>
#include <vector>

#include "TSP/City.h"

class GnuplotGenerator {
public:
    // Evolution graphs
    static void generateGraph(const Logger& logger,
                              const std::string& dataFile = "results/graph_data/evolution.csv",
                              const std::string& outputImage = "results/graph_data/evolution.png");

    static void generateBestGraph(const Logger& logger,
                                  const std::string& dataFile = "results/graph_data/evolution.csv",
                                  const std::string& outputImage = "results/graph_data/best_evolution.png");

    static void generateMultiLineGraph(const Logger& logger,
                                       const std::string& dataFile = "results/graph_data/evolution.csv",
                                       const std::string& outputImage = "results/graph_data/evolution_multi.png");

    // TSP Route graph
    static void generateRouteGraph(const std::vector<City>& cities,
                                   const std::vector<int>& bestTour,
                                   const std::string& outputImage = "results/graph_data/route.png");

private:
    static bool executeGnuplot(const std::string& scriptFile);
};

#endif
