// ANÁLISIS Y DISEÑO DE ALGORITMOS. 2017/18
// Práctica 2 de Laboratorio: Comparación empírica de la complejidad temporal de los algoritmos de ordenación de vectores Quicksort y Heapsort.
// Se deben comparar en tres supuestos distintos: (1) vectores con contenido aleatorio y sin orden pre-establecido; (2) vectores ordenados; (3) vectores ordenados al contrario.
// La comparación debe hacerse mediante la "cuenta de pasos de programa"
// Consulta en el enunciado los detalles para realizar esta práctica.

#include <unistd.h>
#include <iostream>
#include <math.h>


using namespace std;
int _STEPS_ = 0;

//--------------------------------------------------------------
// Middle Quick Sort
void 
middle_QuickSort(int * v, long left, long right){
long i,j;
int pivot;
 _STEPS_++; //A
 if (left<right){ //A
   i=left; j=right;//a
   pivot=v[(i+j)/2]; //a
		do{
		  _STEPS_++; //B
		  while (v[i]<pivot) _STEPS_++; i++;
		  while (v[j]>pivot)_STEPS_++; j--;
			if (i<=j){ //B
				swap(v[i], v[j]);
				i++; j--;
			}
		}while (i<=j); //B
		if (left < j)  middle_QuickSort(v,left,j);
		if (i < right) middle_QuickSort(v,i,right);
	}
}

//--------------------------------------------------------------                
//HEAPSORT
// Procedure sink used by Heapsort algorith
// Sink an element (indexed by i) in a tree to keep the heap property. n is the size of the heap. 

void sink(int *v, size_t n, size_t i)
{
size_t largest;
size_t l, r; //left and right child

do{
  _STEPS_++;
   	largest = i;  // Initialize largest as root
    l = 2*i + 1;  // In a heap, left child (if exists) of node i is at (2*i + 1) position
    r = 2*i + 2;  // right child (if exists) of node i is at (2*i + 2) position
 
    // If left child exists and left child is larger than root
    if (l < n && v[l] > v[largest]) //Note that l>=n means that  root (or largest) node has not left child 
        largest = l;
 
    // If right child exists and right child is larger than largest so far 
    if (r < n && v[r] > v[largest])
        largest = r;
 
    // If largest is still root the process is done
    if (largest == i) break;
    
	// If not (largest has changed), swap new largest with current node i and repeat the process with childs. 
    swap(v[i], v[largest]);
 	i=largest;  
   } while (true);
}
 
//--------------------------------------------------------------                
// Heapsort algorithm 
void heapSort(int *v, size_t n)
{
    // Build heap with the input array
    for (size_t i = n / 2 - 1; i >= 0; i--){
      _STEPS_++;
        sink(v, n, i);
		if (i==0) break; //as size_t is unsigned type
	}	
	// Now we have a HEAP on the input array, let's take this to sort the array. 
    // One by one extract the first element, which is the largest, swap it with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.  
    for (size_t i=n-1; i>0; i--)
    {
      _STEPS_++;
        // Move current root to the end.
        swap(v[0], v[i]);
 		//Now largest element is at the end but do not know if the first element is well placed, so sink process is required
        sink(v, i, 0);
    }
}

int
main(void){

  int * v;
  float time = 0;
  
  size_t size;

  srand(getpid());

  cout << "quickSort CPU times in milliseconds:"
    << endl
    << "Size \t CPU time (ms.)"
    << endl
    << "----------------------------"
    << endl;

  for (int exp = 15; exp <= 23; exp++){
    
    size = (size_t) powl(2,exp);
    v = new int [size];

    //si se crea la matriz
    if (v){
      for(int i = 0; i < 30;i++){
      // relleno la matriz
      for (size_t j = 0; j < size; j++) 
        v[j] = rand(); 

      auto begin = high_resolution_clock::now();
      middle_QuickSort(v,0,size-1);
      auto end = high_resolution_clock::now();

      time = time + duration_cast<milliseconds>(end-begin).count();

      //comprueba que esté bien ordenado
      for (size_t i = 1; i < size; i++)
        if (v[i] < v[i-1]){ 
          cerr << "Panic, array not sorted! " << i << endl; 
          exit(1);      
        }
    }
      cout << size << "\t\t" << std::flush;
      cout << time/30 << endl;

      //reseteamos el tiempo para el siguiente array
      time = 0.0;
      delete v; 
    }

    else {
      cerr << "Error, not enough memory!" << endl;
      exit (1);  
    }
  }
}



