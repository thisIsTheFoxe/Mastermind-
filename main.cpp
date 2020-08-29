// Name: Julian Kugler
// Datum: 05.05.2015
// Beschreibung: Menüsteuerung

/* 

© 2015  Copyright by Henrik Storch, Julian Kugler, Maximilian Hudelmaier, Julian Bundschuh
Datum: 10.6.2015

*/



/*
 
 Henrik Storch, Aug. 29, 2020 - Day six..-teen:
   i tried to save it, i really did.. it's usueless.. imma give you the same advice i wish i had before starting.. this.....
 
   > STOP! <
 
   ther's no need to be a hero.. i'm sure you are a great coder no matter what
   -> YOU CAN'T SAVE IT!

   it's all for nothing..
   
   go away and do something good with your time.. read a book, design a new game..
   
   the choice is your's.. don't say i didn't warn you....
 
 */


#include <unistd.h>  //sleep(sekunden)
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <ctime>
#include "zufall.h"

using namespace std; 			///ösjkldfh kjipfhklöwüoihfnaslöjfcklyXHNC LAfhsdkljk,hacopiH ÄFKL #häelä2     <--- Henriks Kommentar-Ausraster

int igetkey(int);		//Funktion für Pfeiltastenerkennung
int iZeit=0;    //für zusatzliche unterbrechungen
int irunden;	//derzeitige Runde
int ians[5] = {0}; 		// Antwort  auf 9 heißt leer = kein wert. zum überprüfen beim laden
int istift[5] [10] = {0}; 			//wenn wert auf 0 stimmt nichts überein wenn auf 1 richtige farbe, wenn auf 2 richtige farbe,richtige stelle	 //--Stifte zur Hilfe-- auf Null setzten//Stift 
int iScore=0;
int iPin = 0; //aktuell augewählter pin    W=[0;3]
int iStiftFarbe [5] [10] = {0}; // [Stiftnummer]  W=[0;3] 	D=[0;4]	Farbe: 0:Rot 1:Blau 2:Grün 3:Gelb 4:pink
int iHighScore [10] = {0}; //top 10
int istiftschwarz;
int ineustart;

bool bneuesSpiel=1;
bool bEnd;			//nach 10 versuchen
bool bende = 1;		//Bedingung für do-while Schleife, die für die Bildschirmausgabe je nach Pfeiltaste zuständig ist		//global, weil dieser von Funktionen für die main gesetzt werden muss	//keine Zahl dahinter, weil diese nur im main genutzt wird

char cSpieler [10];

string sNames[10];

time_t start, ende; //Zeitmessung


void win();
void game_over();
void printHistory();
void ivergl(int);
void printPins();
void irand();
void spiel_beenden(int);
void spiel_starten();
void write_header();  					//Mastermind header
void write_starten();					//Bildschirm: Spiel starten grün
void write_laden();						//Bildschirm: Spiel laden grün
void write_spielregeln();					//Bildschirm: Bestenlisten grün
void write_beenden();					//Bildschirm: Spiel beenden grün	
void spiel_speichern();
void spiel_laden();
void write_esc();
void write_regeln();
void write_win();
//void write_Highscore();














int main(int argc, char** argv) 								//Julian Kugler
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//Für Farben von bestimmten Textbereichen
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	
	int ikey = 0;			//Pfeiltasten-code
	int iauswahl = 1;		//Angabewert für anzugebenden Bildschirm
	int istart = 0;			//Einlesen des Enters
	
	
	write_header();
	printf("                                   <Enter>");
	
	do
	{
		istart = getch();
	}
	while(istart != 13);
	
	iauswahl = 1;				// Bildschirmauswahl
		do
		{
			//ikey = igetkey();		//Pfeiltastenerkennung
				
			switch(ikey)
			{			
				case 333:			//Pfeiltaste rechts
					iauswahl++;
					if(iauswahl == 5)
					{
						iauswahl = 4;
					}
					break;
					
				case 331:			//Pfeiltaste links
					iauswahl--;
					if(iauswahl == 0)
					{
						iauswahl = 1;
					}
					break;
					
				default:
					;				
			}
			
			switch(iauswahl)		//Bildschirmänderung in Abhängigkeit von der zuletzt gedrückten Pfeiltaste
				{
					case 1:															//erster Bildschirm  Spiel starten ist grün, 10 ist grün, 7 ist weiß !!!!!!!!!!!!!!!!!!!!!!!
						write_header();
						write_starten();
						break;
						
					case 2:			//zweiter Bildschirm
						write_header();
						write_laden();
						break;
						
					case 3:				//dritter Bildschirm
						write_header();
						write_spielregeln();
						break;
						
					case 4:				//vierter Bildschirm
						write_header();
						write_beenden();			
						break;
						
					default:
						;
				}
				ikey = igetkey(iauswahl);		//Pfeiltastenerkennung 		// ikey == 333 ---> Pfeiltaste rechts	//ikey == 331 ---> Pfeiltaste links		//!!!!AUCH!!!! Erkennung von Enter und weiterführen des Programms
				
		}while(bende == 1);			//ununterbrochene Schleife
	
	getch();
	return 0;
}





//##################################################################################################################################################################



























