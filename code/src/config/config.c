#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int GRID_WIDTH;
    int GRID_HEIGHT;
    int SHIP_CARRIER;
    int SHIP_BATTLESHIP;
    int SHIP_DESTROYER;
    int SHIP_SUBMARINE;
} Config;

char isFileAccessible(char * name){
    FILE * f = NULL;
    if ((f = fopen(name,"r"))!=NULL){
        fclose(f);
        return 1;
    } else {
        return 0;
    }
}

char addGlobalError(char * error){
    //Fonction utilisée seulement quand pb pour ecrire dans le fichier de log (c'est pour ca l'appel system et pas du fopen)
    char * name = "../globalErr.txt";
    if (!isFileAccessible(name)){
        system("touch ../globalErr.txt");
    }
    char * msg = malloc((strlen("echo \"")+strlen(error)+strlen("\">>../globalErr.txt")+1)*sizeof(char));
    system(strcat(strcat(strcpy(msg,"echo \""),error),"\">>../globalErr.txt"));
    free(msg);
    printf("%s\n", error);
    return 1;
}

char createEmptyFile(char * name){
    FILE * f = NULL;
    if ((f = fopen(name,"r"))!=NULL){
        fclose(f);
        return 1;
    } else {
        remove(name);
        if((f = fopen(name,"w"))==NULL) {
            addGlobalError("Unknow error creating file");
            return 0;
        } else {
            fclose(f);
            return 1;
        }
    }
}

char writeInLog(char * log){
    char * gameLog = "./src/game/log.txt";
    FILE * logFile = NULL;
    char endWithReturnLine = 1;
    if (strlen(log)<=0) endWithReturnLine = 0;
    else if (log[strlen(log)-1]!='\n') endWithReturnLine = 0;
    if(!isFileAccessible(gameLog)){
        createEmptyFile(gameLog);
    }
    if((logFile = fopen(gameLog,"a"))==NULL){
        addGlobalError(gameLog);
        if (!endWithReturnLine) addGlobalError("\n");
        addGlobalError("Error occured when opening log file\n");
        printf("Error occured when opening log file\n");
        return 0;
    } else {
        fprintf(logFile,"%s%s",log,endWithReturnLine?"":"\n");
        printf("%s%s",log,endWithReturnLine?"":"\n");
        fclose(logFile);
        return 1;
    }
}

Config * getDefaultConfig(){
    Config * config = NULL;
    if ((config = malloc(sizeof(Config)))==NULL){
        writeInLog("Memory allocation - error when allocating memory for config pointer\n");
        return NULL;
    }
    config->GRID_WIDTH = 10;
    config->GRID_HEIGHT = 10;
    //nombre de bateau dans la config
    config->SHIP_CARRIER = 1;
    config->SHIP_BATTLESHIP = 1;
    config->SHIP_DESTROYER = 2;
    config->SHIP_SUBMARINE = 1;
    return config;
}

Config * confRestriction(Config * config){

    printf("%d %d", config->GRID_HEIGHT, config->GRID_WIDTH);

    int pb = 0;
    if (config->GRID_WIDTH<7) {
        writeInLog("Config - Grid width is under 7, it is not acceptable !\n");
        pb++;
    } else if (config->GRID_WIDTH>26){
        writeInLog("Config - Grid width is over 26, it is not acceptable !\n");
        pb++;
    }
    if (config->GRID_HEIGHT<7) {
        writeInLog("Config - Grid heigth is under 7, it is not acceptable !\n");
        pb++;
    } else if (config->GRID_HEIGHT>=26){
        writeInLog("Config - Grid heigth is over 26, it is not acceptable !\n");
        pb++;
    }
    int totalShip = 0;
    int totalTile = config->GRID_HEIGHT*config->GRID_WIDTH;
    totalShip+=config->SHIP_CARRIER;
    totalShip+=config->SHIP_BATTLESHIP;
    totalShip+=config->SHIP_DESTROYER;
    totalShip+=config->SHIP_SUBMARINE;
    if (totalShip<2) {
        writeInLog("Config - The total number of ships is under 2, it is not acceptable !\n");
        pb++;
    }
    //les chiffres sont les tailles des bateaux
    totalTile-=config->SHIP_CARRIER*5;
    totalTile-=config->SHIP_BATTLESHIP*4;
    totalTile-=config->SHIP_DESTROYER*3;
    totalTile-=config->SHIP_SUBMARINE*2;
    if (totalTile<0){
        writeInLog("Config - The ships are too many for the grid, it is not acceptable !\n");
        pb++;
    }
    if (pb>0) return getDefaultConfig();
    return config;
}

char renderConfigConsole(Config * config){
    printf("Configuration :\n");
    printf("GRID_WIDTH = %d\n",config->GRID_WIDTH);
    printf("GRID_HEIGHT = %d\n",config->GRID_HEIGHT);
    printf("GRID_CARRIER = %d\n",config->SHIP_CARRIER);
    printf("GRID_BATTLESHIP = %d\n",config->SHIP_BATTLESHIP);
    printf("GRID_DESTROYER = %d\n",config->SHIP_DESTROYER);
    printf("GRID_SUBMARINE = %d\n",config->SHIP_SUBMARINE);
    return 1;
}

char canBeInteger(char * str){
    while(*(str)!='\0') if (*str<'0' || *(str++)>'9') return 0;
    return 1;
}

Config * initConfig(){
    char * name = "./config.txt";
    Config * config = NULL;
    FILE * f = NULL;
    if ((config = malloc(sizeof(Config)))==NULL){
        writeInLog("Memory allocation - error when allocating memory for config pointer\n");
        return NULL;
    } else {
        if ((f = fopen(name,"r"))==NULL){
            writeInLog("Config - error when opening config file\n");
            return getDefaultConfig();
        } else {
            char throw[100];
            int value;
            for (int i = 0; i < 6; i++){        //6 pcq c'est le nombre de parametre possible pour la config
                if (fscanf(f," %s = %d", throw, &value)!=2) continue;
                else if (strcmp(throw,"GRID_WIDTH")==0) config->GRID_WIDTH = value;
                else if (strcmp(throw,"GRID_HEIGHT")==0) config->GRID_HEIGHT = value;
                else if (strcmp(throw,"SHIP_CARRIER")==0) config->SHIP_CARRIER = value;
                else if (strcmp(throw,"SHIP_BATTLESHIP")==0) config->SHIP_BATTLESHIP = value;
                else if (strcmp(throw,"SHIP_DESTROYER")==0) config->SHIP_DESTROYER = value;
                else if (strcmp(throw,"SHIP_SUBMARINE")==0) config->SHIP_SUBMARINE = value;
            }
            config = confRestriction(config);
            return config;
        }

    }
}