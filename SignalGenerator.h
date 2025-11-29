#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Signal.h"

class SignalGenerator {
private:
    std::vector<std::shared_ptr<Signal>> signals;

    double readPositiveFrequency() const;
    bool readYesNo() const;
    std::string readSignalType() const;

public:
    
    void addSignal();

    
    void insertSignalAtIndex(std::size_t index);

  
    void removeSignalAtIndex(std::size_t index);

    
    void swapSignals(std::size_t index1, std::size_t index2);

    
    void showAll() const;

   
    void findByType(const std::string& searchType) const;

    std::size_t size() const { return signals.size(); }
};