int igetkey(int iauswahl)												//Julian Kugler
{
	HWND hwnd = FindWindow("ConsoleWindowClass",NULL); 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);			//Setzt Konsolen Schrift Farbe wieder auf Weiß
	
	int ikey = getch();
	if (ikey == 0 || ikey == 224)
	{
		ikey = 256 + getch();				//Pfeiltastenerkennung 		// ikey == 333 ---> Pfeiltaste rechts	//ikey == 331 ---> Pfeiltaste links
		return ikey;
	}
	else if(ikey == 13)						//Erkennung von Drücken von Enter im Auswahlmenü !!!! IM MAIN !!!!
	{
		switch(iauswahl)					//Je nach Auswahl im Menü andere Funktion
		{
			case 1:
				bneuesSpiel=1;	
				spiel_starten();				//Spiel starten
				break;
				
			case 2:							//Spiel laden
				spiel_laden();
				if(irunden >= 10)			//Beim laden eines verlorenen/gewonnen Spiels wird irunden wieder 10. -----> Auftauchen einer 11. Runden beim laden
				{
					ineustart = 1;
				}
				
				if(ineustart == 1)			//Verloren/Gewonnen ? --> Neues Spiel
				{
					bneuesSpiel = 1;
				}else
				{
					bneuesSpiel = 0;
				}
				

				ineustart = 0;
				spiel_starten();
				break;
				
			case 3:		
				write_regeln();					//Bestenlisten
//				write_Highscore();
				break;
				
			case 4:	
				spiel_beenden(ikey);						//Spiel beenden
				break;
				
			default:
				;
		}
	}
	

}

void spiel_beenden(int ikey)							//Julian Kugler
{
	int iauswahl4 = 1;			//für Auswahlfenster bei Auswahl des "Spiel beenden" Buttons
	bool bende4 = 1;			//für Schleife im vierten Auswahlfenster bei Auswahl des "Spiel beenden" Buttons
				do
				{
					switch(ikey)			//gleiches Spiel wie im Main: Pfeiltastenerkennung
					{
						case 333:
							iauswahl4++;			//Auswahlpunkt (in dem Fall <Ja>   Nein) bestimmen durch Pfeiltasten         HIER nach rechts
							if(iauswahl4 == 3)
							{
								iauswahl4 = 2;
							}
							break;
							
						case 331:					//Auswahlpunkt (<Nein>   JA) bestimmen durch Pfeiltasten	HIER nach links
							iauswahl4--;
							if(iauswahl4 == 0)
							{
								iauswahl4 = 1;
							}
							break;
							
						default:
							;
							
					}
										
					switch(iauswahl4)			//Ausgaben von verschiedenen Auswahlmöglichkeiten Abhängig von Pfeiltastendruck und iauswahl4
					{
						case 1:
							system("cls");
							printf("\n\n\n				Sind sie sich sicher?\n\n\n\n");
							printf("                                <Ja>   	  Abbrechen\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");			//Ausgabe von Auswahlmöglichkeit "JA"	//viel "\n" weil der Cursor unten links im Konsolenfenster sein sollte
							break;
							
						case 2:
							system("cls");
							printf("\n\n\n				Sind sie sich sicher?\n\n\n\n");
							printf("                              	 Ja   	 <Abbrechen>\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");			//Ausgabe von Auswahlmöglichkeiten "NEIN"
							break;
							
						default:
							;
					}
				
					ikey = getch();
					if (ikey == 0 || ikey == 224)
					{
						ikey = 256 + getch();				//Pfeiltastenerkennung für erneute Auswahlangabe
					}
					else if(ikey == 13)						//Erkennen eines Enterdrucks für Möglichkeiten "JA" oder "NEIN"
					{
						switch(iauswahl4)					//Bei Enterdruck:
						{
							case 1:							//Bestätigen des "JA" Buttons ---> Spiel wird beended
								write_header();
								printf("\n\n\n				Spiel wird beendet!\n\n\n");
								bende4 = 0;																//Schleife in der Funktion wird beendet ---> übergehen ins main Programm
								bende = 0;																//globale Variable für die Auswahlschleife im main Programm  ----> Beenden des gesamten Programms
								break;
								
							case 2:
								bende4 = 0;					//Schleife in der Funktion wird beendet ----> Übergehen ins main Programm !!! OHNE !!! in Schleife im Main Programm zu beenden ---> Erneute Möglichkeit zum auswählen im Menü
								break;
								
							default:
								;								
						}
					}
				
				}while(bende4 == 1);

}



void spiel_starten()									//Henrik Storch
{
	HWND hwnd = FindWindow("ConsoleWindowClass",NULL); 
	MoveWindow(hwnd,0,0,10000,1000,TRUE);						//Konsole groß machen
	
    // insert code here...
    int iPfeilTaste;
    if(bneuesSpiel == 1)
	{ 						     //spiel NEU starten
    	irunden=0;
    	iPin=0;
    	for(int i2=0 ; i2 < 5 ; i2++)
		{
			for(int i3=0 ; i3 < 10 ; i3++)
			{
				iStiftFarbe [i2] [i3] = 0;
			}
		}
	    irand();
	}

 //   printf("iPfeilTaste: %i \n",iPfeilTaste);

    //          0
    //      1   2   3
    
    time(&start);//timer starten
    
    
    
    
    
 
    /*			printf("1es mal!! \n");   
    for(int i; i<5;i++){   		//debugging note :)
			switch(ians[i]){
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
					printf(" 	\xdb ");
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");


//#warning Debug printf!
}

}
 */
 
 
 
    do {
		system("CLS");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),23);
		
    	printf("\n  Benutzen Sie die Pfeiltasten zum raten. \n\n\n");
   	    for(int i=0; i<5;i++)
		{
	//	printf("\n %i;  %i;  %i\n ",i,iPin,iStiftFarbe[i]);   		//debugging note :)

	/*	switch(ians[i])
			{																				//Antwortcode für Test !!
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);			
					printf(" 	\xdb ");												// \xdb  -- ausgefüllter Kasten
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),9);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),13);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");


#warning Debug printf!
			} */

		}
		
		printf("\n \n \n");
 
    	printPins();			//Auswahlpins
    	
    	bEnd=0;
    	
    	iPfeilTaste = getch();
    	
