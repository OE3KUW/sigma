//*****************************************************************************
//
//
//                              Σ i g m a 2 4
//
//
//                                                              қuran 2024
//*****************************************************************************
// history:
// 2024 01 Stundentafeln für Bionics, Wireless und Embeded systems vorbereitet
// 2023.06 refactoring; mah Liste einbezogen
// 2022.05 automatische Verzeichnisse für das Jahr und Monat erstellt
// 2022.06 Abhaengig vom Monat Daten des Wintersemesters (123456) oder SS entw.
// 2022.06 Embedded und Wireless muss noch in ein und selbe Klasse!
// 2022.06 auch die 3AHELS braucht SigmaWerte / je nach sommer oder Winter!
// 2022.06 erstelle Liste aller NG fuer die EL
// 2022.11 alle ; werden durch , ersetzt, gilt für Liste.csv
// 2022.11 die 5ten Klassen sollten auch in die sigma Liste aufgenommen werden!
// 2022.12 resort the sigma list. nr, names ...
// 2023.02 Prognose für EL, und Begründungen schon ab > = 30.Prozent!
// 2023.02 1AO -> 1OHIF; 1BO -> 1PHIF ukrainische Klassen der IF zugeordnet
// 2023.02 sigmaList.txt ebenfalls ins Dir speichern
// 2023.02 filtere alle 5er und N heraus: Step 6!
//*****************************************************************************
// usage:
// 1.)
// Sokrates > Auswertung: Dynamische Suche > Kategorie: Direktor
//          > 404 Schüler mit Noten
//          Kurzbezeichnung, Note, Schulformkennzahl
//          Ausführen, das kann dauern - soll das Ergebnis angezeigt werden ja
//          etwa 7 Minuten...
// Exportieren als Liste.csv - ACHTUNG SEMIKOLOM
// 2.)  define Jahresschluss richtigstellen,
// 3.)  sind in der Liste , als Trenner verwendet / falls nein, aendern!!!
// sokrates > Auswertung > Standard > 152 > FW-Datum, Gegenstand, LehrerIn, Art
// speichern unter: home>sigma>Mah.csv
//*****************************************************************************
// next steps:
// erweitere Linux Version
// verwende neue Stundentafeln
//*****************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "console.h"


#define LINEMAX            8000
#define LEN                 200
#define SMAX                800
#define TRUE                  1
#define FALSE                 0

#define SELTSAME_NOTEN_AUSGEBEN

    /**┌────────────────────────────────────────────────┐**/
    /**  G l o b a l e  Variablen                        **/


