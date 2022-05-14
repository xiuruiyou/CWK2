#ifndef EVOLUTION_C_GENERATE_H
#define EVOLUTION_C_GENERATE_H
//0,0,0,0,0,
//0,0,1,0,0,
//1,0,1,0,0,
//0,1,1,0,0,
//0,0,0,0,0,
//0,0,0,0,0,
typedef struct {
    int column;
    int row;
}world_size;
int generateTxt(int row, int column, char *userFileName);
world_size getSize(char *userFileName1);
void newGame(char *userFileName);
void OldGame(char *userFileName);
#endif //EVOLUTION_C_GENERATE_H
