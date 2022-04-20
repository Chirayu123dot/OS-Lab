#include <stdio.h>

int search(int array[], int size, int val) {
    for(int i=0 ; i<size ; i++) {
        if(array[i] == val) return i;
    }
    return -1;
}

// searches for val in the subarray reference[start.......size-1]
// if it finds the val, returns it's index
// if it does not find the val, then it returns -1 * pageFrameIndex
// We multiply it with -1 so that we can determine whether val was found or not
int getNextIndex(int reference[], int start, int size, int val, int pageFrameIndex) {
    for(int i=start ; i<size ; i++) {
        if(reference[i] == val) return i;
    }
    return pageFrameIndex * -1;
}

int main()
{
    // ------------------------------------- input starts ------------------------------
    int reference[1000], pageFrame[1000];
    int referenceCount, pageFrameCount, pageFrameTop = 0;
    double hitCount = 0;

    printf("Number of references: ");
    scanf("%d", &referenceCount);
    printf("Enter the page references\n");
    for(int i=0 ; i<referenceCount ; i++) scanf("%d", &reference[i]);

    printf("Number of page frames: ");
    scanf("%d", &pageFrameCount);

    for(int i=0 ; i<pageFrameCount ; i++) pageFrame[i] = -1;

    // ------------------------------------ input ends ---------------------------------

    for(int i=0 ; i<referenceCount ; i++) {

        if(search(pageFrame, pageFrameCount, reference[i]) == -1) {     // page is not present in page frame array

            if(pageFrameTop < pageFrameCount) {     // there is space in pageFrame array
                pageFrame[pageFrameTop] = reference[i];
                pageFrameTop++;
                continue;
            }

            // we need to replace a page

            int max = -1, check = 0;
            for(int j=0 ; j<pageFrameCount ; j++) {
                
                if(check == 0) {
                    max = getNextIndex(reference, i+1, referenceCount, pageFrame[j], j);
                    check = 1;
                }

                else {
                    int x = getNextIndex(reference, i+1, referenceCount, pageFrame[j], j);
                    if( (x > max || x <= 0 ) && max > 0 ) max = x;
                }
            }

            if(max <= 0) {
                max *= -1;
                pageFrame[max] = reference[i];
            }
            else {
                int index = search(pageFrame, pageFrameCount, reference[max]);
                pageFrame[index] = reference[i];
            }
        } 
        else {
            // it iz a hit
            hitCount++;
        }  
    }

    printf("Final page frame array\n");
    for(int i=0 ; i<pageFrameCount ; i++) printf("%d ", pageFrame[i]);
    printf("\nHit Count = %.0f\t", hitCount);
    printf("Hit Ratio: %f", hitCount / referenceCount);
    printf("\nNumber of page faults = %.0f\t", referenceCount - hitCount);
    printf("Page Fault Ratio: %f\n", 1 - (hitCount / referenceCount));
}