//    	printf("\n %i",iPfeilTaste);
    
    
        switch (iPfeilTaste) 
		{
            case 224:
                break;
                
            case 72:
                //farbe wechselne
//              printf("%i",iPfeilTaste);
                if (iStiftFarbe[iPin] [irunden]>=4)
				{
					iStiftFarbe [iPin] [irunden] = 0;
				}else
				{
				iStiftFarbe [iPin] [irunden] += 1;
               }
           		 break;
            case 75:
                //linken stift bearbeiten
                if (iPin<=0)
				{
					iPin = 0;
				}else iPin -=1;
				
                break;
                
            case 80:
                //farbe wechsel
                if (iStiftFarbe [iPin] [irunden]<=0)
				{
					iStiftFarbe[iPin] [irunden] = 4;
				}else iStiftFarbe[iPin] [irunden] -= 1;
				
                break;
                
            case 77:
                //rechten stift ändern
                if (iPin>=4)
				{
					iPin = 4;
				}else
				{
				iPin += 1;
				}
                break;
                
            case 13:
            	//enter
            	spiel_speichern();
            	ivergl(irunden);
            	irunden++;
            	break;
            	
            case 27:
            	//esc
            	//menue beenden    	
            	
            	//in julians funk.

            	time(&ende); //timer beenden
   			 	ende -= start; //gebrauchte zeit berechen
    			iZeit += ende;
            	write_esc();
            	break;
                
            default:
				;
//#warning system("pause") oder getch() ??
        }
       	 //bEnd=1;   //debugging
				if(irunden>=10)
				{
				irunden=0;
				bEnd=1;
				printf("\n\n\nAnzahl  ueberschritten");
				ineustart = 1;
				game_over();
				}
				
    	}while (bEnd == 0);
    
    
  
   // cout << "\n \n Du hast " << iScore << " Sekunden gebraucht.\n";
    MoveWindow(hwnd,0,0,10000,340,TRUE);   //Konsolengröße zurücksetzen
    
}

void printPins()					//Henrik Storch
{
	int ischwarz=0;
	int iweiss=0;
	printHistory();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
	printf("Runde: %i",irunden+1);
		
	for(int i; i<5;i++)
	{
	//	printf("\n PP: %i;  %i;  %i\n ",i,iPin,iStiftFarbe[i] [irunden]);   		//debugging note :)
		if(i == iPin)
		{
			switch(iStiftFarbe[i] [irunden])
			{
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
					printf(" 	\xdc ");
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdc ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdc ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdc ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdc ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");


//#warning Debug printf!
			}		
			
		}else
		{		
			switch(iStiftFarbe[i] [irunden])
			{
	
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
					printf(" 	\xdb ");
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 191)\n\n");
//#warning Debug printf!
			}
		}
	
	}

}


void printHistory()					//Henrik Storch
{
	int ischwarz;
	int iweiss;
	
	for(int iRunde=0;iRunde<irunden;iRunde++)
	{
			iweiss=0;							//	##################### zuruücksetzen der pins nach jeder Runde
			ischwarz=0;							//  ##################### 
			
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),23);
			printf("Runde: %i",iRunde+1);
			for(int i=0; i<5;i++){
				//printf("\n PH: %i;  %i; %i \n ",i,iPin,iStiftFarbe[i] [iRunde]);   		//debugging note :)
				switch(iStiftFarbe[i] [iRunde])
				{
					case 0:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);
						printf(" 	² ");
						break;
						
					case 1:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
						printf(" 	² ");
						break;
						
					case 2:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
						printf(" 	² ");
						break;
						
					case 3:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
						printf(" 	² ");
						break;
						
					case 4:
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
						printf(" 	² ");
						break;
					default:
						printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");
	
	
//#warning Debug printf!
				}
		
			}
			ivergl(iRunde);
		printf("\n \n \n \n");
	}
}





	 void irand()				//Maximilian Hudelmaier
	 {
	 	srand(time(NULL));
		int izahl;
	 	for(izahl=0;izahl<=4;izahl++)
	 	{
	   		//ians[izahl] = 2;
	   		ians[izahl] = random2(4);
	  	//	printf("%i\n\n",ians[izahl]);  //debuging
	  
	 	}
	
    }


