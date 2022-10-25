#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SDB_Size 10
#define Grade_Range 100
#define NUM_OF_SUBJS 3


typedef unsigned char uint8;


bool SDB_IsFull (void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades);
void SDB_DeleteEntry(uint8 id);
bool SDB_ReadEntry (uint8 id, uint8* year, uint8* subjects, uint8* grades);
void SDB_GetIdList (uint8* count, uint8* list);
bool SDB_IsIdExist(uint8 ID);


struct std {
    uint8 ID;
    uint8 Year;
    uint8 courses[3];
    uint8 cgrades[3];
    struct std*  next;

}*head, *student;

typedef struct std Student;



int main()
{

    head=NULL;

    uint8 yy=4;
    uint8 std1_subjs[NUM_OF_SUBJS] = {22,33,44};
    uint8 std1_grades[NUM_OF_SUBJS] = {50,60,100};
    uint8 std2_subjs[NUM_OF_SUBJS] = {22,33,44};
    uint8 std2_grades[NUM_OF_SUBJS] = {70,77,80};


    bool std1add = SDB_AddEntry(100, yy, std1_subjs, std1_grades);
    bool std2add = SDB_AddEntry(90, 3, std2_subjs, std2_grades);
    bool std3add = SDB_AddEntry(80, 3, std2_subjs, std2_grades);
    bool std4add = SDB_AddEntry(70, 3, std2_subjs, std2_grades);
    bool std5add = SDB_AddEntry(60, 3, std2_subjs, std2_grades);
    bool std6add = SDB_AddEntry(50, 2, std2_subjs, std2_grades);
    bool std7add = SDB_AddEntry(40, 2, std2_subjs, std2_grades);
    bool std8add = SDB_AddEntry(30, 2, std2_subjs, std2_grades);
    bool std9add = SDB_AddEntry(20, 1, std2_subjs, std2_grades);
    bool std10add = SDB_AddEntry(10, 1, std2_subjs, std2_grades);
    bool std11add = SDB_AddEntry(5, 1, std2_subjs, std2_grades);

    if (std10add == 1)
        printf("Student 10 was successfully added.\n");
    else
        printf("Student 10 couldn't be added!\n");

    if (std11add == 1)
        printf("Student 11 was successfully added.\n\n");
    else
        printf("Student 11 couldn't be added as max DB size reached!\n\n");



    bool readstd = SDB_ReadEntry(100, &yy, std1_subjs, std1_grades);

    if(readstd == 1) {
    printf("Student ID 100 was read successfully!\n");
    printf("Student Year = %d\n", yy);
    for(int i=0 ; i < NUM_OF_SUBJS ; i++) {
        printf("course %d ID = %d\n", i+1, std1_subjs[i]);
        printf("course %d grade = %d\n", i+1, std1_grades[i]);
    }
    }
    bool full = SDB_IsFull();
    printf("\nResult of SDB full = %i\n\n", full);

    SDB_DeleteEntry(100);
    printf("Student of ID 100 was deleted!\n");


    readstd = SDB_ReadEntry(100, yy, std1_subjs, std1_grades);
    printf("\n\nResult of reading student of ID 100 after deletion = %i\n", readstd);
    full = SDB_IsFull();
    printf("Result of SDB full after deletion = %i\n\n", full);


    uint8 c;
    uint8 arr[SDB_Size];
    SDB_GetIdList(&c,arr);
    printf("Size of current students is %d\n", c);
    printf("The list of IDs of the students: \n");
    for(int j=0 ; j < c ; j++)
        printf("Student %d ID = %d\n",j+1, arr[j]);


    bool idexist = SDB_IsIdExist(100);
    if(idexist == 1)
        printf("\n\nStudent of ID 100 exists!\n");
    else
        printf("\n\nStudent of ID 100 doesn't exist!\n");

    return 0;
}



bool SDB_IsFull (void)
{
    uint8 ctr=0;
    Student* temp = head;
    for(int i=0 ; i < SDB_Size ; i++)
    {
        if(temp->next == NULL)
            break;

        if(temp != NULL) {
            ctr++;
            temp = temp->next;
        }

    }

    if(ctr >= (SDB_Size - 1) )
        return 1;
    else
        return 0;

}

uint8 SDB_GetUsedSize(void)
{
    uint8 ctr=0;
    Student* temp = head;
    for(int i=0 ; i < SDB_Size ; i++)
    {
        if(temp->next == NULL)
            break;

        if(temp != NULL) {
            ctr++;
            temp = temp->next;
        }

    }
    return ++ctr;
}


bool SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{

    student = (Student*)malloc(sizeof(Student));

    student->ID = id;
    student->Year = year;
    for(int i=0 ; i < NUM_OF_SUBJS ; i++) {
        student->courses[i] =  subjects[i];
        if(grades[i] <= Grade_Range)
            student->cgrades[i] = grades[i];
        else
        {
            printf("Grade input is out of range (0-%d)!", Grade_Range);
            return 0;
        }
    }
    student->next = NULL;


    if(head==NULL){
		head = student;
		return 1;
	}
	else if (student->ID < head->ID)
    {
        if (SDB_IsFull() == 1)
            return 0;

		student->next = head;
		head = student;
        return 1;
    }
    else {
        printf("You entered a bigger ID than the previous student!\n");
        printf("Please re-enter a smaller ID..\n\n");
        return 0;
    }


}

void SDB_DeleteEntry(uint8 id)
{
    Student* temp = head;
    Student* prevtemp = head;

    if (head->ID == id)
    {

        head = head->next;
        free(temp);

    }
    else {

        for(int i=0 ; i < SDB_Size ; i++)
        {
            if(temp->ID == id)
            {
                prevtemp->next = temp->next;
                free(temp);
            }

            if(temp->next == NULL)
                break;

            prevtemp = temp;
            temp = temp->next;
        }

    }
}

bool SDB_ReadEntry (uint8 id, uint8* year, uint8* subjects, uint8* grades)
{
    Student* temp = head;
    for(int i=0 ; i < SDB_Size ; i++)
    {

        if(temp->ID == id) {
            *year = temp->Year;
            for(int i=0 ; i < NUM_OF_SUBJS ; i++) {
                subjects[i] = temp->courses[i];
                grades[i] = temp->cgrades[i];
            }
            return 1;

        }

        if(temp->next == NULL)
            break;

        temp = temp->next;
    }
    return 0;

}


void SDB_GetIdList (uint8* count, uint8* list)
{
    *count = SDB_GetUsedSize();

    Student* temp = head;
    for(int i=0 ; i  < (*count) ; i++)
    {
        if(temp!= NULL) {
        list[i] = temp->ID;
        temp = temp->next;
        }

    }

}

bool SDB_IsIdExist(uint8 ID)
{

    Student* temp = head;
    for(int i=0 ; i < SDB_Size ; i++)
    {

        if(temp->ID == ID)
            return 1;

        if(temp->next == NULL)
            break;

        temp = temp->next;
    }
    return 0;

}
