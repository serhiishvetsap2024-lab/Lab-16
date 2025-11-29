#include "SignalGenerator.h"
#include <iostream>
#include <limits>

double SignalGenerator::readPositiveFrequency() const {
    while (true) {
        std::cout << "Enter max frequency (Hz, > 0): ";
        double freq;
        std::cin >> freq;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (freq <= 0.0) {
            std::cout << "Frequency must be a positive number. Try again.\n";
            continue;
        }

       
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return freq;
    }
}

bool SignalGenerator::readYesNo() const {
    while (true) {
        std::cout << "Has modulation? (y/n): ";
        char ch;
        std::cin >> ch;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (ch == 'y' || ch == 'Y') return true;
        if (ch == 'n' || ch == 'N') return false;

        std::cout << "Please enter 'y' or 'n'.\n";
    }
}

std::string SignalGenerator::readSignalType() const {
    std::cout << "Enter signal type (can contain spaces): ";
    std::string type;
    std::getline(std::cin, type); 
    return type;
}

void SignalGenerator::addSignal() {
    std::cout << "\n=== Add new signal ===\n";
    std::string type = readSignalType();
    double freq = readPositiveFrequency();
    bool mod = readYesNo();

    auto sig = std::make_shared<Signal>(type, freq, mod);
    signals.push_back(sig);
}

void SignalGenerator::insertSignalAtIndex(std::size_t index) {
    if (index > signals.size()) {
        std::cout << "Invalid index. Valid range: 0.." << signals.size() << std::endl;
        return;
    }

    std::cout << "\n=== Insert signal at index " << index << " ===\n";
    std::string type = readSignalType();
    double freq = readPositiveFrequency();
    bool mod = readYesNo();

    auto sig = std::make_shared<Signal>(type, freq, mod);
    signals.insert(signals.begin() + static_cast<std::ptrdiff_t>(index), sig);
}

void SignalGenerator::removeSignalAtIndex(std::size_t index) {
    if (signals.empty()) {
        std::cout << "List is empty. Nothing to remove.\n";
        return;
    }
    if (index >= signals.size()) {
        std::cout << "Invalid index. Valid range: 0.." << (signals.size() - 1) << std::endl;
        return;
    }

    std::cout << "Removing signal at index " << index << "...\n";
    signals.erase(signals.begin() + static_cast<std::ptrdiff_t>(index));
}

void SignalGenerator::swapSignals(std::size_t index1, std::size_t index2) {
    if (signals.size() < 2) {
        std::cout << "Need at least two signals to swap.\n";
        return;
    }
    if (index1 >= signals.size() || index2 >= signals.size()) {
        std::cout << "Invalid indices. Valid range: 0.." << (signals.size() - 1) << std::endl;
        return;
    }
    if (index1 == index2) {
        std::cout << "Indices are the same. Nothing to swap.\n";
        return;
    }

    std::swap(signals[index1], signals[index2]);
    std::cout << "Signals at indices " << index1 << " and " << index2 << " have been swapped.\n";
}

void SignalGenerator::showAll() const {
    std::cout << "\n=== List of signals ===\n";
    if (signals.empty()) {
        std::cout << "List is empty.\n";
        return;
    }

    for (std::size_t i = 0; i < signals.size(); ++i) {
        std::cout << i << ": ";
        if (signals[i]) {
            signals[i]->printInfo();
        }
        else {
            std::cout << "(null)\n";
        }
    }
}

void SignalGenerator::findByType(const std::string& searchType) const {
    std::cout << "\n=== Search by type: \"" << searchType << "\" ===\n";
    bool found = false;

    for (std::size_t i = 0; i < signals.size(); ++i) {
        if (signals[i] && signals[i]->getType() == searchType) {
            std::cout << "Found at index " << i << ": ";
            signals[i]->printInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No signals with this type were found.\n";
    }
}
