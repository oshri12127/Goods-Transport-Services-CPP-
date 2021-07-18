#include "Simulation.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 3) {
            string error = "miss main arguments";
            throw invalid_argument(error);
        }
    }
    catch (const invalid_argument &e) {
        cerr << "Invalid input in file " << e.what() << " at line 0." << endl;
        exit(1);
    }
    vector<string> allArgs(argv, argv + argc);
    Simulation s(allArgs);//check input and build sim
    s.run();//start the sim
    return 0;
}