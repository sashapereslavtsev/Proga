#include <cmath>
#include <iostream>
#include <algorithm>

void inverse(int n, double** A, double** invA) {
    
    for (int i=0; i < n; i++){
        
        for(int j=0; j < n; j++){
            
            if(i==j) invA[i][j]=1;
            else invA[i][j]=0;
        }
    }
    
    int* perm = new int[n];
    
    for(int k=0; k<n; k++){
        double max =-1;
        int p=k, q=k;
        
        for(int i=k; i<n; i++){
            
            for(int j=k; j<n; j++){
                
                if (abs(A[i][j])>max){
                    max = abs(A[i][j]);
                    p=i;
                    q=j;
                }
                
            }
        }
        
        if (max<1e-15){
            std::cerr << "Матрица вырождена" << std::endl;
            invA = nullptr;
            delete[] perm;
            return;
        }
        
        for (int j=0; j<n; j++){ // меняю местами строки в обеих матрицах
            std::swap(A[k][j], A[p][j]);
            std::swap(invA[k][j], invA[p][j]);
        }
        
        for(int i=0; i<n; i++){ //меняю местами столбцы в первой матрице
            std::swap(A[i][k], A[i][q]);
        }
        
        perm[k]=q; //запоминаю перестановку столбцов
        
        double m=A[k][k]; //снова запоминаю максимальный элемент матрицы, тк он будет меняться
        for (int j=0; j<n; j++){
            invA[k][j] /=m;
            A[k][j] /=m;
        }
        
        for(int i=0; i<n; i++) {//зануляю все элементы k-го столбца, кроме A[k][k]
        if (i==k) continue;
        double x=A[i][k];
            for(int j=0; j<n; j++){
                invA[i][j]-=invA[k][j]*x;
                A[i][j]-=A[k][j]*x;
            }
        
        }
        
    }
    
    for(int k=n-1; k>-1; k--){ //меняем строки в invA в обратном порядке изменения столбцов в A
        for(int j=0; j<n; j++){
            std::swap(invA[k][j], invA[perm[k]][j]);
        }
    }
    
    delete[] perm;
}