void ivergl(int iRunde)				//Julian Kugler u. Maximilian Hudelmaier
{
	

	int itestans[5] = {0,0,0,0,0};				//Testwerte
	int itestfarbe[5] = {0,0,0,0,0};;
	int ischwarz[5] = {0,0,0,0,0};				//0 = kein schwarzer pin  1= schwarzer pin
	int iweiss[5] = {0,0,0,0,0};				//0 = kein weißer pin  1= weißer pin
	int istiftweiss;							 //istiftschwarz;	---> global							//Angeben der Gesamtanzahl der schwarzen und weißen pins

	
//	for(int i=0; i <= 4; i++)
//	{
//		btestfarbe[i] = 1;
//		btestans[i] = 1;
//	}
		
	for(int i=0 ; i<=4 ; i++)
	{
		if(ians[i] == iStiftFarbe[i] [iRunde])	//Antwort gleich Versuch ?
		{
			ischwarz[i] = 1;				//setzt entsprechenden schwarzen Pins auf 1
			itestans[i] = 1;				
			itestfarbe[i] = 1;
		}
		//else if(ians[0] == iStiftFarbe[i] || ians[1] == iStiftFarbe[i] || ians[2] == iStiftFarbe[i] || ians[3] == iStiftFarbe[i] || ians[4] == iStiftFarbe[i])	//Abfrage, ob die farbe IRGENDWO in der Lösung vorkommt
	}
/*	for(int i=0; i <= 4; i++)
	{
	//	printf("%i %i\n",btestans[i],btestfarbe[i]);
	}*/
	for(int i=0 ; i<=4 ; i++)
	{
		//printf("for");
		if(itestans[i] == 0)
		{
		//	printf("i = %i btestans[i] == true \n",i);					//Debug
			for(int i2=0 ; i2<=4 ; i2++)
			{
				if(itestfarbe[i2] == 0)
				{
				//	printf("i2 = %i btestans[i2] == true \n",i2);		//Debug
					if(ians[i] == iStiftFarbe[i2] [iRunde])
					{
						iweiss[i] = 1;
						itestfarbe[i2] = 1;
						itestans[i] = 1;
						//printf("weiss!");								//Debug
					}
				}
			}
		}
	}
	
	istiftweiss = iweiss[0] + iweiss[1] + iweiss[2] + iweiss[3] + iweiss[4];					//Zusammenzählen des Codes für die Anzahl der Pins    Bisher: 01001 oder so   ---> istiftweiss = Gesamtanzahl der weißen stifte
	istiftschwarz = ischwarz[0] + ischwarz[1] + ischwarz[2] + ischwarz[3] + ischwarz[4];		//istiftschwarz = Gesamtanzahl der schwarzen stifte
	
	/*
	
	printf("%i %i %i %i %i\n\n",ians[0], ians[1], ians[2], ians[3], ians[4]);					//Debugging
	printf("%i %i %i %i %i\n\n",iStiftFarbe[0], iStiftFarbe[1], iStiftFarbe[2], iStiftFarbe[3], iStiftFarbe[4]);			//Debugging
	getch();																										//Debugging
	printf("%i %i %i %i %i    schwarz\n\n",ischwarz[0], ischwarz[1], ischwarz[2], ischwarz[3], ischwarz[4]);		//Debugging
	printf("%i %i %i %i %i    weiss\n\n",iweiss[0], iweiss[1], iweiss[2], iweiss[3], iweiss[4]);					//Debugging
	getch();																										//Debugging
	printf("%i   schwarze pins\n\n",istiftschwarz);																	//Debugging
	printf("%i   weisse pins\n\n",istiftweiss);	
	*/																	//Debugging
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),23);
	
	for(int i3=0 ; i3 < istiftschwarz ; i3++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),16);	//schwarz
		printf("   \xdb ");
	}					
	
	for(int i4 = 0 ; i4 < istiftweiss ; i4++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),31);	//weiß
		printf("   \xdb ");
	}
	
	if(istiftschwarz >= 5){
		win();
	}
	
}
	
	


/*void write_Highscore(){	
	#warning HIGHSCORES NOCH MACHEN!!!!  dafür namen benötigt!!
	system("cls");
	for(int i;i<10;i++){
		cout << sNames[i] << iHighScore[i]<<endl;
	}
	getch();
	
}*/


void spiel_laden()				//Henrik Storch
{
      //Spielernamen
      string line;
      ifstream ln;
      ln.open("Spielernamen.dat", ios::in);
      for(int i;i<10;i++)
	  {
   		   ln >> sNames[i];
   		   cout << sNames[i]<<endl;
	}
      ln.close();
     /* //Spielstand gesamt
      ifstream la;
      la.open("Speicher/History.dat", ios::in);
      getline (la,line);
      getline (la,line);
      istringstream inStream(line);
      inStream >> istart;
      getline (la,line);
      istringstream inStream2(line);
      inStream2 >> ispielstand;
      la.close();
      */
      
      ifstream la;
      la.open("irunden.dat", ios::in);
      getline (la,line);
      istringstream inStream(line);
      inStream >> irunden;
      irunden++;
      la.close();
      
      
      
      //Spielstand Spieler1
      ifstream l1;
      l1.open("History.dat", ios::in);
      for(int i=0; i<5; i++)
      {
        getline (l1,line);
        istringstream inStream(line);
        inStream >> ians[i];
      }
      
      	for(int iRunde=0;iRunde<=irunden;iRunde++){
      		for(int i=0;i<5;i++){
      			
      			getline (l1,line);
      		  	istringstream inStream(line);
      			inStream >> iStiftFarbe[i] [iRunde];
			  }
		}

      
       for(int iRunde=0;iRunde<=irunden;iRunde++){
     		for(int i=0;i<5;i++){
   				getline (l1,line);
   			  	istringstream inStream(line);
      			inStream >> istift [i] [iRunde];
			  }
		}
	l1.close();
	
	
      ifstream sc;
      sc.open("score.dat", ios::in);
      getline (sc,line);
      istringstream instream(line);
      instream >> iScore;
      sc.close();
      
      
       ifstream hs;
      hs.open("Highscore.dat", ios::in);
      for(int i=0; i<10; i++)
      {
        getline (hs,line);
        istringstream inStream(line);
        inStream >> iHighScore[i];
  }
	hs.close();	
	
	
}

