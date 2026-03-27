#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void sleep_ms(int milliseconds) {
  clock_t start = clock();
  clock_t end = start + (milliseconds * CLOCKS_PER_SEC / 1000);
  while (clock() < end) {}
}

#define SLEEP(ms) sleep_ms(ms)

#define MAX_TASKS 100
#define MAX_TASK_LEN 256
#define TYPE_DELAY 0
#define TYPE_DELAY_TASKS 15

/* ANSI color codes */
#define COLOR_RESET "\033[0m"
#define COLOR_CYAN "\033[96m"
#define COLOR_GREEN "\033[92m"
#define COLOR_YELLOW "\033[93m"
#define COLOR_RED "\033[91m"
#define COLOR_MAGENTA "\033[95m"
#define COLOR_BLUE "\033[94m"
#define COLOR_BOLD "\033[1m"

typedef struct {
  char description[MAX_TASK_LEN];
  int active;
  int completed;
} Task;

Task tasks[MAX_TASKS];
int task_count = 0;

void typewriter(const char *text, int delay) {
  for (int i = 0; text[i] != '\0'; i++) {
    putchar(text[i]);
    fflush(stdout);
    SLEEP(delay);
  }
}

void typewriter_color(const char *text, const char *color, int delay) {
  printf("%s", color);
  typewriter(text, delay);
  printf("%s", COLOR_RESET);
}

