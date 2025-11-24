#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
#include <chrono>

bool inverse(int n, double** A, double** invA);
void free_matrix(double** A, int n);
double** matrix_make(int k, int n);
double** matrix_read(const char* f, int n);

void matrix_print(int n, int m, double** A){
    if (m>n) m=n;
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
        	printf(" %10.3e", A[i][j]);
        }
        std::cout << std::endl;
    }
}
double how_wrong(double** A, double** B, int n){
    double** C = new double*[n];
    for(int i=0; i<n; i++){
        C[i]= new double[n]; 
    }
    
    for (int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            C[i][j] = 0;
            for(int k=0; k<n; k++){
                C[i][j]+= A[i][k]*B[k][j];
            }
        }
    }
    for(int i=0; i<n; i++){
        C[i][i]-=1;
    }
    double m = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if (std::abs(C[i][j])>m){
                m=std::abs(C[i][j]);
            }
        }
    }
    free_matrix(C, n);
    return m;
}        


int main(int argc, char* argv[])
{
	auto start = std::chrono::high_resolution_clock::now();
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
    double** A_copy = nullptr;
    if (k==0){
        if(argc<5){
            std::cerr<<"При k=0 нужно название файла"<<std::endl;
            return 1;
        }
    if(argc>=6){
    std::cerr<<"Слишком много аргументов!!!"<<std::endl;
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
	A_copy = new double*[n];
	for(int i=0; i<n; i++){
		A_copy[i]= new double[n];
	}

	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			A_copy[i][j] = A[i][j];
		}
	}
    invA = new double*[n]; 
    for (int i=0; i<n; i++){
        invA[i] = new double[n];
    }
	if(!(inverse(n, A, invA))){
	free_matrix(A, n);
	free_matrix(invA, n);
	free_matrix(A_copy, n);
	return 1;
}
    matrix_print(n, m, invA);
    printf("Error %e\n", how_wrong(A_copy, invA, n));
	//std::cout << "Норма несвязки: " << how_wrong(A_copy, invA, n) << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);
	std::cout << "Время выполнения: " << duration.count() << " с" << std::endl;
    
    free_matrix(A, n);
    free_matrix(invA, n);
    free_matrix(A_copy, n);
    return 0;
}