void win()			//Henrik Storch
{
	bEnd=1;
	bneuesSpiel=1;
	time(&ende); //timer beenden
    ende -= start; //gebrauchte zeit berechen
    iScore=ende+iZeit;
   
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),23);
	write_win();
	
/*	if(iScore>iHighScore[9]){
		printf("\n Das ist ein neuer Highscore!! Speicher J/N ??");
		
		if(1==1){
			#warning menuestrg
			printf("Bitte gib deinen namen ein(max. 10 Zeichen):\n");
			cin >> cSpieler;
		//	cout << cSpieler;
		bool bflag=0;
			for(int i;i<10;i++){
				if(iHighScore[i] == 0) {
				iHighScore[i]=iScore;
				bflag=1;
				break;
				}
			}
			if(bflag==0) iHighScore[9]=iScore; 
			
			int itausch;
			bflag=0;
		do 
		{
			bflag = false;
		
			for (int iz = 0; iz < 10; iz++)
				{
					if (iHighScore[iz] > iHighScore[iz+1])
					{
						itausch   = iHighScore[iz];
						iHighScore[iz] = iHighScore[iz+1];
						iHighScore[iz+1] = itausch;
					
						bflag=true;	
					}	
							
				}
		}
		while (bflag == true);
		
		int iIndex;
		for(int i;i<10;i++){
			if(iHighScore[i] == iScore) iIndex=i;
			printf("%i",iIndex);
		}
		
		string sTausch;
		sNames [iIndex] = cSpieler;
		iIndex++;
		for(iIndex;iIndex<10;iIndex++){
			sNames[iIndex] = sTausch;
			sNames[iIndex+1] = sNames[iIndex];
			sNames[iIndex]=sTausch;
			
		}
			for(int i;i<10;i++){
				cout<<sNames[i]<<endl;
			}
			
			
		}
	}
	*/
	
}




void write_esc()			//Julian Kugler
{
	
	int ikey = 0;			//Pfeiltasten-code
	int iauswahl = 1;		//Angabewert für anzugebenden Bildschirm
	int bende4 = 1;
	
	iauswahl = 1;				// Bildschirmauswahl
		do
		{
			bende = 1;
			//ikey = igetkey();		//Pfeiltastenerkennung
				
			switch(ikey)
			{			
				case 333:			//Pfeiltaste rechts
					iauswahl++;
					if(iauswahl == 3)
					{
						iauswahl = 2;
					}
					break;
					
				case 331:			//Pfeiltaste links
					iauswahl--;
					if(iauswahl == 0)
					{
						iauswahl = 1;
					}
					break;
					
				default:
					;				
			}
			
			switch(iauswahl)		//Bildschirmänderung in Abhängigkeit von der zuletzt gedrückten Pfeiltaste
				{
					case 1:						//erster Bildschirm
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);	
						system("CLS");											
						printf("\n\n\n\n\n                    Wollen Sie dieses Spiel wirklich beenden?\n\n");
						printf("                    Bisheriger Fortschritt wird gespeichert!\n\n\n");
						printf("                                  <Ja>     Nein\n\n\n\n");
						break;
						
					case 2:						//zweiter Bildschirm
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
						system("CLS");
						printf("\n\n\n\n\n                    Wollen Sie dieses Spiel wirklich beenden?\n\n");
						printf("                    Bisheriger Fortschritt wird gespeichert!\n\n\n");
						printf("                                   Ja     <Nein>\n\n\n\n");
						break;
						
					default:
						;
				}
					ikey = getch();
					if (ikey == 0 || ikey == 224)
					{
						ikey = 256 + getch();				//Pfeiltastenerkennung 		// ikey == 333 ---> Pfeiltaste rechts	//ikey == 331 ---> Pfeiltaste links
					}
						else if(ikey == 13)						//Erkennung von Drücken von Enter im Auswahlmenü
					{
						switch(iauswahl)
						{
							case 1:
								bende4 = 0;
								ineustart = 0;
								bEnd = 1;
								break;
								
							case 2:
								bende4 = 0;
 							  	time(&start);//timer starten
								break;
								
							default:
								;
								
						}	
					}
		}while(bende4 == 1);

}


