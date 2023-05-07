#include <iostream>

#include <exception>

#include <Windows.h>

#include <process.h>

#include <cstddef>

#include <cmath>
//This is a function template in C++ that takes a value of any type T as input.
//Returns a bool indicating whether the value is "not-a-number" (NaN) or not
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

//The function takes a void pointer arg as input but does not use it in the function body.
//This is a common practice for functions that are intended to be used as a thread function.
//the input parameter can be used to pass in some context or data for the thread to use.
//The function first defines a constant SIZE of 100000000, which represents the number of integers to be allocated.
//malloc() to allocate memory for SIZE integers, each of which is sizeof(int) bytes long
//malloc() function returns a nullptr, which indicates that the memory allocation has failed, the function outputs an error message to the console and returns.
//the function outputs a message indicating that the memory allocation was successful.
//he function frees the allocated memory using the free() function to ensure that the memory is released back to the system and can be used by other processes or threads. 

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
//This is a C++ program that retrieves information about the disk space on the C:\ drive of the current system using the Windows API function GetDiskFreeSpaceEx().
//The program outputs the total disk space, used disk space, and free disk space in gigabytes (GB) to the console.
//The main() function begins by using the GetDiskFreeSpaceEx() function to retrieve information about the disk space.
// the function call fails, the program throws a std::runtime_error with an error message, which is caught by a try-catch block.
//The function then calculates the total disk space, free disk space, and used disk space in GB, using the totalBytes and freeBytesAvailable variables returned by the GetDiskFreeSpaceEx() function
//It checks if any of these values are NaN using the isnan() function, which is a function template that takes a floating-point value as input and returns true if the value is NaN.
//If any of the calculated disk space values are NaN, the program throws a std::runtime_error with an error message.
//The program then outputs the disk space information to the console using cout.
//If the free disk space is less than 1 GB, the program outputs a warning message to the console.
//The catch block catches any std::exception thrown by the program, prints the error message to the standard error stream std::cerr, and exits the program.



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
    // it retrieves information about the memory address space of the current system using the Windows API function GetSystemInfo()
    //The program outputs the minimum and maximum addresses of the symbolic address space, the page size.
    //It also provide allocation granularity, and number of processor cores in the system to the console.
    //The GetSystemInfo() function retrieves information about the system such as the processor type, page size, and memory allocation granularity, among other things
    //The information is returned in a SYSTEM_INFO structure.
    //The program begins by declaring a SYSTEM_INFO structure variable named systemInfo
    //It then calls the GetSystemInfo() function, passing a pointer to the systemInfo variable 
    //the functions are used to recive information of system.
    //The program then outputs the memory address space information to the console using cout
    //It first outputs the minimum and maximum addresses of the symbolic address space using the lpMinimumApplicationAddress and lpMaximumApplicationAddres
    //these are the members of system info structure.
    //It then outputs information about the relative address space, including the page size and allocation granularity
    //They do it using the dwPageSize and dwAllocationGranularity members of the systemInfo structure
    //Finally, it outputs information about the physical address space, including the memory page size and number of processor cores
    //The process is done using the dwPageSize and dwNumberOfProcessors members of the systemInfo structure.
    
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

    //This is a C++ program that demonstrates memory allocation and deallocation using malloc(), calloc(), and realloc() functions.
    //The program begins by declaring a constant integer size and then dynamically allocating an integer array of size
    //they do this using malloc()
    //If malloc() fails to allocate memory, the program prints an error message and returns with a non-zero value
    // Otherwise, the program outputs a message to the console indicating that the memory allocation was successful
    //Next, the program dynamically allocates another integer array of size size using calloc()
    //If calloc() fails to allocate memory, the program prints an error message, frees the previously allocated memory using free()
    //Then returns in with a non zero value.
    //the program outputs a message to the console indicating that the memory allocation was successful.
    //The program then uses realloc() to resize the memory allocated by malloc() to 2 * size elements
    //If realloc() fails to allocate memory, the program prints an error message, frees both previously allocated arrays using free()
    //it also  returns with a non-zero value
    // the program outputs a message to the console indicating that the memory allocation was successful.
    //The program then deallocates the memory allocated by malloc() using free()
    // It then deallocates the memory allocated by calloc() using free().
    //Finally, the program returns with a zero value to indicate that it executed successfully.
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

