**Raster Scan/ Insertion Sort Algorithm**

1. **Struct Definition:**
   ```c
   struct Point {
       int x;
       int y;
   };
   ```
   This code defines a structure `Point` that holds two integers `x` and `y`. This structure is used to represent 2D points with x and y coordinates.

2. **Insertion Sort Function:**
   ```c
   void insertionSort(struct Point arr[], int n, char coordinate, int ascending) {
       int i, j;
       struct Point key;
       for (i = 1; i < n; i++) {
           key = arr[i];
           j = i - 1;
           while (j >= 0 && (
               (coordinate == 'x' && (ascending ? arr[j].x > key.x : arr[j].x < key.x)) ||
               (coordinate == 'y' && (ascending ? arr[j].y > key.y : arr[j].y < key.y))
           )) {
               arr[j + 1] = arr[j]; // shift right
               j = j - 1;
           }
           arr[j + 1] = key;
       }
   }
   ```
   This is the insertion sort function that is modified to sort the array of `Point` structures based on the specified `coordinate` (x or y) and `ascending` flag (whether sorting in ascending or descending order). The code iterates through the array and compares the values of the specified coordinate. If the condition is met, it shifts elements to the right and inserts the current key in the correct position. For more information on how insetion sort works, see [this link](https://en.wikipedia.org/wiki/Insertion_sort).

   ![insertion_sort_gif](https://upload.wikimedia.org/wikipedia/commons/0/0f/Insertion-sort-example-300px.gif)

3. **Raster Scan Sort Function:**
   ```c
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
               insertionSort(&arr[i], j - i, 'x', 1); // sort x in row ascending 
           } else {
               insertionSort(&arr[i], j - i, 'x', 0); // sort x in row descending
           }
           ascending = !ascending; // reverse the flag
           i = j;
       }
   }
   ```
   This function sorts the array of `Point` structures using a raster scan approach. It first sorts all points based on the y-coordinate in descending order. Then, it iterates through the points, treating rows as points where the difference in y-coordinate (`dy`) is less than or equal to `eps`.

   Within each row, it alternates between sorting the points' x-coordinates in ascending or descending order based on the `ascending` flag. After sorting each row, it toggles the `ascending` flag and moves to the next row.

Overall, this code effectively sorts 2D points based on the specified coordinates and order using insertion sort and the raster scan approach.