void spiel_speichern(){			//Henrik Storch
	
	//Spieler
      fstream sn;
      sn.open("Spielernamen.dat", ios::out | ios::trunc);
      for(int i;i<10;i++){
    		sn << sNames[i] << endl;;
	}
   	sn.close();
      
      fstream ir;
      ir.open("irunden.dat", ios::out | ios::trunc);
      ir << irunden << endl;
      ir.close();
      
      
      //Spielstand gesamt
      fstream sa;
      sa.open("History.dat", ios::out | ios::trunc);
      
      for(int i=0;i<5;i++){
      	sa << ians[i] << endl;
	  }
      
		for(int iRunde=0;iRunde<=irunden;iRunde++){
      		for(int i=0;i<5;i++){
      			sa << iStiftFarbe[i] [iRunde] << endl;
			  }
		}
      
      for(int iRunde=0;iRunde<=irunden;iRunde++){
      		for(int i=0;i<5;i++){
      			sa << istift[i] [iRunde] << endl;
			  }
		}
      
      sa.close();
      
		fstream sc;
    sc.open("score.dat", ios::out | ios::trunc);
    sc << iZeit << endl;
    sc.close();
      
      
      fstream hs;
      hs.open("Highscore.dat",ios::out | ios::trunc);
      for(int i=0;i<10;i++){
      	hs << iHighScore [i] << endl;
	  }
	  hs.close();

}





	
	
	
	//############################################################################################################################
	//###########################################################################################################################
	
	
	
	
	
	
	
	
	
	
	
	
	
	
//31=weiß 26=grün
		
void write_header()				//Julian Kugler
{
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 31);
	printf("\n\n  ²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n");
	printf("  ²²                                                                        ²²\n");
	printf("  ²²    ²   ²      ²    ²²²   ²²²²²   ²²²   ²²     ²   ²    ²   ²  ²  ²²    ²²\n");
	printf("  ²²   ² ² ² ²    ² ²  ²        ²    ²     ²  ²   ² ² ² ²   ²  ² ² ²  ² ²   ²²\n");
	printf("  ²²   ² ² ² ²    ² ²  ²        ²    ²     ²  ²   ² ² ² ²   ²  ² ² ²  ²  ²  ²²\n");
	printf("  ²²   ² ² ² ²    ² ²   ²²²     ²     ²²²  ²²²    ² ² ² ²   ²  ² ² ²  ²  ²  ²²\n");										//MASTERMIND HEADER  ----> der IMMER bestehen bleibt !!!
	printf("  ²²  ²   ²   ²  ²²²²²     ²    ²    ²     ² ²   ²   ²   ²  ²  ² ² ²  ²  ²  ²²\n");
	printf("  ²²  ²   ²   ²  ²   ²     ²    ²    ²     ²  ²  ²   ²   ²  ²  ² ² ²  ² ²   ²²\n");
	printf("  ²²  ²   ²   ²  ²   ²  ²²²     ²     ²²²  ²  ²  ²   ²   ²  ²  ²  ²   ²²    ²²\n");
	printf("  ²²                                                                        ²²\n");
	printf("  ²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n\n\n");
}

void write_starten()																							//Grünes Feld: Spiel starten		//Julian Kugler
{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						
						SetConsoleTextAttribute(hConsole, 26);	
						printf("   ²²²²²²²²²²²²²²²²²");
	
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²\n");
	
						SetConsoleTextAttribute(hConsole, 26);
						printf("   ²²             ²²");
	
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²  ²²             ²²  ²²             ²²\n");
	
						SetConsoleTextAttribute(hConsole, 26);
						printf("   ²²    Spiel    ²²");
		
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²    Spiel    ²²  ²²   Spiel-    ²²  ²²    Spiel    ²²\n");
	
						SetConsoleTextAttribute(hConsole, 26);
						printf("   ²²   starten   ²²");
	
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²    laden    ²²  ²²  anleitung  ²²  ²²   beenden   ²²\n");
	
						SetConsoleTextAttribute(hConsole, 26);
						printf("   ²²             ²²");
	
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²  ²²             ²²  ²²             ²²\n");
	
						SetConsoleTextAttribute(hConsole, 26);
						printf("   ²²²²²²²²²²²²²²²²²");
	
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²\n\n\n\n");

}

void write_laden()																							//grünes Feld: "Spiel laden"		//Julian Kugler
{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						
						SetConsoleTextAttribute(hConsole, 31);	
						printf("   ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²\n");
						printf("   ²²             ²²");	
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²  ²²             ²²\n");
						printf("   ²²    Spiel    ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²    Spiel    ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²   Spiel-    ²²  ²²    Spiel    ²²\n");
						printf("   ²²   starten   ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²    laden    ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²  anleitung  ²²  ²²   beenden   ²²\n");
						printf("   ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²  ²²             ²²\n");
						printf("   ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²\n\n\n\n");


}

