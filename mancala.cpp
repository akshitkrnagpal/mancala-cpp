#include<iostream>
#include<windows.h>
#define INIT_SEEDS 4
#define NUM_PITS 4
using namespace std;
void gotoxy(short x, short y) {COORD pos = {x, y};SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);}
void setColor(int color) { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); FlushConsoleInputBuffer(hConsole); SetConsoleTextAttribute(hConsole, color);}
class mancala 
{
	
public:
	int player[NUM_PITS+1],computer[NUM_PITS+1];
	int ox,oy;
	bool playerTurn;
	mancala()
	{
		playerTurn=false;
		ox=2;
		oy=3;
		for(int i=0;i<NUM_PITS;i++)
		{
			player[i]=INIT_SEEDS;
			computer[i]=INIT_SEEDS;
		}
		player[NUM_PITS]=0;
		computer[NUM_PITS]=0;
	}
	void switchPlayer()
	{
		(playerTurn)? playerTurn=false: playerTurn=true;
	}
	void display()
	{
		cout<<"\n                        MANCALA\n";
		cout<<"   _______   _____   _____   _____   _____   _______  \n";
		cout<<"  |       | |     | |     | |     | |     | |       | \n";
		cout<<"  |       | |     | |     | |     | |     | |       | \n";
		cout<<"  |       | |_____| |_____| |_____| |_____| |       | \n";
		cout<<"  |       |  _____   _____   _____   _____  |       | \n";
		cout<<"  |       | |     | |     | |     | |     | |       | \n";
		cout<<"  |       | |     | |     | |     | |     | |       | \n";
		cout<<"  |_______| |____1| |____2| |____3| |____4| |_______| \n";	
		for(int i=1;i<=10;i++)
			refresh(i);
	}
	void refresh(int position,int color=15)
	{
		setColor(color);
		switch(position)
		{
			case 1: gotoxy(ox+13,oy+5);
					(player[0])? cout<<player[0] : cout<<" ";
					break;
			case 2: gotoxy(ox+21,oy+5);
					(player[1])? cout<<player[1] : cout<<" ";
					break;
			case 3: gotoxy(ox+29,oy+5);
					(player[2])? cout<<player[2] : cout<<" ";
					break;
			case 4: gotoxy(ox+37,oy+5);
					(player[3])? cout<<player[3] : cout<<" ";
					break;
			case 5: gotoxy(ox+46,oy+3);
					(player[4])? cout<<player[4] : cout<<" ";
					break;
			case 6: gotoxy(ox+37,oy+1);
					(computer[0])? cout<<computer[0]: cout<<" ";
					break;
			case 7: gotoxy(ox+29,oy+1);
					(computer[1])? cout<<computer[1]: cout<<" ";
					break;
			case 8: gotoxy(ox+21,oy+1);
					(computer[2])? cout<<computer[2]: cout<<" ";
					break;
			case 9: gotoxy(ox+13,oy+1);
					(computer[3])? cout<<computer[3]: cout<<" ";
					break;
			case 10:gotoxy(ox+4,oy+3);
					(computer[4])? cout<<computer[4]: cout<<" ";
					break;		  	
		}
		setColor(15);
		cout<<" ";
	} 
	void click(int position,bool display=true)
	{
		int temp;
		if(position<5 && position>0)
		{
			temp=player[position-1];
			if(temp==0)
				return;
			player[position-1]=0;
		}
		else if(position>5 && position<10)
		{
			temp=computer[position-6];
			if(temp==0)
				return;
			computer[position-6]=0;
		}
		if(display)	
		{
			refresh(position,240);
			setColor(15);
			Sleep(500);
			addSeeds(position+1,temp);
		}
		else
		{	
			addSeeds(position+1,temp,false);
		}
	}
	void addSeeds(int position,int seeds,bool display=true)
	{
		if(seeds==0)
			return;
		switch((position-1)%10 +1)
		{
			case 1: player[0]++; break;
			case 2: player[1]++; break;
			case 3: player[2]++; break;
			case 4: player[3]++; break;
			case 5: (playerTurn)? player[4]++ : seeds++; break;
			case 6: computer[0]++; break;
			case 7: computer[1]++; break;
			case 8: computer[2]++; break;
			case 9: computer[3]++; break;
			case 10:(!playerTurn)?computer[4]++: seeds++; break; 
		}
		if(display && !( (playerTurn && position==10) || (!playerTurn && position==5)) )
		{
			refresh((position-1)%10 +1,1);
			Sleep(500);
			for(int i=1;i<=10;i++)
				refresh(i);
		}
		addSeeds(position+1,seeds-1,display);
		if(seeds==1 && ((playerTurn && position==5) || (!playerTurn && position==10) ))
			switchPlayer();
	}
	int calculate_computer_move()
	{
		int max=0,max_i=0;
		int P_backup[5],C_backup[5];
		for(int i=0;i<5;i++)
		{
			P_backup[i]=player[i];
			C_backup[i]=computer[i];	
		}	
		for(int i=0;i<4;i++)
		{
			for(int j=0;j<4;j++)
			{
				for(int k=0;k<4;k++)
				{
					for(int l=0;l<4;l++)
					{
						(playerTurn)?	click(1+i,false):	click(6+i,false);
						switchPlayer();
						(playerTurn)?	click(1+j,false):	click(6+j,false);
						switchPlayer();
						(playerTurn)?	click(1+k,false):	click(6+k,false);
						switchPlayer();
						(playerTurn)?	click(1+l,false):	click(6+l,false);
						switchPlayer();
						if(max<computer[4] && C_backup[i]!=0)
						{
							max=computer[4];
							max_i=i;
						}
						for(int i=0;i<5;i++)
						{
							player[i]=P_backup[i];
							computer[i]=C_backup[i];	
						}
					}
				}	
			}	
		}
		playerTurn=false;
		//cout<<6+max_i;
		return 6+max_i;
	}
};
int main()
{
	setColor(15);
	mancala game;
	int choice;
	game.display();
	while(true)
	{
		gotoxy(0,12);
		if(!game.playerTurn)
		{
			int temp=game.calculate_computer_move();
			cout<<" Computer is playing ....              \n\n";
			for(int i=1;i<=10;i++)
				game.refresh(i);
			Sleep(1000);
			game.click(temp);
			game.switchPlayer();
		}
		else
		{
			gotoxy(0,12);
			cout<<" Enter the value from 1 to 4 =>  \b";
			cin>>choice;
			for(int i=1;i<=10;i++)
				game.refresh(i);
			if( (choice>0 && choice<5 && game.playerTurn && game.player[choice-1]!=0) )//|| (choice>5 && choice<10 && !game.playerTurn) )
			{
				game.click(choice);
				game.switchPlayer();
			}
		}
	}
}
