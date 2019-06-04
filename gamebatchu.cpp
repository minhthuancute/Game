    /* Code by Thuan Cute */
	
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<dos.h>
#define MAX 10000 
char ch , enter , key ;
int score = 0 , comp = 0 , signal=0 , num=1000 , randx ;
int arrkey[26] , arr[26] ;

void textcolor(int x){
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau , x);
}

void gotoxy(int x , int y){    
	HANDLE hConsoleOutput;    
	COORD Cursor_an_Pos = {x-1 , y-1};   
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);    
	SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}

void hcn(){
	for(int j=1 ; j<=15 ; j++){
		if(j == 1){
			for(int i=1 ; i<=28 ; i++){
				if(i == 1){
					printf("%c" , char(218));
				}
				else if(i == 28){
					printf("%c" , char(191));
				}
				else if(i>1 && i<28){
					printf("%c" , char(196));
				}
			}
		}
		else if(j == 15){
			for(int i=1 ; i<=28 ; i++){
				if(i == 1){
					printf("%c" , char(192));
				}
				else if(i == 28){
					printf("%c" , char(217));
				}
				else if(i>1 && i<28){
					printf("%c" , char(196));
				}
			}
		}
		else if(j>1 && j<28){
			printf("%c" , char(179));
			printf("                          %c" , char(179));
			//cout<<setw(20-1)<<char(179);
		}
		printf("\n");
	}	
}

void display(int score , int comp , int num , int randx){
	textcolor(5);
	gotoxy(1 , 1); // display khung game
	hcn();
	//srand(time(NULL));
	for(int i=0 ; i<26 ; i++){ // khoi tao bang chu cai
		arrkey[i] = 65 + i;
	}
	gotoxy(2 , 2);
	for(int i=0 ; i<26 ; i++){ // display bang chu cai
		if(i == randx){
			gotoxy(i+2 , 2);
			printf(" ");
		}
		else{
			printf("%c" , char(arrkey[i]));
		}
	}
	gotoxy(2 , 11);
	for(int i=1 ; i<=26 ; i++){
		printf("%c" , char(196));
	}
	gotoxy(2 , 12);
	printf("Player : %d" , score);
	gotoxy(2 , 13);
	printf("Fail : %d" , comp);
	gotoxy(2 , 14);
	printf("Level : %d " , num/100);
}

void game(){
	for(int i=0 ; i<26 ; i++){ // khoi tao mang chua vi tri chu roi
		arr[i] = i ;
	}
	textcolor(5);
	law :
		printf("\t\t\t\tWelcom to Keyboard Game\n");
		printf("\t\t\t\t(Created by Thuan cute)\n");
		printf("Law :\n");
		printf("\tKhi co 1 tu roi xuong  , hay go vao phim tuong ung voi \n");
		printf("\ttu do tren ban phim , kiem nhieu diem nhat co the . Neu\n");
		printf("\tchu cham vach hoac ban khong an kip trong thoi gian quy dinh (5s)\n");
		printf("\tban bi -10d , nguoc lai ban duoc +10d .\n");
		printf("Control : \n");
		printf("\tAn Enter de bat dau . An ESC de thoat .\n");
		printf("\tAn mui ten len(xuong) de tang(giam) do kho\n");
		printf("Are you ready ?\n");
		printf("An Enter de bat dau . An ESC de thoat !");
	while(1){ // nhan phim chuc nang khi o man hinh menu
		if(kbhit()){ // neu co phim duoc bam
			ch = getch();
			if(ch == 72){ // mui ten len
				num += 50;
				printf("\n\tBan da giam do kho xuong 1 cap !");
				sleep(1);
				system("cls");
				goto law;
				break;
			}
			if(ch == 80){ // mui ten xuong
				num -=50;
				printf("\n\tBan da tang do kho len 1 cap !");
				sleep(1);
				system("cls");
				goto law;
				break;
			}
			if(ch == 13){ // Enter
				system("cls");
				goto game;
				break;
			}
			if(ch == 27){ // ESC
				printf("\n\n\tHEN GAP LAI ^^ !");
				return ;
				break;
			}
		}
	}
	game :
	// code control game.begin
		/*time_t randkey;
		time_t randx;
		srand((int) time(&randx));
		srand((int) time(&randkey));
		*/
		srand(time(NULL)); // bat dau random
		while(1){
			for(int cnt=1 ; cnt<=5 ; cnt++){
				randx = arr[rand()%26]; // random vi tri roi chu (x) trong mang arr
				display(score , comp , num , randx);
				for(int i=1; i<=8 ; i++){
					gotoxy(randx+2 , i+2); // gotoxy vi tri chu roi
					printf("%c" , (char)arrkey[randx]); // in ra chu duoc random
					gotoxy(randx+2 , i+2); // gotoxy dua con tro xuong ben duoi
					Sleep(num);
					if( kbhit() ){ // neu co phim duoc bam
						signal++;
						ch = getch();
						if(ch == 65+randx){ // phim bam dung
							score = score + 10;
							gotoxy(randx+2 , i+2);
							printf(" ");
							break;
						}
						else{
							if(ch == 27){ // thoat game
								system("cls");
								goto law;
							}
							else{
								score = score - 10; // bam phim sai
								comp++;
								gotoxy(randx+2 , i+2);
								printf(" ");
								break;
							}
						}
					}
					gotoxy(randx+2 , i+2); // thay cho system("cls")
					printf(" ");
				}
				//sum = 0; // dua cnt ve trang thai ban dau
				if(signal == 0){ // check truong hop khong bam phim
					score = score - 10;
					comp++;
				}
				else{
					signal = 0; // dua signal ve trang thai chua bam phim
				}
			}
			if(score - MAX == 0){ // score == 1000 --> Win
				printf("WIN");
				goto law;
			}
			if(comp==MAX){ // am diem hoac may MAX --> Fail
				printf("GAME OVER");
				goto law;
			}
		}
	// code game.end	
}

int main(){
	game();
}
