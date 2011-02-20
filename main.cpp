#include <cstdlib> 
#include <ctime> 
#include <iostream>

const int pituus = 10;
const int leveys = 10;  
int water_seed = 1;
int map[pituus][leveys] = {{0}};

using namespace std;   
   
void print_map (){
	int tark = 0;
    int k = 1;
	int j = pituus -1;

    do {
      for (int i = 0; i <= j ; ++i) {
	  cout << map[k][i];
      }
      cout <<"\n";
    
      if (k > leveys - 2) {
	  tark = 1;
	  break;
      }
      k++;
    } while (tark < 1);

}

void generate_water(){
	srand(time(NULL));
	
	for (int i = 1; i <= water_seed ; i++) {
		int pi_random = rand() % pituus + 1;
		int le_random = rand() % leveys;
	
		map[pi_random][le_random] = 1;
	}
	
}
   
int main() {
    
	generate_water();
    // Taulukon printtaaminen debug tarkoitusta varten.
	print_map ();
      
}

