#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include "bomberman.h"

using namespace std;
using std::chrono::system_clock;
using std::chrono::steady_clock;
using namespace std::chrono;

const int COL=15;
const int ROW=15;
const int HUD=450;

const int IMGs1 = 1;
const int IMGs2 = 59;

//variable stats of player
int playerLife = 3;
int bombRange = 2;
int numLevel = 1;



int main(){

	char lifeTxt[2], rangeTxt[2];
	int bombUpdated = bombRange;

	itoa(playerLife, lifeTxt, 10);
	itoa(bombRange, rangeTxt, 10);
	
	srand(time(0));
	initwindow(COL*60 + HUD, ROW*60);
	
	void* logoIMG = new char[imagesize(1, 1, 590, 250)];
	//logo
	readBMP("sprites/logobomberman.bmp");
	getimage(1, 1, 590, 250, logoIMG);
	
	//sprites
	
	//wall
	readBMP("sprites/wall.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, wallIMG);
	
	//barriers
	readBMP("sprites/Barriers.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, barrierIMG);
	
	//grass
	readBMP("sprites/grass.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, grassIMG);
	
	//doorclosed
	readBMP("sprites/doorclosed.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, doorclosedIMG);
	
	//doorclosed
	readBMP("sprites/doorOpen.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, dooropenIMG);
	
	//slime
	readBMP("sprites/slime.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, slimeIMG);
	
	//player
	readBMP("sprites/player.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, playerIMG);
	
	//bull
	readBMP("sprites/bull.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, bullIMG);
	
	//key
	readBMP("sprites/key.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, keyIMG);
	
	//player damage
	readBMP("sprites/playerlife.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, playerDamageIMG);
	
	//lifeUp
	readBMP("sprites/life.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, lifeIMG);
	
	//rangeUp
	readBMP("sprites/bombrange.bmp");
	getimage(IMGs1, IMGs1, IMGs2, IMGs2, rangeIMG);
	
	cleardevice();
	
	//menu
	
	int button = 0;
	bool start = false, options = false;
	
	int xm, ym;
	
	POINT CursorPosition;
	do{
		
		
		setcolor(COLOR(255,0,0));
		rectangle(0,0,getmaxx(),getmaxy());
		setfillstyle(1,COLOR(255,0,0));
		floodfill(10,10,COLOR(255,0,0));	
		setcolor(COLOR(255,255,255));
		
		putimage(getmaxx()/2 - 300, 20, logoIMG, COPY_PUT);
		
		centerButton(getmaxx()/2, getmaxy()/2 - 100, 100,50,255,255,255,"Start", 255, 0, 0);
		
		centerButton(getmaxx()/2, getmaxy()/2 + 50, 100,50,255,255,255,"Settings", 255, 0, 0);
		
		GetCursorPos(&CursorPosition);
        
        if((CursorPosition.x > getmaxx()/2 - 100 && CursorPosition.x < getmaxx()/2 + 100) && (CursorPosition.y > getmaxy()/2 - 100 -50 && CursorPosition.y < getmaxy()/2 - 100 + 90) )
        {
        	centerButton(getmaxx()/2, getmaxy()/2 - 100, 100,50,255,255,0,"Start",255,0,0);
        	
        	
        	if(ismouseclick(WM_LBUTTONDOWN)){
        		start = true;
			}
		}
		
		else if((CursorPosition.x > getmaxx()/2 - 100 && CursorPosition.x < getmaxx()/2 + 100) && (CursorPosition.y > getmaxy()/2 + 30  && CursorPosition.y < getmaxy()/2 + 135 ))
		{
			centerButton(getmaxx()/2, getmaxy()/2 + 50, 100,50,255,255,0,"Settings",255,0,0);
			
			if(ismouseclick(WM_LBUTTONDOWN)){
        		options = true;
        		button = 200;
        		
        		if(options == true){
        			clearmouseclick(WM_LBUTTONDOWN);
        			cleardevice();
				}
        		
        		do{
        			
        			int n = 150;
        			setcolor(COLOR(255,255,0));
					rectangle(0,0,getmaxx(),getmaxy());
					setfillstyle(1,COLOR(255,255,0));
					floodfill(10,10,COLOR(255,255,0));	
					setcolor(COLOR(255,255,0));
					
					setcolor(COLOR(0,0,0));
					setbkcolor(COLOR(255,255,0));
					
					
					settextjustify(1,1);
					outtextxy(getmaxx()/2, 100, "Settings Menu: ");
					
					settextjustify(0,2);
					
					
					
					outtextxy(200, 300, "Start Life (3 / 4 / 5): ");
					outtextxy(850, 300, lifeTxt);
					
					outtextxy(200, 400, "Start Bomb Range (2 / 3 / 4): ");
					outtextxy(850, 400, rangeTxt);
					
					while(button != 13){
						
						do{
							
							setcolor(COLOR(0,0,255));
							outtextxy(200, 300, "Start Life (3 / 4 / 5): ");
							outtextxy(850, 300, lifeTxt);
							
							button = getch();
							
							if(button >= 51 && button <= 53){
								playerLife = button - 48;
								itoa(playerLife, lifeTxt, 10);
							}
						
						}while(button != 13);
						
						setcolor(COLOR(0,0,0));
						outtextxy(200, 300, "Start Life (3 / 4 / 5): ");
						outtextxy(850, 300, lifeTxt);
							
						do{
						
							setcolor(COLOR(0,0,255));
							outtextxy(200, 400, "Start Bomb Range (2 / 3 / 4): ");
							outtextxy(850, 400, rangeTxt);
							
							button = getch();
							
							if(button >= 50 && button <= 52){
								bombRange = button - 48;
								bombUpdated = bombRange;
								itoa(bombRange, rangeTxt, 10);
							}
							
						
						}while(button!=13);
					}
					
					setcolor(COLOR(0,0,0));
					outtextxy(200, 300, "Start Life (3 / 4 / 5): ");
					outtextxy(850, 300, lifeTxt);
					
					
					
					setcolor(COLOR(0,0,0));
					outtextxy(200, 400, "Start Bomb Range (2 / 3 / 4): ");
					outtextxy(850, 400, rangeTxt);
					
					centerButton(getmaxx()/2, getmaxy()/2 + n, 100,50,0,0,0,"Exit", 255, 255, 0);
					
					button = 13;
					
					GetCursorPos(&CursorPosition);
					if((CursorPosition.x > getmaxx()/2 - n +50 && CursorPosition.x < getmaxx()/2 + n - 50) && (CursorPosition.y > getmaxy()/2 + n -30 && CursorPosition.y < getmaxy()/2 + n + 90  ))
        			{	
        				centerButton(getmaxx()/2, getmaxy()/2 + n, 100,50,0,0,255,"Exit", 255, 255, 0);
        				
        				
        				
        				if(ismouseclick(WM_LBUTTONDOWN)){
        					options = false;
        					clearmouseclick(WM_LBUTTONDOWN);
        				}
					}
					
					else{
						clearmouseclick(WM_LBUTTONDOWN);
					}
				
        			delay(20);
				}while(options != false);
			}
		}
		
		else{
			clearmouseclick(WM_LBUTTONDOWN);
		}
		
		delay(20);
		
		
	}while(start != true);
	
	setbkcolor(COLOR(0,0,0));
	cleardevice();
	

	
	int grid[ROW][COL];
	int control[ROW][COL];
	int controlBomb=100;
	
	//partita
	bool partita=true;
	
	while(partita==true){
		
		for(int i=0; i<R; i++){
			for(int k=0; k<C; k++){
				control[i][k]=200;
			}
		}
		
		//player input 
		
		int start; 
		start=0;
		
		int playerX, playerY;
		
		int playerStatus = 9;
		
		
		playerX=ROW/2;
		playerY=1;

		grid[playerY][playerX]= playerStatus;
		int movePlayer;
		
		//player damage time set
		int damagemill = 2000; 
		auto damaget1 = steady_clock::now();
		auto damaget2 = damaget1+chrono::milliseconds(damagemill);
		
		chrono::steady_clock::duration damageTimer =  damaget2 - damaget1;
		
		
		
		//map generator
		mapWorld1(grid, playerX, playerY);
		
		//gen  door 69
		int xDoor = (rand()%(COL-2)) + 1, yDoor = (rand()%(ROW-6)) + 5;
		grid[yDoor][xDoor]=69;
		
		
		//enemy	
		
		//slime id from -20 to -30 
		int nEnemy= rand()%3+3;
		int typeMove[nEnemy];
	
		bool direction[nEnemy], lifeEnemy[nEnemy];
		
		//odd = x even = y
		int enemyPos[60];
		
		int addId;
		
		for(int i=0, k=0; i<nEnemy; i++ , k+=2){
			
			//direction
			direction[i]=rand()%2;
			
			genEnemy(enemyPos, grid, k, -20 - i);

			//life
			lifeEnemy[i]=1;
			//move
			typeMove[i]=rand()%2;

			//gen area
			enemyArea(enemyPos[k], enemyPos[k+1], (-20-i), grid, typeMove[i]);

		}
		
		//bull id -31 -35
		
		int bullNum = rand()%3;
		bool bullDir[bullNum];
		int bullPos[bullNum*2];
		bool bullLife[bullNum];
		
		for(int i = 0, k = 0; i < bullNum; i++, k+=2){
			bullDir[i] = rand()%2;
			bullLife[i] = 1;
			
			genEnemy(bullPos, grid, k, -31 - i);
			
		}
		
		
		
		int bullmill = 350; 
		auto bullt1 = steady_clock::now();
		auto bullt2 = bullt1+chrono::milliseconds(bullmill);
		
		
		
		//gen key 71
		int xKey, yKey, keys = 0;
		genItems(grid, xKey, yKey, 100, 71);
		
		//show Map
		showGrid(grid);
	

		
		//bomb

		int bombX, bombY, nBomb=1;
		bool bombInGrid=false;
	
		//draw grid
		upGrid(grid, control);
		copyVector(grid,control);
	
		showGrid(control);
		
		//time match
		int matchTime = 150000;
		
		auto realTime = steady_clock::now();
		auto endTime = realTime+chrono::milliseconds(matchTime);
		chrono::steady_clock::duration matchTimer =  endTime - realTime;
		
		int min = matchTime/60000;
		int second = (matchTime/600 - min*100) * 0.6;
		
		//HUD
		setcolor(COLOR(0,255,0));
		rectangle(getmaxx()-HUD,0,getmaxx(), getmaxy());
		setfillstyle(1,COLOR(0,255,0));
		floodfill(getmaxx()-HUD + 20,50,COLOR(0,255,0));
		
		//HUD text
		settextjustify(0,2);
		setcolor(COLOR(0,0,0));
		settextstyle(3,0,4);
		setbkcolor(COLOR(0,255,0));
		
		
		char keysTxt[2], levelTxt[100], minTxt[3], secondTxt[3];
		itoa(playerLife, lifeTxt, 10);
		itoa(bombRange, rangeTxt, 10);
		itoa(keys, keysTxt, 10);
		itoa(numLevel, levelTxt, 10);
		itoa(min, minTxt, 10);
		itoa(second, secondTxt, 10);
		
		outtextxy(getmaxx() - HUD/2 -125, getmaxy()/10,"Time: ");
		setbkcolor(COLOR(0,0,0));
		setcolor(COLOR(255,255,255));
		outtextxy(getmaxx() - HUD/2 +85, getmaxy()/10, minTxt);
		outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10, secondTxt);
		
		setcolor(COLOR(0,0,0));
		setbkcolor(COLOR(0,255,0));
		outtextxy(getmaxx() - HUD/2 -125, getmaxy()/10 * 2,"Life: ");
		outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10 * 2, lifeTxt);
		
		outtextxy(getmaxx() - HUD/2 -125, getmaxy()/10 * 3,"Bomb-Range: ");
		outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10 * 3, rangeTxt);
		
		outtextxy(getmaxx() - HUD/2 -125, getmaxy()/10 * 4,"Keys: ");
		outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10 * 4, keysTxt);
		
		outtextxy(getmaxx() - HUD/2 -125, getmaxy()/10 * 9,"Level: ");
		outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10 * 9, levelTxt);
		
		


		
		//time Bomb
		int mill = 250;
		 
		auto t1 = steady_clock::now();	//prende tempo attuale
		auto t2 = t1+chrono::milliseconds(mill);		//aggiunge all'ora attuale il tempo del tick ci sono dei millesimi di scarto
		
		
		int bombT=3000;
		auto timerStart = steady_clock::now();
		auto timerEnd = timerStart+chrono::milliseconds(bombT);
		
		int bombShowTime;
		
		bool level = true;
		
		int removeTime, controlSecond = -300;
		
		//explosion
		bool explodeinGrid = false;
		
		int explodeMill = 200;
		auto explosionStart = steady_clock::now();
		auto explosionEnd = timerStart+chrono::milliseconds(explodeMill);
		
		//life and range control
		
		int lifeUp = playerLife;
		int rangeUp = bombRange;
	
		showGrid(grid);
		while(level==true){
			
			//update match Time
			
			settextjustify(0,2);
			setcolor(COLOR(0,0,0));
			settextstyle(3,0,4);
			setbkcolor(COLOR(0,0,0));
			
			auto realTime = steady_clock::now();
			chrono::steady_clock::duration matchTimer =   endTime - realTime;
			
			removeTime = matchTimer.count()/1000000000;
			
			if(controlSecond != removeTime){
				controlSecond = removeTime;
				second--;
				if(second == -1){
					min--;
					second = 59;
				}
				

			}
			
			itoa(second, secondTxt, 10);
			itoa(min, minTxt, 10);
			
			setcolor(COLOR(255,255,255));
			outtextxy(getmaxx() - HUD/2 +85, getmaxy()/10, minTxt);
			
			if(second < 10){
				outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10, "0");
				outtextxy(getmaxx() - HUD/2 +143, getmaxy()/10, secondTxt);
			}
			else{
				outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10, secondTxt);
			}
			
			//bomb 
			if(nBomb==0){
				
				chrono::steady_clock::duration timer = timerEnd - timerStart;
				
				bombShowTime = timer.count()/1000000000;
				bombShowTime++;
				
				
					
				if(timer <= chrono::steady_clock::duration::zero() && explodeinGrid == false){
					explode (grid, bombX,  bombY,  bombRange);
					
					explosionStart = steady_clock::now();
					explosionEnd = timerStart+chrono::milliseconds(explodeMill);
					
					explodeinGrid = true;
				}
				
				else if(explodeinGrid == true){
					
					chrono::steady_clock::duration explosion = explosionEnd - explosionStart;
					
					if(explosion <= chrono::steady_clock::duration::zero()){
						cleanBomb(grid, bombX,  bombY,  bombRange);
						grid[bombY][bombX]=0;
						nBomb++;
						bombInGrid=false;
						explodeinGrid = false;
					}
					
					else{
						explosionStart = steady_clock::now();
					}										

				}
					
				else{
					timerStart = steady_clock::now();
				}	
	
			}
			
	
			
			if(kbhit()){
				
				movePlayer=getch();
				//script bomb positioning
				if(movePlayer==32){		
					if(nBomb>0){
						allMoves(grid, movePlayer, playerX, playerY, playerStatus, playerLife, bombRange);
						bombX=playerX;
						bombY=playerY;
						timerStart = steady_clock::now();
						timerEnd = timerStart+chrono::milliseconds(bombT);
						nBomb--;
						bombInGrid=true;
					}
				}
				
				
				else{			
					//input player WASD s=115	w=119	a=97	d=100
					allMoves(grid, movePlayer, playerX, playerY, playerStatus, playerLife, bombRange);	
				}
		
				//bomb without player
				if(bombInGrid==true && (playerX!=bombX || playerY!=bombY)){
					grid[bombY][bombX]=-3;
				}
				
				//update grid bomb without player
				if(bombInGrid==true && (playerX!=bombX || playerY!=bombY)){
					controlBomb = bombShowTime;
					upGrid(grid, control, bombShowTime,true);
				}
			}
			
			//update grid bomb with player
			else if(bombInGrid==true ){
				
				if((playerX==bombX && playerY==bombY)){
					grid[bombY][bombX]=-4;					
				}

				if(controlBomb != bombShowTime){
					controlBomb = bombShowTime;
					upGrid(grid, control, bombShowTime,true);
				}
			}
			
			chrono::steady_clock::duration d = t2-t1;	//calcola la differenza di tempo
			
			//slime enemy moveset
			if(d <= chrono::steady_clock::duration::zero()){
				//input enemy
				
				
				for(int i=0; i<nEnemy; i++){
					if(lifeEnemy[i]==true){
						if(typeMove[i]==0){
							linearEnemy(grid, enemyPos[i*2+1], enemyPos[i*2],	direction[i],(-20-i));	
						}
						
						else if(typeMove[i]==1){
							verticalEnemy(grid, enemyPos[i*2+1], enemyPos[i*2],	direction[i],(-20-i));
						}
		
					}
				}
				
	
	
	
				
				t1 = steady_clock::now();
				t2 = t1+chrono::milliseconds(mill);	
			}
	
			else{
				t1 = steady_clock::now();
			}
			
			//bull enemy
			chrono::steady_clock::duration bulld = bullt2-bullt1;
			if(bulld <= chrono::steady_clock::duration::zero()){
				
				for(int i = 0; i < bullNum; i++){
					if(bullLife[i] == true){
						bullMove(grid, bullPos[i*2+1], bullPos[i*2], playerX, playerY, bullDir[i], -31 -i );
					}

				
					bullt1 = steady_clock::now();
					bullt2 = t1+chrono::milliseconds(bullmill);	
				}

			}
			
			else{
				bullt1 = steady_clock::now();
			}
			
			//drop key
			if(grid[yKey][xKey]==0 && keys == 0){
				grid[yKey][xKey]=70;
			}
			
			
			//get key
			else if(playerY == yKey && playerX == xKey && keys == 0){
				keys++;
				setcolor(COLOR(0,0,0));
				settextstyle(3,0,4);
				settextjustify(0,2);
				setbkcolor(COLOR(0,255,0));
				
				itoa(keys, keysTxt, 10);
				outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10*4, keysTxt);
			}
			
			//open door
			if(keys == 1){
				grid[yDoor][xDoor]=68;
			}
			
			spawnUp(grid, control);
			
			upGrid(grid, control);
			copyVector(grid,control);


	
			//slime die
			for(int i=0; i<nEnemy; i++){
				lifeEnemy[i]=entityDie(grid, (-20-i));
			}
			
			//bull die
			for(int i=0; i<bullNum; i++){
				bullLife[i] = entityDie(grid, -31 -i);
			}
			//win
			if(playerX == xDoor && playerY == yDoor){
				//win game
				delay(500);
				setcolor(COLOR(125,255,255));	
				rectangle(0,0,getmaxx(), getmaxy());
				setfillstyle(1,COLOR(0,255,0));
				floodfill(getmaxx()/2,getmaxy()/2,COLOR(125,255,255));
				
				setcolor(COLOR(255,255,255));	
				settextstyle(3,0,5);
				setbkcolor(COLOR(0,255,0));
				settextjustify(1,1);
				outtextxy(getmaxx()/2,getmaxy()/2,"You passed the Level");
				getch();
				level = false;
				numLevel++;
				bombRange = bombUpdated;
				rangeUp = 2;
				
				setcolor(COLOR(0,0,0));	
				rectangle(0,0,getmaxx(), getmaxy());
				setfillstyle(1,COLOR(0,0,0));
				floodfill(getmaxx()/2,getmaxy()/2,COLOR(0,0,0));
			}
			
			//update HUD and die control
			else if(playerDie(grid)==0){
				playerStatus = 10;
				playerLife-=1;
				grid[playerY][playerX]=playerStatus;
				
				//timer invincible
				damaget1 = steady_clock::now();
				damaget2 = damaget1 + chrono::milliseconds(damagemill);
	
				setcolor(COLOR(0,0,0));
				settextstyle(3,0,4);
				settextjustify(0,2);
				setbkcolor(COLOR(0,255,0));
				itoa(playerLife, lifeTxt, 10);
	
				outtextxy(getmaxx() - HUD/2 + 125, getmaxy()/10*2, lifeTxt);
	
				
			}
			
			//powerUp update HUD
			else if(playerLife != lifeUp || bombRange != rangeUp){
				
				lifeUp = playerLife;
				setcolor(COLOR(0,0,0));
				settextstyle(3,0,4);
				settextjustify(0,2);
				setbkcolor(COLOR(0,255,0));
				itoa(playerLife, lifeTxt, 10);
	
				outtextxy(getmaxx() - HUD/2 + 125, getmaxy()/10*2, lifeTxt);
				
				itoa(bombRange, rangeTxt, 10);
	
				outtextxy(getmaxx() - HUD/2 +125, getmaxy()/10 * 3, rangeTxt);
			}
			
			//exit invincible status
			
			
			chrono::steady_clock::duration damageTimer =  damaget2 - damaget1;
			
			if(damageTimer <= chrono::steady_clock::duration::zero()){
				
				grid[playerY][playerX] = 9;
				playerStatus = 9;

			}
			
			else if(playerStatus == 10 || playerStatus == 11){
				
				if(d <= chrono::steady_clock::duration::zero() && playerStatus == 10){
					grid[playerY][playerX] = 11;
					playerStatus = 11;
				}
				
				else if(d <= chrono::steady_clock::duration::zero() && playerStatus == 11){
					grid[playerY][playerX] = 10;
					playerStatus = 10;
				}
				
				damaget1 = steady_clock::now();
			}
			
			//match end
			partita = playerLife;
			
			if(playerLife == 0){
				level = false;
			}
			
			else if(second == 0 && min == 0){
				level = false;
				partita = false;
			}
			
			
		}
				
		
	}
	
	//end game
	setcolor(COLOR(125,255,255));	
	rectangle(0,0,getmaxx(), getmaxy());
	setfillstyle(1,COLOR(255,0,0));
	floodfill(getmaxx()/2,getmaxy()/2,COLOR(125,255,255));
	
	setcolor(COLOR(0,0,0));	
	settextstyle(3,0,5);
	setbkcolor(COLOR(255,0,0));
	settextjustify(1,1);
	outtextxy(getmaxx()/2,getmaxy()/2,"You Lose Retry");
	
	delay(500);
	
	getch();
	return 0;

	

}