//                  0 1 2 3 4 5 6 7   8 9 0 1 2 3 4 5 6 7 8 9 0 1   2 3 4 5 6
//                  1 1 2 2 3 3 4 4   1 1 2 2 3 3 4 4 4 4 5 5 5 5   1 2 3 4 5
//                  F F F F F F F F   H H H H H H H H H H H H H H   H H H H H
//                  S J W S W W W S   S J W S W S W S W S S J S J   S W W W S
//                                                E E W W E E W W   b i o n i c s
int weight[][27] = {
/*AELT*/           {4,4,4,4,3,3,2,3,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*AM  */           {2,2,2,2,2,2,0,0,  4,4,4,4,3,3,2,2,2,2,2,2,2,2,  4,4,3,2,2},
/*BESP*/           {2,2,2,2,2,2,1,1,  2,2,2,2,2,2,1,1,1,1,1,1,1,1,  2,2,2,1,1},
/*COIT*/           {0,0,0,0,2,2,2,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*CTNT*/           {1,1,2,2,3,3,1,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*D   */           {0,0,0,0,0,0,0,0,  3,3,2,2,2,2,2,2,2,2,2,2,2,2,  3,2,2,2,2},
/*DUK */           {3,3,3,3,2,2,2,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*DIC1*/           {0,0,0,0,0,0,0,0,  0,0,1,1,2,2,2,2,2,2,3,3,2,2,  0,1,2,2,3},
/*E1  */           {2,2,2,2,2,2,0,0,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2},
/*E2  */           {0,0,0,0,0,0,1,2,  0,0,0,0,0,0,2,2,2,2,0,0,0,0,  0,0,1,1,1}, // jeweils 1 wertig - gleich in welchem Jahrgang
/*ELDE*/           {2,2,2,2,2,2,1,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*ELWP*/           {5,5,5,5,4,4,2,5,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*FSST*/           {0,0,0,0,0,0,0,0,  3,3,3,3,3,3,4,4,2,2,5,5,2,2,  3,3,3,2,2},
/*GGP */           {2,2,1,1,0,0,0,0,  2,2,2,2,2,2,2,2,2,2,0,0,0,0,  2,2,2,2,0},
/*HWE1*/           {0,0,0,0,0,0,0,0,  6,6,5,5,3,3,4,4,4,4,7,7,7,7,  5,5,3,4,7}, // Projectnote zu HWE und Labor zugeschlagen
/*KMEL*/           {0,0,2,2,3,3,1,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*KSN1*/           {0,0,0,0,0,0,0,0,  0,0,0,0,2,2,2,2,3,3,2,2,4,4,  0,0,2,2,2},
/*LAB */           {0,0,0,0,3,3,2,4,  0,0,0,0,3,3,4,4,4,4,8,8,8,8,  0,0,3,4,8},
/*MTRS*/           {0,0,0,0,0,0,0,0,  0,0,2,2,2,2,2,2,3,3,2,2,4,4,  0,2,2,2,3},
/*NNWP*/           {4,4,4,4,8,8,2,4,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*NW2 */           {0,0,0,0,0,0,0,0,  3,3,3,3,2,2,2,2,2,2,0,0,0,0,  3,3,2,2,0},
/*NWG */           {2,2,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*PBE */           {0,0,0,0,0,0,0,0,  7,7,7,7,8,8,4,4,4,4,0,0,0,0,  7,7,8,4,0},
/*R   */           {2,2,2,2,2,2,1,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2},
/*RK  */           {2,2,2,2,2,2,1,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2},
/*REL */           {2,2,2,2,2,2,1,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2},
/*ETH */           {2,2,2,2,2,2,1,2,  2,2,2,2,2,2,2,2,2,2,2,2,2,2,  2,2,2,2,2},
/*SOTE*/           {2,2,2,2,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*UNF */           {0,0,2,2,2,2,1,1,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},
/*WIR3*/           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,3,3,3,3,2,2,2,2,  0,0,0,3,2},
/*SOPK*/           {1,1,1,1,0,0,0,0,  1,1,1,1,0,0,0,0,0,0,0,0,0,0,  1,0,0,1,0},
/*NEW */           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2}, // wireless
/*NEW */           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2}, // bionics
/*NEW */           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2}, // embedded
/*FOEX*/           {1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1},
/*WIRE*/           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2},
/*BION*/           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2},
/*EMBE*/           {0,0,0,0,0,0,0,0,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,1,1,2,2},
/*ORC5*/           {1,1,1,1,1,1,1,1,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,  1,1,1,1,1}  // bringt das eine Notenschnittsverbesserung ?
};

 char SubNames[][LINEMAX] =
    {
/*AELT*/    "Englisch                                                                       ",
/*AM  */    "Naturwissenschaftliche Grundlagen                                              ",
/*BESP*/    "Deutsch und Kommunikation                                                      ",
/*COIT*/    "Softwaretechnik                                                                ",
/*CTNT*/    "Netzwerktechnik - Werkstätte und Produktionstechnik                            ",
/*D   */    "Angewandte Mathematik                                                          ",
/*DUK */    "Computer- und Netzwerktechnik                                                  ",
/*DIC1*/    "Angewandte Elektronik                                                          ",
/*E1  */    "Geografie                                                                      ",
/*E2  */    "Elektronik - Werkstätte und Produktionstechnik                                 ",
/*ELDE*/    "Naturwissenschaften                                                            ",
/*ELWP*/    "Elektronik Design                                                              ",
/*FSST*/    "Fachspezifische Softwaretechnik                                                ",
/*GGP */    "Hardwareentwicklung                                                            ",
/*HWE1*/    "Antriebstechnik und Mechatronik                                                ",
/*KMEL*/    "Computerunterstützte Projektentwicklung                                        ",
/*KSN1*/    "Angewandte Informatik                                                          ",
/*LAB */    "Datenbanken und Informationssysteme                                            ",
/*MTRS*/    "Programmieren und Software Engineering                                         ",
/*NNWP*/    "Energiesysteme - Werkstätte und Produktionstechnik                             ",
/*NW2 */    "Energiesysteme                                                                 ",
/*NWG */    "Bewegung und Sport                                                             ",
/*PBE */    "Betriebswirtschaft und Management                                              ",
/*R   */    "Antriebstechnik und Mechatronik                                                ",
/*RK  */    "Antriebstechnik und Mechatronik - Werkstätte und Produktionstechnik            ",
/*REL */    "Automatisierungstechnik                                                        ",
/*ETH */    "Computergestützte Projektentwicklung                                           ",
/*SOTE*/    "Fertigungstechnik 1                                                            ",
/*UNF */    "Konstruktion und Projektmanagement                                             ",
/*WIR3*/    "Elektrotechnik und Automatisierungstechnik                                     ",
/*SOPK*/    "Fertigungstechnik 1 - Werkstätte und Produktionstechnik                        ",
/*NEW */    "Betriebstechnik                                                                ",
/*NEW */    "Produktionstechnologie und Werkstoffe                                          ",
/*NEW */    "Informatik und Informationssysteme                                             ",
/*FOEX*/    "Technische Mechanik und Berechnung                                             ",
/*WIRE*/    "Werkstätte und Produktionstechnik                                              ",
/*BION*/    "Elektrotechnik und Elektronik                                                  ",
/*EMBE*/    "Maschinen und Anlagen                                                          ",
/*ORC5*/    "Wirtschaft und Recht                                                           ",
    "Prozessmanagement                                                              ",
    "Laboratorium                                                                   ",
    "Anlagen- und Prüftechnik                                                       ",
    "Netzwerksysteme und Cyber Security                                             ",
    "Netzwerksysteme und Verteilte Systeme                                          ",
    "Webprogrammierung und Mobile Computing                                         ",
    "Robotik und Prozessdatenverarbeitung                                           ",
    "Systemplanung und Projektentwicklung                                           ",
    "Produktmanagement                                                              ",
    "Industrieelektronik                                                            ",
    "Digitale Systeme und Computersysteme                                           ",
    "Messtechnik und Regelungssysteme                                               ",
    "Kommunikationssysteme und -netze                                               ",
    "Maschinen- und Elektrotechnik                                                  ",
    "Prototypenbau elektronischer Systeme                                           ",
    "Fachspezifische Informationstechnik                                            ",
    "Technische Mechanik und Berechnung                                             ",
    "Mechanik und Maschinenelemente                                                 ",
    "Fertigungstechnik 2                                                            ",
    "Unternehmensführung                                                            ",
    "Automatisierungstechnik und Industrieelektronik                                ",
    "Automatisierungstechnik und Industrieelektronik - Werkstätte und Produktionstechnik ",
    "Computer- und Informationstechnik                                              ",
    "Werkzeugbau und Vorrichtungsbau                                                ",
    "Kommunikationselektronik                                                       ",
    "Computerarchitektur und Betriebssysteme                                        ",
    "Unternehmensführung und Wirtschaftsrecht                                       ",
    "Logistik                                                                       ",
    "Konstruktion und Design                                                        "
    };




char SubN[][20] =
{
/*AELT*/    "E                 ",
/*AM  */    "NWG               ",
/*BESP*/    "DUK               ",
/*COIT*/    "SOTE              ",
/*CTNT*/    "NWWP              ",
/*D   */    "AM                ",
/*DUK */    "CTNT              ",
/*DIC1*/    "AELT              ",
/*E1  */    "GGP               ",
/*E2  */    "ELWP              ",
/*ELDE*/    "NW2               ",
/*ELWP*/    "ELDE              ",
/*FSST*/    "FSST              ",
/*GGP */    "HWE1              ",
/*HWE1*/    "ANTMT             ",
/*KMEL*/    "CPE               ",
/*KSN1*/    "AINF              ",
/*LAB */    "DBI               ",
/*MTRS*/    "POS1              ",
/*NNWP*/    "ES                ",    // ?? ES_3, ES_4
/*NW2 */    "ES1               ",
/*NWG */    "BESP              ",
/*PBE */    "BWM               ",
/*R   */    "ANTMT             ",
/*RK  */    "ANTMTWP           ",
/*REL */    "AUT               ",
/*ETH */    "CPE               ",
/*SOTE*/    "FET1              ",
/*UNF */    "KOP1              ",
/*WIR3*/    "ETAT              ",
/*SOPK*/    "FET1WP            ",     // ?? FET1WP_3, FET1WP_4
/*NEW */    "BET               ",
/*NEW */    "PROTWE            ",
/*NEW */    "INFI              ",
/*FOEX*/    "TMB               ",
/*WIRE*/    "WPT               ",
/*BION*/    "ETE               ",
/*EMBE*/    "MANL              ",
/*ORC5*/    "WIR               ",       // ??
    "PRMN              ",
    "LA1               ",
    "APT1              ",
    "NSCS              ",
    "NVS1              ",
    "WMC               ",
    "ROBP              ",       // ??
    "SYP1              ",
    "PRMN              ",
    "IE1               ",
    "DIC1              ",
    "MTRS              ",
    "KSN1              ",
    "MET1              ",
    "PBE               ",
    "FI                ",
    "TMB               ",
    "MME               ",
    "FET               ",     // FET2 ????
    "UNF               ",
    "AUTI              ",
    "ANTMTWP           ",
    "COIT              ",
    "WBVB              ",
    "KMEL              ",
    "CABS              ",
    "UFW               ",
    "LO1               ",      // LO ??
    "KODES             "











};


int readF(FILE ** f, const char * s);
int writeF(FILE ** f, const char * s);
int delXUnderline(FILE * l, FILE * l_no_unders, int summer);

int copyFile(FILE * d, FILE * s);
int sortTab(FILE * tS, FILE * t); // sortiert <--- tab
int combineSigmaLines(FILE * sL, FILE * sigma);
int selectJ(FILE * sigmaJ, FILE *sigma);
int list2tab(FILE * l, FILE * t, FILE * f, FILE * a, int summer);
int tab2stat(FILE * tab, FILE * stat, FILE * prog);
//int tab2sigma(FILE *tab, FILE * sigma, FILE * nps);
int sortSigma(FILE * si, FILE * so, FILE * cl);
int createNewYear(FILE * n, FILE * t);
int getClassId(char * className, int summer);

int sort(char tab[][SMAX], int n);
int delEQ(char tab[][SMAX], int n, int x);

int ZweiKlassen4System;  // ???
int ZweiKlassen5System;

int getAllSubsOfThisClass(int j, int i, char(*t)[SMAX], char (*subs)[30]);
int getAllFlecks(int j, char(*t)[SMAX]);

int getClassIndex(char * classname); // ???
int getSubId(char * sub);

void CutNames(char * fromFile, char * directory);
int procN[14] = {0}; // 0 == 1AFELC; 1 == 1AHELS; 2 == 1BHELS e.g.
int gesN = 0, gesS = 0; // gesamt Zahl 5er einschließlich N, gesamt Zahl Schüler
int mCounter;
char dir[LEN];  // J2023




    /******************************************************/
    /**                    m a i n                       **/
    /******************************************************/

int main(void)
{
FILE * liste, * listNoUnder, * tab, * fehl, * allTab, * notes, * percent,
     * sigmaList, * protEL, * protET, * protIF, * protMB, *mah,
     * protWI, * check, * wel /* procEL  negList*/;
char text[LINEMAX];
char tnxt[LINEMAX];
char FamNam[LINEMAX];
char VorNam[LINEMAX];
char Name[LINEMAX];
char NextClass[LINEMAX];
char Subject[LINEMAX];
char Sub[LINEMAX];
char Teacher[LINEMAX];
char Date[LINEMAX];

int i, j, k, l, m, n, ok, r, s, w,lines, nSubs, f, h, anzN,
    gefunden, cId, sId, numberOfMembersWith5N, numberOfMembers;

char compClass[12];
char qualifier[LINEMAX];
char (* t)[SMAX];
char (* subs)[30];
double subs5Prozent[30];
int subs5Anz[30];
int subsNAnz[30];
int subsNAnzListe[30];

int nFlecks;
char ClassName[15];
char Abt[5];
float sigmaValue;
char sigmaValueBefore[LINEMAX];
time_t ti = time(NULL);
struct tm tm = *localtime(&ti);
char answer[LEN];
char command[LEN];
char mahnClass[LEN];
char mahnSub[LEN];
char mahnSurName[LEN];
char mahnName[LEN];

int summer; // if TRUE check die Jahresnote e.g. SS   else Semesternote e.g. WS


    /**┌────────────────────────────────────────────────┐**/
{   /**  I n i t s :       Dir createted, summer = T/F   **/


    initConsole();
    clrscr();

    textcolor(RED);
    printf("-------------------------------------------------------------------------------\n");
    printf("                                 Σ i g m a   2 4                               \n");
    printf("-------------------------------------------------------------------------------\n");
    textcolor(WHITE);

    m = tm.tm_mon + 1;

    // im Juni  bis zum Nov möchte ich eine Jahresauswertung, alle anderen Monate nur das Semester


    sprintf(dir,"%c%4d", ((m > 5) && (m < 12)) ? 'J' : 'S', tm.tm_year + 1900);
    printf("data stored in -> %s yes? or set a dir (e.g. J2010)\n", dir);
    printf("from december to may -> Semester, from june to november -> Jahresauswertung\n");

    ok = 0;
    do
    {
        printf("%s yes? ", dir);
        fflush(stdin);
        scanf("%s", answer);

        if (answer[0] == 'y') ok = 1;

        if (((answer[0] == 'J') || (answer[0] == 'S')) &&
            ((answer[1] >= '0') && (answer[1] <= '9')) &&
            ((answer[2] >= '0') && (answer[2] <= '9')) &&
            ((answer[3] >= '0') && (answer[3] <= '9')) &&
            ((answer[4] >= '0') && (answer[4] <= '9'))    )
       {
              answer[5] = '\0';
              sprintf(dir,"%s", answer);
              ok = 1;
       }

    } while (!ok);


    printf("\n----> dir: %s will be created! If it exists: delete it first!", dir);



#ifdef __linux__
    sprintf(command,"mkdir ./%c%c%c%c%c", dir[0], dir[1], dir[2], dir[3], dir[4]);
#else
    sprintf(command,"mkdir   %c%c%c%c%c", dir[0], dir[1], dir[2], dir[3], dir[4]);
#endif

    printf("\n%s\n", command);
    system(command);

#ifdef __linux__
    sprintf(command,"cp   ./Liste.csv       ./%c%c%c%c%c/Liste.csv", dir[0], dir[1], dir[2], dir[3], dir[4]);
#else
    sprintf(command,"copy \"Liste.csv\"   \"./%c%c%c%c%c/Liste.csv\"", dir[0], dir[1], dir[2], dir[3], dir[4]);

#endif

    printf("\n%s\n", command);
    system(command);

getch();

    clrscr();

    gotoxy(0,1); printf("--------------------------------------------------------------------------------");
    gotoxy(0,2); printf("Liste.csv is stored in %s", dir);
    gotoxy(0,3); printf("--------------------------------------------------------------------------------");
    gotoxy(0,4);


    if (dir[0] == 'J')
    {
        summer = TRUE;
        printf("Jahresauswertung");
    }
    else
    {
        summer = FALSE;
        printf("Semesterauswertung");
    }


    t    = (char (*)[SMAX])malloc(SMAX * 40000);  // 20k lines
    subs = (char (*)[30  ])malloc(SMAX * 200);    // 20k lines
    nSubs = 0;

    sId = 0;

    mCounter = 0;



    if (!t) {printf("\nzu wenig Speicher!\n"); exit(-1);}   // in t wird später das ganze File allTabs eingelesen




    gotoxy(0, 6); printf("Initialisierungen abgeschlossen ...... weiter?\n");
    getch();



}
    /**└────────────────────────────────────────────────┘**/

    /**┌────────────────────────────────────────────────┐**/
{   /**          1                                       **/

    printf("Schritt 1: aus Liste.csv werden alle Underlines entfernt!\n");

    readF(&liste, "./Liste.csv");
    writeF(&listNoUnder, "./ListeNoUnder.csv");

    delXUnderline(liste, listNoUnder, summer);

    // hier wurde die 1AO mit 1OHIF, die 1BO mit der 1OHELS ersetzt !

    fclose(liste);
    fclose(listNoUnder);

    writeF(&liste, "./Liste.csv");
    readF(&listNoUnder, "./ListeNoUnder.csv");

    copyFile(liste, listNoUnder);
    fclose(liste);
    fclose(listNoUnder);

}
    /**└────────────────────────────────────────────────┘**/

    /**┌────────────────────────────────────────────────┐**/
{   /**          2                                       **/


    printf("Schritt 2: Liste.csv -> Tab.csv pro Schueler eine Zeile!\n");


    readF(&liste, "./Liste.csv");
    writeF(&tab, "./Tab.csv");
    writeF(&fehl, "./Fehler.csv");
    writeF(&allTab, "./allTab.csv"); // Übersicht über alle Klassen aller Abteilungen

printf("hier 1!\n");

    list2tab(liste, tab, fehl, allTab, summer);

printf("hier 2!\n");

    // zunächst sollen alle Daten aller Abteilungen weggespeichert werden.

    fclose(tab);   // Tab.csv hat nun alle Noten, aller Abteilungen und aller Klassen aufgelistet.

    // tab noch sortieren!  damit die Schüler mit "Vorläufigen Zeugnissen" mit in die Klassen einsortiert werden.

    readF(&tab, "./Tab.csv");

    i = 0;

printf("hier 3!\n");


    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        fgets(text, LINEMAX, tab);
        sprintf(t[i],"%s", text);
        i++;
    } while (!feof(tab));

    fclose(tab);

printf("hier 4!\n");


    sort(t, i); // dadurch werden Schüler mit "nur" vorläufigen Zeugnissen miteinsortiert in ihre Klassen


    writeF(&tab, "./Tab.csv");

    for (j  = 0; j < i; j++)
    {
       fprintf(tab, "%s", t[j]);
    }


    fclose(tab);

}
    /**└────────────────────────────────────────────────┘**/

    /**┌────────────────────────────────────────────────┐**/
{   /**          3          Protokolle werden erstellt   **/

    printf("Schritt 3: Tab.csv -> Protokoll Unterlagen fuer alle Abt generiert\n");

    i = 0;
    anzN = 0; // Anzahl Schueler der EL und Anźahl der Nicht genuegend (bzw Nichtbeurtielt) der EL

    readF(&tab, "./Tab.csv");
    writeF(&allTab, "./allAbtTab.csv");
    writeF(&notes, "./allAbtTabNotes.csv");
    writeF(&percent, "./Prozent5erProGegenstand.csv");

    writeF(&protEL,"./Protokoll_Unterlagen_EL.csv");
    writeF(&protET,"./Protokoll_Unterlagen_ET.csv");
    writeF(&protIF,"./Protokoll_Unterlagen_IF.csv");
    writeF(&protMB,"./Protokoll_Unterlagen_MB.csv");
    writeF(&protWI,"./Protokoll_Unterlagen_WI.csv");

    writeF(&wel,"./Wiederholungspruefungen.csv");  fprintf(wel,"%s\n",dir); // für alle Abteilungen!

/*
J2023
EL;5;05;1AHELS_J  ;GGP;Jukic;Marko;
EL;5;05;1AHELS_J  ;HWE1;Jukic;Marko;
EL;5;03;1AHELS_J  ;AM;Otter;Oliver;
EL;5;03;1AHELS_J  ;FSST;Otter;Oliver;
EL;5;03;1AHELS_J  ;HWE1;Otter;Oliver;
EL;5;01;1AHELS_J  ;HWE1;Pek;Muhammed Huzeyfe;
EL;5;01;1AHELS_J  ;AM;Pinz;Martin;
EL;5;01;1AHELS_J  ;HWE1;Relota;Nicola;
EL;N;06;1AHELS_J  ;AM;Seidl;Alex;
*/

printf("$3 hier 1!\n");

    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        fgets(text, LINEMAX, tab);

        if ((text[0] >= '0') && (text[0] <= '8') &&                      // nur Klassen zwischen dem 1 und 8 Jahrgang (Abendschule)!
            ((text[2] == 'H') || (text[2] == 'F') || (text[2] == 'B')))  // nur Höhere oder Fachschule oder Abendschule - keine V (=Vorgezogene)
        {
            sprintf(t[i],"%s", text);
            fprintf(allTab, "%s",text);  // wer braucht diese Liste noch???
            i++;
        }
    } while (!feof(tab));

    sprintf(t[i],"5AXXX\n"); // Endekennung ...   für die weitere Bearbeitung wird eine letzte Zeile eingefügt
    i++;                     // i speichert hier die Länge der tab Zeilen


    fclose(allTab);          // allTab für weitere Analysen aufbewahrt
    lines = i;


    // nun wird Klasse für Klasse als Block bearbeitet.

    j = 0;

    sprintf(compClass,"%c%c%c%c%c%c%c%c%c%c", t[j][0], t[j][1], t[j][2], t[j][3], t[j][4], t[j][5], t[j][6], t[j][7], t[j][8], t[j][9] );

printf("$3 hier 2!\n");


    for (i = 0; i < lines; i++)    // für alle Einträge
    {
        if ((compClass[0] != t[i][0]) ||           // 5
            (compClass[1] != t[i][1]) ||           // A
            (compClass[2] != t[i][2]) ||           // H
            (compClass[3] != t[i][3]) ||           // E
            (compClass[4] != t[i][4]) ||           // L
            (compClass[5] != t[i][5])              // S .. an 6ter Stelle wäre E oder W, dies wird hier nicht als andere KLasse verstanden!
                                                   // neu hinzukommen wird B ! für bionics
//            (compClass[6] != t[i][6]) ||           // E Embedded W Wireless
//            (compClass[7] != t[i][7]) ||  // 4AHELSE oder 4AHELSW soll sich nicht unterscheiden
//            (compClass[8] != t[i][8]) ||
//            (compClass[9] != t[i][9])
)
       {   // eine neue Klasse wurde gefunden - daher wird die bisherige nun als Block ausgewertet:



       /**
         * Auswertung einer Klasse:
         *
         * j speichert die Zeilenzahl des ersten Schülers dieser Klasse,
         * i speichert den ersten Schüler der nächsten Klasse.
         *
         * nun werden alle Gegenstände einer Klasse ermittelt (auch alle Freigegenstände usw.)
         * Ziel ist es diese so umzusortieren, dass eine einheitliche Liste für die Klasse entsteht.
         *
         **/


            cId = getClassId(compClass, summer);  // diese Id ist wichtig für die Gewichtung der Noten
            // compClass zb 1AHELS
            // t[j][11] hier steht J für Ganzjahr oder S für Semester....
            // summer enthält die gleiche Info!


//if (cId < 0) printf("class: ---> %s found!\n",compClass);  ///  for tests only


            nSubs = getAllSubsOfThisClass(j, i, t, subs);  // eine neue Klasse wurde gefunden - sie reicht von j bis i

            // somit wissen wir, wieviele Gegenstände es in dieser Klasse gibt (nSubs) und auch welche (subs)

            // Arrays mit lauter Null-Einträgen wird vorbereitet:

printf("$3 hier 3!\n");



            for (k = 0; k < nSubs; k++) subs5Anz[k] = subs5Prozent[k] = subsNAnz[k] = 0;

            numberOfMembersWith5N = 0;
            numberOfMembers = i;

            for (; j < i; j++ )   // eine Klasse:
            {

            // Schüler für Schüler dieser Klasse auswerten:

                r = 0;
                s = 0;
                nFlecks = getAllFlecks(j,t);

            // EL ET IF MB WI

                fprintf(notes,"%c%c,", t[j][3], t[j][4]); // Abteilungszugehörigkeit  - in das File AllTabsNotes
                sprintf(Abt,"%c%c;", t[j][3], t[j][4]);   // Abteilungszugehörigkeit
//Abt

            // 4AHELSW
                while(t[j][r] != ',') {fprintf(notes,"%c", t[j][r]); ClassName[r] = t[j][r]; r++;}
                ClassName[r] = '\0';                      // Klassenbezeichnung wird eingetragen
//ClassName
            // Anzahl Flecks:
                fprintf(notes,",%2d, ", nFlecks); r++; r++; r++; // S / J  kann eingespart werden ... könnte man hier einbauen...

                if (nFlecks) numberOfMembersWith5N++;

                sigmaValue = 7.654321;                   // für die spätere Auswertung wird hier Platz geschaffen
                fprintf(notes,"%.6f, ", sigmaValue);

            // name
            //while(t[j][r] != ',') {fprintf(notes,"%c", t[j][r]); r++;}  fprintf(notes,","); r++;

//Control: if ((t[j][r] == 'S') && (t[j][r + 1] == 'p') && (t[j][r + 2] == 'e') && (t[j][r + 3] == 'c'))
//{
//printf("* %c%c%c%c%c%c\n", t[j][r], t[j][r + 1], t[j][r + 2], t[j][r + 3], t[j][r + 4],  t[j][r + 5] );
//
//contr = 1;
//}
//else contr = 0;
                f = 0;
                while(t[j][r] != ',')
                {
                    if(t[j][r] < 0) {s++;}
                    fprintf(notes,"%c", t[j][r]);
                    FamNam[f] = t[j][r];
                    f++; r++;
                }
                FamNam[f] = '\0';
                fprintf(notes,","); r++;


printf("$3 a");



            // Vorname
                h = 0;
                while(t[j][r] != ',')
                {
                    if(t[j][r] < 0) {s++;}
                    fprintf(notes,"%c", t[j][r]);
                    VorNam[h] = t[j][r];
                    h++; r++;
                }
                VorNam[h] = '\0';
                fprintf(notes,","); r++;
                sprintf(qualifier,"%s",t[j]+r);

                s = (s / 2) + 50;  // Umlaute, Sonderezeichen...

printf("$3 b");


                while(r < s) {fprintf(notes," "); r++;} fprintf(notes,",");

                // bis hier steht zB.:
                // EL,1AFELC    , 7, 0.123456, Arslan,Furkan Alp,                   ,
                // in notes
                // nun folgen die Gegenstände

                // in qualifier ist der string gespeichert - ab verh, der alle Gegensände und Noten des Schülers beinhaltet

                w = 0; // gewichte = Summe aller Noten * Notengewicht
                n = 0; // Anzahl der Notengewichte




                for (k = 0; k < nSubs; k++)   // eine Zeile wird eingetragen:
                {

//################################################################
// hier wird nun jeder Gegenstand und seine Note eingetragen:
//################################################################


printf("$3 c");


                gefunden = 0;
                r = 0;
// qualifier enthält alle Gegenstände und alle Noten in einer Zeile - dient zum Suchen der Note

                while((r < (strlen(qualifier) - strlen(subs[k]))) && (gefunden == 0))
                {
                    if ((strncmp(subs[k], qualifier + r, strlen(subs[k])) == 0)  &&
                        (qualifier[ + r + strlen(subs[k])] == ','))
                    {

                        // gefunden
                        //printf("* --> %s", qualifier + r);

                        if (cId >= 0) sId = getSubId(subs[k]);  // liefert die Zeilennummer der Gewichtstabelle  ... > 0 damit keine andere Abteilungen ....... den die haben -1 !!!


//#######
//#######  hier wird ab 2023/2024 eine neue Stundentafel verwendet werden.
//#######
//#######
//#######


// Control: if ( contr)
//{
//printf("| sub %s %c %d ", subs[k], qualifier[ + r + strlen(subs[k]) + 1], weight[sId][cId] );
//}

                        fprintf(notes, "%s,",subs[k]);   //Gegenstand für Gegenstand wird eingetragen....
                        fprintf(notes, "%c,", qualifier[ + r + strlen(subs[k]) + 1] );

// falls 5er rausschreiben

                if (/*(nFlecks > 0) && (nFlecks < 3) && (Abt[1] == 'L') && */
                    (((qualifier[ + r + strlen(subs[k]) + 1]) == '5') ||
                     ((qualifier[ + r + strlen(subs[k]) + 1]) == 'N')     )
                    )
                {
                    fprintf(wel,"%c%c,%c,%02d,%s,ddmmjj,00,0000,%s,%s,%s,\n",
                            ClassName[3],ClassName[4],
                            qualifier[ + r + strlen(subs[k]) + 1], nFlecks, ClassName, subs[k], FamNam, VorNam); // für EL werden hier die Wiederholungsprüfungskandidaten gesammelt
                }
/*
J2023
EL;5;08;1AFELC_J  ;jjmmdd;00;A;TTTT;AELT;Aibartuev;Musa;
EL;5;08;1AFELC_J  ;jjmmdd;00;A;TTTT;AM;Aibartuev;Musa;
Anzahl der 5er, Monat Tag Jahr der letzten Mahnung,  Lehrer...
*/

                        if ((cId >= 0) && (sId >= 0))
                        {
                            m = qualifier[ + r + strlen(subs[k]) + 1];
                            if ((m >= '1') && (m <= '5')) m -= '0';

                            if (m == 'T') m = 1;
                            if (m == 'B') m = 0;
                            if (m == 'S') m = 0;
                            if (m == 'N') m = 5;
                            if (m == 'G') m = 0; // Gestundet
                            if (m == 'Z') m = 0; // zufriedenstellend
                            if (m == 'W') m = 0; // wenig zufriedenstellend
                            if (m == 'X') m = 0; // keine Konfession: REL X -> wird wie S behandelt!!!
                            if (m == '8') {m = 5; printf("§");}// ????? unbekannte Note  in einem ETH Gegenstand

                            if ((m > 0) && (m <= 5))
                            {
                                w += m * weight[sId][cId];
                                n += weight[sId][cId];

                                if (m == 5) anzN++; // Anzahl der Nicht genügend bzw Nicht beurteilt der Abteilung

//printf("geg: %s Note %d Gewicht %d Summe w= %d Summe aller n= %d\n",subs[k], weight[sId][cId], m,w,n);

                            }
                            else
                            {
                                if ((m != '0') && (m != 0)) // 0 bedeutet Note fehlt!
                                printf("Notengewicht im Gegenstant %s von %c ergibt???\n", subs[k], m);
                            }
                        }

                        /**
                          * hier wird jede Note eines Schülers und der betreffende Gegenstand eingetragen
                          *
                          * natürlich auch T, S,G, N, B usw.
                          *
                          *
                          *
                          **/
printf("$3 d");

                        if (qualifier[ + r + strlen(subs[k]) + 1]  == '5') subs5Anz[k]++;  // hier sind die Noten !!!
                        if (qualifier[ + r + strlen(subs[k]) + 1]  == 'N') subs5Anz[k]++;  // hier sind die Noten !!!

                        gefunden = 1;
                        subsNAnz[k]++;

                    }
                    r++;
                }
                if (gefunden == 0)
                {

                    for (s = 0; s < strlen(subs[k]); s++) fprintf(notes, " ");   //Gegenstand für Gegenstand wird eingetragen....
                    fprintf(notes, ", ,");
                }

                //r = strtok(subs[k],qualifier);
                //fprintf(notes, "%c,", qualifier[r+strlen(subs[k])+1]);
            }

            //printf("%s in %s ", subs[0], qualifier);
            //printf("r = %d   %c%c%c\n", r, qualifier[r+strlen(subs[0])], qualifier[r+strlen(subs[0])+1], qualifier[r+strlen(subs[0])]+2);

            //fprintf(notes,"\n");
            //fprintf(notes,"\nVGL: %s",t[j]);
printf("$3 e");
            if (n > 0)
            {
                fprintf(notes,"|%d.%06d|\n", w / n, (w*1000000/n)%1000000);
            }
            else
            {
                fprintf(notes,"\n");
            }
        }

        //Vorbereitung auf die nächste Klasse:
        j = i;
        sprintf(compClass,"%c%c%c%c%c%c%c%c%c%c", t[i][0], t[i][1], t[i][2], t[i][3], t[i][4],t[i][5], t[i][6], t[i][7], t[i][8], t[i][9]);




// Percent5er pro Gegenstand:

//fprintf(percent,"%c%c,", t[j][3], t[j][4]); // Abteilungszugehörigkeit
//while(t[j][r] != ',') {fprintf(percent,"%c", t[j][r]); r++;}

printf("$3 f");

        for (k = 0; k < nSubs; k++)
        {

fprintf(percent,"%s%s;", Abt,ClassName);
fprintf(percent,"%s;%d;%d; %d,%03d\n", subs[k], subs5Anz[k], subsNAnz[k], (subs5Anz[k] == subsNAnz[k]) ? 1: 0,
        (subs5Anz[k] == subsNAnz[k]) ? 0 :
        (subsNAnz[k] > 0) ? (1000*subs5Anz[k])/subsNAnz[k]:0);
        }

printf("$3 g");

        if ((2 * numberOfMembersWith5N) >=   numberOfMembers)
        {
            fprintf(notes,"%c%c,%s,  ,#########, Anzahl der Schueler mit NG  bzw. NB mehr als 50 %% -> Begruendung durch den Jahrgangsvorstand erforderlich,\n", Abt[0], Abt[1], ClassName); // ENDE DER KLASSE!!!
        }

            fprintf(notes,"%c%c,%s,  ,         , Anzahl der 5 bzs. N je Gegenstand:   ,,,", Abt[0], Abt[1], ClassName); // ENDE DER KLASSE!!!
printf("$3 h");
        for (k = 0; k < nSubs; k++)
        {

            l = 0;
            while (l < (int)(strlen(subs[k]) - 1))
            {
                fprintf(notes," ");
                l++;
printf("l = %05d strlen %05d k = %05d %s.\n", l, (strlen(subs[k]) - 1), k, subs[k]);
            }
            fprintf(notes,",%2d,",subs5Anz[k]);
        }
        fprintf(notes,"\n");
printf("$3 i");
            fprintf(notes,"%c%c,%s,  ,         , Anzahl der Noten dieses Fachs:       ,,,", Abt[0], Abt[1], ClassName);

        for (k = 0; k < nSubs; k++)
        {
            l = 0;
            while (l < (int)(strlen(subs[k]) - 1)) {fprintf(notes," "); l++;}
            fprintf(notes,",%2d,",subsNAnz[k]);
        }
        fprintf(notes,"\n");
printf("$3 j");

        fprintf(notes,"%c%c,%s,  ,         , in Prozent  ab 30 %% -> Begruendung!  ,,,", Abt[0], Abt[1], ClassName);

        for (k = 0; k < nSubs; k++) subsNAnzListe[k] = 0;
printf("$3 k");
        for (k = 0; k < nSubs; k++)
        {
            l = 0;
            while (l < (int)(strlen(subs[k]) - 1)) {fprintf(notes," "); l++;}
            fprintf(notes,",%2d,", (subsNAnz[k] == 0)? 0:(int)((subs5Anz[k] * 100.) / subsNAnz[k]));

            if ((int)((subs5Anz[k] * 100.) / subsNAnz[k])  >= 30.)
            {
                subsNAnzListe[k] = (int)((subs5Anz[k] * 100.) / subsNAnz[k]);
            }

        }

printf("$3 l");

        fprintf(notes,"\n"); // ENDE DER KLASSE!!!

        for (k = 0; k < nSubs; k++)
        {
            if (subsNAnzListe[k] > 0)
            {
                fprintf(notes,"%c%c,%s,  ,#########, Begruendung erfortderlich:%s %d.%%\n", Abt[0], Abt[1], ClassName, subs[k], subsNAnzListe[k]);
            }
        }



        fprintf(notes,"%c%c\n", Abt[0],Abt[1]);

        //printf("Klasse %s \n", compClass);
        //if (getch() == 27) exit(0);

    }
}

if (j < i)  // weil es eine 5XXX Klasse gibt, kommt dieser Teil nicht mehr vor.
{
        // zu diesen Zeilen kommt man nur, weil die klasse 5XXX hinzugefügt wurde.
        //nSubs = getAllSubsOfThisClass(j, i, t, subs);
        j = i;

        //sprintf(compClass,"%c%c%c%c%c", t[i][0], t[i][1], t[i][2], t[i][3], t[i][4]);
}

fclose(notes);
fclose(percent);

// -------- #



// fuer die einzelnen Abteilungen Filtern:

    readF(&allTab, "./allAbtTabNotes.csv");

    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {

        fgets(text, LINEMAX, allTab);

// Beistriche durch Strichpunkt ersetzen:


        for (l = 0; l < strlen(text); l++)
            if (text[l] == ',')
                text[l] = ';';




        text[18] = ' ';
        text[19] = ' ';
        text[20] = ' ';
        text[21] = ' ';
        text[22] = ' ';
        text[23] = ' ';
        text[24] = ' ';
        text[25] = ' ';

//        k = strlen(text) - 13;

        //for (l = 17; l < k; l++) text[l] = text[l + 11];

        //text[l] = '\0';
        //text[l+1] = '\n';


        if (text[1] == 'L')
        { // neu eingebaut
            if(text[2] == ';')
            {
                k = 0;
                while ((text[k] != '|') && ( k < strlen(text))) {k++;}

                if (k < strlen(text))
                {
                    text[k] = '\n';
                    text[k+1] = '\0';
                }
                fprintf(protEL,"%s", text + 3);

            }
            else fprintf(protEL,"\n");
        } // neu eingebaut

        if (text[1] == 'T')  { if(text[2] == ';') fprintf(protET,"%s", text + 3); else fprintf(protET,"\n");} // zwei Klammern neu eingebaut
        if (text[1] == 'F')  { if(text[2] == ';') fprintf(protIF,"%s", text + 3); else fprintf(protIF,"\n");}
        if (text[1] == 'B')  { if(text[2] == ';') fprintf(protMB,"%s", text + 3); else fprintf(protMB,"\n");}
        if (text[1] == 'I')  { if(text[2] == ';') fprintf(protWI,"%s", text + 3); else fprintf(protWI,"\n");}


    } while (!feof(allTab));


fclose(protEL);
fclose(protET);
fclose(protIF);
fclose(protMB);
fclose(protWI);

// alle hinten angefügten sigma WSerte müssen jetzt noch nach vo übertragen werden.



    readF(&allTab, "./allAbtTabNotes.csv");
    writeF(&notes, "./allAbtNotesWithSigma.csv");


    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        fgets(text, LINEMAX, allTab);

        l = strlen(text);

        if (text[l-2] == '|')
        {
            text[18] = text[l - 10];
            text[20] = text[l - 8];
            text[21] = text[l - 7];
            text[22] = text[l - 6];
            text[23] = text[l - 5];
            text[24] = text[l - 4];
            text[25] = text[l - 3];

            text[l - 11] = text[l-1];
            text[l - 10] = text[l];



            //printf("%s", text);
        }

        fprintf(notes, "%s",text);  // wer braucht diese Liste noch???



    } while (!feof(allTab));


    fclose(notes);
    fclose(allTab);
    fclose(wel);







// gesamtZeilenzahl merken
// i = j = 0; Vergleichsname der ersten Zeile verwenden

// Liste durchgehen mit i - dabei nachsehen, ob die ersten 1AFEL 5 Zeichen anders sind
// falls ja - Ausgeben
// n Schüler der Klasse .... gefunden  (i - j)
// dann j j auf diese Zeile spriongen

// Protokolle rauskopieren, dabei Namen schwaerzen:



 //   CutNames("./Protokoll_Unterlagen_EL.csv", dir);   ... nicht mehr nötig - andere Lösung: speichere ins Teams.
 //   CutNames("./Protokoll_Unterlagen_ET.csv", dir);
 //   CutNames("./Protokoll_Unterlagen_IF.csv", dir);
 //   CutNames("./Protokoll_Unterlagen_MB.csv", dir);
 //   CutNames("./Protokoll_Unterlagen_WI.csv", dir);






}
    /**└────────────────────────────────────────────────┘**/

    /**┌────────────────────────────────────────────────┐**/
{   /**          4          sigma                        **/
    // hier werden nun alle EL heraus gelöst und zwar nur die vom Jahresende
    // sie werden nach sigma sortiert.


    printf("Schritt 4: Sortiere fuer EL alle sigma-Wertungen! => sigmaList.csv\n");



    i = 0;

    readF(&tab, "./allAbtNotesWithSigma.csv");
    writeF(&sigmaList, "./sigmaNames.csv");

    writeF(&check, "./check.txt");



// zuerst in tab lesen
// dabei aber auch umsortieren - zuallererst kommt der sigma Wert --- fals EL Sommersemester!

    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        fgets(text, LINEMAX, tab);

        if ((text[0] == 'E') && (text[1] == 'L') && (text[15] != ' '))
        {
            // vorbereitet für Jahresschluss:  das muss für Februar 2021 geändert werden!

// hier mit summer umschalten!
//#####
//            if (((text[3] == '1') && (text[10] ==  'J')) ||
//                ((text[3] == '2') && (text[10] ==  'S')) ||
//                ((text[3] == '3') && (text[10] ==  'S')) ||
//                ((text[3] == '4') && (text[10] ==  'S'))    )

            if (((summer == FALSE) && (text[19] == '.'))   // fuer das erste Semester!
                ||

                ((summer == TRUE) &&                       // fuer das yweite Semester

                (((text[3] == '1') && (text[10] ==  'J')) ||
                 (text[3] == '2') ||
                 (text[3] == '3') ||
                 (text[3] == '4') ||
                 (text[3] == '5')    ))

               //((text[3] == '4') && (text[8] ==  'S')))) // fuer das Sommersemester entferne 5te und 4AFELC
               // with the line above - absolventen are filtered out!

                )
            {

                sprintf(t[i],"%c.%c%c%c%c%c%c| %s", text[18], text[20],text[21],text[22],text[23],text[24],text[25],text);


                if (t[i][19] == 'E') // Embedded
                {
                    t[i][19] = ' ';
                    t[i][20] = 'E';
                    t[i][21] = ' ';
                }
                else if (t[i][19] == 'W')
                {
                    t[i][19] = ' ';
                    t[i][20] = 'W';
                    t[i][21] = ' ';
                }
                else
                {
                    t[i][19] = ' ';
                    t[i][20] = ' ';
                    t[i][21] = ' ';
                }
                i++;
            }
        }

    }   while (!feof(tab));

    // sort ...



    sort(t,i);


    for (j = 0; j < i; j++) fprintf(check,"%s", t[j]);

    fclose(check);

    // i stores ne number of pubil


    // erkenne gleich gute Schüler und ergänze einen Reihungswert

    sprintf(sigmaValueBefore,"0.000000");
    sigmaValueBefore[8] = '\0';
    j = 0;
    k = 0;
    while (j < i)
    {
         if (strncmp(sigmaValueBefore,t[j],8) != 0)
         {
             k = j + 1;
         }
         sprintf(sigmaValueBefore,"%s",t[j]);

         if (k > 99) {t[j][ 9] = (k/100)%10 + '0';} else {t[j][ 9] = ' ';}
         if (k >  9) {t[j][10] = (k/ 10)%10 + '0';} else {t[j][10] = ' ';}
         t[j][11] = k%10 + '0';

         l = 0;
         while (t[j][l] != ',') {l++;} l++;
         while (t[j][l] != ',') {l++;} l++;
         while (t[j][l] != ',') {l++;} l++;
         while (t[j][l] != ',') {l++;} l++;
         while (t[j][l] != ',') {l++;} l++;
         while (t[j][l] != ',') {l++;}

         t[j][l] = '\0';

         j++;
    }

    // speichere alles wieder ein

    j = 0;

    while ( j < i)
    {
        fprintf(sigmaList,"%s\n",t[j] + 9);
        j++;
    }



    fclose(sigmaList);
    fclose(tab);

    // resort sigma list:

    readF(&tab, "./sigmaNames.csv");
    writeF(&sigmaList, "./sigmaList.csv");




// zuerst in tab lesen
// ########
// dabei aber auch umsortieren - zuallererst kommt der sigma Wert --- falls EL Sommersemester!

    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        if (fgets(text, LINEMAX, tab) != 0)
        {
            i = 28;
            j = 0;
            l = 0;
            while (text[i] != '\0') {Name[j] = text[i]; i++; j++; l++;}
            Name[l - 1] = ',';
            Name[l] = '\0';

            tnxt[0] = text[0];
            tnxt[1] = text[1];
            tnxt[2] = text[2];
            tnxt[3] = text[3];
            for (m = 0; m < l ; m++) text[4 + m ] = Name[m];
            tnxt[ 4 + l] = text[4];
            tnxt[ 5 + l] = text[5];
            tnxt[ 6 + l] = text[6];
            tnxt[ 7 + l] = text[7];
            tnxt[ 8 + l] = text[8];
            tnxt[ 9 + l] = text[9];
            tnxt[10 + l] = text[10];
            tnxt[11 + l] = text[11];
            tnxt[12 + l] = text[12];
            tnxt[13 + l] = text[13];
            tnxt[14 + l] = text[14];

            tnxt[15 + l] = text[18];
            tnxt[16 + l] = text[19];
            tnxt[17 + l] = text[20];
            tnxt[18 + l] = text[21];
            tnxt[19 + l] = text[22];
            tnxt[20 + l] = text[23];
            tnxt[21 + l] = text[24];
            tnxt[22 + l] = text[25];
            tnxt[23 + l] = text[26];

            //sprintf(tnxt, "%c%c%c%c%s%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
            //            //  1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
            //text[0],  text[1],  text[2],  text[3],  Name,
            //text[4],  text[5],  text[6],  text[7],  text[8],
            //text[9],  text[10], text[11], text[12], text[13],
            //text[14], // Klasse
            //          text[18], text[19], text[20], text[21],
            //text[22], text[23], text[24], text[25], text[26]
            //  );
            tnxt[l + 4 + 11 + 9] = '\0';

            fprintf(sigmaList,"%s\n",tnxt);
        }
    }   while (!feof(tab));

    fclose(sigmaList);
    fclose(tab);


    sprintf(command,"cp ./sigmaList.csv ./%c%c%c%c%c%c/sigmaList.csv", dir[0], dir[1], dir[2], dir[3], dir[4], dir[5]);
    system(command);

}
    /**└────────────────────────────────────────────────┘**/

    /**┌────────────────────────────────────────────────┐**/
{   /**          5          Mahnungen eingetragen        **/



    printf("Schritt 5: Oeffne Mah.txt und trage in Wiederholungsp. ein\n");
    getch();
    system("cls");


    readF(&wel, "./Wiederholungspruefungen.csv");
    readF(&mah, "./Mah.csv");

/*
Klasse,Familienname,Vorname,Geburtsdatum,Gegenstand,FW-Datum,LehrerIn,FW-Art,FW-Anmerkung,,,,
1ABMB,Guthan,Florian,06.09.1998,Englisch,04.05.2023,Vrana Philip,Mahnung,,,,,
1AFELC,Aibartuev,Musa,26.08.2008,Naturwissenschaftliche Grundlagen,11.11.2022,Szabo Simona,Mahnung,,,,,
1AFELC,Aibartuev,Musa,26.08.2008,Englisch,02.04.2023,Waidmayr Margit,Mahnung,,,,,
*/
    // wel in t einlesen.

    //erste Zeile nicht...
    fgets(text, LINEMAX, wel);

    i = 0;

    do   // Tab wird in tab eigelesen ... Gleichzeitig werden hier Vorgezogene Prüfungen entfernt
    {
        fgets(text, LINEMAX, wel);
        sprintf(t[i],"%s", text);
        i++;
    } while (!feof(wel));

    fclose(wel);

    // sortieren ... zur Kontrolle...

    sort(t,i);

    // Zeile für Zeile aus Mah lesen und in t eintragen

    fgets(text, LINEMAX, mah);
//    printf("erste Zeile --->%s", text);

    f = 0;

    while ((!feof(mah)) /*&& (f < 800)*/)  // zuerst nur die ersten paar Zeilen...
    {
        fgets(text, LINEMAX, mah);
//        system("cls");
//        printf("%3d %s\n", f, text);

        f++;
        j = k = 0;  while (text[j] != ',') { ClassName[k] = text[j]; j++; k++; } ClassName[k] = '\0';

//        printf("a) ClassName: .%s.\n", ClassName);

        j++; k = 0; while (text[j] != ',') { FamNam[k] = text[j];    j++; k++; } FamNam[k] = '\0';
        j++; k = 0; while (text[j] != ',') { VorNam[k] = text[j];    j++; k++; } VorNam[k] = '\0';

//        printf("b) Name: .%s.  .%s.\n", FamNam, VorNam);

        j++;        while (text[j] != ',') {j++;} // Geb Datum wird übersprungen

        // Gegenstand einlesen und Kurzform finden.
        //######
        sprintf(Subject, "                                                                                                    ");

        j++; k = 0; while ((text[j] != ',') && ((strcmp("Geografie", Subject) != 0))) { Subject[k] = text[j]; j++; k++; } Subject[k] = '\0';

        if (strncmp("Geografie", Subject, 9) == 0)  // weil GGP ein Gegenstand ist, in dem im Namen ein Beistich vorkommt!!!
        {
            j++; while (text[j] != ',') {j++;}
        }

//        printf("k = %d \n", k);
//        printf("c) sub: %s\n", Subject);



        j++; k = 0; while (text[j] != ',') { Date[k] = text[j];      j++; k++; } Date[k] = '\0';

//        printf("d) Datum: !%s!\n", Date);

        j++; k = 0; while (text[j] != ',') { Teacher[k] = text[j];   j++; k++; } Teacher[k] = '\0';
//        printf("e) teacher: .%s.\n", Teacher);

        n = 0;

//        printf("Subject: %s\n", Subject);


        for (k = 0; k < sizeof(SubNames)/LINEMAX;k++)
        {
            l = strlen(Subject);
            if (strncmp(Subject, SubNames[k], l) == 0)
            {
                sprintf(Sub,"%s",SubN[k]);
//                printf("f) SubN .%s.\n", SubN[k]);
                k = sizeof(SubNames)/LINEMAX;
                n = 1;
            }
        }
        if (n != 1)
        {
            printf("\nSubject not found: %s\n", Subject);
        }

        r = 0; while ((Sub[r] != ' ') && (Sub[r] != '\0')) { r++; } Sub[r] = '\0';

        // printf("---- read in tab --- \n");


        for (m = 0; m < i; m++)
        {

            s = 0; while (t[m][s] != ',') { s++; } s++;
                   while (t[m][s] != ',') { s++; } s++;
                   while (t[m][s] != ',') { s++; } s++;
            r = 0; while (t[m][s] != ',') { mahnClass[r]   = t[m][s]; s++; r++; } s++; mahnClass[r]   = '\0';
            r = 0; while ((mahnClass[r] != '_') && (mahnClass[r] != '\0')) { r++; }    mahnClass[r]   = '\0';
                                                                              // eleminate _J in 1AFELC_J
                   while (t[m][s] != ',') { s++; } s++;
                   while (t[m][s] != ',') { s++; } s++;
                   while (t[m][s] != ',') { s++; } s++;
            r = 0; while (t[m][s] != ',') { mahnSub  [r]   = t[m][s]; s++; r++; } s++; mahnSub[r]     = '\0';
            r = 0; while ((mahnSub[r] != ' ') && (mahnSub[r] != '\0')) { r++; }        mahnSub[r]     = '\0';
            r = 0; while (t[m][s] != ',') { mahnSurName[r] = t[m][s]; s++; r++; } s++; mahnSurName[r] = '\0';
            r = 0; while (t[m][s] != ',') { mahnName[r]    = t[m][s]; s++; r++; } s++; mahnName[r]    = '\0';


            // for tests: if (m <= 10) printf("T:: %02d: .%s. Subject .%s. Name:.%s. name .%s.\n", m, mahnClass, mahnSub, mahnSurName, mahnName);

            if (((strncmp(mahnSurName,FamNam,strlen(FamNam))) == 0) &&
                ((strncmp(mahnName,VorNam,strlen(VorNam))) == 0) &&
                ((strncmp(mahnSub,Sub,strlen(Sub))) == 0)     )
            {
//                printf("== %d: class: .%s. name: .%s. .%s.  subj: .%s. date: %s\n",m, mahnClass, mahnSurName,  mahnName, Sub, Date);

                t[m][19] = Date[0];
                t[m][20] = Date[1];
                t[m][21] = Date[3];
                t[m][22] = Date[4];
                t[m][23] = Date[8];
                t[m][24] = Date[9];
                t[m][32]++;
//                printf("m: %d %s", m, t[m]);
mCounter++;
printf("* %s, %s\n", Teacher, NextClass); // gefunden


            }

        }


//printf("hier!\n");
//        getch();
    }










    //  mah schließen

    fclose(mah);

printf("%d Mahnungen konnten zugeordnet werden\n", mCounter);




    // Wiederholungsprüfungen sortieren und wieder speichern

    writeF(&wel,"./Wiederholungspruefungen.csv");


    for (j = 0; j < i; j++) fprintf(wel,"%s", t[j]);

    fclose(wel);


printf("%d 5er wurden gefunden\n", j);


}
    /**└────────────────────────────────────────────────┘**/



    return 0;
}