void write_spielregeln()																		//grünes Feld: "Bestenlisten"		//Julian Kugler
{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
						
						printf("   ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²\n");
						printf("   ²²             ²²  ²²             ²²");

						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²\n");
						printf("   ²²    Spiel    ²²  ²²    Spiel    ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²   Spiel-    ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²    Spiel    ²²\n");
						printf("   ²²   starten   ²²  ²²    laden    ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²  anleitung  ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²   beenden   ²²\n");
						printf("   ²²             ²²  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²             ²²\n");
						printf("   ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("  ²²²²²²²²²²²²²²²²²\n\n\n\n");


}

void write_beenden()																	//grünes Feld: "Spiel beenden"		//Julian Kugler
{
						HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
						printf("   ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²\n");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("   ²²             ²²  ²²             ²²  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²\n");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("   ²²    Spiel    ²²  ²²    Spiel    ²²  ²²   Spiel-    ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²    Spiel    ²²\n");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("   ²²   starten   ²²  ²²    laden    ²²  ²²  anleitung  ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²   beenden   ²²\n");
						
						SetConsoleTextAttribute(hConsole, 31);
						printf("   ²²             ²²  ²²             ²²  ²²             ²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²             ²²\n");

						SetConsoleTextAttribute(hConsole, 31);
						printf("   ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²  ²²²²²²²²²²²²²²²²²");
						
						SetConsoleTextAttribute(hConsole, 26);
						printf("  ²²²²²²²²²²²²²²²²²\n\n\n\n");


}


void write_regeln()					//Julian Kugler
{
	char css = 0xe1;		//Buchstabe ß
	char coe = 0x94;		//Buchstabe ö
	char cue = 0x81;		//Buchstabe ü
	
	HWND hwnd = FindWindow("ConsoleWindowClass",NULL); 
	
	MoveWindow(hwnd,0,0,10000,1000,TRUE);
	
	system("CLS");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 26);
	
	printf("\n ²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Spielregeln:                                                              ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Der Computer gibt eine Kombination von 5 Farben mit 5 Stiften an.         ²\n");
	printf(" ²  Der Spieler kennt diese Kombination nicht.                                ²\n");
	printf(" ²  Es gilt nun diesen Farbcode innerhalb von 10 Versuchen zu erraten!        ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Hilfsmittel:                                                              ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Nach dem Bet\x84tigen der Enter Taste erscheinen rechts neben dem Versuch    ²\n");
	printf(" ²  h%cchstens 5 Stifte mit den Farben Schwarz oder Wei%c.                      ²\n",coe, css);
	printf(" ²                                                                            ²\n");
	printf(" ²  Die Anzahl der schwarzen Stifte gibt an, wie viele der erratenen          ²\n");
	printf(" ²  Stifte richtig gesetzt sind!                                              ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Die Anzahl der wei%cen Stifte gibt an, wie viele der erratenen Stifte      ²\n", css);
	printf(" ²  zwar die richtige Farbe haben, sich aber am falschen Platz befinden!      ²\n");
	printf(" ²  Zwei gleiche Farben, die richtig sind aber sich am falschen               ²\n");
	printf(" ²  Platz befinden, z\x84hlen als ein wei%cer Stift                               ²\n",css);
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Weitere Hinweise:                                                         ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Das Spiel wird nach jedem Enterdruck gespeichert                          ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Es kann jederzeit durch den Button: -Spiel laden- am zuletzt              ²\n");
	printf(" ²  gespeicherten Punkt fortgesetzt werden.                                   ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Wird ein bereits gewonnenes oder verlorenes Spiel geladen, so wird        ²\n");
	printf(" ²  ein neues Spiel gestartet!                                                ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Steuerung:                                                                ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Zwischen den einzelnen Pins und Farben wird mit den Pfeiltasten           ²\n");
	printf(" ²  navigiert. Mit den Pfeiltasten rechts und links wird der jeweilige        ²\n");
	printf(" ²  Pin gew\x84hlt. Mit den Pfeiltasten oben und unten wird die                  ²\n");
	printf(" ²  jeweilige Farbe gew\x84hlt.                                                  ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²  Durch das Dr%ccken von Enter wird die derzeitige Runde best\x84tigt.          ²\n",cue);
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²                                                                            ²\n");
	printf(" ²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²²\n");


		
	getch();
	
	MoveWindow(hwnd,0,0,10000,340,TRUE);
}



void write_win()			//Julian Kugler
{
	
	bneuesSpiel=1;
	
	bool bende = 1;
	
	do
	{
	
	if(kbhit())								//Keyboardhit
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 26);
	printf("\n\n\n\n\n\n\n\n               ²   ²   ²     ²²   ²²²²²    ²²²     ²²    ²   ²\n");
	printf("               ²   ²   ²    ²       ²     ²   ²   ²  ²    ² ²\n");
	printf("               ²   ²   ²   ²        ²     ²   ²   ²  ²    ² ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ²²²      ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ² ²      ²\n");
	printf("                ² ²    ²    ²       ²     ²   ²   ²  ²     ²\n");
	printf("                 ²     ²     ²²     ²      ²²²    ²  ²     ²\n\n\n\n\n\n");
	printf("                     Sie haben %i Sekunden gebraucht !", iScore);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
		system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 27);
	printf("\n\n\n\n\n\n\n\n               ²   ²   ²     ²²   ²²²²²    ²²²     ²²    ²   ²\n");
	printf("               ²   ²   ²    ²       ²     ²   ²   ²  ²    ² ²\n");
	printf("               ²   ²   ²   ²        ²     ²   ²   ²  ²    ² ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ²²²      ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ² ²      ²\n");
	printf("                ² ²    ²    ²       ²     ²   ²   ²  ²     ²\n");
	printf("                 ²     ²     ²²     ²      ²²²    ²  ²     ²\n\n\n\n\n\n");
	printf("                     Sie haben %i Sekunden gebraucht !", iScore);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
    
    system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 29);
	printf("\n\n\n\n\n\n\n\n               ²   ²   ²     ²²   ²²²²²    ²²²     ²²    ²   ²\n");
	printf("               ²   ²   ²    ²       ²     ²   ²   ²  ²    ² ²\n");
	printf("               ²   ²   ²   ²        ²     ²   ²   ²  ²    ² ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ²²²      ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ² ²      ²\n");
	printf("                ² ²    ²    ²       ²     ²   ²   ²  ²     ²\n");
	printf("                 ²     ²     ²²     ²      ²²²    ²  ²     ²\n\n\n\n\n\n");
	printf("                     Sie haben %i Sekunden gebraucht !", iScore);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }

	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 30);
	printf("\n\n\n\n\n\n\n\n               ²   ²   ²     ²²   ²²²²²    ²²²     ²²    ²   ²\n");
	printf("               ²   ²   ²    ²       ²     ²   ²   ²  ²    ² ²\n");
	printf("               ²   ²   ²   ²        ²     ²   ²   ²  ²    ² ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ²²²      ²\n");
	printf("                ² ²    ²   ²        ²     ²   ²   ² ²      ²\n");
	printf("                ² ²    ²    ²       ²     ²   ²   ²  ²     ²\n");
	printf("                 ²     ²     ²²     ²      ²²²    ²  ²     ²\n\n\n\n\n\n");
	printf("                     Sie haben %i Sekunden gebraucht !", iScore);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }

	
	}while(bende == 1);
	
	ineustart = 1;
	
}

