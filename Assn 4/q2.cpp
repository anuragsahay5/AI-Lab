#include <iostream>
#include <cmath>

using namespace std;

// Structure to represent a point in 2D space
struct Coordinate {
    int x, y;
};

// Class to solve the Monkey Banana Problem
class MonkeyBananaSolver {
private:
    // Room dimensions and heights
    int roomWidth, roomLength, ceilingHeight, boxHeight, monkeyHeight;
    // Coordinates of gate and window
    Coordinate gate, window;

public:
    // Method to fetch user inputs
    void fetchRoomDetails() {
        cout << "Enter room width: ";
        cin >> roomWidth;

        cout << "Enter room length: ";
        cin >> roomLength;

        cout << "Enter ceiling height: ";
        cin >> ceilingHeight;

        cout << "Enter box height: ";
        cin >> boxHeight;

        cout << "Enter monkey height: ";
        cin >> monkeyHeight;

        cout << "Enter coordinates of the gate (x y): ";
        cin >> gate.x >> gate.y;

        cout << "Enter coordinates of the window (x y): ";
        cin >> window.x >> window.y;
    }

    // Method to validate the entered coordinates and heights
    bool validateInputs() {
        bool valid = true;

        // Check if coordinates are within room boundaries
        if (gate.x < 0 || gate.x > roomWidth || gate.y < 0 || gate.y > roomLength)
            valid = false;

        if (window.x < 0 || window.x > roomWidth || window.y < 0 || window.y > roomLength)
            valid = false;

        // Check if heights are non-negative
        if (ceilingHeight <= 0 || boxHeight < 0 || monkeyHeight < 0)
            valid = false;

        return valid;
    }

    // Method to check if the monkey can reach the banana
    bool canMonkeyReachBanana() {
        int totalHeight = boxHeight + monkeyHeight;
        return totalHeight >= ceilingHeight;
    }

    // Method to print the steps for the monkey to reach the banana
    void printSolutionSteps() {
        if (!validateInputs()) {
            cout << "Invalid inputs. Please enter valid coordinates and heights.\n";
            return;
        }

        if (canMonkeyReachBanana()) {
            cout << "Steps to reach the banana:\n";
            if (monkeyHeight >= ceilingHeight) {
                cout << "1. Walk towards the center of the room.\n";
                cout << "2. Jump and grab the banana directly.\n";
            } else {
                cout << "1. Walk towards the window.\n";
                cout << "2. Push the box towards the banana.\n";
                cout << "3. Climb onto the box.\n";
                cout << "4. Reach out and grasp the banana.\n";
            }
        } else {
            cout << "The monkey cannot reach the banana.\n";
        }
    }
};

int main() {
    // Create an instance of MonkeyBananaSolver
    MonkeyBananaSolver solver;
    // Fetch user inputs
    solver.fetchRoomDetails();
    // Print solution steps
    solver.printSolutionSteps();
    return 0;
}
