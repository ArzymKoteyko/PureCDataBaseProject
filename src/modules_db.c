#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"
#include "libs.h"
#include "shared.h"

void menu();

typedef enum {
    BD_CHOICE_SELECT = 0,
    BD_CHOICE_SHOW_TABLES = 1,
    BD_CHOICE_CREATE_BIN = 2,
    BD_CHOICE_EXIT = -1
} BD_CHOICE;

int main() {
    menu();
    return 0;
}

void menu() {
    int is_error = 0;
    int flag = 1;
    while (flag) {
        int choice;

        printf("╔══════════════════════════════╗\n");
        printf("║            МЕНЮ:             ║\n");
        printf("╠══════════════════════════════╣\n");
        printf("║  0 - ВЫБРАТЬ ТАБЛИЦУ         ║\n");
        printf("║  1 - ПОКАЗАТЬ ТАБЛИЦЫ        ║\n");
        printf("║  2 - СОЗДАТЬ ИНДЕКС-ФАЙЛЫ    ║\n");
        printf("║ -1 - ВЫХОД                   ║\n");
        printf("╚══════════════════════════════╝\n");

        choice = getChoice(-1, 2);
        switch (choice) {
            case 0:
                printf("╔══════════════════════════════╗\n");
                printf("║  0 - таблица модули          ║\n");
                printf("║  1 - таблица уровни          ║\n");
                printf("║  2 - таблица ивентов         ║\n");
                printf("║ -1 - назад                   ║\n");
                printf("╚══════════════════════════════╝\n");

                choice = getChoice(-1, 2);
                if (choice == BD_CHOICE_SELECT) is_error = modulesControll();
                if (choice == BD_CHOICE_SHOW_TABLES) is_error = levelsControll();
                if (choice == BD_CHOICE_CREATE_BIN) is_error = eventsControll();
                if (choice == BD_CHOICE_EXIT) break;
                break;
            case 1:
                is_error = showTables();
                break;

            case 2:
                createIndexFileEVENT("indexEVENT.bin");
                createIndexFileMODULE("indexMODULE.bin");
                createIndexFileLEVELS("indexLEVELS.bin");
                break;

            case -1:
                flag = 0;
                break;
        }
        if (is_error) {
            flag = 0;
            printf("error\n");
        }
    }
}