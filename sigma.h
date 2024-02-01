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
/*AELT*/           {4,4,4,4,3,3,2,3,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},  // 0
/*AM  */           {2,2,2,2,2,2,0,0,  4,4,4,4,3,3,2,2,2,2,2,2,2,2,  4,4,3,2,2},  // 1
/*BESP*/           {2,2,2,2,2,2,1,1,  2,2,2,2,2,2,1,1,1,1,1,1,1,1,  2,2,2,1,1},  // 2
/*COIT*/           {0,0,0,0,2,2,2,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},  // 3
/*CTNT*/           {1,1,2,2,3,3,1,2,  0,0,0,0,0,0,0,0,0,0,0,0,0,0,  0,0,0,0,0},  // 4
/*D   */           {0,0,0,0,0,0,0,0,  3,3,2,2,2,2,2,2,2,2,2,2,2,2,  3,2,2,2,2},  // 5
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
        "Englisch                                                                       ",
        "Deutsch                                                                        ",
        "Deutsch und Kommunikation                                                      ",
        "Softwaretechnik                                                                ",
        "Netzwerktechnik - Werkstätte und Produktionstechnik                            ",
        "Angewandte Mathematik                                                          ",
        "Computer- und Netzwerktechnik                                                  ",
        "Angewandte Elektronik                                                          ",
        "Geografie                                                                      ",
        "Elektronik - Werkstätte und Produktionstechnik                                 ",
        "Naturwissenschaften                                                            ",
        "NWG-FACHSCHULE                                                                 ",
        "Elektronik Design                                                              ",
        "Fachspezifische Softwaretechnik                                                ",
        "Hardwareentwicklung                                                            ",
        "Antriebstechnik und Mechatronik                                                ",
        "Computerunterstützte Projektentwicklung                                        ",
        "Angewandte Informatik                                                          ",
        "Datenbanken und Informationssysteme                                            ",
        "Programmieren und Software Engineering                                         ",
        "Energiesysteme - Werkstätte und Produktionstechnik                             ",
        "Energiesysteme                                                                 ",
        "Bewegung und Sport                                                             ",
        "Betriebswirtschaft und Management                                              ",
        "Antriebstechnik und Mechatronik                                                ",
        "Antriebstechnik und Mechatronik - Werkstätte und Produktionstechnik            ",
        "Automatisierungstechnik                                                        ",
        "Computergestützte Projektentwicklung                                           ",
        "Fertigungstechnik 1                                                            ",
        "Konstruktion und Projektmanagement                                             ",
        "Elektrotechnik und Automatisierungstechnik                                     ",
        "Fertigungstechnik 1 - Werkstätte und Produktionstechnik                        ",
        "Betriebstechnik                                                                ",
        "Produktionstechnologie und Werkstoffe                                          ",
        "Informatik und Informationssysteme                                             ",
        "Technische Mechanik und Berechnung                                             ",
        "Werkstätte und Produktionstechnik                                              ",
        "Elektrotechnik und Elektronik                                                  ",
        "Maschinen und Anlagen                                                          ",
        "Wirtschaft und Recht                                                           ",
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
        "Maschinenelemente                                                              ",
        "Data Science und Artificial Intelligence                                       ",
        "Konstruktion und Design                                                        "

    };




char SubN[][20] =
{
    "E                 ",
    "D                 ",
    "DUK               ",
    "SOTE              ",
    "NWWP              ",
    "AM                ",
    "CTNT              ",
    "AELT              ",
    "GGP               ",
    "ELWP              ",
    "NW2               ",
    "NWG               ",
    "ELDE              ",
    "FSST              ",
    "HWE1              ",
    "ANTMT             ",
    "CPE               ",
    "AINF              ",
    "DBI               ",
    "POS1              ",
    "ES                ",    // ?? ES_3, ES_4
    "ES1               ",
    "BESP              ",
    "BWM               ",
    "ANTMT             ",
    "ANTMTWP           ",
    "AUT               ",
    "CPE               ",
    "FET1              ",
    "KOP1              ",
    "ETAT              ",
    "FET1WP            ",     // ?? FET1WP_3, FET1WP_4
    "BET               ",
    "PROTWE            ",
    "INFI              ",
    "TMB               ",
    "WPT               ",
    "ETE               ",
    "MANL              ",
    "WIR               ",       // ??
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
    "MEL               ",
    "DSAI_1            ",
    "KODES             "

};

/* ACHTUNG: Reihenfolge muss identisch sein! */


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




