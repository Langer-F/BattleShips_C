#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

const int O = 6; 	//board size
const int S = 5;	//number of submarines
const int D = 1;	//number of destroyers
const int t = 10;   //number of torpedos



void initOcean ();
void showInventory (int d, int s, int t);
void showOcean (int ocean[O][O],int ta[O][O]);
void submarinesIntoOcean (int ocean[O][O]);
void destryersIntoOcean (int ocean[O][O]);

int
main()
{
    int i,j;
    char MD[10];            //Game mode
	int ocean[O][O];	    //matrix representing the ocean
	int tor[O][O];          //Matrix representing where the player shoots.
	int des = D;            //Count how many destroyers are still alive
	int sub = S;            //Count how many submarines are still alive
	int x=0;                //keeps the horizontal coordinate of the torpedo.
	char y[3];              //keeps the vertical coordinate of the torpedo
	int yint=0;             //converts the vertical coordinate into number
    int torpedos=t;         //how many torpedos we have left

    do {
        printf("Type which game mode you want:\n[1]Normal\n[2]Cheats on\n");
        scanf("%s",MD);
        }while (strcmp(MD,"1")!=0&&strcmp(MD,"2"));
    for(i=0;i<O;i++)        //puts 0 in every location of ocean[O][O]
        for(j=0;j<O;j++)
           ocean[i][j] = 0;
     for(i=0;i<O;i++)        //puts 0 in every location of tor[O][O]
        for(j=0;j<O;j++)
           tor[i][j] = 0;
    showInventory(D,S,torpedos);
    destryersIntoOcean(ocean);
    submarinesIntoOcean(ocean);


    if (!strcmp(MD,"1"))
        printf("\nNORMAL GAMEPLAY\n");
    else
    {
        printf("\nCheating Mode\n");
        printf("0 is empty ocean\n1 is submarine\n2 is destroyer\n\n");
        printf("  ");
        for(j=0;j<O;j++)
            printf(" %.2d ",j+1);
        printf("\n\n");
        for(i=0;i<O;i++)
        {
            printf("%c ",i+65);
            for(j=0;j<O;j++)
                printf("  %d ",ocean[i][j]);
            printf("\n\n");
        }
    }
    while (torpedos>0)
    {
        do  {
            printf("\ntype the coordinate: ");
            scanf("%s",y);
            if (y[0]<65||y[0]>(65+O)||y[1]<49||y[1]>57)
                printf("format of coordinate must be: \"upper case letter\"\"number\"\nexample: X10\n");
           } while (y[0]<65||y[0]>(65+O)||y[1]<49||y[1]>57);
        yint=y[0]-65;
        x=y[1]-48;
        printf("\n");
        tor[yint][x-1]=1;
        showOcean(tor,ocean);
        if(ocean[yint][x-1]==1)
        {
            printf("\nSunk a submarine\n");
            sub--;
            if((sub==0)&&(des==0))
            {
                printf("\nCONGRATS, YOU WIN!!!!\n");
                return 3;
            }
        }else if(ocean[yint][x-1]==2)
         {
            printf("\nYou hit a destroyer\n");
            if ((ocean[yint-1][x-1]==2&&tor[yint-1][x-1]==1)
                ||((ocean[yint+1][x-1]==2)&&(tor[yint+1][x-1]==1))
                ||((ocean[yint][x]==2)&&(tor[yint][x]==1))
                ||((ocean[yint][x-2]==2)&&(tor[yint][x-2]==1)))
                {
                    printf("Sunk a destroyer\n");
                    des--;
                    if((sub==0)&&(des==0))
                    {
                        printf("\nCONGRATS, YOU WIN!!!!\n");
                        return 5;
                    }
                }
         }else
            printf("\nTorpedo lost in the water\n");
        torpedos--;
        if (torpedos==0)
        {
            printf("\nNo more torpedos, game over\n");
            return 7;
        }
        showInventory(des,sub,torpedos);
    }
	return 0;
}

void
initOcean()
{
    int j=0;
    int i=0;
    printf("    ");     //just to line up things
    for(j=0;j<O;j++)    //show the letters at the top of the ocean
        printf(" %.2d ",j+1);
    printf("\n");
	for(i=0;i<O;i++)
	{
		    printf("    ");
			for(j=0;j<O;j++)
				printf("+---");
			printf("+");
			printf("\n");
		    printf("  %c ",65 + i);
			for(j=0;j<O;j++)
				printf("|   ");
			printf("|");
			printf("\n");
	}
	printf("    ");
	for(j=0;j<O;j++)
        printf("+---");
    printf("+");
    printf("\n\n");
}

void
showInventory (int d, int s, int t)
{
    printf("WE HAVE %d TORPEDOS\n",t);
    printf("DESTROYERS: %d \n", d);
    printf("SUBMARINES: %d \n", s);
    printf("--------------------------------------------------\n");
}

