#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
using namespace std;


const int C=15;
const int R=15;

const int IMGsize1 = 1;
const int IMGsize2 = 59;

//texture 
void* wallIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* barrierIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* grassIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* doorclosedIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* dooropenIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* keyIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* slimeIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* playerIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* bullIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* playerDamageIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* lifeIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];
void* rangeIMG = new char[imagesize(IMGsize1, IMGsize1, IMGsize2, IMGsize2)];


//prototipi funzioni per il gioco
void showGrid(int v[R][C]);
void upGrid(int v[R][C], int l[R][C], int b=2, bool rel=false);
void allMoves(int v[R][C], int m, int &x, int &y, int id, int &l, int &r);
bool playerDie(int v[R][C]);
bool entityDie(int v[R][C], int id);
void linearEnemy(int ev[R][C], int &ex, int &ey, bool &dir, int id=-20 );
void verticalEnemy(int ev[R][C], int &ex, int &ey, bool &dir, int id=-20);
void mapWorld1(int v[R][C], int px, int py);
void drawBomb (int x, int y, int show=3);	
void explode (int v[R][C], int x, int y, int r);
void copyVector(int v[R][C], int l[R][C]);
void enemyArea(int ey, int ex, int id, int v[R][C], int type);
void genItems(int v[R][C], int &x, int &y, int probability, int id);
void genEnemy(int ev[], int v[R][C], int n, int id);
void readBMP(char* filename);
void bullMove(int bv[R][C], int &bx, int &by, int px, int py, bool &d, int id);
void cleanBomb(int v[R][C], int x, int y, int r);
void spawnUp(int v[R][C], int c[R][C]);

//menu
void centerButton(int x, int y, int sizeX, int sizeY, int r, int g, int b,  char text[], int br , int bg , int bb );

void centerButton(int x, int y, int sizeX, int sizeY, int r, int g, int b,  char text[], int br , int bg , int bb){
	
	setcolor(COLOR(r,g,b));
	rectangle(x-sizeX, y-sizeY, x+sizeX, y+sizeY);
	settextjustify(1,1);
	setcolor(COLOR(r,g,b));
	settextstyle(3,0,5);
	setbkcolor(COLOR(br,bg,bb));
	outtextxy(x, y, text);
	
}

void spawnUp(int v[R][C], int c[R][C]){

	srand(time(0));
//power Up 300 - 301;	
	int powerUp;
	
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			
			if(v[i][j] == 0 && c[i][j] == 1){
				
				powerUp = rand()%100;
				
				if(powerUp <= 5){
					v[i][j] = 300;
				}
				
				else if(powerUp > 5 && powerUp <= 20){
					v[i][j] = 301;
				}
				
				
			}
		}
	}
}

//bomb explosion
void cleanBomb(int v[R][C], int x, int y, int r){
	//explode X 
	for(int i=x; i<=x+r; i++){
		
		if(v[y][i] == 7 || v[y][i]==69 || v[y][i]==68){
			break;
		}
		
		else if(v[y][i]!=7 && v[y][i]!=69 && v[y][i]!=68){
			v[y][i]=0;
			
			if( x != i ){
				setcolor(COLOR(0,143,57));	
				rectangle(i * 60, y * 60, i * 60 + 60, y * 60 +60);
				setfillstyle(1,COLOR(0,143,57));
				floodfill(i * 60 + 30, y * 60 + 30, COLOR(0,143,57));					
			}

		}

	}
	
	for(int i=x; i>=x-r; i--){
		
		if(v[y][i] == 7 || v[y][i]==69 || v[y][i]==68){
			break;
		}
		
		else if(v[y][i]!=7 && v[y][i]!=69 && v[y][i]!=68){
			v[y][i]=0;
			
			if( x != i ){
				setcolor(COLOR(0,143,57));	
				rectangle(i * 60, y * 60, i * 60 + 60, y * 60 +60);
				setfillstyle(1,COLOR(0,143,57));
				floodfill(i * 60 + 30, y * 60 + 30, COLOR(0,143,57));				
			}

		}
		
		
	}	
	
	
	
	//explode Y
	for(int i=y; i<=y+r; i++){
		
		if(v[i][x] == 7 || v[i][x]==69 || v[i][x]==68){
			break;
		}
		
		else if(v[i][x]!=7 && v[i][x]!=69 && v[i][x]!=68){
			v[i][x]=0;
			
			if(y != i){
				setcolor(COLOR(0,143,57));
				rectangle(x * 60, i * 60, x * 60 + 60, i * 60 +60);
				setfillstyle(1,COLOR(0,143,57));
				floodfill(x * 60 + 30, i * 60 + 30, COLOR(0,143,57));					
			}	

		}

	}
	
	for(int i=y; i>=y-r; i--){
		if(v[i][x] == 7 || v[i][x]==69 || v[i][x]==68){
			break;
		}
		
		else if(v[i][x]!=7 && v[i][x]!=69 && v[i][x]!=68){
			v[i][x]=0;
			
			if(y != i){
				setcolor(COLOR(0,143,57));
				rectangle(x * 60, i * 60, x * 60 + 60, i * 60 +60);
				setfillstyle(1,COLOR(0,143,57));
				floodfill(x * 60 + 30, i * 60 + 30, COLOR(0,143,57));					
			}	

		}
	}
	
	
	
}

