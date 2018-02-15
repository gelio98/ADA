/*
Jose Antonio Juan Prado 48787664H
Análsis y diseño de algoritmos.
Práctica 1: Análisis empírico de la complejidad temporal promedio del algoritmo de ordenación Quicksort central

*/

//--------------------------------------------------------------
// Middle QuickSort

#include <unistd.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <bits/stdc++.h>


using namespace std;


double _STEPS_Q = 0;
double _STEPS_H = 0;

//--------------------------------------------------------------
// Middle Quick Sort
void 
middle_QuickSort(int * v, long left, long right){
long i,j;
int pivot,aux; 
_STEPS_Q++; //A
  if (left<right){
	i=left; j=right;
	pivot=v[(i+j)/2];
	do{
		_STEPS_Q++; //A
		while (v[i]<pivot){ _STEPS_Q++;  i++;}
		while (v[j]>pivot) {_STEPS_Q++;  j--;}
		if (i<=j) {
		  aux=v[i]; v[i]=v[j]; v[j]=aux;
		  i++; j--;
		}
	}while (i<=j);
	if (left<j)  middle_QuickSort(v,left,j);
	if (i<right) middle_QuickSort(v,i,right);
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
  _STEPS_H++;
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
      _STEPS_H++;
        sink(v, n, i);
		if (i==0) break; //as size_t is unsigned type
	}	
	// Now we have a HEAP on the input array, let's take this to sort the array. 
    // One by one extract the first element, which is the largest, swap it with the last element of the vector and rebuild heap by sinking the new placed element on the begin of vector.  
    for (size_t i=n-1; i>0; i--)
    {
      _STEPS_H++;
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
	int prueba = 0;
	int *aux;
	double pasos1,pasos2,pasos3,pasos4 = 0;
  
	size_t size;

	cout << "<script src=\"https://cdnapisec.kaltura.com/p/1926081/sp/192608100/embedIframeJs/uiconf_id/29375172/partner_id/1926081\"></script>\n    \n<script>\n\tkWidget.embed({\n\t\"targetId\": \"kaltura-player\",\n\t\"wid\": \"_1926081\",\n\t\"uiconf_id\": \"29375172\",\n\t\"flashvars\": {\n          \"streamerType\": \"auto\",\n          \"referenceId\": \"9781788479035-video1_1\"\n          },\n\t});\n    </script>\n\n    \n    \n\n  ";

	srand(getpid());

	cout << "QUICKSORT VERSUS HEAPSORT" << endl;
	cout << "Average processing Msteps(million of program steps" << endl;
	cout<< "Number os samples(arrays of integer): 30" << endl;
	cout<< "          " << "RANDOM ARRAYS      SORTED ARRAYS      REVERSE SORTED ARRAYS" << endl;
	cout << "       ------------------  -----------------  ------------------------" << endl;
	cout	<< "Size  QuickSort HeapSort  QuickSort HeapSort     QuickSort HeapSort"<< endl;
	cout << "================================================================================" << endl;


	for (int exp = 15; exp <= 22; exp++){
		
		size = (size_t) powl(2,exp);
		v = new int [size];
		aux = new int[size];

		//si se crea la matriz
		if (v){
			for(int i = 0; i < 30;i++){
			// relleno la matriz
			for (size_t j = 0; j < size; j++){
				v[j] = rand();
				aux[j] = v[j];
			}



			middle_QuickSort(v,0,size-1);


			heapSort(aux,size);

			pasos1 = pasos1 + _STEPS_Q;
			pasos2 = pasos2 + _STEPS_H;
			
			//comprueba que esté bien ordenado
			for (size_t i = 1; i < size; i++)
				if (v[i] < v[i-1]){ 
					cerr << "Panic, array not sorted! " << i << endl; 
					exit(1);			
				}

			_STEPS_Q = 0;
			_STEPS_H = 0;
			middle_QuickSort(v,0,size-1);
			heapSort(aux,size);

			pasos3 = pasos3 + _STEPS_Q;
			pasos4 = pasos4 + _STEPS_H;

			_STEPS_Q = 0;
			_STEPS_H = 0;

		}	
			cout.setf( ios::fixed );
			cout << size << "\t" << std::flush;
			cout <<  fixed << setprecision(3) << pasos1/30/1000000 << "\t" << std::flush;
			cout << fixed << setprecision(3) << pasos2/30/1000000 << "\t" << std::flush;
			cout << "    ";
			cout << fixed << setprecision(3) << pasos3/30/1000000 << "\t" << std::flush;
			cout << fixed << setprecision(3) << pasos4/30/1000000 <<"\t" << std::flush << endl;
			
			_STEPS_H = 0;
			_STEPS_Q = 0;
			pasos1 = 0;
			pasos2 = 0;
			pasos3 = 0;
			pasos4 = 0;
			//reseteamos el tiempo para el siguiente array
			delete v; 
		}

		else {
			cerr << "Error, not enough memory!" << endl;
			exit (1);  
		}
	}
}

