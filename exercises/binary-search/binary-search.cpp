#include <iostream> 
using namespace std; 

/* Parameters:
 *     arr:     the array where we search for x.
 *     (l, r):  the scope within which binary search will be conducted.
 *     x:       the number we look for.                                       */
int binarySearch_recursive(int arr[], int l, int r, int x) { 
    if (r >= l) {
        int mid = l + (r - l) / 2;
 
        // If the element is present at the middle, itself.
        if (arr[mid] == x) {
            return mid;
        }
            
        // If element is smaller than mid, then it can only be present in left subarray.
        if (arr[mid] > x) {
            return binarySearch_recursive(arr, l, mid - 1, x);
        }
            
        // Else the element can only be present, in right subarray.
        return binarySearch_recursive(arr, mid + 1, r, x);
    }
    // We reach here when element is not present in array.
    return -1;
} 

/* The parameters are idential to those of the function above */
int binarySearch_iterative(int arr[], int l, int r, int x) { 
   while (l <= r) {
        int m = l + (r - l) / 2;
 
        // Check if x is present at mid.
        if (arr[m] == x) {
            return m;
        }
            
        // If x greater, ignore left half.
        if (arr[m] < x) {
            l = m + 1;
        }
            
        // If x is smaller, ignore right half.
        else {
            r = m - 1;
        }
    }
    // If we reach here, then element wasn't present.
    return -1;
} 

int main() {
    int arr[] = {2, 3, 4, 10, 40}; // the array where to search for x
    int n = 5; // length of the array

    int x = 10; // our task is to look for this number in the array
    
    cout << "Location of Element (recursive): " << binarySearch_recursive(arr, 0, n - 1, x) << endl;
    cout << "Location of Element (iterative): " << binarySearch_iterative(arr, 0, n - 1, x) << endl;
} 