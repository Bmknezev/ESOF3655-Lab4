#include <stdio.h>

#define MAX_FRAMES 10 // Maximum number of frames

// Function to find the index of the given page in the frame array
int findIndex(int page, int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == page) {
            return i;
        }
    }
    return -1; // Return -1 if page is not found in frames
}

// Function to update the order of pages in the frame array based on LRU
void updateLRU(int frames[], int index, int n) {
    for (int i = index; i > 0; i--) {
        frames[i] = frames[i - 1];
    }
    frames[0] = frames[index];
}

// Function to simulate LRU page replacement algorithm
void simulateLRU(int pages[], int numPages, int numFrames) {
    int frames[MAX_FRAMES] = {-1}; // Initialize frames with -1 indicating empty frame
    int pageFaults = 0;
    int hits = 0;

    for (int i = 0; i < numPages; i++) {
        int page = pages[i];

        // Check if the page is already in a frame
        int index = findIndex(page, frames, numFrames);

        if (index == -1) {
            // Page fault: Page is not in any frame, replace the least recently used page
            pageFaults++;
            if (frames[numFrames - 1] != -1) {
                // If all frames are occupied, remove the last page (LRU)
                updateLRU(frames, numFrames - 1, numFrames);
            }
        } else {
            // Page hit: Page is already in a frame, update LRU order
            hits++;
            updateLRU(frames, index, numFrames);
        }

        // Place the current page in the first frame
        frames[0] = page;
    }

    // Calculate hit ratio
    float hitRatio = (float)hits / numPages * 100;

    // Display results
    printf("Number of Page Faults: %d\n", pageFaults);
    printf("Number of Hits: %d\n", hits);
    printf("Hit Ratio: %.2f%%\n", hitRatio);
}

int main() {
    int numFrames, numPages;

    // Get user input for the number of frames and pages
    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[MAX_FRAMES];

    // Get user input for the sequence of pages
    printf("Enter the sequence of pages:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    // Simulate LRU page replacement algorithm
    simulateLRU(pages, numPages, numFrames);

    return 0;