void explode (int v[R][C], int x, int y, int r){
	
	//explode X
	for(int i=x; i<=x+r; i++){
		
		if(v[y][i] == 7 || v[y][i]==69 || v[y][i]==68){
			break;
		}

		
		else if(v[y][i]!=7 && v[y][i]!=69 && v[y][i]!=68){
			
			
			if( x != i ){
				setcolor(COLOR(255,255,0));	
				circle(i * 60 + 30, y * 60 + 30, 20);
				setfillstyle(1,COLOR(255,255,0));
				floodfill(i * 60 + 30, y * 60 + 30, COLOR(255,255,0));					
			}

		}

	}

	for(int i=x; i>=x-r; i--){
		
		if(v[y][i] == 7 || v[y][i]==69 || v[y][i]==68){
			break;
		}
		
		else if(v[y][i]!=7 && v[y][i]!=69 && v[y][i]!=68){
			
			if( x != i ){
				setcolor(COLOR(255,255,0));	
				circle(i * 60 + 30, y * 60 + 30, 20);
				setfillstyle(1,COLOR(255,255,0));
				floodfill(i * 60 + 30, y * 60 + 30, COLOR(255,255,0));					
			}

		}
		
		
	}
	
	
	
	
	//explode Y
	for(int i=y; i<=y+r; i++){
		
		if(v[i][x] == 7 || v[i][x]==69 || v[i][x]==68){
			break;
		}
		
		else if(v[i][x]!=7 && v[i][x]!=69 && v[i][x]!=68){
			
			if(y != i){
				setcolor(COLOR(255,255,0));
				circle(x * 60 + 30, i * 60 + 30, 20);
				setfillstyle(1,COLOR(255,255,0));
				floodfill(x * 60 + 30, i * 60 + 30, COLOR(255,255,0));			
			}	

		}

	}
	
	for(int i=y; i>=y-r; i--){
		if(v[i][x] == 7 || v[i][x]==69 || v[i][x]==68){
			break;
		}
		
		else if(v[i][x]!=7 && v[i][x]!=69 && v[i][x]!=68){
			
			if(y != i){
				setcolor(COLOR(255,255,0));
				circle(x * 60 + 30, i * 60 + 30, 20);
				setfillstyle(1,COLOR(255,255,0));
				floodfill(x * 60 + 30, i * 60 + 30, COLOR(255,255,0));					
			}	

		}
	}	
	
}

void genEnemy(int ev[], int v[R][C], int n, int id){
	
	int x = rand()%(C-2)+1;
	int y = rand()%(R-2)+1;
	
	cout<<x<<endl;
	cout<<y<<endl;
	bool found=false;
	do{
		x = rand()%(C-2)+1;
		y = rand()%(R-2)+1;
			
		if(v[y][x]==0 && y % 2 == 1 && x % 2 == 1 && y > 4){
			v[y][x]=id;
			ev[n+1] = x;
			ev[n] = y;
			found = true;
		}
			
	}while(found == false);
	
}


void genItems(int v[R][C], int &x, int &y, int probability, int id){
	
	int random;
	
	random=rand()%101;
	
	if(random <= probability){
		bool found=false;
		do{
			x = rand()%(C-2)+1;
			y = rand()%(R-2)+1;
			
			if(v[y][x]==1 && y >= 4){
				v[y][x]	= id;
				found = true;
			}
			
		}while(found == false);
	}
	
}