void game_over()			//Julian Kugler
{
	//	PlaySound(TEXT("game_over.wav"), NULL, SND_ASYNC);
	
	bneuesSpiel=1;
	
	bool bende = 1;
	
	if(istiftschwarz >= 5)
	{
		bende = 0;
	}
	
	while(bende == 1)
	{
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 28);
	printf("\n\n\n\n\n\n\n\n        ²²²      ²       ²   ²      ²²²       ²²²    ²   ²    ²²²    ²²\n");
	printf("       ²        ² ²     ² ² ² ²    ²         ²   ²   ²   ²   ²      ²  ²\n");
	printf("       ²        ² ²     ² ² ² ²    ²         ²   ²   ²   ²   ²      ²  ²\n");
	printf("       ² ²²     ² ²     ² ² ² ²     ²²²      ²   ²    ² ²     ²²²   ²²²\n");
	printf("       ²   ²   ²²²²²   ²   ²   ²   ²         ²   ²    ² ²    ²      ² ²\n");
	printf("       ²   ²   ²   ²   ²   ²   ²   ²         ²   ²    ² ²    ²      ²  ²\n");
	printf("        ²²²    ²   ²   ²   ²   ²    ²²²       ²²²      ²      ²²²   ²  ²\n\n\n\n\n\n\n\n\n\n");

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	printf(" Der richtige Code w\x84re gewesen:\n\n\n");
	
	for(int i=0; i<5;i++)
		{
		switch(ians[i])
			{																				//Antwortcode für Test !!
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);			
					printf(" 	\xdb ");												// \xdb  -- ausgefüllter Kasten
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");
			}
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
		printf("\n\n\nIhr letzter Versuch war:\n\n\n");
	
		for(int i=0 ; i <=4 ; i++)
		{
			switch(iStiftFarbe[i] [9])
			{
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);			
					printf(" 	\xdb ");												// \xdb  -- ausgefüllter Kasten
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");
			}
		}

	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	system("CLS");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	printf("\n\n\n\n\n\n\n\n        ²²²      ²       ²   ²      ²²²       ²²²    ²   ²    ²²²    ²²\n");
	printf("       ²        ² ²     ² ² ² ²    ²         ²   ²   ²   ²   ²      ²  ²\n");
	printf("       ²        ² ²     ² ² ² ²    ²         ²   ²   ²   ²   ²      ²  ²\n");
	printf("       ² ²²     ² ²     ² ² ² ²     ²²²      ²   ²    ² ²     ²²²   ²²²\n");
	printf("       ²   ²   ²²²²²   ²   ²   ²   ²         ²   ²    ² ²    ²      ² ²\n");
	printf("       ²   ²   ²   ²   ²   ²   ²   ²         ²   ²    ² ²    ²      ²  ²\n");
	printf("        ²²²    ²   ²   ²   ²   ²    ²²²       ²²²      ²      ²²²   ²  ²\n\n\n\n\n\n\n\n\n\n");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
	printf(" Der richtige Code w\x84re gewesen:\n\n\n");
	
	for(int i=0; i<5;i++)
		{
		switch(ians[i])
			{																				//Antwortcode für Test !!
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);			
					printf(" 	\xdb ");												// \xdb  -- ausgefüllter Kasten
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");
			} 
		}
		
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 23);
		printf("\n\n\nIhr letzter Versuch war:\n\n\n");
	
		for(int i=0 ; i <=4 ; i++)
		{
			switch(iStiftFarbe[i] [9])
			{
				case 0:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),28);			
					printf(" 	\xdb ");												// \xdb  -- ausgefüllter Kasten
					break;
					
				case 1:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),27);
					printf(" 	\xdb ");
					break;
					
				case 2:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),26);
					printf(" 	\xdb ");
					break;
					
				case 3:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),30);
					printf(" 	\xdb ");
					break;
					
				case 4:
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),29);
					printf(" 	\xdb ");
					break;
				default:
					printf("\n\n fehler beim Zeichen der Pins (Z. 147)\n\n");
			}
		}


	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	
	sleep(1);
	
	if(kbhit())
    {
        int key = getch();
        if(key == 13)
            break;
    }
	}
	
	ineustart = 1;
	
}








