#ifndef EVOLUTION_C_USER_H
#define EVOLUTION_C_USER_H
typedef struct _User
{
    char username[50];
    char password[50];
    struct _User *next1;
}user, *linklist;


void login(linklist head);
void regi(linklist head);
int output(linklist head, char userFile[40]);
#endif //EVOLUTION_C_USER_H
