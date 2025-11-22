#include <cmath>
#include <iostream>
#include <fstream>

void free_matrix(double** A, int n){
    for(int i=0; i<n; i++){
        delete[] A[i];
    }
    delete[] A;
}

double** matrix_make(int k, int n){

    if((k!=0)&&(k!=1)&&(k!=2)&&(k!=3)&&(k!=4)){
        std::cerr<<"Некорректные данные. Если хотите ввести матрицу из файла, третий аргумент должен быть равен нулю и после него стоять файл. Если нужна матрица из списка, на третьем аргументе должна стоять цифра 1, 2, 3 или 4"<<std::endl;
        return nullptr;
    }
    if(n<=0){
        std::cerr<<"Размер матрицы должен быть положительным"<<std::endl;
        return nullptr;
    }
    
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
    }
    
    if(k==1){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int m = i+1;
                if (j+1>m) m = j+1;
                A[i][j]=n-m+1;
            }
        }
    }
    
    if(k==2){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                int m = i+1;
                if (j+1>m) m = j+1;
                A[i][j]=m;
            }
        }
    }    
  
    if(k==3){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                A[i][j]=abs(i+1-j-1);
            }
        }
    }  
    
    if(k==4){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                A[i][j]=1.0/(i+1+j+1-1);
            }
        }
    } 
    return A;
}

double** matrix_read(const char* f, int n){
    if(n<0){
        std::cerr << "Размер матрицы должны быть натуральным числом" << std::endl;
        return nullptr;
    }  
    
    double** A = new double*[n];
    for (int i = 0; i < n; i++) {
        A[i] = new double[n];
    }
    
    std:: ifstream file(f);
    if(!(file.is_open())){
        std::cerr << "Файл не открывается" << std::endl;
        free_matrix(A, n);
        return nullptr;
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(!(file >> A[i][j])){
                std::cerr<<"Некорректный тип данных в файле";
                free_matrix(A, n);
                return nullptr;
            }
        }
    }
    
    file.close();
    return A;
}
