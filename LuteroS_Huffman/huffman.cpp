/*Lutero Simone 4801326
Codifica di Huffman*/

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
 
#define MAX_H 100 //altezza massima dell'albero
 
//Nodi albero MinHeap
struct MinHeapNode {
 
    char data;//carattere di input
 
    unsigned freq;//frequenza carattere di input
 
    MinHeapNode *sx, *dx; //figli del nodo (sx e dx)
    
};
 
//struttura albero MinHeap
struct MinHeap {
 
    unsigned size; //dimensione
 
    unsigned capacity; //capacità
 
    MinHeapNode** array; //Puntatori ai nodi dell'albero
    
};
 
//Funzione di allocazione nuovo nodo
MinHeapNode* newNode(char data, unsigned freq)
{
    MinHeapNode* temp = (MinHeapNode*)malloc
(sizeof(MinHeapNode));
 
    temp->sx = temp->dx = NULL;
    temp->data = data;
    temp->freq = freq;
 
    return temp;
}
 
//Funzione di creazione di un Min-Heap avendo solo la capacita'
MinHeap* createMinHeap(unsigned capacity)
{
 
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
 
    minHeap->size = 0; //dimensione attuale dell'albero pari a zero
 
    minHeap->capacity = capacity;
 
    minHeap->array = (MinHeapNode**)malloc(minHeap->capacity * sizeof(MinHeapNode*));
    return minHeap;
}
 
//Funzione di scambio nodi
void scambioMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
//Funzione minHeapify
void minHeapify(MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int sx = 2 * idx + 1;
    int dx = 2 * idx + 2;
 
    if (sx < minHeap->size && minHeap->array[sx]->freq < minHeap->array[smallest]->freq) smallest = sx;
 
    if (dx < minHeap->size && minHeap->array[dx]->freq < minHeap->array[smallest]->freq) smallest = dx;
 
    if (smallest != idx) {
        scambioMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 
//Funzione di controllo size
int dimensioneUno(MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
 
//Funzione ausiliaria per estrarre il nodo di valore minore
MinHeapNode* extractMin(MinHeap* minHeap)
{
    MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
 
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return temp;
}
 
//Funzione che aggiunge un nodo
void newNode(MinHeap* minHeap, MinHeapNode* minHeapNode)
{
    ++minHeap->size;
    int i = minHeap->size - 1;
 
    while(i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq){
 	minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    
    minHeap->array[i] = minHeapNode;
    
}
 
//Funzione che genera minHeap
void generateMinHeap(MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
 
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
//Stampa array
void stampaArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
        cout<< arr[i];
 
    cout<<"\n";
}
 
//Funzione che verifica un nodo (se è una foglia)
int foglia(MinHeapNode* radice)
{
 
    return !(radice->sx) && !(radice->dx);
}
 
//Generazione MinHeap
MinHeap* minHeapGeneration(char data[], int freq[], int size)
 
{
 
    MinHeap* minHeap = createMinHeap(size);
 
    for (int i = 0; i < size; ++i) minHeap->array[i] = newNode(data[i], freq[i]);
 
    minHeap->size = size;
    generateMinHeap(minHeap);
 
    return minHeap;
}
 
//Funzione per costruire l'albero
MinHeapNode* treeCreate(char data[], int freq[], int size)
 
{
    MinHeapNode *sx, *dx, *top;
 
    // Creazione di un Min-Heap uguale a size
    MinHeap* minHeap = minHeapGeneration(data, freq, size);
 
    //finche' size non vale 1 va avanti
    while (!dimensioneUno(minHeap)) {
 
        //Estrazione dei 2 nodi con probabilità piu' bassa
        sx = extractMin(minHeap);
        dx = extractMin(minHeap);
        
        //Creo un nuovo nodo la cui frequenza corrisponde alla somma delle frequenze dei due nodi estratti ('$' corrisponde al nodo non usato)
        top = newNode('$', sx->freq + dx->freq);
 	
 	//Prendo i  due nodi figli destro e sinistro del nuovo nodo
        top->sx = sx;
        top->dx = dx;
 
        newNode(minHeap, top);
    }
 
    //il nodo rimanente corrisponde alla radice dell'albero
    return extractMin(minHeap);
}
 
//Stampa codifiche car
void stampaCodifiche(MinHeapNode* radice, int arr[], int top)
{
    //Se va a sinistra: 0
    if (radice->sx) {
 
        arr[top] = 0;
        stampaCodifiche(radice->sx, arr, top + 1);
    }
 
    //Se va a destra: 1
    if (radice->dx) {
 
        arr[top] = 1;
        stampaCodifiche(radice->dx, arr, top + 1);
    }
 
    //Se il nodo è una foglia contiene uno dei caratteri dati in input
    // e stampo il carattere seguito dalla sua codifica corrispondente
    if (foglia(radice)) {
 
        cout<< radice->data <<": ";
        stampaArray(arr, top);
    }
}
 
//FUNZIONE CODIFICA HUFFMAN
void CodificaHuffman(char data[], int freq[], int size)
 
{
    //Albero di Huffman come Min-Heap binario
    MinHeapNode* radice = treeCreate(data, freq, size); //chiamo la funzione che crea l'albero
 
    int arr[MAX_H], top = 0;
 
    stampaCodifiche(radice, arr, top); //stampa
}
 
int main()
{
     char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
     
    //Prendiamo il file random generato che contiene soltanto i caratteri a-g
    string testo;
    ifstream fileTesto ("random.txt");
    
    //Conto le frequenze dei vari caratteri presenti nel file di testo
    int freqA=0, freqB=0, freqC=0, freqD=0, freqE=0, freqF=0, freqG=0;
     while (getline(fileTesto,testo)){
      	for (int i = 0; i < testo.size(); i++){
      		if (testo[i] == 'a') freqA++; //se è 'a', incremento frequenza a
      		else if (testo[i] == 'b') freqB++;
      		else if (testo[i] == 'c') freqC++;
      		else if (testo[i] == 'd') freqD++;
      		else if (testo[i] == 'e') freqE++;
      		else if (testo[i] == 'f') freqF++;
      		else if (testo[i] == 'g') freqG++;
      	}	
    }
    fileTesto.close(); //Dopo aver utilizzato il file per le frequenze, lo chiudo
    
    int freq[6]; //Frequenze caratteri contenute in un array freq
    freq[0] = freqA;
    freq[1] = freqB;
    freq[2] = freqC;
    freq[3] = freqD;
    freq[4] = freqE;
    freq[5] = freqF;
    freq[6] = freqG;
 
    int size = sizeof(arr) / sizeof(arr[0]);  //calcolo size
 
    CodificaHuffman(arr, freq, size); //ora chiamo la funzione di codifica huffman utilizzando come parametri l'array, la size e freq
 
    return 0;
}
