#ifndef CWK2_EVOLUTION_H
#define CWK2_EVOLUTION_H
void change(int times, char *userFileName);
typedef struct {
    int column;
    int row;
}world_size;
world_size getSize();
#endif //CWK2_EVOLUTION_H
