#pragma once
#include <string>

class Signal {
private:
    std::string type;
    double maxFrequency;
    bool hasModulation;

public:
    Signal();
    Signal(const std::string& t, double f, bool m);
    ~Signal();

    void printInfo() const;

    const std::string& getType() const { return type; }
    double getMaxFrequency() const { return maxFrequency; }
    bool getHasModulation() const { return hasModulation; }
};
