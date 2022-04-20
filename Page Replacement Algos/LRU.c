// Time complexity - O(referenceCount * pageFrameCount)

#include <stdio.h>

// searches for a page in the page frame array
// returns the index of the element if present, otherwise returns -1
int search(int array[], int size, int value) {
    for(int i=0 ; i<size ; i++) {
        if(array[i] == value) return i;
    }
    return -1;
}

// This function returns the last (largest) index of the value in the array
int getLastIndex(int reference[], int start, int value) {
    for(int i=start ; i>=0 ; i--) {
        if(reference[i] == value) return i;
    }
    return -1;
}

int main()
{
    // ------------------------------ input starts --------------------------
    int pageFrameTop = 0;
    double hitCount = 0;
    int reference[1000], pageFrame[1000];
    int referenceCount, pageFrameCount;

    printf("Total number of page references: ");
    scanf("%d", &referenceCount);
    printf("Enter the page references\n");

    for(int i=0 ; i<referenceCount ; i++) scanf("%d", &reference[i]);

    printf("Total number of page frames: ");
    scanf("%d", &pageFrameCount);

    for(int i=0 ; i<pageFrameCount ; i++) pageFrame[i] = -1;

    // -------------------------------- input ends ---------------------------

    for(int i=0 ; i<referenceCount ; i++){

        // The page is not present in the pageFrame array
        if(search(pageFrame, pageFrameCount, reference[i]) == -1) {  

            // all the page frames are not full
            if(pageFrameTop < pageFrameCount) {  
                pageFrame[pageFrameTop] = reference[i];
                pageFrameTop++;
                continue;
            }

            // all the page frames are full, we need to replace a page
            int min = -1;

            // iterate the page frame array
            for(int j=0 ; j<pageFrameCount ; j++) {

                if(min == -1) {
                    min = getLastIndex(reference, i, pageFrame[j]);
                    continue;
                }
                
                int x = getLastIndex(reference, i, pageFrame[j]);
                if(x < min) min = x;
            }

            // get the index of reference[min] element in pageFrame array
            int index = search(pageFrame, pageFrameCount, reference[min]);

            // replace pageFrame[index]
            pageFrame[index] = reference[i];
        }
        else {
            // it iz a hit
            hitCount++;
        }

        
    }

    printf("Final page frame array: ");
    for(int i=0 ; i<pageFrameCount ; i++) {
        printf("%d ", pageFrame[i]);
    }
    printf("\nHit Count = %.0f\t", hitCount);
    printf("Hit Ratio: %f", hitCount / referenceCount);
    printf("\nNumber of page faults = %.0f\t", referenceCount - hitCount);
    printf("Page Fault Ratio: %f\n", 1 - hitCount / referenceCount);


}

