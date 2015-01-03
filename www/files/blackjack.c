/* The card shuffling and dealing program using structures */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

struct card {
	char *face;
	char *suit;
	int value;
};

typedef struct card Card;

Card deck[52];
Card player[10];
Card computer[10];
int i=0;
int n;
int pValue;
int cValue;
int score;
char *status=":|";
int bet=10;


void fillDeck (Card *, char *[], char *[], int []);
void shuffle(Card *);
void deal(Card *);
void menu();
void hit(Card *);
int calculate(Card *);
void refresh();

main()
{
	int temp/*, j*/;

	static char *face[]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
	static char *suit[]={"H","D","C","S"};
	static int value[]={1,2,3,4,5,6,7,8,9,10,10,10,10};

	srand(time(NULL));
	
	fillDeck(deck, face, suit, value);
	shuffle(deck);
	
	printf("\nStarting Bet? ");
	scanf("%d",&bet);

        while(bet>0)
	{
		if(i>=50)
		{
			printf("\nShuffling...");
			shuffle(deck);
		}
		menu();
	        printf("\n\nAdd to Bet? (Current bet = %d) ",bet);
		scanf("%d", &temp);
		bet=bet+temp;
	}
	return 0;
}

void fillDeck(Card *wDeck, char *wFace[], char *wSuit[], int wValue[])
{
	int k;

	for (k=0; k<52; k++)
	{
		wDeck[k].face = wFace[k%13];
		wDeck[k].suit = wSuit[k/13];
		wDeck[k].value = wValue[k%13]; 
	}
}

void shuffle(Card *wDeck)
{
	int k,j;
	Card temp;
	
	for(k=0; k<52; k++)
	{
		j = rand()%52;
		temp = wDeck[k];
		wDeck[k] = wDeck[j];
		wDeck[j] = temp;
	}
	i=0;
}

void deal(Card *wDeck)
{
	
	int j=0;

	if(i>=46)
	{
		printf("\nShuffling...");
		shuffle(deck);
	}

       	for(j=0;j<10;j++)
	{
		player[j].value=0;
		computer[j].value=0;
	}

	player[0] = deck[i];
	computer[0] = deck[++i];
	player[1] = deck[++i];
	computer[1] = deck[++i];

	n=1;
	pValue = calculate(player);
	cValue = calculate(computer);

	printf("\x1b[2J\x1b[2H");

}

void seventeen()
{
	int j=0;

	while(computer[j].value>0)
		j++;
	while((cValue=calculate(computer))<17)
	{
		if(i>=50)
		{
			printf("\nShuffling...");
		    	shuffle(deck);
	   	}
		
     
		computer[j]=deck[++i];
		j++;
	}
}

int calculate(Card *hand)
{
	
	int j=0, total=0, ace=0;
	
	while(hand[j].value>0)
	{
		if(hand[j].face=="A")
			ace=1;
		total=total+hand[j].value;
		j++;
	}
	if((total<=11)&&(ace==1))
		total=total+10;
	return(total);
}

void refresh()
{
	int j=0,k=0/*, total=0*/;
	printf("\n\x1b[2H\x1b[2J");
	printf("Score: %d          Bet: %d       Status: %s\n",score, bet,status);
	printf("_____________________________________________________________________\n");
	printf("\nYou:\n");
	while(player[k++].value>0)
		printf("________ ");
	k=0;
	printf("\n");
	while(player[k++].value>0)
	{
		if(player[k-1].face=="10")
		{
		printf("|%s%s   | ",player[k-1].face,player[k-1].suit);
		}
		else printf("|%s%s    | ",player[k-1].face,player[k-1].suit);
        }
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
	{
		if(player[k-1].face=="10")
		{
		printf("|   %s%s| ",player[k-1].face,player[k-1].suit);
		}
		else printf("|    %s%s| ",player[k-1].face,player[k-1].suit);
        }
	    
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("-------- ");
	k=0;

		
	
	
       /*	printf("You: ");
	while(player[j].value>0)
		printf("%s%s ",player[j].face, player[j++].suit);
        */
	j=0;
	printf("\nComputer:");

	/*printf("\nComputer: %s%s, *",computer[0].face,computer[0].suit, computer[1].face, computer[1].suit);
	*/
	printf("\n________ ________");
	if(computer[1].face=="10")
		printf("\n|:):):)| |%s%s   | ",computer[1].face,computer[1].suit);
		else printf("\n|:):):)| |%s%s    | ",computer[1].face,computer[1].suit);

	printf("\n|:):):)| |      |");
	printf("\n|:):):)| |      |");
	printf("\n|:):):)| |      |");
	if(computer[1].face=="10")
		printf("\n|:):):)| |   %s%s|",computer[1].face,computer[1].suit);
		else printf("\n|:):):)| |    %s%s|",computer[1].face,computer[1].suit);

	printf("\n-------- --------");
}


