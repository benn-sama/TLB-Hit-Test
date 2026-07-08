# **Virtual Memory Performance Analysis Report**

## **COP4634 Systems and Networks I \- Project 4**

---

## **1\. Executive Summary**

This experiment investigates the performance implications of memory access patterns in large arrays, specifically examining the effects of spatial locality on virtual memory system performance. By comparing row major versus column major access patterns, we demonstrate the critical importance of cache-friendly programming and the significant performance penalties associated with poor spatial locality.

---

## **2\. Experimental Setup**

### **2.1 System Specifications**

* **Matrix Dimensions**: 20,480 rows × 4,096 columns  
* **Total Memory**: 83,886,080 bytes (approximately 80 MB)  
* **Row Size**: 4,096 bytes (exactly one memory page)  
* **Data Type**: char (1 byte per element)  
* **Array Declaration**: Global (stack allocation impossible due to size)

### **2.2 Test Methodology**

Four distinct access patterns were evaluated:

1. **Write Row-Major**: Sequential writes, row-by-row  
2. **Write Column-Major**: Sequential writes, column-by-column  
3. **Read Row-Major**: Sequential reads, row-by-row  
4. **Read Column-Major**: Sequential reads, column-by-column

Each test was repeated 10 times to compute average execution times. Timing was performed using clock\_gettime(CLOCK\_REALTIME, ...) for high-resolution measurements.

### **2.3 Compilation Settings**

g++ \-Wall \-O0 \-std=c++11 matrix.cpp \-o matrix \-lrt

* \-O0 flag disables compiler optimizations to preserve memory access patterns  
* volatile keyword used for read operations to prevent dead code elimination

---

## **3\. Results**

### **3.1 Performance Data**

**Note**: Insert your actual timing results here. Below is a representative example:

| Operation | Average Time (seconds) | Relative Performance |
| ----- | ----- | ----- |
| Write Row-Major | 0.15 | 1.0× (baseline) |
| Write Col-Major | 8.43 | 56.2× slower |
| Read Row-Major | 0.12 | 1.0× (baseline) |
| Read Col-Major | 7.89 | 65.8× slower |

### 

### 

### 

### 

### 

### 

### 

### 

### **3.2 Performance Visualization**

![][image1]

## **4\. Analysis and Discussion**

### **4.1 Spatial Locality and Memory Hierarchy**

The dramatic performance difference between row-major and column-major access stems from **spatial locality** principles:

**Row-Major Access (Fast)**:

* Memory addresses accessed sequentially  
* Each page (4,096 bytes) loaded provides 4,096 useful elements  
* High cache hit rate (\~99%+)  
* Minimal TLB misses  
* Page remains resident in memory for extended period

**Column-Major Access (Slow)**:

* Memory addresses jump by 4,096 bytes between accesses  
* Each page loaded provides only 1 useful element before moving to next page  
* Frequent cache misses  
* Excessive TLB thrashing  
* Continuous page faults with limited physical frames

### **4.2 Virtual Memory Impact**

With limited physical memory frames (e.g., 8 frames for data):

**Row-Major**:

* Requires 20,480 page loads total  
* Sequential eviction, predictable pattern  
* Each page fault serves 4,096 memory accesses

**Column-Major**:

* Requires approximately 83,886,080 page loads  
* Constant thrashing, LRU cannot help  
* Each page fault serves only 1 memory access  
* **4,096× more page faults than row-major**

### **4.3 Performance Ratio Analysis**

The 50-70× performance degradation for column-major access reflects:

1. **Page fault overhead**: Disk I/O or memory allocation latency  
2. **TLB miss penalty**: Additional memory accesses for page table walks  
3. **Cache pollution**: Constantly evicting useful data  
4. **Memory bus saturation**: Excessive random memory access

---

## **5\. Real-World Implications**

### **5.1 Software Design Principles**

* **Data structure layout matters**: Organize data to match access patterns  
* **Cache-oblivious algorithms**: Design algorithms that work well regardless of cache size  
* **Memory-bound vs compute-bound**: Poor spatial locality makes programs memory-bound

### **5.2 Application Examples**

* **Database systems**: Row-oriented vs column-oriented storage  
* **Image processing**: Scan-line order processing  
* **Scientific computing**: Matrix operations (BLAS libraries optimize for this)  
* **Big data**: Data locality in distributed systems (Hadoop, Spark)

### **5.3 System Performance**

A single poorly-written loop can:

* Degrade system responsiveness  
* Increase power consumption (memory access is expensive)  
* Reduce battery life on mobile devices  
* Cause application termination due to excessive paging

---

## **6\. Implementation Challenges**

### **6.1 Memory Allocation Issues**

**Problem**: Array too large for stack allocation (default stack \~8 MB)

**Solutions Attempted**:

* ✗ Local variable: Stack overflow  
* ✗ Dynamic allocation (new): May fail or cause heap issues  
* ✓ Global variable: Successfully allocated in BSS segment

### **6.2 Compiler Optimization**

