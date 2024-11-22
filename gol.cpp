#include "common.hpp"

// Assigns coordinates of different jobs linked to each thread
job_vec Gol::assignJobs(int total_jobs, int threads_per_side, int cells_per_thread) {
    job_vec jobs(total_jobs);   // Null vector containing the total number of threads that will be needed

    int whichThread = 0;    // The index of the current thread being assigned, < jobs.length
    for (int y_thread_num = 0; y_thread_num < threads_per_side; y_thread_num++) {
        int y0 = y_thread_num * cells_per_thread;
        int y1 = (y_thread_num + 1) * cells_per_thread - 1; // Stop just before the next job y-coordinate
        
        for (int x_thread_num = 0; x_thread_num < threads_per_side; x_thread_num++) {
            int x0 = x_thread_num * cells_per_thread;
            int x1 = (x_thread_num + 1) * cells_per_thread - 1;

            // jobs[whichThread].section.first.first   = x0;
            // jobs[whichThread].section.first.second  = y0;
            // jobs[whichThread].section.second.first  = x1;
            // jobs[whichThread].section.second.second = y1;

            // Debugging
            // std::cout << "(" << x0 << ", " << y0 << "), (" << x1 << ", " << y1 << ")\n";

            // Each thread will take a job from (x0, y0) to (x1, y1)
            jobs[whichThread].x0 = x0;
            jobs[whichThread].y0 = y0;
            jobs[whichThread].x1 = x1;
            jobs[whichThread].y1 = y1;

            whichThread++;
        }
    }

    return jobs;
}

// Function to get input based on where the user clicks on the screen
void Gol::mouseCurse(bool_matrix &board) {
    MEVENT event;
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    curs_set(0);
    mouseinterval(3);
    mousemask(ALL_MOUSE_EVENTS, NULL);
	
	printw("Welcome to Conway's Game of Life.\n");
	printw("Click on the screen to place live cells.\n");
	printw("An X will appear when you make a live cell.\n");
	printw("Press q to quit.");
	while(true) {
		int c = getch();
		switch(c) {
            case KEY_MOUSE:
                if(getmouse(&event) == OK) {
                    if(event.bstate & BUTTON1_PRESSED) {
                        
                        if (board[event.y][event.x] == false) {
                            board[event.y][event.x] = true;
                            mvprintw(event.y, event.x, "X");
                        } else {
                            board[event.y][event.x] = false;
                            mvprintw(event.y, event.x, " ");
                        }
                        
                        refresh();
                    }
                }
            break;
            case 'q' : goto end;
		}
	}
	end: endwin();
}

// Prints the board as is
void Gol::printBoard(bool_matrix &board) {
    for (auto row : board) {
        for (auto cell : row) {
            if (cell == true) std::cout << "X";
            else std::cout << " ";
        }

        std::cout << std::endl;
    }
}

// Function to test if one cell is alive or dead
// Check if each of a single cell's neighbour is alive or dead
bool liveTest(bool_matrix &board, int sideLength, int row, int cell) {
    bool isLive = board[row][cell];
    int numLive = 0;
    
    for (int rowCheck = row-1; rowCheck <= row+1; rowCheck++) {             // "For all rows"

        if ((rowCheck >= 0) && (rowCheck < sideLength)) {                   // "If rowCheck is in bounds;" can skip whole row if false

            for (int colCheck = cell-1; colCheck <= cell+1; colCheck++) {   // "For all columns"

                if ((((colCheck >= 0) && (colCheck < sideLength)) &&    // "If columnCheck is in bounds"
                    ((rowCheck != row) || (colCheck != cell))) &&       // "If not checking the element itself"
                    (board[rowCheck][colCheck] == true))                // "If the given cell is alive"
                    numLive++;

            }

        }

    }
    
    // If numLive is 2, will not change state at all
    if (numLive == 3) isLive = true;
    else if (numLive != 2) isLive = false;
    
    return isLive;
}

// Test if each cell in the current job is alive or dead using the corresponding thread
void doThreadJob(job &job_num, bool_matrix &curr_board, bool_matrix &next_board, int sideLength) {
    for (int row = job_num.y0; row <= job_num.y1; row++) {
        for (int cell = job_num.x0; cell <= job_num.x1; cell++) {
            next_board[row][cell] = liveTest(curr_board, sideLength, row, cell);
        }
    }
}

// Creates the next board using threads
bool_matrix Gol::getNextBoard(bool_matrix &curr_board, job_vec &jobs, int total_threads, int sideLength) {
    bool_matrix next_board(sideLength, bool_vec(sideLength));
    
    // Split board into threads
    // Have each thread to complete the job at the coordinates assigned to it
    for (int job_num = 0; job_num < total_threads; job_num++) {
        jobs[job_num].thread = std::thread(
            doThreadJob,
            std::ref(jobs[job_num]),
            std::ref(curr_board),
            std::ref(next_board),
            sideLength
        );
        jobs[job_num].thread.join();
    }

    return next_board;
}

/*
// Creates the next board [OLD]
bool_matrix Gol::getNextBoard(bool_matrix &curr_board, int sideLength) {
    bool_matrix next_board(sideLength, bool_vec(sideLength));
    
    // Test if each cell is alive or dead
    for (int row = 0; row < sideLength; row++) {
        for (int cell = 0; cell < sideLength; cell++) {
            next_board[row][cell] = liveTest(curr_board, sideLength, row, cell);
        }
    }

    return next_board;
}
*/