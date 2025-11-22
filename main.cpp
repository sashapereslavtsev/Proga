#include <iostream>
#include <cmath>
#include <algorithm>
void inverse(int n, double** A, double** invA);
void free_matrix(double** A, int n);
double** matrix_make(int k, int n);
double** matrix_read(const char* f, int n);

void matrix_print(int n, int m, double** A){
    if (m>n) m=n;
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            std::cout << A[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


int main(int argc, char* argv[])
{
    if (argc<4){
        std::cerr << "не хватает аргументов"<< std::endl;
        return 1;
    }
    int n = std::atoi(argv[1]);
    int m = std::atoi(argv[2]);
    int k = std::atoi(argv[3]);
    
    if (m<1){
        std::cerr << "Число выводимых строк и столбцов матрицы должно быть строго положительным"<< std::endl;
        return 1;
    }
    
    double** A = nullptr;
    double** invA = nullptr;
    
    if (k==0){
        if(argc<5){
            std::cerr<<"При k=0 нужно название файла"<<std::endl;
            return 1;
        }
        A = matrix_read(argv[4], n);
    }
    else{
        A=matrix_make(k, n);
    } 
    
    if(A==nullptr){
        return 1;
    }
    
    invA = new double*[n]; 
    for (int i=0; i<n; i++){
        invA[i] = new double[n];
    }
    
    inverse(n, A, invA); //момент истины
    if(invA = nullptr){
        free_matrix(A,n);
        return 1;
    }
    matrix_print(n, m, invA);
    
    free_matrix(A, n);
    free_matrix(invA, n);
    return 0;
}