//This code demonstrates how to use multithreading in C++ using the Windows API.
//The demonstrateMultithreading() function starts by defining a constant variable NUM_THREADS with the value of 4
//it represents the number of threads that will be created
//It then declares an array threadIds of size NUM_THREADS to store the thread IDs for each thread.
//A loop is then used to create the threads. The _beginthread() function is called with three arguments
//the arguments are he address of the allocateMemoryThread() function to be executed by the thread
// the stack size of the thread (which is set to 0), and a pointer to an argument passed to the thread (which is set to NULL).
//The _beginthread() function returns the thread ID of the newly created thread, which is stored in the threadIds array.
//Once all threads have been created, they will run concurrently and execute the allocateMemoryThread() function in parallel.
//he allocateMemoryThread() function allocates a large block of memory using malloc(), then frees the memory using free()
// This function is intended to demonstrate the effect of multiple threads attempting to allocate and free memory simultaneously.

void demonstrateMultithreading() {
    const int NUM_THREADS = 4;
    uintptr_t threadIds[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = _beginthread(&allocateMemoryThread, 0, NULL);
    }

    // Wait for threads to complete

    //The code is using the WaitForSingleObject() function to wait for the threads to complete before exiting the function
    //This is necessary because the threads may still be executing and using the allocated memory when the function returns
    //it causing memory leaks and potential crashes.
    //The WaitForSingleObject() function takes as input a handle to a thread or process and an optional timeout value. 
    // INFINITE is used as the timeout value in this case, indicating that the function should wait indefinitely until the thread completes.
    //The function waits for each thread in a loop by calling WaitForSingleObject() with the handle of the thread
    //this effectively blocking the main thread until all threads have completed their execution
    //Once all threads have completed, the function will return and any allocated memory will be deallocated properly.
    for (int i = 0; i < NUM_THREADS; i++) {
        WaitForSingleObject((HANDLE)threadIds[i], INFINITE);
    }
}
//an abstract base class Allocator, which provides an interface for allocating and freeing memory blocks
//The class has three protected data members
//m_totalSize, which stores the total size of the memory pool managed by the allocator.
//m_used, which stores the current amount of memory used in the memory pool.
//m_peak, which stores the maximum amount of memory used in the memory pool since the allocator was created.
//The class has a constructor that takes the totalSize of the memory pool as an argument and initializes the three data members to zero
// It also has a virtual destructor that sets the m_totalSize to zero.
//The class has three pure virtual member functions that must be implemented by derived classes
//Allocate, which takes the size and alignment requirements of the memory block to be allocated and returns a pointer to the allocated block.
//Free, which takes a pointer to a previously allocated memory block and frees it
//Init, which initializes the allocator and sets up the memory pool.
//the class declares a friend class Benchmark, which is used to measure the performance of the allocator.
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


// Garbage collection

// Linked list node for keeping track of allocated memory blocks
//MemoryBlock is a structure used to represent a block of memory in a linked list of memory blocks.
//address is a pointer to the start of the memory block.
//next is a pointer to the next MemoryBlock in the linked list, which allows for efficient traversal and management of the memory blocks.
//Together, multiple instances of MemoryBlock form a linked list of memory blocks, which can be used to manage a pool of memory for allocation and deallocation
// When a memory block is allocated, the allocator can update the next pointer of the current MemoryBlock 
// This is to point to the next available block in the pool, effectively marking it as use
// When a memory block is freed, the allocator can update the next pointer to point back
// it is for the previously used block, making it available for future allocations.
struct MemoryBlock {
    void* address;
    MemoryBlock* next;
};

// Global linked list for tracking allocated memory blocks

//allocatedMemoryBlocks is a pointer to the head of a linked list of MemoryBlock structures
// Each MemoryBlock structure in the list represents a block of memory that has been allocated by the allocator and its address is stored in the address field
//The next field is a pointer to the next block in the linked list.
//Initially, allocatedMemoryBlocks is set to nullptr to indicate that the linked list is empty.
//As memory blocks are allocated and deallocated, the linked list is updated accordingly to keep track of the currently allocated memory blocks.
MemoryBlock* allocatedMemoryBlocks = nullptr;

