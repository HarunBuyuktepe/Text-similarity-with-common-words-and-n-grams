/*
**Harun Büyüktepe;
**150115020;
**Hw1;
*/
#include<stdio.h>
#include"conio.h"
#include"stdlib.h"
#include<string.h>

struct node {/*Create new data type*/
    char word[40];
	struct node *nextPtr;
  };

typedef struct node ListNode; /* synonym for struct listNode */
typedef ListNode *ListNodePtr; /* synonym for ListNode* */


void menu( void );/*Define functions*/
void seeText( char a );
void insertWord( ListNodePtr *sPtr, char ANM[40]);
void findCommonWords(void);
void printList( ListNodePtr currentPtr );
void insertWordUnOrdered( ListNodePtr *sPtr,char ANM[40] );
void find2grams(void);
void printList2( ListNodePtr currentPtr );

ListNodePtr commonList = NULL;/*Create global pointer to keep common words*/
ListNodePtr commonListText1 = NULL;
ListNodePtr commonListText2 = NULL;
ListNodePtr common2Grams = NULL;

int main()
{ 	
	menu();
    return 0; //* indicates successful termination */
} //* end main */

void menu(void){
	
	 /* user's choice */
	printf("\nPlease select...\n1.)Print text one..."
	"\n2.)Print text two..."
	"\n3.)Find the number of common words and the number of common 2-grams..."
	"\n0 is exit.\n");
	
	char choice;
	printf( "Enter your choice : " );
	choice=getch();/*Give choice from user*/
	printf("%c\n\n",choice);
	if(choice=='0')exit(1);
	
	while ( choice != '0' )
	 { 

        switch ( choice ) { 
        	case '1':
        		seeText(choice);/*Open text1*/
           		break;
			
			case '2':
				seeText(choice);/*Open text2*/
				menu();
				break;
			
			case '3':
				find2grams();/*Find 2-grams between two text*/
				menu();
				break;	
			default:
        	
            	printf( "Invalid choice.\n\n" );
			   	menu();
            	break;
      
	
		}
	}
	menu();
}
    
void seeText( char a )
{
	FILE *p,*open;
	if(a=='1')
	{
		open=fopen("text1.txt","r");/*Give adress to compiler*/
		if( open == NULL )/*If no txt file , create new one.*/
		{
	    	open=fopen("text2.txt","w");
	       	printf("\nFile is created.\n\n\n");
	       	fclose(open);
	       	menu();
	   	}
	}
	else
	{
		open=fopen("text2.txt","r");/*Give adress to compiler*/
		if( open == NULL )/*If no txt file , create new one.*/
		{
    		open=fopen("text2.txt","w");
       		printf("\nFile is created.\n\n\n");
       		fclose(open);
    	   	menu();
   		}
	}
	char words[40];
	while(!feof(open))/*Give word from text*/
	{
	
		fscanf(open,"%s",words);	
		printf("%s ",words);

	}
	fclose(open);
	printf("\n\n\t---\t---\t---\t---\t---\t---\t---\t--- \n");			
	menu();
	
}

