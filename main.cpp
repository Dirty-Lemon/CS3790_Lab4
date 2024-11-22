#include "common.hpp"

/* argv[0] = "./gol"
 * argv[1] = sideLength
 * argv[2] = threadsPerSide
 * argv[3] = numGens
 */
int main(int argc, char* argv[]) {
    
    // Test for correct number of arguments
    bool goodArgc = (argc == 4);
    if (!goodArgc) {    
        std::cout << "Malformed request.\n";
        std::cout << "Usage: " << argv[0] << " <side_length> <procs_per_side> <num_gens>\n" << std::endl;
        return 1;
    }

    int sideLength = atoi(argv[1]);
    int threads_per_side = atoi(argv[2]);               // Number of threads generated along one axis of the board
    int numGen = atoi(argv[3]);

    bool allPositive = ((sideLength > 0) && (threads_per_side > 0) && (numGen > 0));
    if (!allPositive) {
        std::cout << "Malformed request.\n";
        std::cout << "All arguments after \"" << argv[0] << "\" must be positive.\n" << std::endl;
        return 1;
    }

    // Test for divisibility
    bool isDivisible = (sideLength % threads_per_side == 0);
    if (!isDivisible) {
        std::cout << "Malformed request.\n";
        std::cout << "<procs_per_side> argument must be evenly divisible by <side_length> argument.\n" << std::endl;
        return 1;
    }

    Gol g;  // Instance of the Gol class
    bool_matrix board(sideLength, bool_vec(sideLength));

    int total_threads = threads_per_side * threads_per_side;
    int cells_per_job = sideLength / threads_per_side;  // Number of cells in each job

    // Create a vector that stores all threads needed with their corresponding job coordinates
    // "jobs" is a vector of structs containing a thread and four integers, used as the coordinates
    job_vec jobs = g.assignJobs(total_threads, threads_per_side, cells_per_job);

    g.mouseCurse(board);    // Get starting board through user clicks
    g.printBoard(board);    // Display the starting board after mouseCurse() ends

    // Get the next generation as many times as the user requested
    for (int i = 0; i < numGen; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // board = g.getNextBoard(board, sideLength);
        board = g.getNextBoard(board, jobs, total_threads, sideLength);
        g.printBoard(board);
    }
    
    return 0;
}