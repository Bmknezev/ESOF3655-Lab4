#include <iostream>
#include <list>
#include <unordered_map>

using namespace std;

class LRUCache {
private:
    list<int> lruList;                     // Linked list to maintain LRU order
    unordered_map<int, list<int>::iterator> pageMap; // Map to store page number and its iterator in the linked list
    int capacity;                         // number of frames
    int pageFaults;                       // Counter for page faults
    int hits;                             // Counter for hits

public:
    LRUCache(int capacity) : capacity(capacity), pageFaults(0), hits(0) {}

    // Function to handle a page reference
    void referencePage(int page) {
        // Check if the page is already in the cache
        if (pageMap.find(page) != pageMap.end()) {
            // Page hit
            hits++;
            lruList.erase(pageMap[page]);   // Remove the page from its current position in the list
        } else {
            // Page fault
            pageFaults++;
            if (lruList.size() == capacity) {
                // Remove the least recently used page from the back of the list
                int lruPage = lruList.back();
                lruList.pop_back();
                pageMap.erase(lruPage);
            }
        }

        // Add the referenced page to the front of the list
        lruList.push_front(page);
        pageMap[page] = lruList.begin();
    }

    // Function to display the content of frames
    void displayFrames() {
        cout << "Frames: ";
        for (int page : lruList) {
            cout << "[" << page << "] ";
        }
        cout << endl;
    }

    // Function to calculate and display page fault information
    void displayPageFaultInfo() {
        float hitRatio = static_cast<float>(hits) / (hits + pageFaults);
        cout << "\nNumber of Page Faults: " << pageFaults << endl;
        cout << "Number of Hits: " << hits << endl;
        cout << "Hit Ratio: " << hitRatio << endl;
    }
};

int main() {
    int numFrames, numPages;

    // Get user input for the number of frames and pages
    cout << "Enter the number of frames: ";
    cin >> numFrames;

    cout << "Enter the number of pages: ";
    cin >> numPages;

    // Create an instance of the LRUCache
    LRUCache lruCache(numFrames);

    int page;

    cout << "Enter the sequence of pages:\n";

    for (int i = 0; i < numPages; i++) {
        cin >> page;
        lruCache.referencePage(page);

        // Display the current state of frames after each page reference
        lruCache.displayFrames();
    }

    // Display page fault information
    lruCache.displayPageFaultInfo();

    return 0;
}
