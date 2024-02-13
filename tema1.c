/* SAMSON Alexandru-Valentin - 312CC */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listNode // nod din lista dublu inlantuita
{
    char elem;             // caracterul continut
    struct listNode *next; // adresa nodului urmator
    struct listNode *prev; // adresa nodului precedent
} listNode, *pListNode;

typedef struct band // banda
{
    pListNode sentinel, finger; // adresa santinelei si a degetului
} band, *pBand;

typedef struct queueCell // celula din coada
{
    char op[20];            // operatia continuta
    struct queueCell *next; // adresa celulei urmatoare
} queueCell, *pQueueCell;

typedef struct queue // coada
{
    pQueueCell front, rear; // adresa fetei si a spatelui
} tQueue;

typedef struct stackCell // celula din stiva
{
    pListNode pos;          // adresa pozitiei continute
    struct stackCell *next; // adresa celulei urmatoare
} stack, *pStack;

tQueue initQueue() // initializare coada
{
    tQueue q;
    q.front = q.rear = NULL;
    return q;
}

int isEmptyQueue(tQueue q) // verificare coada goala
{
    if (q.front == NULL)
    {
        return 1;
    }

    return 0;
}

tQueue addQueue(tQueue q, char op[20]) // adaugare celula in coada
{
    pQueueCell p = (pQueueCell)malloc(sizeof(queueCell));

    strcpy(p->op, op);
    p->next = NULL;

    if (q.front == NULL)
        q.front = q.rear = p;
    else
    {
        q.rear->next = p;
        q.rear = p;
    }

    return q;
}

tQueue delQueue(tQueue q, char op[20]) // scoatere celula din coada
{
    pQueueCell p;

    strcpy(op, q.front->op);

    if (q.front == q.rear)
    {
        free(q.front);
        q.front = q.rear = NULL;
    }
    else
    {
        p = q.front;
        q.front = q.front->next;
        free(p);
    }

    return q;
}

void freeQueue(tQueue q) // eliberare memorie coada
{
    pQueueCell p, aux;

    p = q.front;

    while (p != NULL)
    {
        aux = p;
        p = p->next;
        free(aux);
    }
}

pStack initStack() // initializare stiva
{
    pStack s = NULL;

    return s;
}

int isEmptyStack(pStack s) // verificare stiva goala
{
    if (s == NULL)
    {
        return 1;
    }

    return 0;
}

pStack pushStack(pStack s, pListNode p) // adaugare element in stiva
{
    pStack t = (pStack)malloc(sizeof(stack));

    t->pos = p;
    t->next = s;

    return t;
}

pListNode popStack(pStack *s) // scoatere element din stiva
{
    pStack t;
    pListNode p = (*s)->pos;

    t = *s;
    *s = (*s)->next;
    free(t);

    return p;
}

void freeStack(pStack s) // eliberare memorie stiva
{
    pStack aux;

    while (s != NULL)
    {
        aux = s;
        s = s->next;
        free(aux);
    }
}

pListNode initListNode(pListNode s) // initializare primul nod din lista
{
    // nodul propriu-zis
    pListNode first = (pListNode)malloc(sizeof(listNode));
    first->elem = '#';
    first->next = NULL;

    // santinela
    s = (pListNode)malloc(sizeof(listNode));
    s->next = first;
    s->prev = NULL;
    s->elem = ' ';

    first->prev = s;

    return s;
}

void addList(pListNode new, pListNode pos) // adaugare nod in lista
{
    new->next = pos->next;
    new->prev = pos;
    pos->next = new;
}

void freeList(pListNode s) // eliberare memorie lista
{
    pListNode aux;

    while (s != NULL)
    {
        aux = s;
        s = s->next;
        free(aux);
    }
}

pBand initBand(pBand b) // initializare banda
{
    b = (pBand)malloc(sizeof(band));

    b->sentinel = NULL;
    b->sentinel = initListNode(b->sentinel);
    b->finger = b->sentinel->next;

    return b;
}

void freeBand(pBand b) // eliberare memorie banda
{
    freeList(b->sentinel);
    free(b);
}

pBand MOVE_LEFT(pBand b) // operatia MOVE_LEFT
{
    // degetul se muta cu o pozitie la stanga
    b->finger = b->finger->prev;

    return b;
}

