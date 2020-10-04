#include <stdio.h>
#include "helper_api.h"

typedef struct employee {

    char employee_name[32];
    char company_name[50];
    char employee_job_title[50]; 
    uint32_t employee_id;
} employee_t;

typedef struct student{

    char student_name[32];
    uint32_t student_rollno;
    uint32_t student_total_marks;
    char* student_result;
} student_t;


int main(int argc, char **argv){

    //initialize memory manager
    mm_init();
    //register all structure
    MM_REG_STRUCT(employee_t);
    MM_REG_STRUCT(student_t);

    //display registed page families
    mm_print_registered_page_families();

    //allocate memory using Custom Linux Memory Manager API implemented in memory_manager.c file
    employee_t *emp1 = XCALLOC(1, employee_t);
    employee_t *emp2 = XCALLOC(1, employee_t);
    employee_t *emp3 = XCALLOC(1, employee_t);
    employee_t *emp4 = XCALLOC(3, employee_t);

    student_t *stud1 = XCALLOC(1, student_t);
    student_t *stud2 = XCALLOC(2, student_t);
    student_t *stud3 = XCALLOC(1, student_t);

    printf("\n**********************  Case 1 : Allocating memeory for 4 structure of type employee_t  **********************");
    printf("\n**********************         : Allocating memeory for 3 structure of type student_t   **********************\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();

    XFREE(emp1);
    XFREE(emp2);
    XFREE(stud1);

    printf("\n**********************  Case 2 : Freeing memeory for 2 structure of type employee_t  **********************");
    printf("\n**********************         : Freeing memeory for 1 structure of type student_t   **********************\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();

    XFREE(emp3);
    XFREE(stud2);
    XFREE(emp4);
    XFREE(stud3);

    printf("\n**********************  Case 3 : Freeing memeory for 2 structure of type employee_t  **********************");
    printf("\n**********************         : Freeing memeory for 2 structure of type student_t   **********************\n");
    mm_print_memory_usage(0);
    mm_print_block_usage();
    printf("\n\n");

    return 0; 
}