void print_menu(void) {
  printf("\n");
  typewriter_color("╔════════════════════════════════════╗\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║     ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("📋 TO-DO LIST APP 📋", COLOR_BOLD, TYPE_DELAY);
  typewriter_color("      ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("╠════════════════════════════════════╣\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║  ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("[1]", COLOR_GREEN, TYPE_DELAY);
  typewriter_color(" Add Task                    ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║  ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("[2]", COLOR_YELLOW, TYPE_DELAY);
  typewriter_color(" View All Tasks              ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║  ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("[3]", COLOR_BLUE, TYPE_DELAY);
  typewriter_color(" Check/Uncheck Task          ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║  ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("[4]", COLOR_RED, TYPE_DELAY);
  typewriter_color(" Remove Task                 ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║  ", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("[5]", COLOR_MAGENTA, TYPE_DELAY);
  typewriter_color(" Exit                        ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("╚════════════════════════════════════╝\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("\n➤ Choose an option: ", COLOR_BLUE, TYPE_DELAY);
}

void add_task(void) {
  if (task_count >= MAX_TASKS) {
    typewriter_color("\n❌ Task list is full! Cannot add more tasks.\n", COLOR_RED, TYPE_DELAY);
    return;
  }

  char input[MAX_TASK_LEN];
  typewriter_color("\n✏️  Enter task description: ", COLOR_GREEN, TYPE_DELAY);
  if (fgets(input, sizeof(input), stdin) != NULL) {
    input[strcspn(input, "\n")] = '\0';
    
    if (strlen(input) == 0) {
      typewriter_color("❌ Task cannot be empty.\n", COLOR_RED, TYPE_DELAY);
      return;
    }

    strncpy(tasks[task_count].description, input, MAX_TASK_LEN - 1);
    tasks[task_count].description[MAX_TASK_LEN - 1] = '\0';
    tasks[task_count].active = 1;
    tasks[task_count].completed = 0;
    task_count++;
    
    typewriter_color("\n✅ Task added successfully!\n", COLOR_GREEN, TYPE_DELAY);
  }
}

void view_tasks(void) {
  int active_count = 0;
  
  for (int i = 0; i < task_count; i++) {
    if (tasks[i].active) {
      active_count++;
    }
  }

  if (active_count == 0) {
    typewriter_color("\n📭 No tasks in your to-do list. Add some tasks to get started!\n", COLOR_YELLOW, TYPE_DELAY);
    return;
  }

  printf("\n");
  typewriter_color("╔════════════════════════════════════╗\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("║      📝 YOUR TO-DO LIST 📝        ║\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("╚════════════════════════════════════╝\n", COLOR_CYAN, TYPE_DELAY);
  
  for (int i = 0; i < task_count; i++) {
    if (tasks[i].active) {
      char task_line[512];
      const char *checkbox = tasks[i].completed ? " ☑" : " ☐";
      const char *color = tasks[i].completed ? COLOR_GREEN : COLOR_YELLOW;
      
      snprintf(task_line, sizeof(task_line), "\n  %s%d.%s ", color, i + 1, COLOR_RESET);
      printf("%s", task_line);
      
      if (tasks[i].completed) {
        printf("%s", COLOR_GREEN);
      }
      typewriter(tasks[i].description, TYPE_DELAY_TASKS);
      if (tasks[i].completed) {
        printf("%s", COLOR_RESET);
      }
      printf("%s", checkbox);
      printf("\n");
    }
  }
  printf("\n");
}

void check_task(void) {
  view_tasks();
  
  int active_count = 0;
  for (int i = 0; i < task_count; i++) {
    if (tasks[i].active) {
      active_count++;
    }
  }

  if (active_count == 0) {
    return;
  }

  int task_num;
  typewriter_color("✓  Enter task number to check/uncheck: ", COLOR_BLUE, TYPE_DELAY);
  
  if (scanf("%d", &task_num) != 1) {
    while (getchar() != '\n');
    typewriter_color("\n❌ Invalid input.\n", COLOR_RED, TYPE_DELAY);
    return;
  }
  while (getchar() != '\n');

  if (task_num < 1 || task_num > task_count || !tasks[task_num - 1].active) {
    typewriter_color("\n❌ Invalid task number.\n", COLOR_RED, TYPE_DELAY);
    return;
  }

  tasks[task_num - 1].completed = !tasks[task_num - 1].completed;
  
  if (tasks[task_num - 1].completed) {
    typewriter_color("\n✅ Task marked as completed!\n", COLOR_GREEN, TYPE_DELAY);
  } else {
    typewriter_color("\n🔄 Task marked as incomplete.\n", COLOR_YELLOW, TYPE_DELAY);
  }
}

void remove_task(void) {
  view_tasks();
  
  int active_count = 0;
  for (int i = 0; i < task_count; i++) {
    if (tasks[i].active) {
      active_count++;
    }
  }

  if (active_count == 0) {
    return;
  }

  int task_num;
  typewriter_color("🗑️  Enter task number to remove: ", COLOR_RED, TYPE_DELAY);
  
  if (scanf("%d", &task_num) != 1) {
    while (getchar() != '\n');
    typewriter_color("\n❌ Invalid input.\n", COLOR_RED, TYPE_DELAY);
    return;
  }
  while (getchar() != '\n');

  if (task_num < 1 || task_num > task_count || !tasks[task_num - 1].active) {
    typewriter_color("\n❌ Invalid task number.\n", COLOR_RED, TYPE_DELAY);
    return;
  }

  tasks[task_num - 1].active = 0;
  typewriter_color("\n✅ Task removed successfully!\n", COLOR_GREEN, TYPE_DELAY);
}

int main(void) {
  int choice;

  printf("\n");
  typewriter_color("═══════════════════════════════════════\n", COLOR_CYAN, TYPE_DELAY);
  typewriter_color("   🎮 WELCOME TO TO-DO LIST APP 🎮\n", COLOR_MAGENTA, TYPE_DELAY);
  typewriter_color("═══════════════════════════════════════\n", COLOR_CYAN, TYPE_DELAY);

  while (1) {
    print_menu();

    if (scanf("%d", &choice) != 1) {
      while (getchar() != '\n');
      typewriter_color("\n❌ Invalid input. Please enter a number.\n", COLOR_RED, TYPE_DELAY);
      continue;
    }
    while (getchar() != '\n');

    switch (choice) {
    case 1:
      add_task();
      break;

    case 2:
      view_tasks();
      break;

    case 3:
      check_task();
      break;

    case 4:
      remove_task();
      break;

    case 5:
      printf("\n");
      typewriter_color("═══════════════════════════════════════\n", COLOR_CYAN, TYPE_DELAY);
      typewriter_color("   👋 Goodbye! Stay productive! 👋\n", COLOR_GREEN, TYPE_DELAY);
      typewriter_color("═══════════════════════════════════════\n", COLOR_CYAN, TYPE_DELAY);
      printf("\n");
      return 0;

    default:
      typewriter_color("\n❌ Invalid option. Please choose 1-5.\n", COLOR_RED, TYPE_DELAY);
      break;
    }
  }

  return 0;
}