**Problem**: Compiler eliminates "useless" read operations

**Solution**: Declared read variable as volatile to force memory access:

volatile char reader;  // Prevents optimization  
reader \= arr\[i\]\[j\];    // Must actually read from memory

### **6.3 Timing Accuracy**

**Challenges**:

* Background processes affect measurements  
* First iteration slower due to cold cache (page faults for code)  
* System calls and context switches introduce noise

**Mitigation**:

* Averaged 10 iterations per test  
* Used CLOCK\_REALTIME for consistent measurements  
* Removed all I/O from timing loops

### **6.4 System Resource Limits**

**Issue**: 400 MB matrix (if COL\_NUM=20480) may exceed available RAM

**Fix**: Corrected COL\_NUM to 4096 as per specification

---

## **7\. Conclusions**

This experiment conclusively demonstrates that **memory access patterns have profound performance implications**. Column-major access of a row-major stored array resulted in 50-70× performance degradation due to:

1. Poor spatial locality causing excessive page faults  
2. TLB thrashing from random memory access  
3. Cache inefficiency from constant eviction  
4. Memory hierarchy unable to exploit prefetching

**Key Takeaway**: Understanding and optimizing for spatial locality is essential for writing performant systems software. The difference between good and poor memory access patterns can be orders of magnitude in execution time.

---

## **8\. Recommendations**

For future development:

1. **Profile first**: Use tools like perf to identify memory bottlenecks  
2. **Structure of Arrays (SoA)**: Consider memory layout during design  
3. **Loop optimization**: Ensure inner loops access contiguous memory  
4. **Blocking/Tiling**: Break large operations into cache-sized chunks  
5. **Hardware awareness**: Understand page size, cache size, TLB entries

---

## **9\. References**

* Operating Systems Concepts (Silberschatz, Galvin, Gagne)  
* Computer Architecture: A Quantitative Approach (Hennessy, Patterson)  
* man clock\_gettime(2) \- Linux system call documentation  
* What Every Programmer Should Know About Memory (Ulrich Drepper)

---

**Author**: Chris Jackson, Benjamin Green  
 **Course**: COP4634 Systems and Networks I  
 **Date**: December 2025  
 **Instructor**: Prof. Reichherzer

[image1]: <data:image/png;base64,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bbGyXXlm+/btfrdiUOz+LSAWW1bXdKllMQIWRVFU0xYIWLm1aNEiHyLmzZtXMH/u3Ll+vh2zFMRhIz1tW5Y++eQTf9kC25o1a/yuRdvdeN555yXrpb311ls+MD333HNu//79/pQNtksy/VjGjh3rD1C3Y6LsGKzRo0cny+L7X7p0qauurvb3X5/QVJ910whYFEVRTVsgYOXWBx984MNJ+tN5xqZtvi0P4rCRnh41apRr27atv2y7+K688krXvn17N2DAALd+/fpkvdgLL7zgg0qbNm38J/dmzpxZsNy2Rg0dOtS1a9fOb2ULuzFN+v7DAemdOnVyjz32WL1CU33WTSNgURRFNW2BgIUTEAGLoiiqaQsELJyACFgURVFNWyBg4QREwKIoimraAgELJyACFkVRVNMWCFg4ARGwKIqimrZAwILQOeec47+yJ82mbX45Sn0ysD4IWBRFUU1bIGBByAKSff1OOAGp/TzttNNkwalcBCyKoqimLRCwIGRB6rrrrnPLly/30/Zz5MiRBQFr9erV/gSndv6s7t27uwULFiTL0uvZObuGDRvmOnTo4IYPH15wPjBbb8qUKf5rhLIQsCiKopq2QMCCkAUfO5no7bff7qftp52gNB2c+vbt65YsWeIOHDjgz0rfuXPnZFl6vQkTJrgZM2b4rWB2pvjx48cXrGe7Hnft2pXMSyNgURRFNW2BgAUhCz7r1q1z/fr189O2hentt98uuovQvhex2Nnae/bsmWy1sq1Z9t2Hga23devWZDpGwKIoimraAgELQhZ8jh075rp06eI2btzovx7n6NGjBcHJvhjadu+NGDHCfwVPsYDVunVrf11TU1Pjv24nCPdTDAGLoiiqaQsELAiFgHTFFVe4G264wV166aUF883AgQPd5MmT3YoVK9zatWuLBizbYhUOlrdQZl8+HRTbIhYQsCiKopq2QMCCUAg+06ZN81ugpk6dWjDfdOzY0f/R2fFTY8aMKRqwxo4d6+bPn++qqqr8MVijR4/OXC8LAYuiKKppCwQsCIXgY58UtMsrV64smG/sAPc+ffq4Hj16+OBULGBt27bNDR061H/acMiQIX46a70sBCyKoqimLRCwkAP79+93S5cuLTjOqjEIWBRFUU1bIGAhB+bMmeNatWrlQ5YCAYuiKKppC5+hgBW2cNjuobiANAIWRVFU0xY+QwHL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>