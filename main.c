#include <stdio.h>
#include <stdlib.h>

typedef struct Student Student;
struct Student
{
    int age;
    Student *next;
};

Student *createStudent(int age)
{
    Student *student = malloc(sizeof(*student));

    if (student == NULL)
    {
        exit(EXIT_FAILURE);
    }

    student->age = age;
    student->next = NULL;

    return student;
}

typedef struct L3 L3;
struct L3
{
    Student *first;
};

L3 *init(Student *student)
{
    L3 *L3 = malloc(sizeof(*L3));

    if (L3 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    L3->first = student;

    return L3;
}

void insertAt(L3 *L3,Student *student,int position)
{
    if (L3 == NULL || student == NULL || position < 1)
    {
        exit(EXIT_FAILURE);
    }

    int currentPosition = 1;
    Student *studentBeforePosition = L3->first;

    while(currentPosition <= position){
        if(studentBeforePosition->next != NULL){
            studentBeforePosition = studentBeforePosition->next;
            currentPosition++;
        }
        else{
            break;
        }
    }

    student->next = studentBeforePosition->next;
    studentBeforePosition->next = student;
}

void insertAtTop(L3 *L3,Student *student)
{
    insertAt(L3,student,1);
}

void deleteAt(L3 *L3,int position)
{
    if (L3 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    if (L3->first != NULL)
    {
        int currentPosition = 1;
        Student *studentAtPosition = L3->first;

        while(currentPosition <= position){
            if(studentAtPosition->next){
                studentAtPosition = studentAtPosition->next;
                currentPosition++;
            }
            else{
                break;
            }
        }

        studentAtPosition = studentAtPosition->next;
    }
}

void deleteAtTop(L3 *L3)
{
    deleteAt(L3,1);
}

void deleteAll(L3 *L3)
{
    L3 = NULL;
}

void display(L3 *L3)
{
    if (L3 == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Student *actual = L3->first;

    while (actual != NULL)
    {
        printf("(Etudiant{Age: %d}) -> ", actual->age);
        actual = actual->next;
    }
    printf("NULL \n");
}

int count(L3 *L3)
{
    if (L3 == NULL){
        return 0;
    }
    else{

        int elCount = 1;
        Student *studentAtPosition = L3->first;

        while(studentAtPosition->next){
            studentAtPosition = studentAtPosition->next;
            elCount++;
        }

        return elCount;
    }
}

void sort(L3 *L3,int ASC)
{
    Student *start = L3->first;

    void swap(Student *a, Student *b)
    {
        int temp = a->age;
        a->age = b->age;
        b->age = temp;
    }

    int swapped, i;
    Student *ptr1;
    Student *lptr = NULL;

    if(ASC){
        do
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != lptr)
            {
                if (ptr1->age > ptr1->next->age)
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
        while (swapped);
    }
    else{
        do
        {
            swapped = 0;
            ptr1 = start;

            while (ptr1->next != lptr)
            {
                if (ptr1->age < ptr1->next->age)
                {
                    swap(ptr1, ptr1->next);
                    swapped = 1;
                }
                ptr1 = ptr1->next;
            }
            lptr = ptr1;
        }
        while (swapped);
    }

    L3->first = start;
}


int main()
{
    int n = 1;
    L3 *l3 = NULL;

    printf("Entre le nombre d'etudiants : \n");
    scanf("%d", &n);


    for(int i = 1; i<=n; i++)
    {
        int age = 0;

        printf("Entre l'age de l'etudiant %d: \n",i);
        scanf("%d", &age);

        Student *student = createStudent(age);

        if (l3 == NULL){
            l3 = init(student);
        }
        else{
            insertAtTop(l3,student);
        }
    }
    printf("Liste etudiants: \n");
    display(l3);
    ///////////////////////////////////////////////
    printf("Etudiants moins de 20 ans: ");

    int underTwenty = 0;

    Student *actual = l3->first;

    while (actual != NULL)
    {
        if(actual->age < 20){
            underTwenty++;
        }
        actual = actual->next;
    }

    printf("%d \n",underTwenty);
    ////////////////////////////////////////////////
    printf("Etudiants ordre ASC: \n");

    L3 *l3ASC = l3;

    sort(l3ASC,1);

    display(l3ASC);

    ///////////////////////////////////////////////
    L3 *l3EvenAge   = NULL;
    L3 *l3OddAge    = NULL;

    Student *actualFilter = l3ASC->first;

    while (actualFilter != NULL)
    {
        if(actualFilter->age % 2 == 0){
            if (l3EvenAge == NULL){
                l3EvenAge = init(createStudent(actualFilter->age));
            }
            else{
                insertAtTop(l3EvenAge,createStudent(actualFilter->age));
            }
        }
        else{
            if (l3OddAge == NULL){
                l3OddAge = init(createStudent(actualFilter->age));
            }
            else{
                insertAtTop(l3OddAge,createStudent(actualFilter->age));
            }
        }
        actualFilter = actualFilter->next;
    }

    printf("Etudiants age paire: \n");
    if(l3EvenAge == NULL){
        printf("%d \n",0);
    }
    else{
        sort(l3EvenAge,0);
        display(l3EvenAge);
    }

    printf("Etudiants age impaire: \n");
    if(l3OddAge == NULL){
        printf("%d \n",0);
    }
    else{
        sort(l3OddAge,0);
        display(l3OddAge);
    }
    //////////////////////////////////////////////

    printf("Nombre etudiants: \n");
    printf("%d \n",count(l3));

    //////////////////////////////////////////////

    printf("Suppression des etudiants \n");
    deleteAll(l3);
    //////////////////////////////////////////////
    return 0;
}
