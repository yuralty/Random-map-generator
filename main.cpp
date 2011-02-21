#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <SDL/SDL.h> 

const int pituus = 50;
const int leveys = 50;
//Water_seed tarkoittaa kuinka monta "lähdettä" mapissa on.  
int water_seed = 1;
//Water_level_pro määrittelee prosentti määrän jolla vesi etenee. 5 = 50% 
int water_level_pro = 5;
int map[pituus][leveys] = {{0}};

using namespace std;   

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy);

void print_map (int g, int f){
	int tark = 0;
	int k = 1;
	int j = pituus -1;
		
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

void clear_map(){
 
 	int tark = 0;
	int k = 1;
	int j = pituus -1;
		

    do {
      for (int i = 0; i <= j ; ++i) {
	map[k][i] = 0;
      }  
    
      if (k > leveys - 2) {
	  tark = 1;
	  break;
      }
      k++;
    } while (tark < 1);

} 

   
int main() {
	Ref:
	int mapX = 0,mapY = 0;
	generate_water_seed();
	water_fill();
	// Taulukon printtaaminen debug tarkoitusta varten.
	
	Uint8* nappi;                    
	SDL_Event tapahtuma; 
	
	bool pois=false;
	
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )  
	{
	    fprintf(stderr, "SDL:n alustus ei onnistunut: %s\n", SDL_GetError()); 
	    return 0; // lopetetaan ohjelma
	}

	SDL_Surface *naytto;
	SDL_Surface *kuva;

	naytto = SDL_SetVideoMode(1280, 800, 30, SDL_HWSURFACE|SDL_DOUBLEBUF);

	kuva = SDL_LoadBMP("data/tileset.bmp");

	SDL_FreeSurface(kuva);

   while(pois==false) {
        
        SDL_PollEvent(&tapahtuma);
            if ( tapahtuma.type == SDL_QUIT )  { 
	      pois = true;  
	      }  
            if ( tapahtuma.type == SDL_KEYDOWN )  {
                    if ( tapahtuma.key.keysym.sym == SDLK_ESCAPE ) { 
		      pois = true;  
		    }   
            }
         
            if ( tapahtuma.type == SDL_KEYDOWN )  {
                    if ( tapahtuma.key.keysym.sym == SDLK_F5 ) { 
			clear_map();
			goto Ref;
		    }   
            }
         
       
         print_map(mapX,mapY);
         
        nappi = SDL_GetKeyState(NULL);
        if ( nappi[SDLK_UP] )  mapY -= 4;
        if ( nappi[SDLK_DOWN] )  mapY += 4;
        if ( nappi[SDLK_LEFT] )  mapX-= 4;
        if ( nappi[SDLK_RIGHT] )  mapX+= 4;
         
         
         
        SDL_Flip(naytto);    
	SDL_Delay(40);
    }
    
    SDL_Quit(); 	
      
}

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy)
{
    SDL_Rect kuvaalue; // alue, mikä kuvasta piirretään
    kuvaalue.x = kuvax;
    kuvaalue.y = kuvay;
    kuvaalue.h = korkeus;
    kuvaalue.w = leveys;

    SDL_Rect nayttoalue; // alue näytöllä, jolle kuva piirretään
    nayttoalue.x = nayttox;
    nayttoalue.y = nayttoy;

    SDL_BlitSurface(kuva, &kuvaalue, naytto, &nayttoalue);
}
