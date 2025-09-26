#ifndef CONFIG_H
#define CONFIG_H


typedef struct {
    int GRID_WIDTH;
    int GRID_HEIGHT;
    int SHIP_CARRIER;
    int SHIP_BATTLESHIP;
    int SHIP_DESTROYER;
    int SHIP_SUBMARINE;
} Config;

char isFileAccessible(char * name);

char addGlobalError(char * error);

char createEmptyFile(char * name);

char writeInLog(char * log);

Config * getDefaultConfig();

Config * confRestriction(Config * config);

char renderConfigConsole(Config * config);

char canBeInteger(char * str);

Config * initConfig();

#endif //CONFIG_H