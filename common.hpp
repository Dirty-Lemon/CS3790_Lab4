#ifndef common_hpp
#define common_hpp

#include <iostream>     // std::cout
// #include <utility>      // std::pair
#include <ncurses.h>
#include <vector>
#include <thread>
#include <chrono>       // std::this_thread::sleep_for, std::chrono::milliseconds

using bool_vec = std::vector<bool>;
using bool_matrix = std::vector<bool_vec>;  // std::vector<vector<bool>>

// using point_t = std::pair<int, int>;
// using job_area = std::pair<point_t, point_t>;

// struct job {
//     std::thread thread;
//     job_area section;
// };

struct job {
    std::thread thread;
    int x0;
    int y0;
    int x1;
    int y1;
};

using job_vec = std::vector<job>;

class Gol {
// private:

public:
    void mouseCurse(bool_matrix &);
    void printBoard(bool_matrix &);
    job_vec assignJobs(int, int, int);
    // bool_matrix getNextBoard(bool_matrix &,  int);
    bool_matrix getNextBoard(bool_matrix &, job_vec &, int, int);
};

#endif