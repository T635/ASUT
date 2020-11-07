#include <malloc.h>
#include <stdio.h>
#include <string.h>

typedef struct aux {
  char host[65];
  struct aux *next;
} ELEMENT;

typedef ELEMENT *PONT;

typedef struct {
  PONT first;
} QUEUE;

void inicializeQueue(QUEUE *l);
void insertItem(QUEUE *l, char host[], PONT *finalItem);
void openFile(char *fileName, FILE *fp, QUEUE *l);
char *detectingFileName(int argc, char *argv[]);
void clearString(char host[65]);
void printList(QUEUE *l);
PONT lastItem(QUEUE *l, PONT *ant);

void inicializeQueue(QUEUE *l) { l->first = NULL; }

void insertItem(QUEUE *l, char host[], PONT *finalItem) {
  PONT ant, data;
  data = lastItem(l, &ant);
  data = (PONT)malloc(sizeof(ELEMENT));
  strcpy(data->host, host);
  if (ant == NULL) {
    data->next = l->first;
    l->first = data;
  } else {
    data->next = ant->next;
    ant->next = data;
  }
}

PONT lastItem(QUEUE *l, PONT *ant) {
  *ant = NULL;
  PONT atual = l->first;
  while (atual != NULL) {
    *ant = atual;
    atual = atual->next;
  }
  return atual;
}

void printList(QUEUE *l) {
  PONT end = l->first;
  printf("\033[0;31m[!] \033[0m Reading list of hosts\n");
  while (end != NULL) {
    printf("%s\n", end->host);
    end = end->next;
  }
}

char *detectingFileName(int argc, char *argv[]) {
  char *parameter = "-f";
  for (int i = 0; i < argc; i++) {
    if (strcmp(parameter, argv[i]) == 0) {
      i++;
      if (argv[i] == NULL) {
        printf("\033[0;31m[!] \033[0m Error, parameter f not found\n");
        return NULL;
      } else {
        char *fileName = argv[i];
        return fileName;
      }
    }
  }
}

void openFile(char *fileName, FILE *fp, QUEUE *l) {
  char host[65], c;
  int i = 0;
  fp = fopen(fileName, "r");
  while (c != EOF) {
    c = fgetc(fp);
    if (c == '\n') {
      insertItem(l, host, &(l->first));
      i = 0;
      c = fgetc(fp);
      clearString(host);
    }
    host[i] = c;
    i++;
  }
}

void clearString(char host[65]) {
  for (int i = 0; i < 65; i++) {
    host[i] = '\0';
  }
}

void main(int argc, char *argv[]) {
  char *fileName = detectingFileName(argc, argv);
  FILE *fp;
  QUEUE l;
  inicializeQueue(&l);
  openFile(fileName, fp, &l);
}
