#include <iostream>

   const int pituus = 10;
   const int leveys = 10;  

   
int main() {
  
    int tark = 0;
    int k = 1;
    int kartta[pituus][leveys] = {{0}};
    int j = pituus -1;
    
    kartta[0][0] = 1;
    kartta[4][9] = 1;
    
    // Taulukon printtaaminen debug tarkoitusta varten.
    do {
      for (int i = 0; i <= j ; ++i) {
	  std::cout << kartta[k][i];
      }
      std::cout <<"\n";
    
      if (k > leveys - 2) {
	  tark = 1;
	  break;
      }
      k++;
    } while (tark < 1);
    
      
}