void
showOcean(int tor[O][O],int ta[O][O])
{
    int i,j;
    printf("    ");     //para deixar tudo alinhado
        for(j=0;j<O;j++)    //Mostra os numeros topo do tabuleiro
            printf(" %.2d ",j+1);
        printf("\n");
        for(i=0;i<O;i++)    //conta as linhas do tabuleiro
        {
            printf("    ");
            for(j=0;j<O;j++)    //conta as colunas do tabuleiro
                printf("+---");
            printf("+");
            printf("\n");
            printf("  %c ",65 + i);
            for(j=0;j<O;j++)
            {
                if((tor[i][j]==1)&&((ta[i][j]==1)||ta[i][j]==2))
                        printf("| * ");
                else if((tor[i][j]==1)&&(ta[i][j]==0))
                    printf("| 0 ");
                else
                    printf("|   ");
            }
            printf("|");
            printf("\n");
        }
        printf("    ");
        for(j=0;j<O;j++)
        {
            printf("+---");
        }
        printf("+");
}

void
destryersIntoOcean(int ta[O][O])
{
    int s,i,j;
    srand(time(NULL));
    int z=0;               //Tells if the destroyer is vertically or horizontally placed
    for(s=0;s<D;s++)
    {
        z=(rand()%2);
        if(z==1)
        {
            i=(rand()%O);
            j=(rand()%O);
            while(ta[i][j]==1
                  ||ta[i-1][j]==1
                  ||ta[i+2][j]==1
                  ||ta[i][j-1]==1
                  ||ta[i][j+1]==1
                  ||ta[i+1][j+1]==1
                  ||ta[i+1][j-1]==1
                  ||ta[i-1][j-1]==1
                  ||ta[i-1][j+1]==1
                  ||ta[i+2][j+1]==1
                  ||ta[i+2][j-1]==1
                  ||ta[i][j]==2
                  ||ta[i-1][j]==2
                  ||ta[i+2][j]==2
                  ||ta[i][j-1]==2
                  ||ta[i][j+1]==2
                  ||ta[i+1][j+1]==2
                  ||ta[i+1][j-1]==2
                  ||ta[i-1][j-1]==2
                  ||ta[i-1][j+1]==2
                  ||ta[i+2][j+1]==2
                  ||ta[i+2][j-1]==2)
            {
                i=(rand()%O);
                j=(rand()%O);
            }
            ta[i][j]=2;
            ta[i+1][j]=2;
        }else
         {
            i=(rand()%O);
            j=(rand()%O);
            while(ta[i][j]==1
                  ||ta[i][j-1]==1
                  ||ta[i-1][j]==1
                  ||ta[i-1][j+1]==1
                  ||ta[i][j+2]==1
                  ||ta[i+1][j+1]==1
                  ||ta[i+1][j]==1
                  ||ta[i-1][j-1]==1
                  ||ta[i-1][j+2]==1
                  ||ta[i+1][j+2]==1
                  ||ta[i+1][j-1]==1
                  ||ta[i][j]==2
                  ||ta[i][j-1]==2
                  ||ta[i-1][j]==2
                  ||ta[i-1][j+1]==2
                  ||ta[i][j+2]==2
                  ||ta[i+1][j+1]==2
                  ||ta[i+1][j]==2
                  ||ta[i-1][j-1]==2
                  ||ta[i-1][j+2]==2
                  ||ta[i+1][j+2]==2
                  ||ta[i+1][j-1]==2)
            {
                i=(rand()%O);
                j=(rand()%O);
            }
            ta[i][j]=2;
            ta[i][j+1]=2;
        }
    }
}

void
submarinesIntoOcean (int ta[O][O])
{
    int s,j,i;
    srand(time(NULL));
    for(s=0;s<S;s++)        //coloca os submarinos na matriz
    {
        i=(rand()%O);
        j=(rand()%O);
        while(ta[i][j]==1
              ||ta[i-1][j]==1
              ||ta[i+1][j]==1
              ||ta[i][j-1]==1
              ||ta[i][j+1]==1
              ||ta[i+1][j+1]==1
              ||ta[i-1][j+1]==1
              ||ta[i-1][j-1]==1
              ||ta[i+1][j-1]==1
              ||ta[i][j]==2
              ||ta[i-1][j]==2
              ||ta[i+1][j]==2
              ||ta[i][j-1]==2
              ||ta[i][j+1]==2
              ||ta[i+1][j+1]==2
              ||ta[i-1][j+1]==2
              ||ta[i-1][j-1]==2
              ||ta[i+1][j-1]==2)  //enquanto houver sub adjacente, gera novos valores
        {
            i=(rand()%O);
            j=(rand()%O);
        }
        ta[i][j]=1;
    }
}
