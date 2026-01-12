#include "Logger.h"
#include <fstream>
#include <iostream>
#include <iomanip>

Logger::Logger(const std::string& logPath, const std::string& csvPath)
    : logFile(logPath), csvFile(csvPath) {}

void Logger::logGeneration(int gen, double best, double avg, double worst) {
    GenerationData gd;
    gd.generation = gen;
    gd.bestDistance = best;
    gd.avgDistance = avg;
    gd.worstDistance = worst;
    data.push_back(gd);
}

void Logger::saveToFile() {
    std::ofstream file(logFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open log file: " << logFile << std::endl;
        return;
    }
    
    file << "========================================\n";
    file << "   GA Evolution Log\n";
    file << "========================================\n\n";
    file << std::setw(12) << "Generation" << std::setw(15) << "Best"
         << std::setw(15) << "Average" << std::setw(15) << "Worst" << "\n";
    file << std::string(57, '-') << "\n";
    
    for (const auto& d : data) {
        file << std::setw(12) << d.generation
             << std::setw(15) << std::fixed << std::setprecision(2) << d.bestDistance
             << std::setw(15) << d.avgDistance
             << std::setw(15) << d.worstDistance << "\n";
    }
    file.close();
    std::cout << "\n✓ Log saved to: " << logFile << std::endl;
}

void Logger::saveCSV() {
    std::ofstream file(csvFile);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open CSV file: " << csvFile << std::endl;
        return;
    }
    
    file << "Generation,Best,Average,Worst\n";
    for (const auto& d : data) {
        file << d.generation << "," << std::fixed << std::setprecision(2)
             << d.bestDistance << "," << d.avgDistance << "," << d.worstDistance << "\n";
    }
    file.close();
    std::cout << "✓ CSV saved to: " << csvFile << std::endl;
}

const std::vector<GenerationData>& Logger::getData() const {
    return data;
}