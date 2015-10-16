#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdint.h>
#include <omp.h>

using namespace std;

inline uint64_t fib_iterative(const size_t n) {
    uint64_t fn0 = 0;
    uint64_t fn1 = 1;
    uint64_t fn2 = 0;
    if(n==0) return fn0;
    if(n==1) return fn1;
    
    for(int i=2; i<(n+1); i++) {
        fn2 = fn0 + fn1;
        fn0 = fn1;
        fn1 = fn2;
    }
    return fn2;
}

inline uint64_t fib_recursive(uint64_t n) {
    if ( n == 0 || n == 1 ) return(n);
    return(fib_recursive(n-1) + fib_recursive(n-2));
}

int fib_recursive_omp(int n) {
    int i, j;
    if (n<2)
        return n;
    else {
#pragma omp task shared(i) firstprivate(n)
        i=fib_recursive_omp(n-1);
        
#pragma omp task shared(j) firstprivate(n)
        j=fib_recursive_omp(n-2);
        
#pragma omp taskwait
        return i+j;
    }
}

int fib_recursive_omp_fix(int n) {
    int i, j;
    if (n<2)
        return n;
    else {
        if ( n < 20 )
        {
            return(fib_recursive_omp_fix(n-1)+fib_recursive_omp_fix(n-2));
        }
        else {
#pragma omp task shared(i) firstprivate(n)
            i=fib_recursive_omp_fix(n-1);
            
#pragma omp task shared(j) firstprivate(n)
            j=fib_recursive_omp_fix(n-2);
            
#pragma omp taskwait
            return i+j;
        }
    }
}

int main() {
    const size_t n = 40;
    uint64_t result;
    double dtime;
    
    ofstream myfile;
    myfile.open ("result.dat");
    
    dtime = omp_get_wtime();
    result = fib_iterative(n);
    dtime = omp_get_wtime() - dtime;
    printf("iterative time %f, results %lu\n", dtime, result);
    myfile << "iterative time " << dtime <<", results "<< result << endl;
    
    dtime = omp_get_wtime();
    result = fib_recursive(n);
    dtime = omp_get_wtime() - dtime;
    printf("recursive time %f, results %lu\n", dtime, result);
    myfile << "recursive time " << dtime <<", results "<< result << endl;
    
    dtime = omp_get_wtime();
    result = fib_recursive_omp(n);
    dtime = omp_get_wtime() - dtime;
    printf("recursive omp time %f, results %lu\n", dtime, result);
    myfile << "recursive omp time " << dtime <<", results "<< result << endl;

    omp_set_num_threads(1);
    dtime = omp_get_wtime();
    result = fib_recursive_omp_fix(n);
    dtime = omp_get_wtime() - dtime;
    printf("recursive omp fix 1 thread time %f, results %lu\n", dtime, result);
    myfile << "recursive omp fix 1 thread time " << dtime <<", results "<< result << endl;

    omp_set_num_threads(2);
    dtime = omp_get_wtime();
    result = fib_recursive_omp_fix(n);
    dtime = omp_get_wtime() - dtime;
    printf("recursive omp fix 2 thread, time %f, results %lu\n", dtime, result);
    myfile << "recursive omp fix 1 thread time " << dtime <<", results "<< result << endl;
   
    myfile.close();
    
    string buff;
    ifstream fin("datain.dat");
    if (fin==NULL) {
        cout << "Error loading file \n";
    }
    else {
        fin >> buff;
        cout << buff << endl;
    }
    
}