#include <iostream>
#include <exception>
#include <Windows.h>
#include <process.h>

#include <cstddef>
#include <cmath>

template <typename T>
bool my_isnan(T value) {
    return value != value;
}
using namespace std;
//  The iostream header is used for standard input/output operations. 
//  The Windows.h header provides access to various Windows API functions,
//  and the process.h header provides functions for working with threads.

//  Function to allocate memory using malloc() in a separate thread
//  This function is called by demonstrateMultithreading() 
//  function to allocate memory using the malloc() function in a separate thread.
//  The function takes a void pointer argument which is not used.
class MyException : public std::exception {
public:
    MyException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() {
        return message_.c_str();
    }
private:
    std::string message_;
};


void allocateMemoryThread(void* arg) {
    const int SIZE = 100000000;
    int* ptr = (int*)malloc(SIZE * sizeof(int));

    if (ptr == nullptr) {
        cout << "Error allocating memory using malloc()." << endl;
        return;
    }

    cout << "Memory allocation successful." << endl;
    free(ptr);
}


int main()


{


    try {
    ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;

    if (!GetDiskFreeSpaceEx("C:\\", &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
        throw std::runtime_error("Error getting disk space information!");
    }

    double totalSpace = static_cast<double>(totalBytes.QuadPart) / (1024 * 1024 * 1024);

    double freeSpace = static_cast<double>(freeBytesAvailable.QuadPart) / (1024 * 1024 * 1024);

    double usedSpace = totalSpace - freeSpace;

    if (isnan(totalSpace) || isnan(freeSpace) || isnan(usedSpace)) {
        throw std::runtime_error("Error calculating disk space information!");
    }

    cout << "Disk Space Information:" << endl;

    cout << "Total disk space: " << totalSpace << " GB" << endl;

    cout << "Used disk space: " << usedSpace << " GB" << endl;

    cout << "Free disk space: " << freeSpace << " GB" << endl;

    if (freeSpace < 1) {
        cout << "Warning: Low disk space! Less than 1 GB free space available." << endl;
    }

} catch (const std::exception& e) {
    std::cerr << "Exception caught: " << e.what() << std::endl;
}




    // Get memory address space information
    SYSTEM_INFO systemInfo;
    GetSystemInfo(&systemInfo);



    cout << endl << "Memory Address Space Information:" << endl;

    cout << "Symbolic address space:" << endl;

    cout << "    Minimum address: 0x" << systemInfo.lpMinimumApplicationAddress << endl;

    cout << "    Maximum address: 0x" << systemInfo.lpMaximumApplicationAddress << endl;
    cout << "Relative address space:" << endl;

    cout << "    Page size: " << systemInfo.dwPageSize << " bytes" << endl;

    cout << "    Allocation granularity: " << systemInfo.dwAllocationGranularity << " bytes" << endl;

    cout << "Physical address space:" << endl;

    cout << "    Memory page size: " << systemInfo.dwPageSize << " bytes" << endl;

    cout << "    Number of processor cores: " << systemInfo.dwNumberOfProcessors << endl;


    // Memory allocation and deallocation
    const int size = 1000000;
    int* arr = reinterpret_cast<int*>(malloc(size * sizeof(int)));
    if (arr == nullptr)
    
    {
        cout << "Failed to allocate memory using malloc()." << endl;
        return 1;
    }
    cout << endl << "Memory allocation using malloc() successful." << endl;

    int* arr2 = reinterpret_cast<int*>(calloc(size, sizeof(int)));
    if (arr2 == nullptr)
    {
        cout << "Failed to allocate memory using calloc()." << endl;
        free(arr);
        return 1;
    }
    cout << "Memory allocation using calloc() successful." << endl;

    arr = reinterpret_cast<int*>(realloc(arr, 2 * size * sizeof(int)));
    if (arr == nullptr)
    {
        cout << "Failed to allocate memory using realloc()." << endl;
        free(arr);
        free(arr2);
        return 1;
    }
    cout << "Memory allocation using realloc() successful." << endl;

    free(arr);
    cout << "Memory deallocation using free() successful." << endl;

    free(arr2);
     cout << "Memory deallocation using free() successful." << endl;

    return 0;
}

// Function to demonstrate multithreading
void demonstrateMultithreading() {
    const int NUM_THREADS = 4;
    uintptr_t threadIds[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = _beginthread(&allocateMemoryThread, 0, NULL);
    }

    // Wait for threads to complete
    for (int i = 0; i < NUM_THREADS; i++) {
        WaitForSingleObject((HANDLE)threadIds[i], INFINITE);
    }
}
class Allocator {
protected:
    std::size_t m_totalSize;
    std::size_t m_used;   
    std::size_t m_peak;
public:
    
    Allocator(const std::size_t totalSize) : m_totalSize { totalSize }, m_used { 0 }, m_peak { 0 } { }

    virtual ~Allocator() { m_totalSize = 0; }

    virtual void* Allocate(const std::size_t size, const std::size_t alignment = 0) = 0;

    virtual void Free(void* ptr) = 0;

    virtual void Init() = 0;

    friend class Benchmark;
};


/*// Garbage collection

// Linked list node for keeping track of allocated memory blocks
struct MemoryBlock {
    void* address;
    MemoryBlock* next;
};

// Global linked list for tracking allocated memory blocks
MemoryBlock* allocatedMemoryBlocks = nullptr;

// Allocate a block of memory of the specified size
void* allocateMemory(size_t size) {
    void* address = VirtualAlloc(nullptr, size, MEM_COMMIT, PAGE_READWRITE);
    if (address != nullptr) {
        // Add the allocated memory block to the linked list
        MemoryBlock* block = new MemoryBlock{ address, allocatedMemoryBlocks };
        allocatedMemoryBlocks = block;
    }
    return address;
}

// Free a block of memory that was previously allocated with allocateMemory
void freeMemory(void* address) {
    // Remove the memory block from the linked list
    MemoryBlock** blockPtr = &allocatedMemoryBlocks;
    while (*blockPtr != nullptr) {
        if ((*blockPtr)->address == address) {
            MemoryBlock* block = *blockPtr;
            *blockPtr = block->next;
            delete block;
            break;
        }
        blockPtr = &(*blockPtr)->next;
    }
    // Free the memory block using the Windows API
    VirtualFree(address, 0, MEM_RELEASE);
}

// Garbage collect all memory blocks that are no longer in use
void garbageCollect() {
    MemoryBlock** blockPtr = &allocatedMemoryBlocks;
    while (*blockPtr != nullptr) {
        MemoryBlock* block = *blockPtr;
        if (!IsBadReadPtr(block->address, 1)) {
            // The memory block is still in use, skip it
            blockPtr = &block->next;
        } else {
            // The memory block is no longer in use, free it
            *blockPtr = block->next;
            VirtualFree(block->address, 0, MEM_RELEASE);
            delete block;
        }
    }
}*/