//*****************************************************************************
int readF(FILE ** f, const char * s)
//*****************************************************************************
{
    *f = fopen((const char*)s, "r+");

    if (*f == NULL)
    {
        printf("\n@1:%s konnte nicht geoeffnet werden.\n", s);
        exit(1);
    }
    return 0;
}

//*****************************************************************************
int writeF(FILE ** f, const char * s)
//*****************************************************************************
{
    *f = fopen((const char*)s, "w+");

    if (*f == NULL)
    {
        printf("\n@2:%s konnte nicht angelegt werden. \n", s);
        exit(2);
    }
    return 0;
}

//*****************************************************************************
int copyFile(FILE * d, FILE * s)
//*****************************************************************************
{
char text[LINEMAX];

    do
    {
        if (fgets(text, LINEMAX, s))
        {
            fprintf(d, "%s", text);
        }
    } while (!feof(s));

    return 0;
}

//*****************************************************************************
int delXUnderline(FILE * l, FILE * l_no_unders, int summer)
//*****************************************************************************
{
char text[LINEMAX];
int i, j, underLineFound;
char newText[LINEMAX + 50];


    do
    {

        if (fgets(text, LINEMAX, l))
        {
            if ((strncmp(text,"1AO",3) == 0) && (text[33] == '2')) // 03.02 Semesterzeugnis!
            {
                sprintf(newText,"1OHIF,Schulnachricht%s", text + 28);
                strncpy(text,newText,LINEMAX);
                printf("%s", text);
            }
            if ((strncmp(text,"1AO",3) == 0) && (text[33] == '6')) // 30.06 Semesterzeugnis!
            {
                sprintf(newText,"1OHIF,Jahreszeugnis%s", text + 28);
                strncpy(text,newText,LINEMAX);
                printf("%s", text);
            }

            if ((strncmp(text,"1BO",3) == 0) && (text[33] == '2')) // 03.02 Semesterzeugnis!
            {
                sprintf(newText,"1OHEL,Schulnachricht%s", text + 28);
                strncpy(text,newText,LINEMAX);
                printf("%s", text);
            }
            if ((strncmp(text,"1BO",3) == 0) && (text[33] == '6')) // 30.06 Semesterzeugnis!
            {
                sprintf(newText,"1OHEL,Jahreszeugnis%s", text + 28);
                strncpy(text,newText,LINEMAX);
                printf("%s", text);
            }

            // wird nur beim ersten Durchlauf angezeigt!

            if ( (text[1] != 'O') ||
                ((text[1] == 'O') && (text[6] == 'S') && (summer == 0)) ||    // hier werden entweder nur J Zeilen odeer nur S Zeilen für die O Klassen zugelassen
                ((text[1] == 'O') && (text[6] == 'J') && (summer == 1))    )
            {


                for (i = 0; i < strlen(text); i++) if (text[i] == ';') text[i] = ',';
                i = 0;

                while(text[i] != ',') {newText[i] = text[i]; i++;} newText[i] = text[i]; i++;
                while(text[i] != ',') {newText[i] = text[i]; i++;} newText[i] = text[i]; i++;
                while(text[i] != ',') {newText[i] = text[i]; i++;} newText[i] = text[i]; i++;
                while(text[i] != ',') {newText[i] = text[i]; i++;} newText[i] = text[i]; i++;
                while(text[i] != ',') {newText[i] = text[i]; i++;} newText[i] = text[i]; i++;

                // gibts hier ein Underline?:

                j = i;

                underLineFound = 0;

                while(text[j]!= ',')
                {
                    if (text[j] == '_') underLineFound = 1;
                    j++;
                }

                j = i;
                if (underLineFound)
                {
                    while(text[j]!= '_') j++;
                    j++;
                }

                while(text[j]!= '\0') {newText[i] = text[j];

                i++; j++;}
                newText[i] = '\0';

                fprintf(l_no_unders,"%s",newText);

            }
        }

    } while (!feof(l));

    return 0;
}