void enemyArea(int ey, int ex, int id, int v[R][C], int type){
	
	int range= 5; //rand()%5+3, 
	int start= 5; //rand()%3+1;
	
	if(type==0){

		for(int i=ex-start; i<(ex-start)+range; i++){
			if(v[ey][i]!=id && v[ey][i]!=7 && (!(v[ey][i]<=-20 && v[ey][i]>=-30)) && v[ey][i] != 71 && v[ey][i] != 69){
				v[ey][i]=0;
			}
		}	
	}
	
	else if(type==1){
		
		for(int i=ey-start; i<(ey-start)+range; i++){
			if(v[i][ex]!=id && v[i][ex]!=7 && (!(v[ey][i]<=-20 && v[ey][i]>=-30)) && v[ey][i] != 71 && v[ey][i] != 69){
				v[i][ex]=0;
			}
		}
	}

	
	
	
}


void copyVector(int v[R][C], int l[R][C]){
	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
			l[i][k] = v[i][k];

		}
	}
}




void drawBomb (int x, int y, int show){
	
	char t[2]={0,'\0'};
	int r;
	

	//bomb
	
	if(show!=1){
		r=10;
	}
	
	else{
		r=255;
	}
	
	setcolor(COLOR(r,0,0));
	circle(x-((C*60)/C)/2, y-((R*60)/R)/2, 20);
	setfillstyle(1,COLOR(r,0,0));
	floodfill(x-((C*60)/C)/2, y-((R*60)/R)/2,COLOR(r,0,0));
	
	rectangle(x-((C*60)/C)/2+5,y-((R*60)/R)+20, x-((C*60)/C)/2-5, y-((R*60)/R)+5 );
	
	floodfill(x-((C*60)/C)/2+3, y-((R*60)/R)/2-20,COLOR(r,0,0));
	
	setcolor(COLOR(255,255,255));
	
	setlinestyle(0,0,3);
	
	arc(x-((C*60)/C)/2, y-((R*60)/R)/2, -20, 55,15 );
	


	itoa(show,t,10);
	settextstyle(3,0,3);
	settextjustify(1,1);
	setbkcolor(COLOR(r,0,0));
	outtextxy(x-((C*60)/C)/2, y-((R*45)/R)/2, t);
	
	setlinestyle(0,0,1);
	

}

void mapWorld1(int v[R][C], int px, int py){
	
	srand(time(0));
	int area=1;
	int counter=0;
	
	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
				if(i==0 || k==0 || k==C-1 || i==R-1 || i % 2 == 0 && k % 2 == 0){
					//muri Indistruttibili
					v[i][k]=7;
				}
				
				else if(counter<=12){ //<=12
					//muri
					v[i][k]=rand()%2;
					if(v[i][k]==1){
						counter++;						
					}
			
				}
				
				else{
					v[i][k]=0;
				}
					
			
		}
		counter=0;
	}
	

	
	//area generator
	
	//start area
	area=rand()%2;
	
	//rectangle 3x2
	if(area==0){
		if(px==R/2 && py==1){
			for(int i=py; i<py+2; i++){
				for(int k=px-1; k<px+2; k++){
					if(i==py && k==px){
						v[i][k]=9;	
					}
					
					else{
						v[i][k]=0;	
					}
	
				}
					
				
			}
		}
		
				
		else{
			v[py][px]=9;
		}
	}
	
	// T area
	else if(area==1){
		if(px==R/2 && py==1){
			for(int k=px-1; k<px+2; k++){
				if(k==px){
					v[py][k]=9;					
				}
				
				else{
					v[py][k]=0;				
				}
			}
			
			for(int i=py+1; i<py+3; i++){
				v[i][px]=0;
			}
		}
		
		else{
			v[py][px]=9;
		}
		
	}	
}


void showGrid(int v[R][C]){
	
	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
			cout<<" "<<v[i][k];
		}
		cout<<endl;
	}
}