void menu()
{
	char *result/*, *moveStringPtr=" ", moveString[2]*/;
	int move =0,j=0, dbl=0, k=0;
	
	
	deal(deck);
	while((move !=3)&&(pValue<21)&&(n<4)&&(move!=2)&&(!dbl))
	{
		refresh();
		if(dbl)
			move=3;

		{
		        printf("\n[1]-Hit, [2]-Double, [3]-Stay: ");
			scanf("%d",&move);                 
		}                                          
		
		if(move == 1)   
		{ 
			if(i>=50)
			{
				printf("\nShuffling...");
		    		shuffle(deck);
	   		}

			hit(deck);
			i++;
			n++;
			pValue = calculate(player);
		}

		if(move == 2)
		{ 
			if(i>=50)
			{
				printf("\nShuffling...");
		    		shuffle(deck);
	   		}

			dbl=1;
			hit(deck);
			i++;
			n++;
			pValue = calculate(player);

		}

	}

	

	if((pValue<21)&&(n<4))
		seventeen();
	pValue=calculate(player);
	cValue=calculate(computer);
	
	if(dbl)
		bet=2*bet;
/*
	
if((((player[0].value==10)&&((strcmp(player[0].face,"10"))!=0)&&((strcmp
(player[1].face,"A"))==0))||((player[1].value==10)&&((strcmp
(player[1].face,"10"))!=0)&&((strcmp(player[0].face,"A"))==0)))&& -
(!(((computer[0].value==10)&&((strcmp(computer[0].face,"10"))!=0)&&((strcmp
(computer[1].face,"A"))==0))||((computer[1].value==10)&&((strcmp
(computer[1].face,"10"))!=0)&&((strcmp(computer[0].face,"A"))==0)))))



	{
		result="\a\a\aBlaCKJaCK!   :)";
		score=score+1.5*bet;
	}
*/
	if((pValue==21)&&(n==1))
	{
		result="\a\a\aBlaCKJaCK!   :)";
		score=score+1.5*bet;
	}
	else if((pValue<=21)&&(n==4))
	{
		result="\a5 iN A RoW    :)";
		score=score+bet;
	}
	else if((pValue<=21)&&((pValue>cValue)||(cValue>21)))
	{
		result="\aWiN    :)";
		score=score+bet;
	}
	else if((pValue==cValue)&&(pValue<=21))
	{
		result="TiE    :|";
		score=score+0;
	}
	else if((pValue<cValue)&&(cValue<=21))
	{
		result="LoSE    :(";
		score=score-bet;
	}
	else if((pValue>21))
	{
		result="BuST    :(";
		score=score-bet;
	}

	else { result="HuH?    :?";
		score=score+0;}
	if(dbl)
		bet=bet/2;

	
	
	if(score>0)
		status=":)";
	else if(score<0)
		status=":(";
	else
		status=":|";


/* Graphical display of score */

	printf("\n\x1b[2H\x1b[2J");
	printf("Score: %d        Bet: %d         %s\n",score,bet,result);
	printf("___________________________________________________________________\n");
	printf("You:\n");
	while(player[k++].value>0)
		printf("________ ");
	k=0;
	printf("\n");
	while(player[k++].value>0)
	{
		if(player[k-1].face=="10")
		{
		printf("|%s%s   | ",player[k-1].face,player[k-1].suit);
		}
		else printf("|%s%s    | ",player[k-1].face,player[k-1].suit);
        }
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(player[k++].value>0)
	{
		if(player[k-1].face=="10")
		{
		printf("|   %s%s| ",player[k-1].face,player[k-1].suit);
		}
		else printf("|    %s%s| ",player[k-1].face,player[k-1].suit);
        }
	    
	printf("\n");
	k=0;
	while(player[k++].value>0)
		printf("-------- ");
	k=0;

		printf("\nYou: Total = %d\n",pValue);

	j=0;
	printf("\nComputer: ");	
		printf(" Total = %d\n",cValue);

	while(computer[k++].value>0)
		printf("________ ");
	k=0;
	printf("\n");
	while(computer[k++].value>0)
	{
		if(computer[k-1].face=="10")
		{
		printf("|%s%s   | ",computer[k-1].face,computer[k-1].suit);
		}
		else printf("|%s%s    | ",computer[k-1].face,computer[k-1].suit);
        }
	printf("\n");
	k=0;
	while(computer[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(computer[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(computer[k++].value>0)
		printf("|      | ");
	printf("\n");
	k=0;
	while(computer[k++].value>0)
	{
		if(computer[k-1].face=="10")
		{
		printf("|   %s%s| ",computer[k-1].face,computer[k-1].suit);
		}
		else printf("|    %s%s| ",computer[k-1].face,computer[k-1].suit);
        }
	    
	printf("\n");
	k=0;
	while(computer[k++].value>0)
		printf("-------- ");
	k=0;

        		
}

void hit(Card *wDeck)
{

	if(i>=50)
	{
		printf("Shuffling...");
		shuffle(deck);
	}       
	player[n+1] = wDeck[i];
}