//*****************************************************************************
int list2tab(FILE * l, FILE * t, FILE * fehl, FILE * a, int summer)
//*****************************************************************************
{
char text[LINEMAX];
char tclass[LEN];
char tstundentafel[LEN];
char tname[LEN];
char tvorname[LEN];
char tsub[LEN];
char tval[LEN];
char tjvs;

char lastName[LEN] = {0};
char lastVorName[LEN] = {0};

int i, j;
int not[6] = {0};
int sum[6][2][6][6] = {{{{0}}}};
int sch[6][2][6] = {{{0}}};
int jg, hf, ab, no, n;
int ojg, ohf, oab;
int zeile = 1;

int auswerten;
int length;

    fgets(text, LINEMAX, l); // Klasse,Zeugnisart,Zeugnisdatum,Familienname,Vorname,Kurzbezeichnung,Note,Schulformkennzahl

printf("hier sub 1!\n");

    jg = hf = ab = no = n = 0;

    do
    {
        fgets(text, LINEMAX, l);

        length = strlen(text);
        zeile++;


printf("%06d len %06d %s", zeile, length, text);

        if (length > 0)
        {

            i = 0;
            j = 0;
            while ((text[i] != ',') /*&& (text[i] != '_')*/)   // class:  _WS  _SS abschneiden
            // für die weitere Arbeiten brauchen wir die Semesterinformation WS oder SS
            {
            tclass[j] = text[i];
                j++;
                i++;
            }
printf("a");
            if (tclass[0] == '1')
            {
                tclass[j] = '_'; j++;
                tclass[j] = text[i+1];j++;    // fügt J oder S ein
                                            // J Jahreszeugnis
                                            // S Schulnachricht
            }
printf("    b");

            tclass[j] = '\0';

            ojg = jg;
            ohf = hf;
            oab = ab;

            jg = tclass[0] - '0';
            hf = (tclass[2] == 'H') ? 0 : 1;
            ab = ((tclass[3] == 'E') && (tclass[4] == 'L')) ? 1 :
                 ((tclass[3] == 'E') && (tclass[4] == 'T')) ? 2 :
                 ((tclass[3] == 'I') && (tclass[4] == 'F')) ? 3 :
                 ((tclass[3] == 'M') && (tclass[4] == 'B')) ? 4 :
                 ((tclass[3] == 'W') && (tclass[4] == 'I')) ? 5 : 0;


                i++;
                tjvs = text[i];

//printf    ("%c\n", tjvs);   // J für Jahreszeugnis   S für Semesterzeugnis  V für Vorläufiges Zeugnis
            if (tjvs  == 'V') {tjvs = text[i + 13]; }   // Vorläufiges Semesterzeugnis bzw. Vorläufiges Jahreszeugnis
// das e    s vorläufig ist, macht nichts aus...
//#### s    icherlich noch nicht die beste Lösung!

            auswerten = FALSE;

            // summer:

printf("    c");

                if (summer == TRUE)
                {
                    if (tjvs == 'J') auswerten = TRUE;

                if ((tjvs == 'S') && (text[i + 1] == 'e'))  // Semesteryeugnis!
                {
                    if (text[i - 3] == 'S') auswerten = TRUE;  // sommersemesterzeugnis!
                    if ((tclass[0] == '2') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '4') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '6') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '8') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    }

                }
                else
                {
                    if ((tjvs == 'S') && (text[i + 1] == 'c')) auswerten = TRUE; // Schulnachricht

                    if ((tjvs == 'S') && (text[i + 1] == 'e'))  // Semesteryeugnis!
                    {
                    if (text[i - 3] == 'W') auswerten = TRUE;  // sommersemesteryeugnis!
                    if ((tclass[0] == '1') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '3') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '5') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer
                    if ((tclass[0] == '7') && (tclass[2] == 'B')) auswerten = TRUE;  // Abendschule Sommer

                    }


            }

printf("    d");


            while (text[i] != ',') // Schulnachricht bzw. Zeugnis
            {
                i++;
            }
            i++;


            while (text[i] != ',') // Ausstellungsdatum
            {
                i++;
            }
            i++;

printf("    e");


            j = 0;
            while (text[i] != ',')
            {
                tname[j] = text[i];
                j++;
                i++;
            }
            tname[j] = '\0';
            i++;

            j = 0;
            while (text[i] != ',')
            {
                tvorname[j] = text[i];
                j++;
                i++;
            }
            tvorname[j] = '\0';
            i++;

            j = 0;
            while (text[i] != ',')
            {
                tsub[j] = text[i];
                j++;
                i++;
            }
            tsub[j] = '\0';
            i++;

            j = 0;
            while (text[i] != ',')
            {
                tval[j] = text[i];
                j++;
                i++;
            }
            tval[j] = '\0';
            i++;

            if (j == 0)
            {
                if (text[0] == 'A')
                {
                    fprintf(fehl, "RDP/AP, %s", text);
                }
                else
                {
                    fprintf(fehl, "NOTE fehlet, %s", text);
                }

                tval[0] = '0';
            }
            else if (tval[0] == '5')
            {
                if (text[0] == 'A')
                {
                    fprintf(fehl, "RDP/AP 5er!, %s", text);
                }

            }

printf("    f");



/* Noten     umleiten seit 2020 April abgeschalten!
        if (!((tval[0] >= '0') && (tval[0] <= '5')))
        {
            if      ( tval[0] == 'S') {tval[0] = '1'; tval[1] = '\0';}   // Sehr zufriedenstellend
            else if ( tval[0] == 'Z') {tval[0] = '2'; tval[1] = '\0';}   // Zufriedenstellend
            else if ( tval[0] == 'W') {tval[0] = '3'; tval[1] = '\0';}   // Wenig zufriedenstellend
            else if ((tval[0] == 'N') && (tval[1] == 'Z') )
                                      {tval[0] = '8'; tval[1] = '\0';}   // Nicht zufriedenstellend

            else if ( tval[0] == 'B') {tval[0] = '1'; tval[1] = '\0';}   // Befreit   -   um diese Schüler nicht zu benachteiligen!
            else if ( tval[0] == 'T') {tval[0] = '1'; tval[1] = '\0';}   // Teilgenommen zählt als Sehr Gut
            else if ( tval[0] == 'G') {tval[0] = '6'; tval[1] = '\0';}   // Gestundet wird vorläufig nicht gewertet
            else if ( tval[0] == 'N') {tval[0] = '7'; tval[1] = '\0';}   // Nicht beurteilt - wie 6
            else if ( tval[0] == 'F') {tval[0] = '9'; tval[1] = '\0';}   // Nichts abgegeben ... Diplomarbeit ...
            else if ( tval[0] == 'X') {tval[0] = '9'; tval[1] = '\0';}   // 2018 in einer Abendschule - Bedeutung unklar         else if ( tval[0] == 'Y') {tval[0] = '9'; tval[1] = '\0';}   // ist in Mödling vorgekommen ...

            else
            {
#ifdef SELTSAME_NOTEN_AUSGEBEN
            printf("seltsame Note = .%c. zeile %d :: %s %s %s\n", tval[0], zeile, tclass, tname, tsub);
#endif
            }
            n =  (tval[0] == '0') ? 0 :   // 0 .... keine Note eingegeben!
                 (tval[0] == '1') ? 1 :
                 (tval[0] == '2') ? 2 :
                 (tval[0] == '3') ? 3 :
                 (tval[0] == '4') ? 4 :
                 (tval[0] == '5') ? 5 : 0;

            not[n]++;
        }
*/

printf("g");


            j = 0;
            while (text[i] != '\n')
            {
                tstundentafel[j] = text[i];
                j++;
                i++;
            }
            tstundentafel[j] = '\0';
            i++;

printf("h");


//        printf("%s",text);
//        printf("%s %s %s %s\n",tname, tvorname, tsub, tval);

            if (strcmp(tclass,"4BHELS") == 0) ZweiKlassen4System = 1;
            if (strcmp(tclass,"5BHELS") == 0) ZweiKlassen5System = 1;



            if ((strcmp(lastName,tname) != 0) || (strcmp(lastVorName,tvorname) != 0))
            {

                //printf("%s\n", tname);
                sprintf(lastName,"%s",tname);
                sprintf(lastVorName,"%s",tvorname);
                if (auswerten == TRUE) fprintf(t,"\n");

                jg = ojg;
                hf = ohf;
                ab = oab;

                if ((jg <= 5)  && (tclass[2] != 'B'))
            // statistik interessiert nur für Klassen 1 bis 5 - nicht eine AP_ Klasse, oder eine BRP Klasse usw.
            // auch Abendschule wird hier ausgesiebt
                {
                    sum[jg][hf][ab][0] += not[0]; not [0] = 0;
                    sum[jg][hf][ab][1] += not[1]; not [1] = 0;
                    sum[jg][hf][ab][2] += not[2]; not [2] = 0;
                    sum[jg][hf][ab][3] += not[3]; not [3] = 0;
                    sum[jg][hf][ab][4] += not[4]; not [4] = 0;
                    sum[jg][hf][ab][5] += not[5]; not [5] = 0;

                    sch[jg][hf][ab]++;
                }

                jg = hf = ab = no = n = 0;


                if ((strncmp(tclass,"4AHELS", 6) == 0)  ||
                    (strncmp(tclass,"4BHELS", 6) == 0)  ||
                    (strncmp(tclass,"5AHELS", 6) == 0)  ||
                    (strncmp(tclass,"5BHELS", 6) == 0)      )
                {
                    if (strncmp(tstundentafel,"8628_01", 7) == 0)
                    {
                        tclass[6] = 'E';
                    }
                    else
                    {
                        tclass[6] = 'W';
                    }

                    if (strncmp(tstundentafel,"8728_01", 7) == 0)
                    {
                        tclass[6] = 'E';
                    }
                    else
                    {
                        tclass[6] = 'W';
                    }

                // #### mit dem neuen Schwerpunkten kommt es hier zu neuen Nummern!  erstmals 2024 / 2025 im Semester!


                }
/*
if (strn    cmp(tclass,"1OHEL",5) == 0)
{
    if (    strncmp(tname,"Furmanov", 8) == 0)
    {
            printf("#\n");

            if (auswerten == TRUE) printf("%-10s,%c,", tclass,tjvs / *stundentafel* /);  // Klassen auf 10 Zeichen mit Blanks auffüllen
        if (auswerten == TRUE) printf("%s,%s,",tname,tvorname);
        if (auswerten == TRUE) printf("%s,%s,",tsub,tval);


    }

}
*/


                if (auswerten == TRUE) fprintf(t, "%-10s,%c,", tclass,tjvs /*stundentafel*/);  // Klassen auf 10 Zeichen mit Blanks auffüllen
                if (auswerten == TRUE) fprintf(t,"%s,%s,",tname,tvorname);
                if (auswerten == TRUE) fprintf(t,"%s,%s,",tsub,tval);

            }
            else
            {

                if (auswerten == TRUE) fprintf(t,"%s,%s,",tsub,tval);

                n =  (tval[0] == '0') ? 0 :   // 0 .... keine Note eingegeben!
                     (tval[0] == '1') ? 1 :
                     (tval[0] == '2') ? 2 :
                     (tval[0] == '3') ? 3 :
                     (tval[0] == '4') ? 4 :
                     (tval[0] == '5') ? 5 : 0;

                    not[n]++;

            }
        }

    } while (!feof(l));

