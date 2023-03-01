#include <iostream>
#include <vector>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <string>


using namespace std;

// Function to check if two queens threaten each other
bool isThreatening(int x1, int y1, int x2, int y2) 
{
    return (x1 == x2) || (y1 == y2) || (x1 + y1 == x2 + y2) || (x1 - y1 == x2 - y2);
}

// Function to check if a queen can be placed on the board
bool isSafe(int x, int y, vector<int>& solution) 
{
    for (int i = 0; i < y; i++) 
    {
        if (isThreatening(solution[i], i, x, y)) 
        {
            return false;
        }
    }
    return true;
}

// Recursive function to find all solutions to the N-Queens problem
void nQueens(int n, int y, vector<int>& solution, int& count) 
{
    if (y == n) 
    {
        #pragma omp critical
        {
            count++;
            cout << "[";
            for (int i = 0; i < n; i++) 
            {
                cout << "(" << solution[i] << "," << i << ")";
            }
            cout << "]" << endl;
        }
        return;
    }
    for (int x = 0; x < n; x++) 
    {
        if (isSafe(x, y, solution)) 
        {
            solution[y] = x;
            nQueens(n, y + 1, solution, count);
            solution[y] = -1;
        }
    }
}

int main(int argc, char* argv[]) 
{
    if (argc < 3 || argc > 3) 
    {
        std::cout << "Usage: " << argv[0] << " <number of Queens> <number of threads>\n";
        return 1;
    }
    vector<int> solution;
    int count;
    struct timeval tv1, tv2;
    struct timezone tz;
    double elapsed;
    int n = stoi(argv[1]);
    int numThreads = stoi(argv[2]);
    count = 0;
    solution = vector<int>(n, -1);
    gettimeofday(&tv1, &tz);
    #pragma omp parallel num_threads(numThreads)
    {
        vector<int> private_solution = solution;
        int private_count = 0;
        #pragma omp for schedule(dynamic)
        for (int x = 0; x < n; x++) {
            private_solution[0] = x;
            nQueens(n, 1, private_solution, private_count);
            private_solution[0] = -1;
        }
        #pragma omp critical
        {
            count += private_count;
        }
    }
    gettimeofday(&tv2, &tz);
    elapsed = (double) (tv2.tv_sec-tv1.tv_sec) + (double) (tv2.tv_usec-tv1.tv_usec) * 1.e-6;
    cout << "Solutions for N = " << n << ":" << endl;
    cout << "Total solutions: " << count << endl;
    cout << "Total Time Elapsed = " << elapsed << endl;
    cout << endl;
    return 0;
}
