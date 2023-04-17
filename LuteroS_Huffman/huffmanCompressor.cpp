/*Lutero Simone 4801326*/
/*Compressore che utilizza la codifica di Huffman ottenuta con l'esecuzione di "huffman.cpp" 
dal file di testo "random.txt" */

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
  	string testo;
    	ifstream fileTesto ("random.txt"); //Apro il file per prendere il testo generato randomicamente 
    	
    	ofstream fileCompressed; //Apro il file che conterra' il testo compresso
  	fileCompressed.open ("compressed.txt");
  	
    	while (getline(fileTesto,testo)){
      		for (int i = 0; i < testo.size(); i++)//ciclo che legge il file per la compressione{
      			if (testo[i] == 'a') fileCompressed << "0"; //compressione in base al carattere ricorrente
      			else if (testo[i] == 'b') fileCompressed << "10";
      			else if (testo[i] == 'c') fileCompressed << "110";
      			else if (testo[i] == 'd') fileCompressed << "11110";
      			else if (testo[i] == 'e') fileCompressed << "11111";
      			else if (testo[i] == 'f') fileCompressed << "11101";
      			else if (testo[i] == 'g') fileCompressed << "11100";
      		}	
    	}
  	
  	fileCompressed.close(); //ora chiudo il file che contiene la compressione
  	fileTesto.close(); //chiudo il file da cui ho preso il testo da comprimere
  	
}
