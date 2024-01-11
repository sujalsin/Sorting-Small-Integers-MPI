/*  Sujal
 *  Singh
 *  sujalsin
 */

#ifndef A2_HPP
#define A2_HPP

#include <vector>
#include <mpi.h>
#include <algorithm>
#include <limits>

void isort(std::vector<short int>& Xi, MPI_Comm comm) {
    int p, rank;
    MPI_Comm_size(comm, &p);
    MPI_Comm_rank(comm, &rank);

    const int max_short = std::numeric_limits<short int>::max();
    const int min_short = std::numeric_limits<short int>::min();
    int range = max_short - min_short + 1;
    std::vector<int> localCounts(range, 0);
    std::vector<int> globalCounts(range, 0);

    for (short int num : Xi) {
        localCounts[num - min_short]++;
    }

    MPI_Allreduce(localCounts.data(), globalCounts.data(), range, MPI_INT, MPI_SUM, comm);

    std::vector<short int> sortedData;
    int totalCount = 0;
    for (int i = 0; i < range; ++i) {
        int globalCount = globalCounts[i];
        while (globalCount > 0) {
            int targetProc = (totalCount / (Xi.size()));
            if (targetProc == rank) {
                sortedData.push_back(i + min_short);
            }
            totalCount++;
            globalCount--;
        }
    }

    Xi = sortedData;
}


#endif // A2_HPP