pBand MOVE_RIGHT(pBand b) // operatia MOVE_RIGHT
{
    // daca degetul este in capatul din dreapta
    if (b->finger->next == NULL)
    {
        // se formeaza un nod nou
        pListNode new = (pListNode)malloc(sizeof(listNode));
        new->elem = '#';

        pListNode p = b->sentinel;

        while (p->next != NULL)
        {
            p = p->next;
        }
        // se adauga nodul nou in dreapta degetului
        addList(new, p);
        // degetul se muta pe nodul nou
        b->finger = new;
    }
    // daca nu este in capatul din dreapta
    else
    {
        // degetul se muta cu o pozitie la dreapta
        b->finger = b->finger->next;
    }

    return b;
}

pBand MOVE_LEFT_CHAR(pBand b, char c, FILE *f) // operatia MOVE_LEFT_CHAR <C>
{
    pListNode p = b->finger;

    // cat timp caracterul cautat nu a fost gasit
    while (p->elem != c)
    {
        // daca se ajunge in capatul din stanga se afiseaza eroare
        if (p->prev == NULL)
        {
            fprintf(f, "ERROR\n");
            return b;
        }
        p = p->prev;
    }

    // degetul se muta la pozitia caracterului cautat daca acesta este gasit
    b->finger = p;

    return b;
}

pBand MOVE_RIGHT_CHAR(pBand b, char c) // operatia MOVE_RIGHT_CHAR <C>
{
    pListNode p = b->finger;

    // cat timp caracterul cautat nu a fost gasit
    while (p->elem != c)
    {
        // daca se ajunge in capatul din dreapta se opreste cautarea
        if (p->next == NULL)
        {
            // se formeaza un nod nou
            pListNode new = (pListNode)malloc(sizeof(listNode));
            new->elem = '#';

            // se adauga nodul nou in capatul din dreapta
            addList(new, p);
            // degetul se muta pe nodul nou
            b->finger = new;

            return b;
        }
        p = p->next;
    }

    // degetul se muta la pozitia caracterului cautat daca acesta este gasit
    b->finger = p;

    return b;
}

pBand WRITE(pBand b, char c) // operatia WRITE <C>
{
    pListNode p = b->finger;

    // introduce caracterul dat pe pozitia degetului
    p->elem = c;

    return b;
}

pBand INSERT_LEFT(pBand b, char c, FILE *f) // operatia INSERT_LEFT <C>
{
    // daca degetul este in capatul din stanga se afiseaza eroare
    if (b->finger->prev == b->sentinel)
    {
        fprintf(f, "ERROR\n");
        return b;
    }

    // se formeaza un nod nou ce contine caracterul dat
    pListNode new = (pListNode)malloc(sizeof(listNode));
    new->elem = c;

    // se introduce nodul nou in stanga degetului
    addList(new, b->finger->prev);
    // degetul se muta pe nodul nou
    b->finger = new;

    return b;
}

pBand INSERT_RIGHT(pBand b, char c) // operatia INSERT_RIGHT <C>
{
    // se formeaza un nod nou ce contine caracterul dat
    pListNode new = (pListNode)malloc(sizeof(listNode));
    new->elem = c;

    // se introduce nodul nou in dreapta degetului
    addList(new, b->finger);
    // degetul se muta pe nodul nou
    b->finger = new;

    return b;
}

pBand SHOW_CURRENT(pBand b, FILE *f) // operatia SHOW_CURRENT
{
    // se afiseaza caracterul indicat de deget
    fprintf(f, "%c\n", b->finger->elem);

    return b;
}

pBand SHOW(pBand b, FILE *f) // operatia SHOW
{
    pListNode p = b->sentinel->next;

    // cat timp mai sunt noduri de parcurs
    while (p != NULL)
    {
        // caracterul indicat de deget este afisat evidentiat de bare
        if (p == b->finger)
        {
            fprintf(f, "|%c|", p->elem);
        }
        // celelalte caractere sunt afisate normal
        else
        {
            fprintf(f, "%c", p->elem);
        }
        p = p->next;
    }
    fprintf(f, "\n");

    return b;
}