void upGrid(int v[R][C], int l[R][C], int b, bool rel){
	int x=0, y=0;
	int xf=60, yf=60;
	int addx=60, addy=60;

	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
		
			if(v[i][k]!=l[i][k]){
				//grass
				if(v[i][k]==0){
					setcolor(COLOR(0,143,57));
					setfillstyle(1,COLOR(0,143,57));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,143,57));	
				}
				
				//door
				else if(v[i][k]==69){
					/*setcolor(COLOR(255,0,255));
					setfillstyle(1,COLOR(255,0,255));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,0,255));*/
					putimage(x, y, doorclosedIMG, COPY_PUT);	
				}
				
				else if(v[i][k]==68){
					/*setcolor(COLOR(161,161,161));
					setfillstyle(1,COLOR(161,161,161));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(161,161,161));*/
					putimage(x, y, dooropenIMG, COPY_PUT);	
				}
				
				//key
				else if(v[i][k]==70){
					/*setcolor(COLOR(0,255,255));
					setfillstyle(1,COLOR(0,255,255));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,255,255));*/
					putimage(x, y, keyIMG, COPY_PUT);					
				}
				
				//border
				else if(v[i][k]==7){
					
					
					/*setcolor(COLOR(255,0,0));
					setfillstyle(1,COLOR(255,0,0));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,0,0));*/	
					putimage(x, y, barrierIMG, COPY_PUT);
				}
				
				//walls
				else if(v[i][k]==1 || v[i][k]==71){
					/*setcolor(COLOR(255,255,0));
					setfillstyle(1,COLOR(255,255,0));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,255,0));*/
					putimage(x, y, wallIMG, COPY_PUT);	
				}
				
				//player
				else if(v[i][k]==9 || v[i][k]==11){
					/*setcolor(COLOR(0,0,255));
					setfillstyle(1,COLOR(0,0,255));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,0,255));*/
					putimage(x, y, playerIMG, COPY_PUT);					
				}
				
				else if(v[i][k]==10){
					putimage(x, y, playerDamageIMG, COPY_PUT);
				}
				
				//slime enemy
				else if(v[i][k]<=-20 && v[i][k]>=-30 ){
					/*setcolor(COLOR(255,0,127));
					setfillstyle(1,COLOR(255,0,127));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,0,127));*/
					putimage(x, y, slimeIMG, COPY_PUT);	
				}
				
				//bull enemy
				else if(v[i][k]<=-31 && v[i][k]>=-35 ){
					/*setcolor(COLOR(255,0,127));
					setfillstyle(1,COLOR(255,0,127));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,0,127));*/
					putimage(x, y, bullIMG, COPY_PUT);	
				}
				
				//life
				else if(v[i][k]==300){
					/*setcolor(COLOR(255,0,0));
					setfillstyle(1,COLOR(255,0,0));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(255,0,0));*/
					putimage(x, y, lifeIMG, COPY_PUT);
				}
				
				//range
				else if(v[i][k]==301){
					/*setcolor(COLOR(0,0,0));
					setfillstyle(1,COLOR(0,0,0));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,0,0));*/
					putimage(x, y, rangeIMG, COPY_PUT);
				}

			}
			
			if(rel==true){
				//bomb
				
				//bomb Player
				if(v[i][k]==-4){
					/*setcolor(COLOR(0,0,255));
					setfillstyle(1,COLOR(0,0,255));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,0,255));*/
					
					
				
					putimage(x, y, playerIMG, COPY_PUT);		
					drawBomb(xf,yf,b);				
						
				}
				
				else if(v[i][k]==-3){
					
					
					setcolor(COLOR(0,143,57));
					setfillstyle(1,COLOR(0,143,57));
					rectangle(x,y,xf,yf);
					floodfill(xf-20,yf-20,COLOR(0,143,57));	
					
					
					drawBomb(xf,yf,b);	
				}
					

				
				
			}
				
			
			

			x=xf;
			xf+=addx;		
		}	
		x=0;
		xf=(C*60)/C;
		
		y=yf;
		yf+=addy;
		
			
	}
}

void allMoves(int v[R][C], int m, int &x, int &y, int id, int &l, int &r){

		//input s
		if(m==115 && (v[y+1][x]==0 || v[y+1][x]==70 || v[y+1][x]==68 || v[y+1][x]==300 || v[y+1][x]==301)){
			
			if(v[y+1][x]==300){
				l++;
			}
			
			else if(v[y+1][x]==301){
				r++;
			}
			
			v[y][x]=0;
			y++;
			v[y][x]=id;
		}
		
		//input w
		else if(m==119 && (v[y-1][x]==0 || v[y-1][x]==70 || v[y-1][x]==68 || v[y-1][x]==300 || v[y-1][x]==301)){
			
			if(v[y-1][x]==300){
				l++;
			}
			
			else if(v[y-1][x]==301){
				r++;
			}
			
			v[y][x]=0;
			y--;
			v[y][x]=id;
		}
		
		//input a
		else if(m==97 && (v[y][x-1]==0 || v[y][x-1]==70 || v[y][x-1]==68 || v[y][x-1]==300 || v[y][x-1]==301)){
			
			if(v[y][x-1]==300){
				l++;
			}

			else if(v[y][x-1]==301){
				r++;
			}	
					
			v[y][x]=0;
			x--;
			v[y][x]=id;			
		}
		
		//input d
		else if(m==100 && (v[y][x+1]==0 || v[y][x+1]==70 || v[y][x+1]==68 || v[y][x+1]==300 || v[y][x+1]==301)){

			if(v[y][x+1]==300){
				l++;
			}
			
			else if(v[y][x+1]==301){
				r++;
			}
			
			v[y][x]=0;
			x++;
			v[y][x]=id;			
		}
		
		//input bomb
		else if(m==32){
			v[y][x]=-4;
		}
		
		
}


