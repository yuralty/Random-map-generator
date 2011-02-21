#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <SDL/SDL.h> 

const int pituus = 100;
const int leveys = 100;
//Water_seed tarkoittaa kuinka monta "l‰hdett‰" mapissa on.  
int water_seed = 1;
//Water_level_pro m‰‰rittelee prosentti m‰‰r‰n jolla vesi etenee. 5 = 50% 
int water_level_pro = 5;
int map[pituus][leveys] = {{0}};

using namespace std;   

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy);

void print_map (){
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	int g = 0;
	int f = 0;
	
	SDL_Surface *naytto;
	SDL_Surface *kuva;

	naytto = SDL_SetVideoMode(1280, 800, 30, SDL_HWSURFACE|SDL_DOUBLEBUF);

	kuva = SDL_LoadBMP("data/tileset.bmp");

    do {
      for (int i = 0; i <= j ; ++i) {
	if (map[k][i] == 0){
	    PiirraKuva(kuva, naytto, 0, 0, 16, 16, g, f );
	    g = g + 16;
	}
	else {
	    PiirraKuva(kuva, naytto, 16, 0, 16, 16, g, f );
	    g = g + 16;
	}
	//cout << map[k][i];
      }
     
      g = 0;
      f = f + 16;
    
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
	
	Uint8* nappi;                    // n‰pp‰imet
	SDL_Event tapahtuma; 
	
	bool pois=false;
	
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )  // paluuarvon ollessa pienempi kuin 0, tapahtui virhe
	{
	    fprintf(stderr, "SDL:n alustus ei onnistunut: %s\n", SDL_GetError()); // virheest‰ tiedot tiedostoon
	    return 0; // lopetetaan ohjelma
	}

	SDL_Surface *naytto;
	SDL_Surface *kuva;

	naytto = SDL_SetVideoMode(1280, 800, 30, SDL_HWSURFACE|SDL_DOUBLEBUF);

	kuva = SDL_LoadBMP("data/tileset.bmp");

	
	
	print_map();
	
	
	

	SDL_FreeSurface(kuva);

   while(pois==false) {

        // poistutaanko
        SDL_PollEvent(&tapahtuma);
            if ( tapahtuma.type == SDL_QUIT )  {  pois = true;  }  //poistumistapahtuma
            if ( tapahtuma.type == SDL_KEYDOWN )  {
                    if ( tapahtuma.key.keysym.sym == SDLK_ESCAPE ) { pois = true; }   // n‰inkin voi lukea n‰pp‰imi‰                
            }
         
        SDL_Flip(naytto);    
    }
    
    SDL_Quit(); // "suljetaan" SDL
	
      
}

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy)
{
    SDL_Rect kuvaalue; // alue, mik‰ kuvasta piirret‰‰n
    kuvaalue.x = kuvax;
    kuvaalue.y = kuvay;
    kuvaalue.h = korkeus;
    kuvaalue.w = leveys;

    SDL_Rect nayttoalue; // alue n‰ytˆll‰, jolle kuva piirret‰‰n
    nayttoalue.x = nayttox;
    nayttoalue.y = nayttoy;

    SDL_BlitSurface(kuva, &kuvaalue, naytto, &nayttoalue);
}