// frage    : braucht das wer?

    if (    auswerten == TRUE) fprintf(a,"Abt, Klassse, Anzahl, n/s, 1, 2, 3, 4, 5, G, Sum, pro Kopf 1, 2, 3, 4, 5, G, Prozent, 1, 2, 3, 4, 5, G\n");

    n = sum[1][1][1][1] + sum[1][1][1][2] + sum[1][1][1][3] + sum[1][1][1][4] + sum[1][1][1][5] + sum[1][1][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 1AFELC, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][1][1], (float)n/sch[1][1][1],sum[1][1][1][1],sum[1][1][1][2],sum[1][1][1][3],sum[1][1][1][4],sum[1][1][1][5],sum[1][1][1][0], n, (float)sum[1][1][1][1]/sch[1][1][1],(float)sum[1][1][1][2]/sch[1][1][1],(float)sum[1][1][1][3]/sch[1][1][1],(float)sum[1][1][1][4]/sch[1][1][1],(float)sum[1][1][1][5]/sch[1][1][1],(float)sum[1][1][1][0]/sch[1][1][1], 100.*sum[1][1][1][1]/n,100.*sum[1][1][1][2]/n,100.*sum[1][1][1][3]/n,100.*sum[1][1][1][4]/n,100.*sum[1][1][1][5]/n,100.*sum[1][1][1][0]/n);
    n = sum[2][1][1][1] + sum[1][1][1][2] + sum[1][1][1][3] + sum[1][1][1][4] + sum[1][1][1][5] + sum[1][1][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 2AFELC, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][1][1], (float)n/sch[2][1][1],sum[2][1][1][1],sum[2][1][1][2],sum[2][1][1][3],sum[2][1][1][4],sum[2][1][1][5],sum[2][1][1][0], n, (float)sum[2][1][1][1]/sch[2][1][1],(float)sum[2][1][1][2]/sch[2][1][1],(float)sum[2][1][1][3]/sch[2][1][1],(float)sum[2][1][1][4]/sch[2][1][1],(float)sum[2][1][1][5]/sch[2][1][1],(float)sum[2][1][1][0]/sch[2][1][1], 100.*sum[2][1][1][1]/n,100.*sum[2][1][1][2]/n,100.*sum[2][1][1][3]/n,100.*sum[2][1][1][4]/n,100.*sum[2][1][1][5]/n,100.*sum[2][1][1][0]/n);
    n = sum[3][1][1][1] + sum[1][1][1][2] + sum[1][1][1][3] + sum[1][1][1][4] + sum[1][1][1][5] + sum[1][1][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 3AFELC, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][1][1], (float)n/sch[3][1][1],sum[3][1][1][1],sum[3][1][1][2],sum[3][1][1][3],sum[3][1][1][4],sum[3][1][1][5],sum[3][1][1][0], n, (float)sum[3][1][1][1]/sch[3][1][1],(float)sum[3][1][1][2]/sch[3][1][1],(float)sum[3][1][1][3]/sch[3][1][1],(float)sum[3][1][1][4]/sch[3][1][1],(float)sum[3][1][1][5]/sch[3][1][1],(float)sum[3][1][1][0]/sch[3][1][1], 100.*sum[3][1][1][1]/n,100.*sum[3][1][1][2]/n,100.*sum[3][1][1][3]/n,100.*sum[3][1][1][4]/n,100.*sum[3][1][1][5]/n,100.*sum[3][1][1][0]/n);
    n = sum[4][1][1][1] + sum[1][1][1][2] + sum[1][1][1][3] + sum[1][1][1][4] + sum[1][1][1][5] + sum[1][1][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 4AFELC, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][1][1], (float)n/sch[4][1][1],sum[4][1][1][1],sum[4][1][1][2],sum[4][1][1][3],sum[4][1][1][4],sum[4][1][1][5],sum[4][1][1][0], n, (float)sum[4][1][1][1]/sch[4][1][1],(float)sum[4][1][1][2]/sch[4][1][1],(float)sum[4][1][1][3]/sch[4][1][1],(float)sum[4][1][1][4]/sch[4][1][1],(float)sum[4][1][1][5]/sch[4][1][1],(float)sum[4][1][1][0]/sch[4][1][1], 100.*sum[4][1][1][1]/n,100.*sum[4][1][1][2]/n,100.*sum[4][1][1][3]/n,100.*sum[4][1][1][4]/n,100.*sum[4][1][1][5]/n,100.*sum[4][1][1][0]/n);
    n = sum[1][1][2][1] + sum[1][1][2][2] + sum[1][1][2][3] + sum[1][1][2][4] + sum[1][1][2][5] + sum[1][1][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 1AFET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][1][2], (float)n/sch[1][1][2],sum[1][1][2][1],sum[1][1][2][2],sum[1][1][2][3],sum[1][1][2][4],sum[1][1][2][5],sum[1][1][2][0], n, (float)sum[1][1][2][1]/sch[1][1][2],(float)sum[1][1][2][2]/sch[1][1][2],(float)sum[1][1][2][3]/sch[1][1][2],(float)sum[1][1][2][4]/sch[1][1][2],(float)sum[1][1][2][5]/sch[1][1][2],(float)sum[1][1][2][0]/sch[1][1][2], 100.*sum[1][1][2][1]/n,100.*sum[1][1][2][2]/n,100.*sum[1][1][2][3]/n,100.*sum[1][1][2][4]/n,100.*sum[1][1][2][5]/n,100.*sum[1][1][2][0]/n);
    n = sum[2][1][2][1] + sum[1][1][2][2] + sum[1][1][2][3] + sum[1][1][2][4] + sum[1][1][2][5] + sum[1][1][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 2AFET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][1][2], (float)n/sch[2][1][2],sum[2][1][2][1],sum[2][1][2][2],sum[2][1][2][3],sum[2][1][2][4],sum[2][1][2][5],sum[2][1][2][0], n, (float)sum[2][1][2][1]/sch[2][1][2],(float)sum[2][1][2][2]/sch[2][1][2],(float)sum[2][1][2][3]/sch[2][1][2],(float)sum[2][1][2][4]/sch[2][1][2],(float)sum[2][1][2][5]/sch[2][1][2],(float)sum[2][1][2][0]/sch[2][1][2], 100.*sum[2][1][2][1]/n,100.*sum[2][1][2][2]/n,100.*sum[2][1][2][3]/n,100.*sum[2][1][2][4]/n,100.*sum[2][1][2][5]/n,100.*sum[2][1][2][0]/n);
    n = sum[3][1][2][1] + sum[1][1][2][2] + sum[1][1][2][3] + sum[1][1][2][4] + sum[1][1][2][5] + sum[1][1][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 3AFET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][1][2], (float)n/sch[3][1][2],sum[3][1][2][1],sum[3][1][2][2],sum[3][1][2][3],sum[3][1][2][4],sum[3][1][2][5],sum[3][1][2][0], n, (float)sum[3][1][2][1]/sch[3][1][2],(float)sum[3][1][2][2]/sch[3][1][2],(float)sum[3][1][2][3]/sch[3][1][2],(float)sum[3][1][2][4]/sch[3][1][2],(float)sum[3][1][2][5]/sch[3][1][2],(float)sum[3][1][2][0]/sch[3][1][2], 100.*sum[3][1][2][1]/n,100.*sum[3][1][2][2]/n,100.*sum[3][1][2][3]/n,100.*sum[3][1][2][4]/n,100.*sum[3][1][2][5]/n,100.*sum[3][1][2][0]/n);
    n = sum[4][1][2][1] + sum[1][1][2][2] + sum[1][1][2][3] + sum[1][1][2][4] + sum[1][1][2][5] + sum[1][1][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 4AFET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][1][2], (float)n/sch[4][1][2],sum[4][1][2][1],sum[4][1][2][2],sum[4][1][2][3],sum[4][1][2][4],sum[4][1][2][5],sum[4][1][2][0], n, (float)sum[4][1][2][1]/sch[4][1][2],(float)sum[4][1][2][2]/sch[4][1][2],(float)sum[4][1][2][3]/sch[4][1][2],(float)sum[4][1][2][4]/sch[4][1][2],(float)sum[4][1][2][5]/sch[4][1][2],(float)sum[4][1][2][0]/sch[4][1][2], 100.*sum[4][1][2][1]/n,100.*sum[4][1][2][2]/n,100.*sum[4][1][2][3]/n,100.*sum[4][1][2][4]/n,100.*sum[4][1][2][5]/n,100.*sum[4][1][2][0]/n);
    n = sum[1][1][4][1] + sum[1][1][4][2] + sum[1][1][4][3] + sum[1][1][4][4] + sum[1][1][4][5] + sum[1][1][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 1AFMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][1][4], (float)n/sch[1][1][4],sum[1][1][4][1],sum[1][1][4][2],sum[1][1][4][3],sum[1][1][4][4],sum[1][1][4][5],sum[1][1][4][0], n, (float)sum[1][1][4][1]/sch[1][1][4],(float)sum[1][1][4][2]/sch[1][1][4],(float)sum[1][1][4][3]/sch[1][1][4],(float)sum[1][1][4][4]/sch[1][1][4],(float)sum[1][1][4][5]/sch[1][1][4],(float)sum[1][1][4][0]/sch[1][1][4], 100.*sum[1][1][4][1]/n,100.*sum[1][1][4][2]/n,100.*sum[1][1][4][3]/n,100.*sum[1][1][4][4]/n,100.*sum[1][1][4][5]/n,100.*sum[1][1][4][0]/n);
    n = sum[2][1][4][1] + sum[1][1][4][2] + sum[1][1][4][3] + sum[1][1][4][4] + sum[1][1][4][5] + sum[1][1][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 2AFMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][1][4], (float)n/sch[2][1][4],sum[2][1][4][1],sum[2][1][4][2],sum[2][1][4][3],sum[2][1][4][4],sum[2][1][4][5],sum[2][1][4][0], n, (float)sum[2][1][4][1]/sch[2][1][4],(float)sum[2][1][4][2]/sch[2][1][4],(float)sum[2][1][4][3]/sch[2][1][4],(float)sum[2][1][4][4]/sch[2][1][4],(float)sum[2][1][4][5]/sch[2][1][4],(float)sum[2][1][4][0]/sch[2][1][4], 100.*sum[2][1][4][1]/n,100.*sum[2][1][4][2]/n,100.*sum[2][1][4][3]/n,100.*sum[2][1][4][4]/n,100.*sum[2][1][4][5]/n,100.*sum[2][1][4][0]/n);
    n = sum[3][1][4][1] + sum[1][1][4][2] + sum[1][1][4][3] + sum[1][1][4][4] + sum[1][1][4][5] + sum[1][1][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 3AFMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][1][4], (float)n/sch[3][1][4],sum[3][1][4][1],sum[3][1][4][2],sum[3][1][4][3],sum[3][1][4][4],sum[3][1][4][5],sum[3][1][4][0], n, (float)sum[3][1][4][1]/sch[3][1][4],(float)sum[3][1][4][2]/sch[3][1][4],(float)sum[3][1][4][3]/sch[3][1][4],(float)sum[3][1][4][4]/sch[3][1][4],(float)sum[3][1][4][5]/sch[3][1][4],(float)sum[3][1][4][0]/sch[3][1][4], 100.*sum[3][1][4][1]/n,100.*sum[3][1][4][2]/n,100.*sum[3][1][4][3]/n,100.*sum[3][1][4][4]/n,100.*sum[3][1][4][5]/n,100.*sum[3][1][4][0]/n);
    n = sum[4][1][4][1] + sum[1][1][4][2] + sum[1][1][4][3] + sum[1][1][4][4] + sum[1][1][4][5] + sum[1][1][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 4AFMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][1][4], (float)n/sch[4][1][4],sum[4][1][4][1],sum[4][1][4][2],sum[4][1][4][3],sum[4][1][4][4],sum[4][1][4][5],sum[4][1][4][0], n, (float)sum[4][1][4][1]/sch[4][1][4],(float)sum[4][1][4][2]/sch[4][1][4],(float)sum[4][1][4][3]/sch[4][1][4],(float)sum[4][1][4][4]/sch[4][1][4],(float)sum[4][1][4][5]/sch[4][1][4],(float)sum[4][1][4][0]/sch[4][1][4], 100.*sum[4][1][4][1]/n,100.*sum[4][1][4][2]/n,100.*sum[4][1][4][3]/n,100.*sum[4][1][4][4]/n,100.*sum[4][1][4][5]/n,100.*sum[4][1][4][0]/n);
    n = sum[1][0][1][1] + sum[1][0][1][2] + sum[1][0][1][3] + sum[1][0][1][4] + sum[1][0][1][5] + sum[1][0][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 1xHELS, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][0][1], (float)n/sch[1][0][1],sum[1][0][1][1],sum[1][0][1][2],sum[1][0][1][3],sum[1][0][1][4],sum[1][0][1][5],sum[1][0][1][0], n, (float)sum[1][0][1][1]/sch[1][0][1],(float)sum[1][0][1][2]/sch[1][0][1],(float)sum[1][0][1][3]/sch[1][0][1],(float)sum[1][0][1][4]/sch[1][0][1],(float)sum[1][0][1][5]/sch[1][0][1],(float)sum[1][0][1][0]/sch[1][0][1], 100.*sum[1][0][1][1]/n,100.*sum[1][0][1][2]/n,100.*sum[1][0][1][3]/n,100.*sum[1][0][1][4]/n,100.*sum[1][0][1][5]/n,100.*sum[1][0][1][0]/n);
    n = sum[2][0][1][1] + sum[2][0][1][2] + sum[2][0][1][3] + sum[2][0][1][4] + sum[2][0][1][5] + sum[2][0][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 2xHELS, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][0][1], (float)n/sch[2][0][1],sum[2][0][1][1],sum[2][0][1][2],sum[2][0][1][3],sum[2][0][1][4],sum[2][0][1][5],sum[2][0][1][0], n, (float)sum[2][0][1][1]/sch[2][0][1],(float)sum[2][0][1][2]/sch[2][0][1],(float)sum[2][0][1][3]/sch[2][0][1],(float)sum[2][0][1][4]/sch[2][0][1],(float)sum[2][0][1][5]/sch[2][0][1],(float)sum[2][0][1][0]/sch[2][0][1], 100.*sum[2][0][1][1]/n,100.*sum[2][0][1][2]/n,100.*sum[2][0][1][3]/n,100.*sum[2][0][1][4]/n,100.*sum[2][0][1][5]/n,100.*sum[2][0][1][0]/n);
    n = sum[3][0][1][1] + sum[3][0][1][2] + sum[3][0][1][3] + sum[3][0][1][4] + sum[3][0][1][5] + sum[3][0][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 3xHELS, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][0][1], (float)n/sch[3][0][1],sum[3][0][1][1],sum[3][0][1][2],sum[3][0][1][3],sum[3][0][1][4],sum[3][0][1][5],sum[3][0][1][0], n, (float)sum[3][0][1][1]/sch[3][0][1],(float)sum[3][0][1][2]/sch[3][0][1],(float)sum[3][0][1][3]/sch[3][0][1],(float)sum[3][0][1][4]/sch[3][0][1],(float)sum[3][0][1][5]/sch[3][0][1],(float)sum[3][0][1][0]/sch[3][0][1], 100.*sum[3][0][1][1]/n,100.*sum[3][0][1][2]/n,100.*sum[3][0][1][3]/n,100.*sum[3][0][1][4]/n,100.*sum[3][0][1][5]/n,100.*sum[3][0][1][0]/n);
    n = sum[4][0][1][1] + sum[4][0][1][2] + sum[4][0][1][3] + sum[4][0][1][4] + sum[4][0][1][5] + sum[4][0][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 4xHELS, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][0][1], (float)n/sch[4][0][1],sum[4][0][1][1],sum[4][0][1][2],sum[4][0][1][3],sum[4][0][1][4],sum[4][0][1][5],sum[4][0][1][0], n, (float)sum[4][0][1][1]/sch[4][0][1],(float)sum[4][0][1][2]/sch[4][0][1],(float)sum[4][0][1][3]/sch[4][0][1],(float)sum[4][0][1][4]/sch[4][0][1],(float)sum[4][0][1][5]/sch[4][0][1],(float)sum[4][0][1][0]/sch[4][0][1], 100.*sum[4][0][1][1]/n,100.*sum[4][0][1][2]/n,100.*sum[4][0][1][3]/n,100.*sum[4][0][1][4]/n,100.*sum[4][0][1][5]/n,100.*sum[4][0][1][0]/n);
    n = sum[5][0][1][1] + sum[5][0][1][2] + sum[5][0][1][3] + sum[5][0][1][4] + sum[5][0][1][5] + sum[5][0][1][0]; if (auswerten == TRUE) fprintf(a,"EL, 5xHELS, %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[5][0][1], (float)n/sch[5][0][1],sum[5][0][1][1],sum[5][0][1][2],sum[5][0][1][3],sum[5][0][1][4],sum[5][0][1][5],sum[5][0][1][0], n, (float)sum[5][0][1][1]/sch[5][0][1],(float)sum[5][0][1][2]/sch[5][0][1],(float)sum[5][0][1][3]/sch[5][0][1],(float)sum[5][0][1][4]/sch[5][0][1],(float)sum[5][0][1][5]/sch[5][0][1],(float)sum[5][0][1][0]/sch[5][0][1], 100.*sum[5][0][1][1]/n,100.*sum[5][0][1][2]/n,100.*sum[5][0][1][3]/n,100.*sum[5][0][1][4]/n,100.*sum[5][0][1][5]/n,100.*sum[5][0][1][0]/n);
    n = sum[1][0][2][1] + sum[1][0][2][2] + sum[1][0][2][3] + sum[1][0][2][4] + sum[1][0][2][5] + sum[1][0][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 1xHET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][0][2], (float)n/sch[1][0][2],sum[1][0][2][1],sum[1][0][2][2],sum[1][0][2][3],sum[1][0][2][4],sum[1][0][2][5],sum[1][0][2][0], n, (float)sum[1][0][2][1]/sch[1][0][2],(float)sum[1][0][2][2]/sch[1][0][2],(float)sum[1][0][2][3]/sch[1][0][2],(float)sum[1][0][2][4]/sch[1][0][2],(float)sum[1][0][2][5]/sch[1][0][2],(float)sum[1][0][2][0]/sch[1][0][2], 100.*sum[1][0][2][1]/n,100.*sum[1][0][2][2]/n,100.*sum[1][0][2][3]/n,100.*sum[1][0][2][4]/n,100.*sum[1][0][2][5]/n,100.*sum[1][0][2][0]/n);
    n = sum[2][0][2][1] + sum[2][0][2][2] + sum[2][0][2][3] + sum[2][0][2][4] + sum[2][0][2][5] + sum[2][0][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 2xHET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][0][2], (float)n/sch[2][0][2],sum[2][0][3][1],sum[2][0][2][2],sum[2][0][2][3],sum[2][0][2][4],sum[2][0][2][5],sum[2][0][2][0], n, (float)sum[2][0][2][1]/sch[2][0][2],(float)sum[2][0][2][2]/sch[2][0][2],(float)sum[2][0][2][3]/sch[2][0][2],(float)sum[2][0][2][4]/sch[2][0][2],(float)sum[2][0][2][5]/sch[2][0][2],(float)sum[2][0][2][0]/sch[2][0][2], 100.*sum[2][0][2][1]/n,100.*sum[2][0][2][2]/n,100.*sum[2][0][2][3]/n,100.*sum[2][0][2][4]/n,100.*sum[2][0][2][5]/n,100.*sum[2][0][2][0]/n);
    n = sum[3][0][2][1] + sum[3][0][2][2] + sum[3][0][2][3] + sum[3][0][2][4] + sum[3][0][2][5] + sum[3][0][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 3xHET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][0][2], (float)n/sch[3][0][2],sum[3][0][3][1],sum[3][0][2][2],sum[3][0][2][3],sum[3][0][2][4],sum[3][0][2][5],sum[3][0][2][0], n, (float)sum[3][0][2][1]/sch[3][0][2],(float)sum[3][0][2][2]/sch[3][0][2],(float)sum[3][0][2][3]/sch[3][0][2],(float)sum[3][0][2][4]/sch[3][0][2],(float)sum[3][0][2][5]/sch[3][0][2],(float)sum[3][0][2][0]/sch[3][0][2], 100.*sum[3][0][2][1]/n,100.*sum[3][0][2][2]/n,100.*sum[3][0][2][3]/n,100.*sum[3][0][2][4]/n,100.*sum[3][0][2][5]/n,100.*sum[3][0][2][0]/n);
    n = sum[4][0][2][1] + sum[4][0][2][2] + sum[4][0][2][3] + sum[4][0][2][4] + sum[4][0][2][5] + sum[4][0][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 4xHET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][0][2], (float)n/sch[4][0][2],sum[4][0][3][1],sum[4][0][2][2],sum[4][0][2][3],sum[4][0][2][4],sum[4][0][2][5],sum[4][0][2][0], n, (float)sum[4][0][2][1]/sch[4][0][2],(float)sum[4][0][2][2]/sch[4][0][2],(float)sum[4][0][2][3]/sch[4][0][2],(float)sum[4][0][2][4]/sch[4][0][2],(float)sum[4][0][2][5]/sch[4][0][2],(float)sum[4][0][2][0]/sch[4][0][2], 100.*sum[4][0][2][1]/n,100.*sum[4][0][2][2]/n,100.*sum[4][0][2][3]/n,100.*sum[4][0][2][4]/n,100.*sum[4][0][2][5]/n,100.*sum[4][0][2][0]/n);
    n = sum[5][0][2][1] + sum[5][0][2][2] + sum[5][0][2][3] + sum[5][0][2][4] + sum[5][0][2][5] + sum[5][0][2][0]; if (auswerten == TRUE) fprintf(a,"ET, 5xHET , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[5][0][2], (float)n/sch[5][0][2],sum[5][0][3][1],sum[5][0][2][2],sum[5][0][2][3],sum[5][0][2][4],sum[5][0][2][5],sum[5][0][2][0], n, (float)sum[5][0][2][1]/sch[5][0][2],(float)sum[5][0][2][2]/sch[5][0][2],(float)sum[5][0][2][3]/sch[5][0][2],(float)sum[5][0][2][4]/sch[5][0][2],(float)sum[5][0][2][5]/sch[5][0][2],(float)sum[5][0][2][0]/sch[5][0][2], 100.*sum[5][0][2][1]/n,100.*sum[5][0][2][2]/n,100.*sum[5][0][2][3]/n,100.*sum[5][0][2][4]/n,100.*sum[5][0][2][5]/n,100.*sum[5][0][2][0]/n);
    n = sum[1][0][3][1] + sum[1][0][3][2] + sum[1][0][3][3] + sum[1][0][3][4] + sum[1][0][3][5] + sum[1][0][3][0]; if (auswerten == TRUE) fprintf(a,"IF, 1xHIF , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][0][3], (float)n/sch[1][0][3],sum[1][0][3][1],sum[1][0][3][2],sum[1][0][3][3],sum[1][0][3][4],sum[1][0][3][5],sum[1][0][3][0], n, (float)sum[1][0][3][1]/sch[1][0][3],(float)sum[1][0][3][2]/sch[1][0][3],(float)sum[1][0][3][3]/sch[1][0][3],(float)sum[1][0][3][4]/sch[1][0][3],(float)sum[1][0][3][5]/sch[1][0][3],(float)sum[1][0][3][0]/sch[1][0][3], 100.*sum[1][0][3][1]/n,100.*sum[1][0][3][2]/n,100.*sum[1][0][3][3]/n,100.*sum[1][0][3][4]/n,100.*sum[1][0][3][5]/n,100.*sum[1][0][3][0]/n);
    n = sum[2][0][3][1] + sum[2][0][3][2] + sum[2][0][3][3] + sum[2][0][3][4] + sum[2][0][3][5] + sum[2][0][3][0]; if (auswerten == TRUE) fprintf(a,"IF, 2xHIF , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][0][3], (float)n/sch[2][0][3],sum[2][0][3][1],sum[2][0][3][2],sum[2][0][3][3],sum[2][0][3][4],sum[2][0][3][5],sum[2][0][3][0], n, (float)sum[2][0][3][1]/sch[2][0][3],(float)sum[2][0][3][2]/sch[2][0][3],(float)sum[2][0][3][3]/sch[2][0][3],(float)sum[2][0][3][4]/sch[2][0][3],(float)sum[2][0][3][5]/sch[2][0][3],(float)sum[2][0][3][0]/sch[2][0][3], 100.*sum[2][0][3][1]/n,100.*sum[2][0][3][2]/n,100.*sum[2][0][3][3]/n,100.*sum[2][0][3][4]/n,100.*sum[2][0][3][5]/n,100.*sum[2][0][3][0]/n);
    n = sum[3][0][3][1] + sum[3][0][3][2] + sum[3][0][3][3] + sum[3][0][3][4] + sum[3][0][3][5] + sum[3][0][3][0]; if (auswerten == TRUE) fprintf(a,"IF, 3xHIF , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][0][3], (float)n/sch[3][0][3],sum[3][0][3][1],sum[3][0][3][2],sum[3][0][3][3],sum[3][0][3][4],sum[3][0][3][5],sum[3][0][3][0], n, (float)sum[3][0][3][1]/sch[3][0][3],(float)sum[3][0][3][2]/sch[3][0][3],(float)sum[3][0][3][3]/sch[3][0][3],(float)sum[3][0][3][4]/sch[3][0][3],(float)sum[3][0][3][5]/sch[3][0][3],(float)sum[3][0][3][0]/sch[3][0][3], 100.*sum[3][0][3][1]/n,100.*sum[3][0][3][2]/n,100.*sum[3][0][3][3]/n,100.*sum[3][0][3][4]/n,100.*sum[3][0][3][5]/n,100.*sum[3][0][3][0]/n);
    n = sum[4][0][3][1] + sum[4][0][3][2] + sum[4][0][3][3] + sum[4][0][3][4] + sum[4][0][3][5] + sum[4][0][3][0]; if (auswerten == TRUE) fprintf(a,"IF, 4xHIF , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][0][3], (float)n/sch[4][0][3],sum[4][0][3][1],sum[4][0][3][2],sum[4][0][3][3],sum[4][0][3][4],sum[4][0][3][5],sum[4][0][3][0], n, (float)sum[4][0][3][1]/sch[4][0][3],(float)sum[4][0][3][2]/sch[4][0][3],(float)sum[4][0][3][3]/sch[4][0][3],(float)sum[4][0][3][4]/sch[4][0][3],(float)sum[4][0][3][5]/sch[4][0][3],(float)sum[4][0][3][0]/sch[4][0][3], 100.*sum[4][0][3][1]/n,100.*sum[4][0][3][2]/n,100.*sum[4][0][3][3]/n,100.*sum[4][0][3][4]/n,100.*sum[4][0][3][5]/n,100.*sum[4][0][3][0]/n);
    n = sum[5][0][3][1] + sum[5][0][3][2] + sum[5][0][3][3] + sum[5][0][3][4] + sum[5][0][3][5] + sum[5][0][3][0]; if (auswerten == TRUE) fprintf(a,"IF, 5xHIF , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[5][0][3], (float)n/sch[5][0][3],sum[5][0][3][1],sum[5][0][3][2],sum[5][0][3][3],sum[5][0][3][4],sum[5][0][3][5],sum[5][0][3][0], n, (float)sum[5][0][3][1]/sch[5][0][3],(float)sum[5][0][3][2]/sch[5][0][3],(float)sum[5][0][3][3]/sch[5][0][3],(float)sum[5][0][3][4]/sch[5][0][3],(float)sum[5][0][3][5]/sch[5][0][3],(float)sum[5][0][3][0]/sch[5][0][3], 100.*sum[5][0][3][1]/n,100.*sum[5][0][3][2]/n,100.*sum[5][0][3][3]/n,100.*sum[5][0][3][4]/n,100.*sum[5][0][3][5]/n,100.*sum[5][0][3][0]/n);
    n = sum[1][0][4][1] + sum[1][0][4][2] + sum[1][0][4][3] + sum[1][0][4][4] + sum[1][0][4][5] + sum[1][0][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 1xHMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][0][4], (float)n/sch[1][0][4],sum[1][0][4][1],sum[1][0][4][2],sum[1][0][4][3],sum[1][0][4][4],sum[1][0][4][5],sum[1][0][4][0], n, (float)sum[1][0][4][1]/sch[1][0][4],(float)sum[1][0][4][2]/sch[1][0][4],(float)sum[1][0][4][3]/sch[1][0][4],(float)sum[1][0][4][4]/sch[1][0][4],(float)sum[1][0][4][5]/sch[1][0][4],(float)sum[1][0][4][0]/sch[1][0][4], 100.*sum[1][0][4][1]/n,100.*sum[1][0][4][2]/n,100.*sum[1][0][4][3]/n,100.*sum[1][0][4][4]/n,100.*sum[1][0][4][5]/n,100.*sum[1][0][4][0]/n);
    n = sum[2][0][4][1] + sum[2][0][4][2] + sum[2][0][4][3] + sum[2][0][4][4] + sum[2][0][4][5] + sum[2][0][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 2xHMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][0][4], (float)n/sch[2][0][4],sum[2][0][4][1],sum[2][0][4][2],sum[2][0][4][3],sum[2][0][4][4],sum[2][0][4][5],sum[2][0][4][0], n, (float)sum[2][0][4][1]/sch[2][0][4],(float)sum[2][0][4][2]/sch[2][0][4],(float)sum[2][0][4][3]/sch[2][0][4],(float)sum[2][0][4][4]/sch[2][0][4],(float)sum[2][0][4][5]/sch[2][0][4],(float)sum[2][0][4][0]/sch[2][0][4], 100.*sum[2][0][4][1]/n,100.*sum[2][0][4][2]/n,100.*sum[2][0][4][3]/n,100.*sum[2][0][4][4]/n,100.*sum[2][0][4][5]/n,100.*sum[2][0][4][0]/n);
    n = sum[3][0][4][1] + sum[3][0][4][2] + sum[3][0][4][3] + sum[3][0][4][4] + sum[3][0][4][5] + sum[3][0][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 3xHMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][0][4], (float)n/sch[3][0][4],sum[3][0][4][1],sum[3][0][4][2],sum[3][0][4][3],sum[3][0][4][4],sum[3][0][4][5],sum[3][0][4][0], n, (float)sum[3][0][4][1]/sch[3][0][4],(float)sum[3][0][4][2]/sch[3][0][4],(float)sum[3][0][4][3]/sch[3][0][4],(float)sum[3][0][4][4]/sch[3][0][4],(float)sum[3][0][4][5]/sch[3][0][4],(float)sum[3][0][4][0]/sch[3][0][4], 100.*sum[3][0][4][1]/n,100.*sum[3][0][4][2]/n,100.*sum[3][0][4][3]/n,100.*sum[3][0][4][4]/n,100.*sum[3][0][4][5]/n,100.*sum[3][0][4][0]/n);
    n = sum[4][0][4][1] + sum[4][0][4][2] + sum[4][0][4][3] + sum[4][0][4][4] + sum[4][0][4][5] + sum[4][0][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 4xHMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][0][4], (float)n/sch[4][0][4],sum[4][0][4][1],sum[4][0][4][2],sum[4][0][4][3],sum[4][0][4][4],sum[4][0][4][5],sum[4][0][4][0], n, (float)sum[4][0][4][1]/sch[4][0][4],(float)sum[4][0][4][2]/sch[4][0][4],(float)sum[4][0][4][3]/sch[4][0][4],(float)sum[4][0][4][4]/sch[4][0][4],(float)sum[4][0][4][5]/sch[4][0][4],(float)sum[4][0][4][0]/sch[4][0][4], 100.*sum[4][0][4][1]/n,100.*sum[4][0][4][2]/n,100.*sum[4][0][4][3]/n,100.*sum[4][0][4][4]/n,100.*sum[4][0][4][5]/n,100.*sum[4][0][4][0]/n);
    n = sum[5][0][4][1] + sum[5][0][4][2] + sum[5][0][4][3] + sum[5][0][4][4] + sum[5][0][4][5] + sum[5][0][4][0]; if (auswerten == TRUE) fprintf(a,"MB, 5xHMB , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[5][0][4], (float)n/sch[5][0][4],sum[5][0][4][1],sum[5][0][4][2],sum[5][0][4][3],sum[5][0][4][4],sum[5][0][4][5],sum[5][0][4][0], n, (float)sum[5][0][4][1]/sch[5][0][4],(float)sum[5][0][4][2]/sch[5][0][4],(float)sum[5][0][4][3]/sch[5][0][4],(float)sum[5][0][4][4]/sch[5][0][4],(float)sum[5][0][4][5]/sch[5][0][4],(float)sum[5][0][4][0]/sch[5][0][4], 100.*sum[5][0][4][1]/n,100.*sum[5][0][4][2]/n,100.*sum[5][0][4][3]/n,100.*sum[5][0][4][4]/n,100.*sum[5][0][4][5]/n,100.*sum[5][0][4][0]/n);
    n = sum[1][0][5][1] + sum[1][0][5][2] + sum[1][0][5][3] + sum[1][0][5][4] + sum[1][0][5][5] + sum[1][0][5][0]; if (auswerten == TRUE) fprintf(a,"WI, 1xHWI , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[1][0][5], (float)n/sch[1][0][5],sum[1][0][5][1],sum[1][0][5][2],sum[1][0][5][3],sum[1][0][5][4],sum[1][0][5][5],sum[1][0][5][0], n, (float)sum[1][0][5][1]/sch[1][0][5],(float)sum[1][0][5][2]/sch[1][0][5],(float)sum[1][0][5][3]/sch[1][0][5],(float)sum[1][0][5][4]/sch[1][0][5],(float)sum[1][0][5][5]/sch[1][0][5],(float)sum[1][0][5][0]/sch[1][0][5], 100.*sum[1][0][5][1]/n,100.*sum[1][0][5][2]/n,100.*sum[1][0][5][3]/n,100.*sum[1][0][5][4]/n,100.*sum[1][0][5][5]/n,100.*sum[1][0][5][0]/n);
    n = sum[2][0][5][1] + sum[2][0][5][2] + sum[2][0][5][3] + sum[2][0][5][4] + sum[2][0][5][5] + sum[2][0][5][0]; if (auswerten == TRUE) fprintf(a,"WI, 2xHWI , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[2][0][5], (float)n/sch[2][0][5],sum[2][0][5][1],sum[2][0][5][2],sum[2][0][5][3],sum[2][0][5][4],sum[2][0][5][5],sum[2][0][5][0], n, (float)sum[2][0][5][1]/sch[2][0][5],(float)sum[2][0][5][2]/sch[2][0][5],(float)sum[2][0][5][3]/sch[2][0][5],(float)sum[2][0][5][4]/sch[2][0][5],(float)sum[2][0][5][5]/sch[2][0][5],(float)sum[2][0][5][0]/sch[2][0][5], 100.*sum[2][0][5][1]/n,100.*sum[2][0][5][2]/n,100.*sum[2][0][5][3]/n,100.*sum[2][0][5][4]/n,100.*sum[2][0][5][5]/n,100.*sum[2][0][5][0]/n);
    n = sum[3][0][5][1] + sum[3][0][5][2] + sum[3][0][5][3] + sum[3][0][5][4] + sum[3][0][5][5] + sum[3][0][5][0]; if (auswerten == TRUE) fprintf(a,"WI, 3xHWI , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[3][0][5], (float)n/sch[3][0][5],sum[3][0][5][1],sum[3][0][5][2],sum[3][0][5][3],sum[3][0][5][4],sum[3][0][5][5],sum[3][0][5][0], n, (float)sum[3][0][5][1]/sch[3][0][5],(float)sum[3][0][5][2]/sch[3][0][5],(float)sum[3][0][5][3]/sch[3][0][5],(float)sum[3][0][5][4]/sch[3][0][5],(float)sum[3][0][5][5]/sch[3][0][5],(float)sum[3][0][5][0]/sch[3][0][5], 100.*sum[3][0][5][1]/n,100.*sum[3][0][5][2]/n,100.*sum[3][0][5][3]/n,100.*sum[3][0][5][4]/n,100.*sum[3][0][5][5]/n,100.*sum[3][0][5][0]/n);
    n = sum[4][0][5][1] + sum[4][0][5][2] + sum[4][0][5][3] + sum[4][0][5][4] + sum[4][0][5][5] + sum[4][0][5][0]; if (auswerten == TRUE) fprintf(a,"WI, 4xHWI , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[4][0][5], (float)n/sch[4][0][5],sum[4][0][5][1],sum[4][0][5][2],sum[4][0][5][3],sum[4][0][5][4],sum[4][0][5][5],sum[4][0][5][0], n, (float)sum[4][0][5][1]/sch[4][0][5],(float)sum[4][0][5][2]/sch[4][0][5],(float)sum[4][0][5][3]/sch[4][0][5],(float)sum[4][0][5][4]/sch[4][0][5],(float)sum[4][0][5][5]/sch[4][0][5],(float)sum[4][0][5][0]/sch[4][0][5], 100.*sum[4][0][5][1]/n,100.*sum[4][0][5][2]/n,100.*sum[4][0][5][3]/n,100.*sum[4][0][5][4]/n,100.*sum[4][0][5][5]/n,100.*sum[4][0][5][0]/n);
    n = sum[5][0][5][1] + sum[5][0][5][2] + sum[5][0][5][3] + sum[5][0][5][4] + sum[5][0][5][5] + sum[5][0][5][0]; if (auswerten == TRUE) fprintf(a,"WI, 5xHWI , %2d, %.2f,  %3d, %2d, %2d, %2d, %2d, %2d, %3d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f,, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", sch[5][0][5], (float)n/sch[5][0][5],sum[5][0][5][1],sum[5][0][5][2],sum[5][0][5][3],sum[5][0][5][4],sum[5][0][5][5],sum[5][0][5][0], n, (float)sum[5][0][5][1]/sch[5][0][5],(float)sum[5][0][5][2]/sch[5][0][5],(float)sum[5][0][5][3]/sch[5][0][5],(float)sum[5][0][5][4]/sch[5][0][5],(float)sum[5][0][5][5]/sch[5][0][5],(float)sum[5][0][5][0]/sch[5][0][5], 100.*sum[5][0][5][1]/n,100.*sum[5][0][5][2]/n,100.*sum[5][0][5][3]/n,100.*sum[5][0][5][4]/n,100.*sum[5][0][5][5]/n,100.*sum[5][0][5][0]/n);

    return 0;
}

//*****************************************************************************
int sortTab(FILE * tS, FILE * t) // sortiert <--- tab
//*****************************************************************************
{
char text[LINEMAX];
char ntext[LINEMAX];
char cName[LINEMAX];
char (* tab)[SMAX];
int i, n;
int j, k;

    tab = (char (*)[SMAX])malloc(SMAX * 20000);  // 20k lines
    if (!tab) {printf("no space for tab!\n"); exit(-1);}

    fgets(text, LINEMAX, t); // erste Zeile..
    fprintf(tS,"%s",text);
    fgets(text, LINEMAX, t); // sigma, klasse, name, vorname

    i = 0;

    do
    {
        sprintf(ntext, "%s", text);  //3AFEL
        j = k = 5;                   //012345

        if (text[5] == ',') { ntext[5] = ' '; ntext[6] = ' '; k = 7;}
        else if(text[6] == ',')
        {
            ntext[j] = text[k];
            j = k = 6;
            if (text[j] == ',') { ; ntext[6] = ' '; k = 7;}
        }
        else  // 4AHELSE,S, !!
              // 2AFELC_SS,S,   oder:
        {     // 012345678901
            if( text[6]== '_')
            {
                ntext[5] = text[5];
                ntext[6] = ' ';
                ntext[7] = ',';
                ntext[8] = (text[7] == 'S') ? 'J' : 'S';

                j = 11;
                k = 9;
            }
            else
            {
                j = k = 10;    //5AHELSW,S,
            }

        }

        while(text[j] != '\0') { ntext[k] = text[j]; k++; j++;}
        ntext[k] = '\0';

        sprintf(tab[i],"%s",ntext);
        i++;
        fgets(text, LINEMAX, t);

    } while (!feof(t));


    n = i;

    for (i = 0; i < n; i++)
    {
         sprintf(text, "%s",tab[i]);

         sprintf(cName,"%s",text);

         j = 0;
         k = strlen(text);

         while (j < k - 1 ) {text[j] = text[ (j + 10) % k]; j++;}

         text[k - 11] = cName[0];
         text[k - 10] = cName[1];
         text[k - 9] = cName[2];
         text[k - 8] = cName[3];
         text[k - 7] = cName[4];
         text[k - 6] = cName[5];
         text[k - 5] = cName[6];
         text[k - 4] = cName[7];
         text[k - 3] = cName[8];
         text[k - 2] = cName[9];
         text[k - 1] = 10; // LF !!!

         sprintf(tab[i],"%s",text);
    }


    sort(tab, n);

    for (i = 0; i < n; i++)
    {
        k = strlen(tab[i]);
        sprintf(text + 10, "%s", tab[i]);
        text[0]   = tab[i][k - 11];
        text[1]   = tab[i][k - 10];
        text[2]   = tab[i][k - 9];
        text[3]   = tab[i][k - 8];
        text[4]   = tab[i][k - 7];
        text[5]   = tab[i][k - 6];
        text[6]   = tab[i][k - 5];
        text[7]   = tab[i][k - 4];
        text[8]   = '*'; //tab[i][k - 3];
        text[9]   = tab[i][k - 2];
        //text[k-1] = 10;   // LF
        //text[k]   = '\0'; //
        sprintf(tab[i],"%s",text);
    }

    sort(tab, n);

    for (i = 0; i < n; i++)
    {
        k = strlen(tab[i]);
        tab[i][8] = tab[i][k - 3];
        tab[i][k - 11] = 10;
        tab[i][k - 10] = '\0';
    }

    for (i = 0; i < n; i++)
    {
//        printf("%s", tab[i]);
        fprintf(tS,"%s", tab[i]);
    }


    return 0;
}


//*****************************************************************************
int sortSigma(FILE * si, FILE * so, FILE * cl)
{
//*****************************************************************************
char num[10];
char onum[10];
char onumC[14][10];
char onumCB[14][10]; // old number of the Class Best one!
char (* tab)[SMAX];
char text[LINEMAX];
int numberOfEqualNumLevelInClass;
int i, j, n, r, s, c;

int rang[14] = {0};
float cRang[14] = {0};

    c = 0;

    // read sigma -> sort sigma
    numberOfEqualNumLevelInClass = 0;

    tab = (char (*)[SMAX])malloc(SMAX * 20000);  // 20k lines
    if (!tab) {printf("no space for tab!\n"); exit(-1);}

    sprintf(onum, "0.000000");
    for (i = 0; i < 14; i++) sprintf(onumC[i],  "0.000000");
    for (i = 0; i < 14; i++) sprintf(onumCB[i], "0.000000");



    fgets(text, LINEMAX, si); // erste Zeile..
    fgets(text, LINEMAX, si); // sigma, klasse, name, vorname

    i = 0;

    do
    {
        sprintf(tab[i],"%s",text);
        i++;
        fgets(text, LINEMAX, si);

    } while (!feof(si));


    n = i;

    sort(tab, n);

    r = s = 0;

    for(i = 0; i < n; i++) // Tabelle ist bereits sortiert - nun jede Zeile durchsehen:
    {
        j = 0;
        while (tab[i][j] != ',') j++;

//12345678
/*4BHELSE*/

        if ((tab[i][j+1] == '1') && (tab[i][j+3] == 'F')) c = 0;  /*1AFEL*/
        if ((tab[i][j+1] == '2') && (tab[i][j+3] == 'F')) c = 1;  /*2AFEL*/
        if ((tab[i][j+1] == '3') && (tab[i][j+3] == 'F')) c = 2;  /*3AFEL*/
        if ((tab[i][j+1] == '4') && (tab[i][j+3] == 'F')) c = 3;  /*4AFEL*/

        if ((tab[i][j+1] == '1') && (tab[i][j+2] == 'A')&& (tab[i][j+3] == 'H')) c = 4;  /*1AHEL*/
        if ((tab[i][j+1] == '1') && (tab[i][j+2] == 'B')&& (tab[i][j+3] == 'H')) c = 5;  /*1BHEL*/

        if ((tab[i][j+1] == '2') && (tab[i][j+2] == 'A')&& (tab[i][j+3] == 'H')) c = 6;  /*1AHEL*/
        if ((tab[i][j+1] == '2') && (tab[i][j+2] == 'B')&& (tab[i][j+3] == 'H')) c = 7;  /*1BHEL*/

        if ((tab[i][j+1] == '3') && (tab[i][j+2] == 'A')&& (tab[i][j+3] == 'H')) c = 8;  /*1AHEL*/
        if ((tab[i][j+1] == '3') && (tab[i][j+2] == 'B')&& (tab[i][j+3] == 'H')) c = 9;  /*1BHEL*/

        if ((tab[i][j+1] == '4') && (tab[i][j+2] == 'A')&& (tab[i][j+3] == 'H')) c = 10;  /*1AHEL*/
        if ((tab[i][j+1] == '4') && (tab[i][j+2] == 'B')&& (tab[i][j+3] == 'H')) c = 11;  /*1BHEL*/

        if ((tab[i][j+1] == '5') && (tab[i][j+2] == 'A')&& (tab[i][j+3] == 'H')) c = 12;  /*1AHEL*/
        if ((tab[i][j+1] == '5') && (tab[i][j+2] == 'B')&& (tab[i][j+3] == 'H')) c = 13;  /*1BHEL*/

        rang[c]++; // Rang innerhalb der Klasse!
        strncpy(num,tab[i],8); // das ist der Notendurchschnitt

        num[8] = '\0';

//        printf("%f\n", atof(num));

        cRang[c] += atof(num);  // damit wird der Notenschnitt innerhalb der Klasse aufsummiert.

        {
            r++; // Reihung
            s++;

//        strncpy(num,tab[i],8);  wird schon oberhalb erledigt ...
//        num[8] = '\0';

            if (strcmp(num,onum) == 0) r--;  // durch diese Zeile wird nicht weitergezählt, solange der Notenschnitt gleich ist!
            else r = s;

            if (strcmp(num,onumC[c]) == 0) numberOfEqualNumLevelInClass++;
            else numberOfEqualNumLevelInClass = 0;

            fprintf(so,"%d,%d,%s,%s", r, rang[c] - numberOfEqualNumLevelInClass,((rang[c] - numberOfEqualNumLevelInClass) == 1)? "Klassenbester/beste":" ",tab[i]);
            // falls rang[c]
            sprintf(onum,"%s",num);

            sprintf(onumC[c],"%s",num);
        }
    }

    for (i = 0; i < 14; i++)
    {
        fprintf(cl,"%s, %f\n",    (i ==  0)? "1AFEL":
                                  (i ==  1)? "2AFEL":
                                  (i ==  2)? "3AFEL":
                                  (i ==  3)? "4AFEL":
                                  (i ==  4)? "1AHEL":
                                  (i ==  5)? "1BHEL":
                                  (i ==  6)? "2AHEL":
                                  (i ==  7)? "2BHEL":
                                  (i ==  8)? "3AHEL":
                                  (i ==  9)? "3BHEL":
                                  (i == 10)? "4AHELS":
                                  (i == 11)? "4BHELS":
                                  (i == 12)? "5AHELS":
                                  (i == 13)? "5BHELS":
                                  "unknown class",


        cRang[i] / rang[i]);
    }



    return 0;
}
//*****************************************************************************
int createNewYear(FILE * n, FILE * t)
//*****************************************************************************
{
char text[LINEMAX];
char (* tab)[SMAX];
int i, j, k, a, b, c;
char mark;
int n5[SMAX] = {0}; // Anzahl der Nichtgenügend
int nG[SMAX] = {0}; // Anzahl der Gestundet
int nN[SMAX] = {0}; // Anzahl der NichtBeurteilt
int maxS;

    tab = (char (*)[SMAX])malloc(SMAX * 20000);  // 20k lines   --- sicher zuviel!

    if (tab == NULL) {printf("kein Speicher mehr vorhanden!\n create new year\n"); exit(0);}

    fgets(text, LINEMAX, t); // Klasse ... weg -

    i = j = 0;

    do
    {
        fgets(text, LINEMAX, t);
        sprintf(tab[i],"%s",text);
        j = 0;

        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;

        // ab hier stehen die Noten!

        while(j < strlen(tab[i]))
        {
            if (tab[i][j] == '5') n5[i]++;
            if (tab[i][j] == '6') nG[i]++;
            if (tab[i][j] == '7') nN[i]++;
            while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
            while(tab[i][j] != ',' && j < strlen(tab[i])) {j++;} j++;
        }


        i++;
    } while (!feof(t));

    // i speichert nun die Anzahl aller Schülerzeilen
    maxS = i;

    i = 0;
    do
    {
        if (((n5[i] + nG[i]) < 3) && (nN[i] == 0))
        {


            tab[i][0] = (tab[i][0]) + 1; // steigt auf.
        }
        i++;
    } while (i < maxS);

    sort(tab, maxS);



    i = 0;
    a = b = c = 0;
    k = 0;
    do
    {
        if ((a != tab[i][0]) ||
            (b != tab[i][1]) ||
            (c != tab[i][2]) )
        {

            k = 0;
            fprintf(n,"\n");
        }

        a = tab[i][0];
        b = tab[i][1];
        c = tab[i][2];

        k++;

        mark = ' ';

        j = 0; while (tab[i][j] != '\0') { if (tab[i][j] == '6') mark ='G'; j++; }
        j = 0; while (tab[i][j] != '\0') { if (tab[i][j] == '7') mark ='X'; j++; }

        fprintf(n, "%2d, %2c, %s", k, mark, tab[i]);
        i++;
    } while (i < maxS);



    free(tab);;

    return 0;
}

//*****************************************************************************
int selectJ(FILE * sigmaJ, FILE *sigma)
//*****************************************************************************
{
char text[LINEMAX];
int i, k;

    fgets(text, LINEMAX, sigma);
    fprintf(sigmaJ, "%s", text);

    //2.647059,1AFELC ,J,Azimi,Taher,
    //0123456789012345678901234567890123456789
    //          1         2         3

    do
    {
        if (fgets(text, LINEMAX, sigma))
        {
            if ((text[17] == 'J') || (text[17] == 'V'))
            {
                k = strlen(text);
                for (i = 17; i < k; i++) text[i] = text[i+2];

                fprintf(sigmaJ, "%s", text);
            }
        }

    } while (!feof(sigma));

    return 0;
}


//*****************************************************************************
int combineSigmaLines(FILE * sL, FILE * sigma)
//*****************************************************************************
{
char text[LINEMAX];
char ctl[LINEMAX]; //  combined text line
char sj;
int i;
long j, s, m, d;

    fprintf(sL,"avgY, delta, avgJ, avgS, className, Name,\n");

    fgets(text, LINEMAX, sigma); // Klasse ... weg -
    sprintf(ctl,"                                                                   ");
               //n.nnNNnn,+n.nnNN.nn, n.nnNNnn, n.nnNNnn, 1AFELC , Name, Vorname
               //012345678901234567890123456789012345678901234567890123456789
               //          1         2         3         4         5
    do
    {
        if (fgets(text, LINEMAX, sigma))
        {
            //printf(": %s", text);

            //2.647059,1AFELC ,J,Azimi,Taher,
            //0123456789012345678901234567890

            sj = text[17]; // Schulschlus (J) oder Semester (S) ... oder V = vorläufig

            text[17] = ' ';

            if(ctl[50] != ' ')
            {
                // es ist bereits ein Name vorhanden

                //printf("%s", text + 8);
                //printf("%s", ctl + 40);
                //printf("---\n");

                if (strcmp(text + 9, ctl + 41) == 0)
                {
                    // gleicher Name! und gleiche Klasse

                    if (sj == 'S') for (i = 0; i < 9; i++) ctl[31 + i] = text[i]; else for (i = 0; i < 9; i++) ctl[21 + i] = text[i];


                }
                else
                {
                    // alte Zeile abschließen:
//                    printf("%s", ctl);

                    // hier noch die Note berechnen!

                    j = 0;
                    if (ctl[21] != ' ')
                    {
                        j = ctl[21] - '0'; j *= 10;
                        j += ctl[23] - '0'; j *= 10;
                        j += ctl[24] - '0'; j *= 10;
                        j += ctl[25] - '0'; j *= 10;
                        j += ctl[26] - '0'; j *= 10;
                        j += ctl[27] - '0'; j *= 10;
                        j += ctl[28] - '0';

                    }

                    s = 0;
                    if (ctl[31] != ' ')
                    {
                        s = ctl[31] - '0'; s *= 10;
                        s += ctl[33] - '0'; s *= 10;
                        s += ctl[34] - '0'; s *= 10;
                        s += ctl[35] - '0'; s *= 10;
                        s += ctl[36] - '0'; s *= 10;
                        s += ctl[37] - '0'; s *= 10;
                        s += ctl[38] - '0';

                    }


                    m = (j == 0) ? s :
                        (s == 0) ? j :
                        (s + j) / 2;

                    d = (j == 0) ? 0 :
                        (s == 0) ? 0 :
                        (s - j);


                    ctl[0] = (m/1000000) % 10 + '0';
                    ctl[1] = '.';
                    ctl[2] = (m/100000) % 10 + '0';
                    ctl[3] = (m/10000) % 10 + '0';
                    ctl[4] = (m/1000) % 10 + '0';
                    ctl[5] = (m/100) % 10 + '0';
                    ctl[6] = (m/10) % 10 + '0';
                    ctl[7] =  m    % 10 + '0';
                    ctl[8] = ',';

                    if (d < 0) {ctl[9] = '-'; d = -d;} else ctl[9] = '+';


                    ctl[10] = (d/1000000) % 10 + '0';
                    ctl[11] = '.';
                    ctl[12] = (d/100000) % 10 + '0';
                    ctl[13] = (d/10000) % 10 + '0';
                    ctl[14] = (d/1000) % 10 + '0';
                    ctl[15] = (d/100) % 10 + '0';
                    ctl[16] = (d/10) % 10 + '0';
                    ctl[17] =  d    % 10 + '0';
                    ctl[19] = ',';
                    ctl[29] = ',';
                    ctl[39] = ',';

                    //printf("m = %ld  d = %ld  j = %ld   s = %ld \n", m, d, j, s);
                    //printf("%s", ctl);


                    // Durchschnitt aus J + S:

                    // Differenz aus J - S;
//getch();

                    fprintf(sL,"%s",ctl);
                    sprintf(ctl,"                                                                   ");
                    sprintf(ctl + 41, "%s", text + 9);

                    if (sj == 'S') for (i = 0; i < 9; i++) ctl[31 + i] = text[i]; else for (i = 0; i < 9; i++) ctl[21 + i] = text[i];


                }
            }
            else
            {
                // neueer Name gefunden - neuen Namen und Werte eintragen:

                sprintf(ctl + 41, "%s", text + 9);

                if (sj == 'S') for (i = 0; i < 9; i++) ctl[31 + i] = text[i]; else for (i = 0; i < 9; i++) ctl[21 + i] = text[i];

            }



        }

    } while (!feof(sigma));


    return 0;
}

//*****************************************************************************
int sort(char tab[][SMAX], int n)
//*****************************************************************************
{
int k, l, i, j;
char text[SMAX];

    // sort tab:
    for (k = 0; k < (n - 1); k++)
    {
        for (l = k; l < n; l++)
        {

            if (strcmp((const char *)(tab + k),
                       (const char *)(tab + l)) > 0)  // tab + 1 adds SMAX-Bytes !!!
            {
                //sprintf(text,"%s",(char *)(tab + k));
                j = strlen((char *)(tab + k));
                for (i = 0; i < j; i++) text[i] = ((char *)(tab + k))[i];
                text[i] = '\0';

                //sprintf((char*)(tab + k),"%s",(char*)(tab + l));
                j = strlen((char*)(tab + l));
                for (i = 0; i < j; i++) ((char*)(tab + k))[i] = ((char*)(tab + l))[i];
                ((char*)(tab + k))[i] = '\0';

                sprintf((char*)(tab + l),"%s",text);

            }
        }
    }
    return 0;
}

//*****************************************************************************
int delEQ(char tab[][SMAX], int n, int x)  // x: wieviele Stellen m�ssen gleich sein
// IN: tab: any table; n: the length of the tab which should be compared,
//     x: how many bytes has to be equal.
// POST: the tab is up to n elements redused to only one sample per element
// RETURN: the new (reduced) length of the table
//*****************************************************************************
{
    int k, m, i, j;
    m = 0;

    // note:  tab + 1 jumps SMAX bytes!   (char*)(tab) + 1 jumps only one !!!
    for (k = 0; m < n; k++)
    {
        //sprintf((char*)(tab) + ((k * SMAX)),"%s",(char*)(tab) + ((m*SMAX)));
        j = strlen((char*)(tab) + ((m*SMAX)));
        for(i = 0; i < j; i++) ((char*)(tab) + ((k * SMAX)))[i] = ((char*)(tab) + ((m*SMAX)))[i];
        ((char*)(tab) + ((k * SMAX)))[i] = '\0';

        while ((m < n) &&
                (strncmp((const char *)(tab) + ((k*SMAX)),
                         (const char *)(tab) + ((m*SMAX)) , x) == 0))
        {
            m++;
        }
    }
    return k;

}

int getAllSubsOfThisClass(int j, int i, char(*t)[SMAX], char (*subs)[30])
{
    int q, r, x,k,o;
    char newSubName[30];
    char secSubName[30];
    int verhInList = -1;
    int l, m, n,  listLength = 0, subAlreadyInList;

    for (q = j; q < i; q++)
    {
        r = 0;
        while(t[q][r] != ',') {r++;} r++;
        while(t[q][r] != ',') {r++;} r++;
        while(t[q][r] != ',') {r++;} r++;
        while(t[q][r] != ',') {r++;} r++;

        //erster Gegenstand gefunden

        while((t[q][r] != '\0') && (t[q][r] != '\n'))
        {
            x = 0;
            while(t[q][r] != ',')
            {
                newSubName[x] = t[q][r];
                x++;
                r++;
            }
            newSubName[x] = '\0';

// printf(".%s.\n", newSubName);  // neuer Gegenstand gefunden.    // gibt es den schon in der SubListe ?

            subAlreadyInList = 0;

            for (l = 0; l < listLength; l++)
            {
                if (strcmp(newSubName, subs[l]) == 0)
                {
                    subAlreadyInList = 1;
                     //printf("Sub %s bereits in Liste!\n", newSubName);
                    l = listLength;
                }
            }

            if (subAlreadyInList == 0)
            {
                listLength++;
                //printf("\nneuer Name gefunden... %d\n", listLength);
                sprintf(subs[l],"%s",newSubName);
            }

            while(t[q][r] != ','  &&
                  t[q][r] != '\0' &&
                  t[q][r] != '\n') {r++;}

            if ((t[q][r] != '\0') &&
                (t[q][r] != '\n'))  r++;

            while(t[q][r] != ','  &&
                  t[q][r] != '\0' &&
                  t[q][r] != '\n') {r++;}

            if ((t[q][r] != '\0') &&
                (t[q][r] != '\n')) r++;

        } // while ! \0  repeat!!
    }

    // Gegenstände sortieren:
    // falls verh in Liste - sollte es als erstes stehen

    for(m = 0; m < listLength; m++)
    {
        if (strcmp(subs[m], "verh") == 0)
        {
            verhInList = m;
            m = listLength;
        }
    }

    m = 0;

    if (verhInList >= 0)
    {
        sprintf(secSubName,"%s", subs[0]);

        //sprintf(subs[0],"%s", subs[verhInList]);
        o = strlen(subs[verhInList]);
        for (k = 0; k < o; k++) (subs[0])[k] = (subs[verhInList])[k];
        (subs[0])[k] = '\0';

        sprintf(subs[verhInList], "%s",secSubName);
        m = 1;
    }

    for(; m < listLength - 1; m++)
    {
        for (n = m; n < listLength; n++)
        {
            if (strcmp(subs[m], subs[n]) > 0)
            {
                sprintf(secSubName,"%s", subs[m]);

                //sprintf(subs[m],"%s", subs[n]);
                o= strlen(subs[n]);
                for (k = 0; k < o; k++) (subs[m])[k] = (subs[n])[k];
                (subs[m])[k] = '\0';

                sprintf(subs[n], "%s",secSubName);

            }
        }
    }

    return listLength;
}



int getAllFlecks(int j, char(*t)[SMAX])
{
int r;
int z;

        //printf("%s", t[j]);

        z = r = 0;
        while(t[j][r] != ',') {r++;} r++;
        while(t[j][r] != ',') {r++;} r++;
        while(t[j][r] != ',') {r++;} r++;
        while(t[j][r] != ',') {r++;} r++;
        while(t[j][r] != ',') {r++;} r++;


        while((t[j][r] != '\0') && (t[j][r] != '\n'))
        {

          //printf("%c-", t[j][r]);


          if((t[j][r] == '5') || (t[j][r] == 'N'))  z++;  // alle 5er und auch alle Nichtbeurteilt!
          while((t[j][r] != ',')  &&  (t[j][r] != '\0') && (t[j][r] != '\n')) {r++;} r++;
          while((t[j][r] != ',')  &&  (t[j][r] != '\0') && (t[j][r] != '\n')) {r++;} r++;

        }
        //printf("\n%d\n", z);

 //getch();
        return z;
}

int getClassIndex(char * classname)
{
    int ret = 0;

    if ((classname[3] == 'E') && (classname[4] == 'L'))
    {
         if ((classname[0] == '1') &&(classname[1] == 'A') && (classname[2] == 'H'))                          ret =  1;
         if ((classname[0] == '1') &&(classname[1] == 'B') && (classname[2] == 'H'))                          ret =  2;
         if ((classname[0] == '2') &&(classname[1] == 'A') && (classname[2] == 'H'))                          ret =  3;
         if ((classname[0] == '2') &&(classname[1] == 'B') && (classname[2] == 'H'))                          ret =  4;
         if ((classname[0] == '3') &&(classname[1] == 'A') && (classname[2] == 'H'))                          ret =  5;
         if ((classname[0] == '3') &&(classname[1] == 'B') && (classname[2] == 'H'))                          ret =  6;
         if ((classname[0] == '4') &&(classname[1] == 'A') && (classname[2] == 'H') && (classname[6] == 'E')) ret =  7;
         if ((classname[0] == '4') &&(classname[1] == 'B') && (classname[2] == 'H') && (classname[6] == 'E')) ret =  8;
         if ((classname[0] == '4') &&(classname[1] == 'A') && (classname[2] == 'H') && (classname[6] == 'W')) ret =  9;
         if ((classname[0] == '4') &&(classname[1] == 'B') && (classname[2] == 'H') && (classname[6] == 'W')) ret = 10;
         if ((classname[0] == '5') &&(classname[1] == 'A') && (classname[2] == 'H') && (classname[6] == 'E')) ret = 11;
         if ((classname[0] == '5') &&(classname[1] == 'B') && (classname[2] == 'H') && (classname[6] == 'E')) ret = 12;
         if ((classname[0] == '5') &&(classname[1] == 'A') && (classname[2] == 'H') && (classname[6] == 'W')) ret = 13;
         if ((classname[0] == '5') &&(classname[1] == 'B') && (classname[2] == 'H') && (classname[6] == 'W')) ret = 14;

         if ((classname[0] == '1') &&(classname[1] == 'A') && (classname[2] == 'F'))                          ret = 15;
         if ((classname[0] == '2') &&(classname[1] == 'A') && (classname[2] == 'F'))                          ret = 16;
         if ((classname[0] == '3') &&(classname[1] == 'A') && (classname[2] == 'F'))                          ret = 17;
         if ((classname[0] == '4') &&(classname[1] == 'A') && (classname[2] == 'F') && (classname[7] == 'W')) ret = 18;
         if ((classname[0] == '4') &&(classname[1] == 'A') && (classname[2] == 'F') && (classname[7] == 'W')) ret = 19;



    }
    return ret;
}

char subNames[][11] = {
/* "verh",*/
"AELT",
"AM",
"BESP",
"COIT",
"CTNT",
"D",
"DUK",
"DIC1",
"E1",
"E2",
"ELDE",
"ELWP",
"FSST",
"GGP",
"HWE1",
"KMEL",
"KSN1",
"LA1", /**/
"MTRS",
"NNWP",
"NW2",
"NWG",
"PBE",
"R",
"RK",
"REL",
"ETH",
"SOTE",
"UNF",
"WIR",   /**/
"SOPK",
"ORC5",
};


//                        1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9
//                        1  1  2  2  3  3  4  4  4  4  5  5  5  5  1  2  3  4  4
//                        A  B  A  B  A  B  A  B  A  B  A  B  A  B  A  A  A  A  A
//                        H  H  H  H  H  H  H  H  H  H  H  H  H  H  F  F  F  F  F
//                                          E  E  W  W  E  E  W  W           W  S

//char XXXsubWeight[][19] = {
/*
/ *verh  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *RK    * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
/ *REL   * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
/ *ETH   * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
/ *R     * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
/ *D     * /             {  3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *E1    * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *E2    * /             {  0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *GGP   * /             {  2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *WIR3  * /             {  0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *WIR   * /             {  0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *BESP  * /             {  2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
/ *AM    * /             {  4, 4, 4, 4, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0 },
/ *NW2   * /             {  3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *SOPK  * /             {  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *HWE1  * /             {  6, 6, 5, 5, 3, 3, 2, 2, 2, 2, 3, 3, 3, 3, 0, 0, 0, 0, 0 },
/ *MTRS  * /             {  0, 0, 2, 2, 2, 2, 2, 2, 3, 3, 2, 2, 4, 4, 0, 0, 0, 0, 0 },
/ *DIC1  * /             {  0, 0, 1, 1, 2, 2, 4, 4, 4, 4, 4, 4, 5, 5, 0, 0, 0, 0, 0 },
/ *KSN1  * /             {  0, 0, 0, 0, 2, 2, 3, 3, 2, 2, 4, 4, 6, 6, 0, 0, 0, 0, 0 },
/ *FSST  * /             {  3, 3, 3, 3, 3, 3, 4, 4, 2, 2, 5, 5, 2, 2, 0, 0, 0, 0, 0 },
/ *LA1   * /             {  0, 0, 0, 0, 3, 3, 4, 4, 4, 4, 8, 8, 8, 8, 0, 0, 0, 0, 0 },
/ *PBE3  * /             {  0, 0, 0, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *PBE4  * /             {  7, 7, 7, 7, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *PBE   * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *BTP   * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *DUK   * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 2 },/ * ?? * /
/ *NWG   * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *UNF   * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *ELWP  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *ELDE  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *AELT  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *NWWP  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *KMEL  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *SOTE  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *COIT  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *CTNT  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
/ *ORC5  * /             {  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
} ;
*/


int getSubId(char * sub)
{
    int i, j;
    char s[11];
    sprintf(s,"          ");
    sprintf(s,"%s",sub);

    i = 0;
    j = -1;
    while ( i < sizeof(subNames)/11)
    {
        if (strcmp(subNames[i], s) == 0)
        {
            // gefunden:
            j = i;
            i = sizeof(subNames) / 11;  // damit sofort beendet wird
        }
        i++;
    }
    return j; // nur für EL gültig!
}



int getClassId(char * className, int summer)
{
int ret = -1;

// der Unterschied sommer oder winter ist im Grunde nur für die 4AFELC von Bedeutung!
// Frage: wo kommen die E und W her?
// ?


    if      (strncmp(className,"1AFELC_S",  8) == 0) ret = 0;
    else if (strncmp(className,"1AFELC_J",  8) == 0) ret = 1;

    else if (strncmp(className,"2AFELC",    6) == 0) ret = (summer == TRUE) ? 3 : 2;  // Wintersemester - ### muss im Sommer verändert werden ? oder ??
    else if (strncmp(className,"2AFELC_WS", 9) == 0) ret = 2;
    else if (strncmp(className,"2AFELC_SS", 9) == 0) ret = 3;

    else if (strncmp(className,"3AFELC",    6) == 0) ret = (summer == TRUE) ? 5 : 4;
    else if (strncmp(className,"3AFELC_WS", 9) == 0) ret = 4;
    else if (strncmp(className,"3AFELC_SS", 9) == 0) ret = 5;

    else if (strncmp(className,"4AFELC",    6) == 0) ret = (summer == TRUE) ? 7 : 6;
    else if (strncmp(className,"4AFELC_WS", 9) == 0) ret = 6;
    else if (strncmp(className,"4AFELC_SS", 9) == 0) ret = 7;

    else if (strncmp(className,"1AHELS_S",  8) == 0) ret = 8;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 9;

    else if (strncmp(className,"2AHELS",    6) == 0) ret = (summer == TRUE) ? 11 : 10;
    else if (strncmp(className,"2AHELS_WS", 9) == 0) ret = 10;
    else if (strncmp(className,"2AHELS_SS", 9) == 0) ret = 11;

///####    3AHELS alleine gibt es auch!

    else if (strncmp(className,"3AHELS",    6) == 0) ret = (summer == TRUE) ? 13 : 12;
    else if (strncmp(className,"3AHELS_WS", 9) == 0) ret = 12;
    else if (strncmp(className,"3AHELS_SS", 9) == 0) ret = 13;

    else if (strncmp(className,"4AHELSE",   7) == 0) ret = (summer == TRUE) ? 15 : 14;
    else if (strncmp(className,"4AHELSEWS", 9) == 0) ret = 14;
    else if (strncmp(className,"4AHELSESS", 9) == 0) ret = 15;

    else if (strncmp(className,"4AHELSW",   7) == 0) ret = (summer == TRUE) ? 17 : 16;
    else if (strncmp(className,"4AHELSWWS", 9) == 0) ret = 16;
    else if (strncmp(className,"4AHELSWSS", 9) == 0) ret = 17;

    else if (strncmp(className,"5AHELSE",   7) == 0) ret = (summer == TRUE) ? 19 : 17;
    else if (strncmp(className,"5AHELSEWS", 9) == 0) ret = 18;
    else if (strncmp(className,"5AHELSESS", 9) == 0) ret = 19;

    else if (strncmp(className,"5AHELSW",   7) == 0) ret = (summer == TRUE) ? 21 : 20;
    else if (strncmp(className,"5AHELSWWS", 9) == 0) ret = 20;
    else if (strncmp(className,"5AHELSWSS", 9) == 0) ret = 21;

    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 8;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 9;

    else if (strncmp(className,"2BHELS",    6) == 0) ret = (summer == TRUE) ? 11 : 10;
    else if (strncmp(className,"2BHELS_WS", 9) == 0) ret = 10;
    else if (strncmp(className,"2BHELS_SS", 9) == 0) ret = 11;

    else if (strncmp(className,"3BHELS",    6) == 0) ret = (summer == TRUE) ? 13 : 12;
    else if (strncmp(className,"3BHELS_WS", 9) == 0) ret = 12;
    else if (strncmp(className,"3BHELS_SS", 9) == 0) ret = 13;

    else if (strncmp(className,"4BHELSE",   7) == 0) ret = (summer == TRUE) ? 15 : 14;
    else if (strncmp(className,"4BHELSEWS", 9) == 0) ret = 14;
    else if (strncmp(className,"4BHELSESS", 9) == 0) ret = 15;

    else if (strncmp(className,"4BHELSW",   7) == 0) ret = (summer == TRUE) ? 17 : 16;
    else if (strncmp(className,"4BHELSWWS", 9) == 0) ret = 16;
    else if (strncmp(className,"4BHELSWSS", 9) == 0) ret = 17;

    else if (strncmp(className,"5BHELSE",   7) == 0) ret = (summer == TRUE) ? 19 : 18;
    else if (strncmp(className,"5BHELSEWS", 9) == 0) ret = 18;
    else if (strncmp(className,"5BHELSESS", 9) == 0) ret = 19;

    else if (strncmp(className,"5BHELSW",   7) == 0) ret = (summer == TRUE) ? 21 : 20;
    else if (strncmp(className,"5BHELSWWS", 9) == 0) ret = 20;
    else if (strncmp(className,"5BHELSWSS", 9) == 0) ret = 21;

// hier fehlt noch die Info Embedded odere Wireless!
// und die B Klassen
// ?


    if ((dir[3] == '2') && (dir[4] == '4'))   // 2024
    {
         if (strncmp(className,"1AHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_J",  8) == 0) ret = 22;
    }

    else if ((dir[3] == '2') && (dir[4] == '5'))   // 2025
    {
         if (strncmp(className,"1AHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_S",  8) == 0) ret = 22;
    else {if (strncmp(className,"1CHELS_J",  8) == 0) ret = 22;}

         if (strncmp(className,"2AHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2AHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2CHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2CHELS_J",  8) == 0) ret = 23;

    }

    else if ((dir[3] == '2') && (dir[4] == '6'))   // 2026
    {
         if (strncmp(className,"1AHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_S",  8) == 0) ret = 22;
    else {if (strncmp(className,"1CHELS_J",  8) == 0) ret = 22;}

         if (strncmp(className,"2AHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2AHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2CHELS_S",  8) == 0) ret = 23;
    else {if (strncmp(className,"2CHELS_J",  8) == 0) ret = 23;}

         if (strncmp(className,"3AHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3AHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3CHELS_S",  8) == 0) ret = 24;
    else {if (strncmp(className,"3CHELS_J",  8) == 0) ret = 24;}


    }

    else if ((dir[3] == '2') && (dir[4] == '7'))   // 2027
    {
         if (strncmp(className,"1AHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_S",  8) == 0) ret = 22;
    else {if (strncmp(className,"1CHELS_J",  8) == 0) ret = 22;}

         if (strncmp(className,"2AHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2AHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2CHELS_S",  8) == 0) ret = 23;
    else {if (strncmp(className,"2CHELS_J",  8) == 0) ret = 23;}

         if (strncmp(className,"3AHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3AHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3CHELS_S",  8) == 0) ret = 24;
    else {if (strncmp(className,"3CHELS_J",  8) == 0) ret = 24;}

         if (strncmp(className,"4AHELS_S",  8) == 0) ret = 25;
    else if (strncmp(className,"4AHELS_J",  8) == 0) ret = 25;
    else if (strncmp(className,"4BHELS_S",  8) == 0) ret = 25;
    else if (strncmp(className,"4BHELS_J",  8) == 0) ret = 25;
    else if (strncmp(className,"4CHELS_S",  8) == 0) ret = 25;
    else {if (strncmp(className,"4CHELS_J",  8) == 0) ret = 25;}

    }

    else if ((dir[3] == '2') && (dir[4] == '8'))   // 2028
    {
         if (strncmp(className,"1AHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1AHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_S",  8) == 0) ret = 22;
    else if (strncmp(className,"1BHELS_J",  8) == 0) ret = 22;
    else if (strncmp(className,"1CHELS_S",  8) == 0) ret = 22;
    else {if (strncmp(className,"1CHELS_J",  8) == 0) ret = 22;}

         if (strncmp(className,"2AHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2AHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_S",  8) == 0) ret = 23;
    else if (strncmp(className,"2BHELS_J",  8) == 0) ret = 23;
    else if (strncmp(className,"2CHELS_S",  8) == 0) ret = 23;
    else {if (strncmp(className,"2CHELS_J",  8) == 0) ret = 23;}

         if (strncmp(className,"3AHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3AHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_S",  8) == 0) ret = 24;
    else if (strncmp(className,"3BHELS_J",  8) == 0) ret = 24;
    else if (strncmp(className,"3CHELS_S",  8) == 0) ret = 24;
    else {if (strncmp(className,"3CHELS_J",  8) == 0) ret = 24;}

         if (strncmp(className,"4AHELS_S",  8) == 0) ret = 25;
    else if (strncmp(className,"4AHELS_J",  8) == 0) ret = 25;
    else if (strncmp(className,"4BHELS_S",  8) == 0) ret = 25;
    else if (strncmp(className,"4BHELS_J",  8) == 0) ret = 25;
    else if (strncmp(className,"4CHELS_S",  8) == 0) ret = 25;
    else {if (strncmp(className,"4CHELS_J",  8) == 0) ret = 25;}

         if (strncmp(className,"5AHELS_S",  8) == 0) ret = 26;
    else if (strncmp(className,"5AHELS_J",  8) == 0) ret = 26;
    else if (strncmp(className,"5BHELS_S",  8) == 0) ret = 26;
    else if (strncmp(className,"5BHELS_J",  8) == 0) ret = 26;
    else if (strncmp(className,"5CHELS_S",  8) == 0) ret = 26;
    else {if (strncmp(className,"5CHELS_J",  8) == 0) ret = 26;}


    }



    return ret;
}


void CutNames(char * fromFile, char * directory)
{
FILE * prot,  * protCut;
char fName[LEN];
char text[LINEMAX];
char dir[LEN];
char file[LEN];
char textCutted[LEN];

char fN0a, fN0b, fN0c;
char fN1a, fN1b, fN1c;
char fN2a, fN2b, fN2c;
char vN0a, vN0b, vN0c;
char vN1a, vN1b, vN1c;

int i, j, k, l;



    readF(&prot, fromFile);

    sprintf(file,"%s",fromFile);
    sprintf(dir, "%s", directory);



    sprintf(fName,"./%c%c%c%c%c%c/Report_%c%c.csv", dir[0],    dir[1],    dir[2],    dir[3],    dir[4],    dir[5],    file[22],    file[23]);

    writeF(&protCut, fName);

    // zuerst filtern wir alle Begruendungszeilen aus:

    do
    {
        fgets(text, LINEMAX, prot);

        if (!feof(prot))
        {

            if (text[14] == '#')
            {
                fprintf(protCut, "%s",text);
            }
        }

    } while (!feof(prot));

    fprintf(protCut, "-----------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(prot);
    fclose(protCut);

    sprintf(fName,"./%c%c%c%c%c%c/Protokoll_%c%c.csv",    dir[0],    dir[1],    dir[2],    dir[3],    dir[4],    dir[5],    file[22],    file[23]);

    writeF(&protCut, fName);
    readF(&prot, fromFile);


    do
    {
        fgets(text, LINEMAX, prot);

        if (!feof(prot))
        {
            //sprintf(textCutted,"%s", text);
            strncpy(textCutted, text, strlen(text));
            i = 25;

            if (text[12] != ' ')
            {

                fN0c = fN1c = fN2c = vN0c = vN1c = 0;
                fN0a = fN0b = fN1a = fN1b = fN2a = fN2b = vN0a = vN0b = vN1a = vN1b = ' ';



                while (text[i] != ';') {i++;} j = i; i++;
                while (text[i] != ';') {i++;} k = i; i++;
                while (text[i] != ';') {i++;} l = i;

                textCutted[j] = '|';
                textCutted[k] = '|';



                i = 25;
                if (text[i] < 0) {fN0a = text[i]; i++; fN0b = text[i]; fN0c = 1; } else {fN0a = text[i];} i++;
                if (text[i] < 0) {fN1a = text[i]; i++; fN1b = text[i]; fN1c = 1; } else {fN1a = text[i];} i++;
                if (text[i] < 0) {fN2a = text[i]; i++; fN2b = text[i]; fN2c = 1; } else {fN2a = text[i];} i++;
                if (fN2a == ';') fN2a = ' ';

                i = j + 1;
                if (text[i] < 0) {vN0a = text[i]; i++; vN0b = text[i]; vN0c = 1; } else {vN0a = text[i];} i++;
                if (text[i] < 0) {vN1a = text[i]; i++; vN1b = text[i]; vN1c = 1; } else {vN1a = text[i];} i++;


                i = 25;
                if (fN0c) {textCutted[i] = fN0a; i++; textCutted[i] = fN0b;} else {textCutted[i] = fN0a;} i++;
                if (fN1c) {textCutted[i] = fN1a; i++; textCutted[i] = fN1b;} else {textCutted[i] = fN1a;} i++;
                if (fN2c) {textCutted[i] = fN2a; i++; textCutted[i] = fN2b;} else {textCutted[i] = fN2a;} i++;

                if (textCutted[i] < 0) { textCutted[i] = ';'; textCutted[i + 1] = 'X';} else { textCutted[i] = ';'; } i++;

                if (vN0c) {textCutted[i] = vN0a; i++; textCutted[i] = vN0b;} else {textCutted[i] = vN0a;} i++;
                if (vN1c) {textCutted[i] = vN1a; i++; textCutted[i] = vN1b;} else {textCutted[i] = vN1a;} i++;

                if (textCutted[i] < 0) { textCutted[i] = ';'; textCutted[i + 1] = 'X';} else { textCutted[i] = ';'; } i++;  // added

                j = i;  while (text[l] != 0) {textCutted[j] = text[l]; j++; l++;}

                textCutted[j] = 0; // nullterminater
            }
            else
            {
                // if (text[30] == 'o') {text[30] = '*';text[31] = '*'; j = 28; } else {j = 30;} // in der jeweils letyten Yeile steht Beguendung! Umlaut!
                l = 62;
                j = 28;
                while (text[l] != 0) {
                                         textCutted[j] = text[l];
                                         if ((j > 29) && (text[l] == ';') && (text[l - 1] == ';'))
                                         {
                                             textCutted[j] = ' '; // damit Spalten entstehen!
                                             j++;
                                             textCutted[j] = ';';
                                         }
                                         j++;
                                         l++;
                                     }
                //textCutted[27] = ';'; // eine Spalte mehr!
                //textCutted[28] = ';'; // eine Spalte mehr!
                //textCutted[29] = '*'; // eine Spalte mehr!
                textCutted[j] = 0; // nullterminater

//4BHELSWSS ; 0;         ; Sch;Ja;;verh;S;AM;1;BESP;1;D;2;DIC1;1;E1;2;E2;T;   ; ;FSST;1;GGP;1;HWE1;1;KSN1;1;LA1;1;MTRS;1;NW2;1;PBE;1;REL;1;  ; ;WIR;1;
//4BHELSWSS ;  ;         ; *nzahl der 5 bzs. N je Gegenstand:   ;;;   ; 0; ; 0;   ; 0;; 0;   ; 0; ; 0; ; 0;  ; 0;   ; 0;  ; 0;   ; 0;   ; 0;  ; 0;   ; 0;  ; 0;  ; 0;  ; 0; ; 0;  ; 0;
//4BHELSWSS ;  ;         ; *nzah;;;   ; 0; ; 0;   ; 0;; 0;   ; 0; ; 0; ; 0;  ; 0;   ; 0;  ; 0;   ; 0;   ; 0;  ; 0;   ; 0;  ; 0;  ; 0;  ; 0; ; 0;  ; 0;


            }

            fprintf(protCut, "%s",textCutted);

        }


    } while (!feof(prot));

    fclose(prot);
    fclose(protCut);
}

