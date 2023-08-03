#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BILLION  1000000000.0

struct Point {
    int x;
    int y;
};

// time complexity: O(n^2)
// space complexity: O(1)
void insertionSort(struct Point arr[], int n, char coordinate, int ascending) {
    int i, j;
    struct Point key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i-1;
        while (j >= 0 && (                                                               // if j within array bounds
            (coordinate == 'x' && (ascending ? arr[j].x > key.x : arr[j].x < key.x)) ||  // if coordinate == x, sort based on x, if ascending = 0, arr[j].x < key.x ...
            (coordinate == 'y' && (ascending ? arr[j].y > key.y : arr[j].y < key.y))     // if coordinate == y, sort based on y, if ascending = 1, arr[j].y > key.y ...
        )) {
            arr[j+1] = arr[j]; // shift right
            j = j-1;
        }
        arr[j+1] = key;
    }
}

void rasterScanSort(struct Point arr[], int n, int eps) {
    insertionSort(arr, n, 'y', 0); // sort by y-coordinate descending

    int i = 0;
    int ascending = 1; // flag used to alternate ascending/descending sort
    while (i < n) {
        int j = i + 1;
        while (j < n && abs(arr[j].y - arr[i].y) <= eps) { // consider rows to be points where dy<eps
            j++;
        }
        if (ascending) {
            insertionSort(&arr[i], j-i, 'x', 1); // sort x in row ascending 
        } else {
            insertionSort(&arr[i], j-i, 'x', 0); // sort x in row descending
        }
        ascending = !ascending; // reverse the flag
        i = j;
    }
}

void printArray(struct Point arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("(%d, %d) ", arr[i].x, arr[i].y);
    }
    printf("\n");
}

void readPointsFromCSV(const char* filename, struct Point arr[], int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Unable to open the file.\n");
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d,%d", &(arr[i].x), &(arr[i].y)) != 2) {
            printf("Error reading point %d from the file.\n", i+1);
        }
    }
    fclose(file);
}

void savePointsToSCV(const char* filename, struct Point arr[], int n) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to open the file for writing");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d, %d\n", arr[i].x, arr[i].y);
    }
    fclose(file);
    printf("Sorted points saved to %s\n", filename);
}

void generateRandomPoints(struct Point arr[], int n, int eps) {
    for (int i = 0; i < n; i++) {
        arr[i].x = rand();
        arr[i].y = rand();
    }
}

double timeFunction(void (*f)(struct Point arr[], int n, int eps), struct Point arr[], int n, int eps) {
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    (*f)(arr, n, eps);
    clock_gettime(CLOCK_REALTIME, &end);
    double time_elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / BILLION;
    return time_elapsed;
}

int main(int argc, char *argv[]) {
    const char* filename = "C:/Users/memerson/Documents/code/embedded-sort/steve-points.csv";

    // Generate random points and evaluate performance
    // srand(time(NULL));
    // int n = 1000;
    // struct Point arr[n];
    // double timer1_elapsed = timeFunction(generateRandomPoints, arr, n, 10);
    // printf("Time to generate numbers: %f\n", timer1_elapsed);

    // Alternatively, sort points from csv file
    int n = 211; // known number of points in csv
    struct Point arr[n];
    readPointsFromCSV(filename, arr, n);

    printf("Unsorted Array: ");
    printArray(arr, n);
    printf("\n");

    int eps = 10;
    double time_elapsed = timeFunction(rasterScanSort, arr, n, eps);

    printf("Sorted Array: ");
    printArray(arr, n);
    
    printf("Time to sort: %f", time_elapsed);
    printf("\n");

    savePointsToSCV("../sorted_steve_points.csv", arr, n);

    return 0;
}