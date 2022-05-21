#ifndef EVOLUTION_C_GENERATE_H
#define EVOLUTION_C_GENERATE_H
typedef struct {
    int column;
    int row;
}world_size;
int generateTxt(int row, int column, char *userFileName);
int generateAllDeadTxt(int row, int column, char *userFileName);
world_size getSize(char *userFileName1);
void newRandomGame(char *userFileName);
void newAllDeadGame(char *userFileName);
void OldGame(char *userFileName);
int over(char *userFileName, int row, int column);
#endif //EVOLUTION_C_GENERATE_H