int main()
{
    FILE *fr, *fw;
    int nrOp, i;
    char op[20], c;
    tQueue queue;
    pStack undoStack, redoStack;
    pBand b = NULL;
    pListNode pos;

    // initializari
    queue = initQueue(queue);
    undoStack = initStack(undoStack);
    redoStack = initStack(redoStack);
    b = initBand(b);

    // deschidere fisiere
    fr = fopen("tema1.in", "r");
    fw = fopen("tema1.out", "w");

    // citire numar de operatii din fisier
    fscanf(fr, "%d", &nrOp);
    fgetc(fr);

    // pentru fiecare operatie
    for (i = 0; i < nrOp; i++)
    {
        // operatia este citita din fisier
        fgets(op, 20, fr);
        op[strlen(op) - 1] = '\0';

        // daca este operatie de tip UPDATE, este adaugata in coada
        if (strstr(op, "MOVE_LEFT") || strstr(op, "MOVE_RIGHT") ||
        strstr(op, "WRITE") || strstr(op, "INSERT"))
        {
            queue = addQueue(queue, op);
        }
        // daca este operatie de tip QUERY,
        // sunt apelate pe loc functiile corespunzatoare
        else if (!strcmp(op, "SHOW_CURRENT"))
        {
            b = SHOW_CURRENT(b, fw);
        }
        else if (!strcmp(op, "SHOW"))
        {
            b = SHOW(b, fw);
        }
        // daca este operatie de tip UNDO
        else if (!strcmp(op, "UNDO"))
        {
            // este extras pointerul retinut in varful stivei UNDO
            pos = popStack(&undoStack);
            // pointerul la pozitia curenta a degetului
            // este adaugat in varful stivei REDO
            redoStack = pushStack(redoStack, b->finger);
            // degetul se muta pe pozitia indicata de pointerul extras
            b->finger = pos;
        }
        // daca este operatie de tip REDO
        else if (!strcmp(op, "REDO"))
        {
            // este extras pointerul retinut in varful stivei REDO
            pos = popStack(&redoStack);
            // pointerul la pozitia curenta a degetului
            // este adaugat in varful stivei UNDO
            undoStack = pushStack(undoStack, b->finger);
            // degetul se muta pe pozitia indicata de pointerul extras
            b->finger = pos;
        }
        // daca este operatia EXECUTE
        else if (!strcmp(op, "EXECUTE"))
        {
            // se extrage operatia din varful cozii
            queue = delQueue(queue, op);

            // pentru operatia MOVE_LEFT
            if (!strcmp(op, "MOVE_LEFT"))
            {
                // daca degetul nu este la capatul din stanga
                if (b->finger->prev != b->sentinel)
                {
                    // se introduce in varful stivei
                    // pointerul ce indica pozitia curenta a degetului
                    pos = b->finger;
                    undoStack = pushStack(undoStack, pos);
                    // se apeleaza functia corespunzatoare
                    b = MOVE_LEFT(b);
                }
            }
            // pentru operatia MOVE_RIGHT
            else if (!strcmp(op, "MOVE_RIGHT"))
            {
                // se introduce in varful stivei
                // pointerul ce indica pozitia curenta a degetului
                pos = b->finger;
                undoStack = pushStack(undoStack, pos);
                // se apeleaza functia corespunzatoare
                b = MOVE_RIGHT(b);
            }
            // pentru operatia MOVE_LEFT_CHAR <C>
            else if (strstr(op, "MOVE_LEFT_CHAR"))
            {
                // se extrage caracterul de cautat
                c = op[strlen(op) - 1];
                // se apeleaza functia corespunzatoare
                b = MOVE_LEFT_CHAR(b, c, fw);
            }
            // pentru operatia MOVE_RIGHT_CHAR <C>
            else if (strstr(op, "MOVE_RIGHT_CHAR"))
            {
                // se extrage caracterul de cautat
                c = op[strlen(op) - 1];
                // se apeleaza functia corespunzatoare
                b = MOVE_RIGHT_CHAR(b, c);
            }
            // pentru operatia WRITE <C>
            else if (strstr(op, "WRITE"))
            {
                // se extrage caracterul de cautat
                c = op[strlen(op) - 1];
                // se apeleaza functia corespunzatoare
                b = WRITE(b, c);

                // se golesc stivele de UNDO si REDO
                while (!isEmptyStack(undoStack))
                {
                    popStack(&undoStack);
                }
                while (!isEmptyStack(redoStack))
                {
                    popStack(&redoStack);
                }
            }
            // pentru operatia INSERT_LEFT <C>
            else if (strstr(op, "INSERT_LEFT"))
            {
                // se extrage caracterul de cautat
                c = op[strlen(op) - 1];
                // se apeleaza functia corespunzatoare
                b = INSERT_LEFT(b, c, fw);
            }
            // pentru operatia INSERT_RIGHT <C>
            else if (strstr(op, "INSERT_RIGHT"))
            {
                // se extrage caracterul de cautat
                c = op[strlen(op) - 1];
                // se apeleaza functia corespunzatoare
                b = INSERT_RIGHT(b, c);
            }
        }
    }

    // inchidere fisiere
    fclose(fr);
    fclose(fw);

    // eliberari de memorie
    freeQueue(queue);
    freeStack(undoStack);
    freeStack(redoStack);
    freeBand(b);

    return 0;
}