void insertWord( ListNodePtr *sPtr,char wrd[40] )/*This inserts words alphaticaly*/
{ 
    ListNodePtr newPtr;      /* pointer to new node */
    ListNodePtr previousPtr; /* pointer to previous node in list */
    ListNodePtr currentPtr;  /* pointer to current node in list */
	
	newPtr = (ListNodePtr)malloc( sizeof( ListNode )); /* create node */
    if ( newPtr != NULL ) { /* is space available */
        
		strncpy(newPtr->word,wrd,40);
        newPtr->nextPtr = NULL; /* node does not link to another node */
        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop to find the correct location in the list */
        while ( currentPtr != NULL && strcmp(wrd,currentPtr->word)>0  ) { 
            previousPtr = currentPtr;          /* walk to ...   */
            currentPtr = currentPtr->nextPtr;  /* ... next node */ 
        } /* end while */

        /* insert new node at beginning of list */
        if ( previousPtr == NULL ) { 
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* end if */
        else { /* insert new node between previousPtr and currentPtr */
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } /* end else */
   	
    } /* end if */
    else {
        printf( "%s not inserted. No memory available.\n" ,wrd);
    } /* end else */

} /* end function insert */
void findCommonWords(void)/*This finds common word between two texts.*/
{
	FILE *open1,*open;
	char Aname[40],word[40],common[40];
	int diff='a'-'A';/*To fix words*/
	int count=0;
	ListNodePtr startPtr0 = NULL;
	ListNodePtr startPtr1 = NULL;
	ListNodePtr startPtr2 = NULL;
	ListNodePtr Ptr0 = NULL;
	ListNodePtr Ptr1 = NULL;
	ListNodePtr Ptr2 = NULL;
	open=fopen("text1.txt","r");/*Open text1*/
    if( open == NULL )
	{
   	 	open=fopen("text1.txt","w");
      	printf("\nFile is created.\n\n\n");
    	fclose(open);
    	menu();
   	}
	int i;
	while(!feof(open))
	{
	
		fscanf(open,"%s",Aname);/*Give words*/
		
		for(i=0;i<40;i++)
		{
			if(Aname[i]<='Z'&& Aname[i]>='A')/*Fix from condition*/
			{	
				Aname[i] += diff;/*Make lower*/
				
			}
			else if(Aname[i]=='.'|| Aname[i]==','||Aname[i]=='?'||Aname[i]=='!'||Aname[i]=='-'||Aname[i]=='/'||Aname[i]=='('||Aname[i]==')'||Aname[i]=='"'||Aname[i]==':'||Aname[i]==';')
			{
				Aname[i]='\0';/*Discreate these*/
			}
		
		}
		strcpy(word,Aname);
		insertWord(&startPtr0,word);/*Add alphabetic linked list*/
		insertWordUnOrdered(&commonListText1,word);/*Add linked list*/
	}
	fclose(open);
	printf("\n\t\t...First text was processed...\n");
	
	open1=fopen("text2.txt","r");/*Open text1*/
    if( open == NULL )
	{
   	 	open1=fopen("text2.txt","w");
      	printf("\nFile is created.\n\n\n");
       	fclose(open1);
       	menu();
   	}
	int j;
	while(!feof(open1))
	{
	
		fscanf(open1,"%s",Aname);
		
		for(j=0;j<40;j++)
		{
			if(Aname[j]<='Z'&& Aname[j]>='A')/*Fix from condition*/
			{	
				Aname[j] += diff;/*Make lower*/
				
			}
			else if(Aname[j]=='.'|| Aname[j]==','||Aname[j]=='?'||Aname[j]=='!'||Aname[j]=='-'||Aname[j]=='/'||Aname[j]=='('||Aname[j]==')'||Aname[j]=='"'||Aname[j]==':'||Aname[j]==';')
			{
				Aname[j]='\0';/*Discreate these*/
			}
			
		}
		strcpy(word,Aname);
		insertWord(&startPtr1,word);/*Add alphabetic linked list*/
		insertWordUnOrdered(&commonListText2,word);/*Add linked list*/
	}
	fclose(open1);
	printf("\n\t\t...Second text was processed...");

	Ptr1=startPtr1;
	Ptr2=startPtr2;
	while(startPtr0!=NULL){/*Find common words*/
		
		while(startPtr1!=NULL)/*Search first text in second text*/
		{
			
			if(strcmp(startPtr0->word,startPtr1->word)==0)
			{
				if(startPtr2==NULL)/*If pointer is null insert it.*/
				{
					insertWord(&startPtr2,startPtr1->word);count++;
					insertWord(&Ptr2,startPtr1->word);/*Two times adding in Linked list to make decition*/
				}
				
				while(Ptr2!=NULL)/*to make this control that same words can not be in linked list*/
				{
					if(strcmp(startPtr0->word,Ptr2->word)==0)
					{
						break;/*If same word is in Linked list ,don't add it.Next word should come.*/
					}
					Ptr2=Ptr2->nextPtr;
					insertWord(&startPtr2,startPtr1->word);count++;
					insertWord(&Ptr2,startPtr1->word);
				}
	
			}
			startPtr1=startPtr1->nextPtr;
			
		}
		startPtr0=startPtr0->nextPtr;
		startPtr1=Ptr1;/*Intrup to come null value ; other words, search again*/
	}

	
	printf("\nThe common words are: ");
	commonList=startPtr2;
	printList(startPtr2);
	printf("\n\nThe number of common words: %d",count);
}


void insertWordUnOrdered( ListNodePtr *sPtr,char ANM[40] )/*Make list order*/
{ 
    ListNodePtr newPtr;      /* pointer to new node */
    ListNodePtr previousPtr; /* pointer to previous node in list */
    ListNodePtr currentPtr;  /* pointer to current node in list */
	
	newPtr = (ListNodePtr)malloc( sizeof( ListNode )); /* create node */
    if ( newPtr != NULL ) { /* is space available */
        
		strncpy(newPtr->word,ANM,40);
        newPtr->nextPtr = NULL; /* node does not link to another node */
		//printf("%s\n",ANM);
        previousPtr = NULL;
        currentPtr = *sPtr;

        /* loop to find the correct location in the list */
        while ( currentPtr != NULL ) { 
            previousPtr = currentPtr;          /* walk to ...   */
            currentPtr = currentPtr->nextPtr;  /* ... next node */ //bir sonraki icin
        } /* end while */

        /* insert new node at beginning of list */
        if ( previousPtr == NULL ) { 
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } /* end if */
        else { /* insert new node between previousPtr and currentPtr */
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        } /* end else */
   	
    } /* end if */
    else {
        printf( "%s not inserted. No memory available.\n" ,ANM);
    } /* end else */

} /* end function insert */

void find2grams(void)
{
	findCommonWords();/*First bring common list,first text and second text in linked list */
	char temp0[40],temp1[40];
	ListNodePtr Ptr0 = NULL;
	ListNodePtr Ptr1 = NULL;
	ListNodePtr Ptr2 = NULL;
	ListNodePtr startPtr4 = NULL;
	
	printf("\nThe common 2-grams are :\n");
	
	Ptr0=commonList;
	Ptr1=commonListText1;
	Ptr2=commonListText2;
	
	while(Ptr0!=NULL){/*Search common word on txt1 then if found search at txt2*/
		
		while(Ptr1->nextPtr!=NULL&&Ptr1!=NULL)
		{
			if(strcmp(Ptr0->word,Ptr1->word)==0)
			{
				strcpy(temp0,Ptr1->word);
				strcpy(temp1,Ptr1->nextPtr->word);
				while(Ptr2->nextPtr!=NULL &&Ptr2!=NULL )
				{
					if(strcmp(Ptr2->word,temp0)==0 && strcmp(Ptr2->nextPtr->word,temp1)==0)/*Make control*/
					{
						insertWordUnOrdered(&startPtr4,temp0);/*inser 2-grams*/
						insertWordUnOrdered(&startPtr4,temp1);
						break;
					}
					Ptr2=Ptr2->nextPtr;/*Pass next node*/
				}
				Ptr2=commonListText2;/*refull the list because pointer arrive Null value*/

			}
			Ptr1=Ptr1->nextPtr;
			
		}
		Ptr1=commonListText1;/*refull the list because pointer arrive Null value*/
		Ptr0=Ptr0->nextPtr;
		
	}
	
	printList2(startPtr4);
	printf("\n\n");
	commonList=NULL;
	commonListText1=NULL;
	commonListText2=NULL;
	startPtr4=NULL;
	
	
}
void printList2( ListNodePtr currentPtr )
{ 
	common2Grams=NULL;
	int count=0;
	char temp0[40],temp1[40];
	/* if list is empty */printf( "\n\n" );
    if ( currentPtr == NULL ) {
        printf( "List is empty.\n\n" );
    } /* end if */
    
    else { 

        /* while not the end of the list */
        while ( currentPtr != NULL &&currentPtr->nextPtr != NULL ) 
		{ 
            
			if(currentPtr->nextPtr->nextPtr==NULL)
			{
				printf( "%s %s\n", currentPtr -> word ,currentPtr->nextPtr -> word);count++;
				break;
			}
			
			if(strcmp(temp0,currentPtr->nextPtr ->nextPtr-> word)!=0&&strcmp(temp1,currentPtr ->nextPtr->nextPtr-> word)!=0)
			{
				strcpy(temp0,currentPtr -> word);
				strcpy(temp1,currentPtr->nextPtr -> word);
				printf( "%s %s\n", currentPtr -> word ,currentPtr->nextPtr -> word);count++;
				insertWordUnOrdered(&common2Grams,temp0);/*inser 2-grams*/
				insertWordUnOrdered(&common2Grams,temp1);
            }
			
			currentPtr = currentPtr->nextPtr;
			currentPtr = currentPtr->nextPtr;
			
			
        } /* end while */
        printf("\nThe number of common 2-grams : %d",count);
    } /* end else */

} /* end function printList */


void printList( ListNodePtr currentPtr )
{ 
	/* if list is empty */printf( "\n\n" );
    if ( currentPtr == NULL ) {
        printf( "List is empty.\n\n" );
    } /* end if */
    
    else { 
    

        /* while not the end of the list */
        while ( currentPtr != NULL ) { 
            printf( "%s\n", currentPtr -> word );
			currentPtr = currentPtr->nextPtr;   
        } /* end while */
        
    } /* end else */

} /* end function printList */

