#include <cstdlib> 
#include <ctime> 
#include <iomanip>
#include <iostream>
#include <SDL/SDL.h> 

const int pituus = 200;
const int leveys = 100;
//Ground_seed tarkoittaa kuinka monta "lähdettä" mapissa on.  
int ground_seed = 4;
//Ground_level_pro määrittelee prosentti määrän jolla vesi etenee. 5 = 50% 
float ground_level_pro = 5;
//Forest_seed määrittelee kuinka monta metsän alkua mapissa on.
int forest_seed = 4;
// Prosentti määrä jolla metsä leviää.
int forest_level_pro = 4;

double map[pituus][leveys] = {{0}};
double map_back[pituus][leveys] = {{0}};
int SCREEN_WIDTH = 800;
int SCREEN_HEIGHT = 1280;


using namespace std;   

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy);

void print_map (int g, int f){
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	int x = g ;
	int y = f ;
	
	SDL_Surface *naytto;
	SDL_Surface *kuva;
	naytto = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 30, SDL_HWSURFACE|SDL_DOUBLEBUF);
	kuva = SDL_LoadBMP("data/tileset.bmp");
	
	
	do {           
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 2){
				// Maa
				PiirraKuva(kuva, naytto, 0, 0, 16, 16, x * 4 - g , f);
					g = g + 16;
			}
			else if (map[k][i] == 3) {
				//Puu
				PiirraKuva(kuva, naytto, 32, 16, 16, 16, x * 4 - g , f);
				PiirraKuva(kuva, naytto, 32, 0, 16, 16, x * 4 - g , f - 16);
				g = g + 16;
			}
			else if (map[k][i] == 4) {
				//Oikea
				PiirraKuva(kuva, naytto, 96, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			
			else if (map[k][i] == 5) {
				//Ala
				PiirraKuva(kuva, naytto, 64, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			
			else if (map[k][i] == 6) {
				//Vasen
				PiirraKuva(kuva, naytto, 112, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			else if (map[k][i] == 7) {
				//Yla
				PiirraKuva(kuva, naytto, 64, 16, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			else if (map[k][i] == 4.6) {
				//Oikea yla
				PiirraKuva(kuva, naytto, 80, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			else if (map[k][i] == 4.5) {
				//Vasen ylakulma
				PiirraKuva(kuva, naytto, 48, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			
			else if (map[k][i] == 4.7) {
				//Vasen alakulma
				PiirraKuva(kuva, naytto, 48, 16, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			
			else if (map[k][i] == 4.8) {
				//Vasen alakulma
				PiirraKuva(kuva, naytto, 80, 16, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
			
			else {
				//Vesi
				PiirraKuva(kuva, naytto, 16, 0, 16, 16, x * 4 - g , f);
				g = g + 16;
			}
		}
         
		g = x;
		f = f + 16;
    
		if (k > leveys - 2) {
			tark = 1;
			break;
		}     
		k++;        
	} while (tark < 1);
	
	

	
	
	
}

void generate_ground_seed(){
	srand(time(NULL));
	cout << "Generating ground seeds.";
	cout << "\n";
	for (int i = 1; i <= ground_seed ; i++) {
		int pi_random = rand() % pituus + 1;
		int le_random = rand() % leveys;
		map[pi_random][le_random] = 1;		
	}
}

void ground_fill(int yht) {
  
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	int l = 0;
	int r = 0;
	int b = 0;
	int v = 1;
	int c = 0;
	int random = 0;
	int kok = 0;
	
	srand(time(NULL));
	cout << "Generating ground level.";
	cout << "\n";	
	
	do {
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 1) {
					random = rand() % 10;
					if (random < ground_level_pro) {
						if (map[k][i - 1] == 2) {
						
						}
						else {
							map[k][i - 1] = 1;
						}	
					}
					random = rand() % 10;
					if (random < ground_level_pro) {
						if (map[k + 1][i] == 2) {
						
						}
						else {
							map[k + 1][i] = 1;
						}	
					}
					random = rand() % 10;
					if (random < ground_level_pro) {
						if (map[k][i + 1] == 2) {
						
						}
						else {
							map[k][i+1] = 1;
						}	
					}
			
					random = rand() % 10;
					if (random < ground_level_pro) {
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
    
	tark = 0;
	k=1;
	
	cout << "Cleaning up ground.";
	cout << "\n";
	
do {
  kok = 0;

	do {
		for (int i = 0; i <= j ; ++i) {
		  
		r = 0;
		b = 0;
		v = 0;
			if (map[k][i] == 0) {
				if (map[k][i - 1] == 2) {
					if (map[k + 1][i] == 2) {
						if (map[k][i + 1] == 2) {	
							if (map[k - 1][i] == 2) {
								map[k][i] = 2;
								kok = 1;
								k = 1;
								r = 0;
							} else if (map[k - 1][i] == 0) { 
								r = r + 1;
								b = k - 1;
								v = i;
							}
						} else if (map[k][i + 1] == 0) { 
							r = r + 1;
							b = k;
							v = i + 1;  
						}  
					} else if (map[k + 1][i] == 0) {
						r = r + 1;
						b = k + 1;
						v = i;	 
					}
				} else if (map[k][i - 1] == 0){
					r = r + 1;
					b = k;
					v = i - 1;
				}
			}
			
			if (r == 1) {
				map[k][v] = 2;  
				if (map[b][v - 1] == 2 && map[b + 1][v] == 2 && map[b][v + 1] == 2 && map[b - 1][v] == 2) {
					map[b][v] = 2;
					kok = 1;
				} else {
					map[k][v] = 0;
				}
			}
		}
		k++;
		if (k > leveys - 2) {
			tark = 1;
			break;
		}
	} while (tark < 1);    
		
	int i = 1;
	tark = 0;
	
	do {
		for (int k = 0; k <= j ; ++k) {
		  
		r = 0;
		b = 0;
		v = 0;
			if (map[k][i] == 0) {
				if (map[k][i - 1] == 2) {
					if (map[k + 1][i] == 2) {
						if (map[k][i + 1] == 2) {
							if (map[k - 1][i] == 2) {
								map[k][i] = 2;
								kok = 1;
								k = 1;
								r = 0;
							} else if (map[k - 1][i] == 0) { 
								r = r + 1;
								b = k - 1;
								v = i;
							}
						} else if (map[k][i + 1] == 0) { 
							r = r + 1;
							b = k;
							v = i + 1;  
						}  
					} else if (map[k + 1][i] == 0) {
						r = r + 1;
						b = k + 1;
						v = i;	 
					}
				} else if (map[k][i - 1] == 0){
					r = r + 1;
					b = k;
					v = i - 1;
				}
			}
			
			if (r == 1) {
				map[b][i] = 2;  
				if (map[b][v - 1] == 2 && map[b + 1][v] == 2 && map[b][v + 1] == 2 && map[b - 1][v] == 2) {
					map[b][v] = 2;
					kok = 1;
				} else {
					map[b][i] = 0;
				}
			}
			
		}
		i++;
		if (i > leveys - 2) {
			tark = 1;
			break;
		}
	} while (tark < 1);   
} while (kok == 1);
}

void clear_map(){
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	
	cout << "Cleaning up old map.";
	cout << "\n";
	
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

void generate_forest_seed() {
  
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	cout << "Generating forest seeds.";
	cout << "\n";
	
	for (int i = 1; i <= forest_seed ; i++) {
		int pi_random = rand() % pituus + 1;
		int le_random = rand() % leveys;
		if (map[pi_random][le_random] == 2){
			map[pi_random][le_random] = 1;	
		}
		else {
			i = 1;
		}	
	}
	

}

void generate_forest() {
  
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	int random = 0;
	int kok = 0;
	
	srand(time(NULL));
	cout << "Generating forest.";
	cout << "\n";
	
	do {
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 1) {
					random = rand() % 10;
					if (random < forest_level_pro) {
						if (map[k][i - 1] == 3) {
						
						}
						else {
							map[k][i - 1] = 1;
						}	
					}
					random = rand() % 10;
					if (random < forest_level_pro) {
						if (map[k + 1][i] == 3) {
						
						}
						else {
							map[k + 1][i] = 1;
						}	
					}
					random = rand() % 10;
					if (random < forest_level_pro) {
						if (map[k][i + 1] == 3) {
						
						}
						else {
							map[k][i+1] = 1;
						}	
					}
			
					random = rand() % 10;
					if (random < forest_level_pro) {
						if (map[k - 1][i] == 3) {
						
						}
						else {
							map[k-1][i] = 1;
						}	
					}		
				map[k][i] = 3;	
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

void generate_shoreline() {
  
	int tark = 0;
	int k = 1;
	int j = pituus -1;
	
	cout << "Generating shorelines.";
	cout << "\n";	
 
	do {
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 2) {

			  
				if (map[k][i - 1] == 0) {
					 //Oikea
					map[k][i] = 4;
				} 
				testi:
				
				if (map[k + 1][i] == 0) {
					//Ala
					map[k][i] = 5;
				} 
				
				if (map[k][i + 1] == 0) {
					//Vasen
					map[k][i] = 6;
				}
				if (map[k - 1][i] == 0) {
					//Ylä
					map[k][i] = 7;
				}
			}
			
			
			
		}
		k++;
		if (k > leveys - 2) {
			tark = 1;
			break;
		}
	} while (tark < 1);    
	
	k = 0;
	
	do {
		for (int i = 0; i <= j ; ++i) {
			if (map[k][i] == 2) {
			 
				if(map[k][i - 1] == 6 && map[k - 1][i] == 5) {
					map[k][i] = 4.5;
				}
				if(map[k][i + 1] == 6 && map[k - 1][i] == 5 ) {
					map[k][i] = 4.6;
				}
				if(map[k][i - 1] == 6 && map[k + 1][i] == 5) {
					map[k][i] = 4.7;
				}
				if(map[k][i + 1] == 6 && map[k + 1][i] == 5) {
					map[k][i] = 4.8;
				}


			}
			
			
		}
		k++;
		if (k > leveys - 2) {
			tark = 1;
			break;
		}
	} while (tark < 1);   	
	
	
	
	
  
}

int main() {
	Ref:
	int mapX = SCREEN_HEIGHT / 3 ,mapY = SCREEN_WIDTH / 100;
	int ground_fill_counter = 4; 
	
	generate_ground_seed();
	ground_fill(ground_fill_counter);
	generate_forest_seed();
	generate_forest();
	generate_shoreline();

	Uint8* nappi;                    
	SDL_Event tapahtuma; 
	
	bool pois=false;
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
		fprintf(stderr, "SDL:n alustus ei onnistunut: %s\n", SDL_GetError()); 
		return 0; // lopetetaan ohjelma
	}

	SDL_Surface *naytto;
	SDL_Surface *kuva;

	naytto = SDL_SetVideoMode(SCREEN_HEIGHT, SCREEN_WIDTH, 30, SDL_HWSURFACE|SDL_DOUBLEBUF);

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
		if ( nappi[SDLK_UP] )  mapY += 4;
		if ( nappi[SDLK_DOWN] )  mapY -= 4;
		if ( nappi[SDLK_LEFT] )  mapX+= 4;
		if ( nappi[SDLK_RIGHT] ) mapX-= 4;      
         
		SDL_Flip(naytto);    
		SDL_Delay(4);
	}
	SDL_Quit(); 	 
}

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy) {
	SDL_Rect kuvaalue; // alue, mikä kuvasta piirretään
	kuvaalue.x = kuvax;
	kuvaalue.y = kuvay;
	kuvaalue.h = korkeus;
	kuvaalue.w = leveys;

	SDL_Rect nayttoalue; // alue näytöllä, jolle kuva piirretään
	nayttoalue.x = nayttox;
	nayttoalue.y = nayttoy;

	SDL_SetColorKey( kuva, SDL_SRCCOLORKEY, SDL_MapRGB(naytto->format, 255, 0, 255) );
	
	SDL_BlitSurface(kuva, &kuvaalue, naytto, &nayttoalue);
}