bool playerDie(int v[R][C]){
	
	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
			if(v[i][k]==9 || v[i][k]==-4 || v[i][k]==10 || v[i][k]==11){
				return true;
			}
		}
	}
	
	return false;
}



bool entityDie(int v[R][C], int id){
	
	for(int i=0; i<R; i++){
		for(int k=0; k<C; k++){
			if(v[i][k]==id){
				return true;
			}
		}
	}
	
	return false;
}

//slime
void linearEnemy(int ev[R][C], int &ex, int &ey, bool &dir, int id){

	if(dir==true){	
		if(ev[ey][ex+1]==0 || ev[ey][ex+1]==9){
			ev[ey][ex]=0;
			ex++;
			ev[ey][ex]=id;	
		}
		
		else{
			dir=false;
		}
	
	}
	
	else{
		if(ev[ey][ex-1]==0 || ev[ey][ex-1]==9){
			ev[ey][ex]=0;
			ex--;
			ev[ey][ex]=id;	
		}
		
		else{
			dir=true;
		}
	}
	

}

void verticalEnemy(int ev[R][C], int &ex, int &ey, bool &dir, int id){
	
	if(dir==true){	
		if(ev[ey+1][ex]==0 || ev[ey+1][ex]==9){
			ev[ey][ex]=0;
			ey++;
			ev[ey][ex]=id;	
		}
		
		else{
			dir=false;
		}
	}
	
	else{
		if(ev[ey-1][ex]==0 || ev[ey-1][ex]==9){
			ev[ey][ex]=0;
			ey--;
			ev[ey][ex]=id;	
		}
		
		else{
			dir=true;
		}
	}

}

void bullMove(int bv[R][C], int &bx, int &by, int px, int py, bool &d, int id){
	
	if(px != bx && d == 0){
		bv[by][bx]=0;
		if(px > bx && (bv[by][bx+1] == 0 ||  bv[by][bx+1] == 1 ||  bv[by][bx+1] == 9)){
			bx++;	
		}
		
		else if(bv[by][bx-1] == 0 ||  bv[by][bx-1] == 1 ||  bv[by][bx-1] == 9){
			bx--;
		}
		
		else if(bv[by+1][bx] != 7 ){
			by++;
		}

		bv[by][bx]=id;
		
		if(bx == px){
			d = 1;
		}
		
	}
	
	else{
		bv[by][bx]=0;
		if(py > by && (bv[by+1][bx] == 0 ||  bv[by+1][bx] == 1 ||  bv[by+1][bx] == 9)){
			by++;	
		}
		
		else if(bv[by-1][bx] == 0 ||  bv[by-1][bx] == 1 ||  bv[by-1][bx] == 9){
			by--;
		}
		
		else if(bv[by][bx-1] != 7 ){
			bx--;
		}

		bv[by][bx]=id;
		if(by == py){
			d = 0;
		}
	}
}

//images
void readBMP(char* filename)
{
    int i;
    FILE* f = fopen(filename, "rb");
    unsigned char info[54];

    // read the 54-byte header
    fread(info, sizeof(unsigned char), 54, f);

    // extract image height and width from header
    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
        std::cout<<width<<" x "<<height<<std::endl;
    // allocate 3 bytes per pixel
    int size = 3 * width * height;
    int off=0;
        int of=0;
        if ((width*3+of)%4!=0) of=2;
        size+=of*height;
   
    unsigned char* data = new unsigned char[size];
       

    // read the rest of the data at once
    fread(data, sizeof(unsigned char), size, f);  //devo leggere anche gli spazi tra una riga %8 e l'altra
    fclose(f);
   
       
        std::cout<<of<<" offset "<<std::endl;
        for(int y = 0; y < height; y ++){
             for(int x = 0; x < width; x ++){
                        putpixel(x,height-y,COLOR((int)data[y*width*3+x*3+off+2],(int)data[y*width*3+x*3+1+off],(int)data[y*width*3+x*3+off]));
                 }
                off+=of;
        }
}

