#include <cstdlib> 
#include <ctime> 
#include <iostream>

const int pituus = 10;
const int leveys = 10;
//Water_seed tarkoittaa kuinka monta "l‰hdett‰" mapissa on.  
int water_seed = 1;
//Water_level_pro m‰‰rittelee prosentti m‰‰r‰n jolla vesi etenee. 5 = 50% 
int water_level_pro = 5;
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

void generate_water_seed(){
	srand(time(NULL));
	
	for (int i = 1; i <= water_seed ; i++) {
		int pi_random = rand() % pituus + 1;
		int le_random = rand() % leveys;
		map[pi_random][le_random] = 1;		
	}
	
}

void water_fill(){
	int tark = 0;
    int k = 1;
	int j = pituus -1;
	int l = 0;
	int random = 0;	
	
	srand(time(NULL));
	
	do {
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 1) {
					random = rand() % 10;
					if (random < water_level_pro) {
						if (map[k][i - 1] == 2) {
						
						}
						else {
							map[k][i - 1] = 1;
						}	
					}
					random = rand() % 10;
					if (random < water_level_pro) {
						if (map[k + 1][i] == 2) {
						
						}
						else {
							map[k + 1][i] = 1;
						}	
					}
					random = rand() % 10;
					if (random < water_level_pro) {
						if (map[k][i + 1] == 2) {
						
						}
						else {
							map[k][i+1] = 1;
						}	
					}
			
					random = rand() % 10;
					if (random < water_level_pro) {
						if (map[k - 1][i] == 2) {
						
						}
						else {
							map[k-1][i] = 1;
						}	
					}		
				map[k][i] = 2;	
				k = 1;
			}
		}
    
		if (k > leveys - 2) {
			tark = 1;
			break;
		}
      k++;
    } while (tark < 1);

}
   
int main() {
    
	generate_water_seed();
	water_fill();
	// Taulukon printtaaminen debug tarkoitusta varten.
	print_map();
      
}

