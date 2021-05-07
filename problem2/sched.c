#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define TASK_NAME_LENGTH 20
#define SCHED_YES 1
#define SCHED_NO 2
#define SCHED_UNKNOWN 3

typedef struct task {
    char name[TASK_NAME_LENGTH];
    int period;
    int WCET;
    int priority;
    int deadline;
    struct task* next;
} task;

task* first_task = NULL;
task* last_task = NULL;

/* Allocate a task and add it to the end of the linked list */
void add_task(char* name, int period, int WCET, int priority, int deadline)
{
    task* new_task = (task*)malloc(sizeof(task));
    if (strlen(name) < TASK_NAME_LENGTH) {
        strcpy(new_task->name, name);
    }
    else {
        printf("The task name is too long.\n");
        exit(-1); // Exit with an error code
    }

    new_task->period = period;
    new_task->WCET = WCET;
    new_task->priority = priority;
    new_task->deadline = deadline;

    new_task->next = NULL;
    if (first_task == NULL && last_task == NULL) { // If this is the first task to be added
        first_task = new_task;
        last_task = new_task;
        return;
    }
    last_task->next = new_task;
    last_task = new_task;
}

/* Remove first task in the list */
void remove_first_task()
{
    task* temp = first_task;

    if (first_task == NULL) {
        printf("The task list is empty\n");
        return;
    }
    if (first_task == last_task) { // Exactly one task in the list
        first_task = NULL;
        last_task = NULL;
    }
    else { // Set first_task to be the second task in the list
        first_task = first_task->next;
    }
    free(first_task); // Deallocate the memory for the first task
}

/* Remove all tasks by iteratively removing the first task until the list is
   empty
*/
void remove_all_tasks()
{
    while (first_task != NULL) {
        remove_first_task();
    }
}

/* This function should return the number of tasks added to the system */
int nbr_of_tasks()
{
    // Todo: Implement this function. You should not change anything outside this
    // function.
	return 0;
}

/* Print information about all tasks in the list
   Notice, how to iterate through all tasks in the list
*/
void print_tasks()
{
    task* curr_task = first_task;

    while (curr_task != NULL) {
        printf("Name: %s, period: %d, WCET: %d, priority %d, deadline: %d\n",
            curr_task->name, curr_task->period, curr_task->WCET,
            curr_task->priority, curr_task->deadline);
        curr_task = curr_task->next;
    }
}

/*
Test if the tasks is schedulable according to the critera by Liu and Layland.
Reference: C. L. Liu and J. Layland. Scheduling algorithms for multiprogramming
in a hard real-time environment, Journal of the ACM, 20(1), 1973, pp. 46-61.
Return:
   1: Yes, the tasks are schedulable (according to the criteria)
   2: No, the tasks are not schedulable
   3: The criteria cannot determine if the tasks are schedulable or not

Assumptions: Priorities are unique, the list of tasks contains at least one
task.
*/
int schedulable_Liu_Layland()
{
    // Todo: Implement this function

    // REMOVE

    int schedulable = SCHED_UNKNOWN; // Change this
    return schedulable;
}

/*
Test if the tasks is schedulable according to the exact response time analysisnd
Layland.
Return:
   1: Yes, the tasks are schedulable (according to the criteria)
   2: No, the tasks are not schedulable
   3: The criteria cannot determine if the tasks are schedulable or not

Assumptions: Priorities are unique, the list of tasks contains at least one
task.
*/
int schedulable_response_time_analysis()
{
    // Todo: Implement this function
    // The C library provides a ceiling function that returns the smallest integer
    // value greater than or equal to x: double ceil(double x)
    int schedulable = SCHED_UNKNOWN; // Change this
    return schedulable;
}

int check_schedulable(int correct_response_Liu_Layland,
    int correct_response_response_time_analysis)
{
    int nbr_of_failed_tests = 0;
    if (schedulable_Liu_Layland() != correct_response_Liu_Layland) {
        nbr_of_failed_tests++;
        printf("\n=== Schedulable test failed: Liu-Layland\n");
        print_tasks();
        printf("===\n");
    }

    if (schedulable_response_time_analysis() != correct_response_response_time_analysis) {
        nbr_of_failed_tests++;
        printf("\n=== Schedulable test failed: Response-Time Analysis\n");
        print_tasks();
        printf("===\n");
    }
    return nbr_of_failed_tests;
}

/* Do not change or remove any code in this function.
   If you like you can add additional test cases.
   TODO
*/
int check_tests()
{
    int nbr_of_failed_tests = 0;

    remove_all_tasks();

    // Add test
    // add_task(name, period, WCET, priority, deadline)
    add_task("T1", 25, 10, 5, 25);
    add_task("T2", 25, 8, 4, 25);
    add_task("T3", 50, 5, 3, 50);
    add_task("T4", 50, 4, 2, 50);
    add_task("T5", 100, 2, 1, 100);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_UNKNOWN);

    remove_all_tasks();
    // Add test
    add_task("T1", 50, 12, 1, 50);
    add_task("T2", 40, 10, 2, 40);
    add_task("T3", 30, 10, 3, 50);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_UNKNOWN);

    remove_all_tasks();
    // Add test
    add_task("T1", 80, 12, 1, 50);
    add_task("T2", 40, 10, 2, 40);
    add_task("T3", 20, 10, 3, 50);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_UNKNOWN);

    remove_all_tasks();
    // Add test
    add_task("T1", 7, 3, 3, 7);
    add_task("T2", 12, 3, 2, 12);
    add_task("T3", 20, 5, 1, 20);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_UNKNOWN);

    remove_all_tasks();
    // Add test
    add_task("T1", 7, 3, 3, 3);
    add_task("T2", 12, 3, 2, 6);
    add_task("T3", 20, 5, 1, 20);

    nbr_of_failed_tests += check_schedulable(SCHED_UNKNOWN, SCHED_UNKNOWN);

    return nbr_of_failed_tests;
}

int main()
{
    int nbr_of_failed_tests = check_tests();
    printf("\n=== Total number of failed tests: %d\n", nbr_of_failed_tests);
 //   fflush(stdout); // Flush print buffer before terminating
    return 0;
}
