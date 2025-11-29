#include "Signal.h"
#include <iostream>

Signal::Signal()
    : type("Unknown"), maxFrequency(0.0), hasModulation(false)
{
    std::cout << "[Signal] Default constructed\n";
}

Signal::Signal(const std::string& t, double f, bool m)
    : type(t), maxFrequency(f), hasModulation(m)
{
    std::cout << "[Signal] Constructed: " << type
        << ", f_max = " << maxFrequency
        << " Hz, modulation = " << (hasModulation ? "yes" : "no")
        << std::endl;
}

Signal::~Signal() {
    std::cout << "[Signal] Destroyed: " << type << std::endl;
}

void Signal::printInfo() const {
    std::cout << "Type: " << type
        << ", f_max = " << maxFrequency << " Hz"
        << ", modulation: " << (hasModulation ? "yes" : "no")
        << std::endl;
}
