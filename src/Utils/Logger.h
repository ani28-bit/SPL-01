#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>

struct GenerationData {
    int generation;
    double bestDistance;
    double avgDistance;
    double worstDistance;
};

class Logger {
private:
    std::vector<GenerationData> data;
    std::string logFile;
    std::string csvFile;

public:
    Logger(const std::string& logPath = "../results/logs/ga_log.txt",
           const std::string& csvPath = "../results/graph_data/evolution.csv");
    
    void logGeneration(int gen, double best, double avg, double worst);
    void saveToFile();
    void saveCSV();
    const std::vector<GenerationData>& getData() const;
};

#endif