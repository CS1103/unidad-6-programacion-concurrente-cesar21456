//
// Created by USUARIO on 21/06/2019.
//

#include <iostream>
#include <vector>
#include<stdlib.h>
#include<time.h>
#include<thread>
#include <ctime>
#define NUM_HILOS 2
using namespace std;

template <typename A>
class matriz{
    A **matrizz;
    int filas;
    int columnas;
public:
    friend void calcular(matriz<int>& temp,matriz<int>& matriz1, matriz<int>&    matriz2,int id);
    A** get_matriz()const {
        return matrizz;
    }
    int get_filas() const {
        return filas;
    }
    int get_columnas()const {
        return columnas;
    }
    void imprimir_matriz(){
        for (int i=0;i<filas;i++){
            for (int j=0;j<columnas;j++){
                cout<<matrizz[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    matriz(A a, A b):columnas(b),filas(a){
        matrizz=new A*[filas];
        for (int i=0;i<filas;i++){
            matrizz[i]=new A[columnas];
        }
        for(int i=0;i<filas;i++){
            for (int j=0;j<columnas;j++){
                matrizz[i][j]=0;
            }
        }
    }

    void set_valores_random(){
        for(int i=0;i<filas;i++){
            for (int j=0;j<columnas;j++){
                matrizz[i][j]=rand()%10;
            }
        }
    }


    ~matriz(){
        for (int i=0;i<filas;i++){
            delete matrizz[i];
        }
        delete matrizz;
    }



    matriz<A> operator*( const matriz<A>& matriz2){
        matriz<A> temp(this->filas,matriz2.columnas);
        if(this->columnas== matriz2.filas) {
            for (int i = 0; i < this->filas; i++) {
                for (int j = 0; j < matriz2.columnas; j++){
                    for (int z = 0; z < matriz2.filas; z++) {
                        temp.matrizz[i][j] += this->matrizz[i][z] * matriz2.matrizz[z][j];
                    }
                }
            }
        }
        else{
            cout<<"las filas y columnas que se ingresaron fueron diferentes"<<endl;
            return temp;
        }

    }
};
void calcular(matriz<int>& temp,matriz<int>& matriz1,matriz<int>& matriz2,int id) {
    if (matriz1.columnas == matriz2.filas) {
        int lim_inf = id * (matriz1.filas) / NUM_HILOS;
        int lim_sup = (id + 1) * (matriz1.filas) / NUM_HILOS;
        for (int i = lim_inf; i < lim_sup; i++) {
            for (int j = 0; j < matriz2.columnas; j++) {
                for (int z = 0; z < matriz2.filas; z++) {
                    temp.matrizz[i][j] += matriz1.matrizz[i][z] * matriz2.matrizz[z][j];
                }

            }

        }
    }
}





int main() {
    srand(time(NULL));
    matriz<int> a(500, 500);
    matriz<int> b(500, 500);
    //matriz<int> c(3,4);
    a.set_valores_random();

    cout<<endl;
    b.set_valores_random();


    cout << endl;
    auto t0=clock();
    auto c = a * b;
    auto t1 = clock();
    double time = (double(t1-t0)/CLOCKS_PER_SEC);


    cout<<endl;


    matriz<int> f(500, 500);
    /*calcular(f, a, b, 0);
    calcular(f, a, b, 1);
    calcular(f, a, b, 2);
    calcular(f, a, b, 3);
    */
    auto t2=clock();

    thread a1(calcular,ref(f),ref(a),ref(b),0);


    a1.join();
    cout<<"hola"<<endl;

    auto t3=clock();
    double time2 = (double(t3-t2)/CLOCKS_PER_SEC);
    cout << "Execution Time: " << time << endl;
    cout << "Execution Time: " << time2 << endl;



    return 0;
}