// Allocate a block of memory of the specified size

//This function allocateMemory allocates a block of virtual memory using the Windows function VirtualAlloc
// The VirtualAlloc function reserves or commits a region of pages in the virtual address space of the calling process
//If the allocation is successful, the function creates a new MemoryBlock
//with the address of the allocated block and adds it to the linked list of allocatedMemoryBlocks
//This linked list keeps track of all the allocated memory blocks so that they can be deallocated later.
//Finally, the function returns the address of the allocated block.

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

//freeMemory is a function that frees a previously allocated block of memory
//It takes a pointer to the beginning of the memory block as an argument.
//In the implementation of freeMemory that you're referring to, it appears that the function is implemented using a linked list of MemoryBlock structures
//The function traverses the linked list to find the MemoryBlock structure that contains the specified address
//then calls VirtualFree to release the memory associated with that block
//the MemoryBlock structure is removed from the linked list and deallocated.

void freeMemory(void* address) {
    // Remove the memory block from the linked list
    //This function is used to free memory that was previously allocated using the allocateMemory() function
    //It takes a pointer to the memory block to be freed as an argument.
    //The function starts by initializing a double pointer to the head of the linked list of allocated memory blocks
    //It then iterates through the linked list until it finds the block with the specified memory address
    // Once it finds the block, it updates the previous block's next pointer to skip the block being freed, effectively removing it from the linked list
    //Finally, it frees the memory used by the block and terminates the loop
    //the block with the specified address is not found, the function does nothing.
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

    //VirtualFree is a Windows API function that frees a region of memory that was previously allocated with VirtualAlloc or VirtualAllocEx
    //The first parameter specifies the base address of the region of memory to be freed, which is the address returned by VirtualAlloc
    //The second parameter specifies the size of the region to be freed, which should be set to 0 if the entire region should be freed.
    //The third parameter specifies the type of free operation to be performed, which in this case is MEM_RELEASE
    //the memory pages are immediately released and any physical pages that correspond to the released pages are available for other uses.
    VirtualFree(address, 0, MEM_RELEASE);
}

// Garbage collect all memory blocks that are no longer in use

//This garbageCollect() function iterates through the linked list of allocated memory blocks, pointed to by allocatedMemoryBlocks
// For each block, it checks if the memory block is still in use by using the IsBadReadPtr() function
//If the memory block is still in use, it skips to the next block
//If the memory block is no longer in use, it removes the block from the linked list
// it frees the memory block using VirtualFree()
// deallocates the MemoryBlock object using the delete operator.
void garbageCollect() {
    MemoryBlock** blockPtr = &allocatedMemoryBlocks;
    while (*blockPtr != nullptr) {
        MemoryBlock* block = *blockPtr;
        if (!IsBadReadPtr(block->address, 1)) {
            // The memory block is still in use, skip it
            
            //blockPtr = &block->next is setting the blockPtr to point to the next pointer of the current MemoryBlock
            // This is done in order to properly remove a memory block from the linked list if it is no longer in use.
            //The next pointer of the previous block is updated to skip over the current block and point directly to the next block in the list.
            //it will effectively removing the current block from the list
            blockPtr = &block->next;
        } 
        else
        {
            // The memory block is no longer in use, free it
            //In the garbageCollect function, if a memory block is determined to be no longer in use, it is removed from the linked list and freed using VirtualFree
            //a Windows API function used to free memory previously allocated using VirtualAlloc.
            //The *blockPtr = block->next; line updates the previous block's next pointer to skip the current block, effectively removing it from the linked list
            //The VirtualFree call releases the virtual memory allocated for the block back to the operating system, and the delete block
            //the MemoryBlock object itself, which was allocated using new when the memory block was first added to the linked list.

            *blockPtr = block->next;
            VirtualFree(block->address, 0, MEM_RELEASE);
            delete block;
        }
    }
}
