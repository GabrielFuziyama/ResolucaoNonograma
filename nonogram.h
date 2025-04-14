#ifndef nonogram_h
#define nonogram_h
typedef struct nonograma Nonograma;

Nonograma NonogramAllocate(int n);
void Nonogramfree(Nonograma *tab);
void NonogramRead(Nonograma *tab);
int NonogramPlay(Nonograma *tab);
void NonogramPrint(Nonograma *tab);

#endif