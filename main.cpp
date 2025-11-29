#include <iostream>
#include <limits>
#include <string>

#include "SignalGenerator.h"
#include "SmartPointerDemos.h"

std::size_t readIndex(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        long long idx;
        std::cin >> idx;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter integer index.\n";
            continue;
        }

        if (idx < 0) {
            std::cout << "Index cannot be negative.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return static_cast<std::size_t>(idx);
    }
}

int main() {
    std::cout << "=== Lab 16: Smart pointers & Signal generator ===\n";

    SignalGenerator generator;
    bool running = true;

    while (running) {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1 - Add signal (push back)\n";
        std::cout << "2 - Insert signal at index\n";
        std::cout << "3 - Remove signal at index\n";
        std::cout << "4 - Swap two signals\n";
        std::cout << "5 - Show all signals\n";
        std::cout << "6 - Find signals by type\n";
        std::cout << "7 - unique_ptr demo\n";
        std::cout << "8 - shared_ptr demo\n";
        std::cout << "9 - weak_ptr demo\n";
        std::cout << "10 - doubly linked list demo\n";
        std::cout << "0 - Exit\n";
        std::cout << "Your choice: ";

        int choice;
        std::cin >> choice;

        if (!std::cin) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            generator.addSignal();
            break;
        case 2: {
            std::size_t idx = readIndex("Enter index (0..size): ");
            generator.insertSignalAtIndex(idx);
            break;
        }
        case 3: {
            std::size_t idx = readIndex("Enter index (0..size-1): ");
            generator.removeSignalAtIndex(idx);
            break;
        }
        case 4: {
            std::size_t idx1 = readIndex("Enter first index: ");
            std::size_t idx2 = readIndex("Enter second index: ");
            generator.swapSignals(idx1, idx2);
            break;
        }
        case 5:
            generator.showAll();
            break;
        case 6: {
            std::cout << "Enter type to search (can contain spaces): ";
            std::string searchType;
            std::getline(std::cin, searchType);
            generator.findByType(searchType);
            break;
        }
        case 7:
            uniquePtrDemo();
            break;
        case 8:
            sharedPtrDemo();
            break;
        case 9:
            weakPtrDemo();
            break;
        case 10:
            listDemo();
            break;
        case 0:
            running = false;
            break;
        default:
            std::cout << "Wrong menu choice.\n";
            break;
        }
    }

    std::cout << "\n=== Program finished ===\n";
    return 0;
}
