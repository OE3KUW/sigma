//*****************************************************************************
//                              Σ i g m a 2 4
//                         H e a d e r   -   F i l e
//*****************************************************************************

#define LINEMAX            1000
#define LEN                 200
#define SMAX                800
#define TRUE                  1
#define FALSE                 0


/**************************  G l o b a l e  Variablen ***********************/

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

int ZweiKlassen4System;
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




