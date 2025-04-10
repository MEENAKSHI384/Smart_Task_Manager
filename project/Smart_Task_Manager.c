#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TASKS 100  // Maximum number of tasks

// Structure to store task details
typedef struct {
    char name[100];
    char deadline[20];
    int priority;
} Task;

Task tasks[MAX_TASKS];  // Array to store tasks
int taskCount = 0;      // Number of tasks

// Function to add a new task
void addTask() {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    printf("\nEnter task name: ");
    scanf(" %[^\n]", tasks[taskCount].name);

    printf("Enter deadline (YYYY-MM-DD): ");
    scanf("%s", tasks[taskCount].deadline);

    printf("Enter priority (1-5): ");
    scanf("%d", &tasks[taskCount].priority);

    taskCount++;
    printf("Task added successfully!\n");
}

// Function to display all tasks
void viewTasks() {
    if (taskCount == 0) {
        printf("\nNo tasks available.\n");
        return;
    }

    printf("\n📌 Task List:\n");
    for (int i = 0; i < taskCount; i++) {
        printf("%d. [%d] %s (Deadline: %s)\n", i + 1, tasks[i].priority, tasks[i].name, tasks[i].deadline);
    }
}

// Function to sort tasks by priority (ascending order)
void sortTasks() {
    if (taskCount == 0) {
        printf("\nNo tasks available to sort.\n");
        return;
    }

    for (int i = 0; i < taskCount - 1; i++) {
        for (int j = 0; j < taskCount - i - 1; j++) {
            if (tasks[j].priority > tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    printf("\nTasks sorted by priority!\n");
    viewTasks();  // Display sorted tasks
}

// Function to show upcoming tasks (based on deadline and priority)
void showUpcomingTasks() {
    if (taskCount == 0) {
        printf("\nNo tasks available to show upcoming ones.\n");
        return;
    }

    // Get current date
    time_t t;
    struct tm *tm_info;
    char currentDate[20];
    
    time(&t);
    tm_info = localtime(&t);
    strftime(currentDate, sizeof(currentDate), "%Y-%m-%d", tm_info);

    printf("\n🔔 Upcoming Tasks:\n");
    
    int foundUpcoming = 0;
    
    // Display tasks that have a deadline after the current date
    for (int i = 0; i < taskCount; i++) {
        if (strcmp(tasks[i].deadline, currentDate) >= 0) {
            printf("%d. [%d] %s (Deadline: %s)\n", i + 1, tasks[i].priority, tasks[i].name, tasks[i].deadline);
            foundUpcoming = 1;
        }
    }

    if (!foundUpcoming) {
        printf("No upcoming tasks!\n");
    }
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n=== Smart Task Manager ===\n");
        printf("1. Add Task\n2. View Tasks\n3. Sort Tasks by Priority\n4. Show Upcoming Tasks\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: sortTasks(); break;
            case 4: showUpcomingTasks(); break;
            case 5: printf("\nExiting Smart Task Manager... Goodbye!\n"); exit(0);
            default: printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}