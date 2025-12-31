#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Task {
    int id;
    char title[100];
    int completed;   // 0 = Not completed, 1 = Completed
};

struct Task *tasks = NULL;
int taskCount = 0;

/* Function Prototypes */
void addTask();
void viewTasks();
void completeTask();
void deleteTask();

int main() {
    int choice;

    while (1) {
        printf("\n===== TO DO MANAGER =====\n");
        printf("1. Add Task\n");
        printf("2. View Tasks\n");
        printf("3. Mark Task as Completed\n");
        printf("4. Delete Task\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addTask(); break;
            case 2: viewTasks(); break;
            case 3: completeTask(); break;
            case 4: deleteTask(); break;
            case 5:
                free(tasks);
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* Add a new task */
void addTask() {
    tasks = realloc(tasks, (taskCount + 1) * sizeof(struct Task));
    if (tasks == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    tasks[taskCount].id = taskCount + 1;
    tasks[taskCount].completed = 0;

    printf("Enter task title: ");
    getchar();  // Clear buffer
    fgets(tasks[taskCount].title, 100, stdin);
    tasks[taskCount].title[strcspn(tasks[taskCount].title, "\n")] = '\0';

    taskCount++;
    printf("Task added successfully!\n");
}

/* Display all tasks */
void viewTasks() {
    if (taskCount == 0) {
        printf("No tasks available.\n");
        return;
    }

    printf("\n---- Task List ----\n");
    for (int i = 0; i < taskCount; i++) {
        printf("ID: %d | %s | Status: %s\n",
               tasks[i].id,
               tasks[i].title,
               tasks[i].completed ? "Completed" : "Pending");
    }
}

/* Mark a task as completed */
void completeTask() {
    int id, found = 0;
    printf("Enter task ID to mark as completed: ");
    scanf("%d", &id);

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].completed = 1;
            printf("Task marked as completed!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Task not found!\n");
}

/* Delete a task */
void deleteTask() {
    int id, found = 0;
    printf("Enter task ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            found = 1;
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
                tasks[j].id = j + 1;
            }
            taskCount--;
            tasks = realloc(tasks, taskCount * sizeof(struct Task));
            printf("Task deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Task not found!\n");
}