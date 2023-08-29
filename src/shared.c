#include "shared.h"

#include "db_levels.h"
#include "db_modules.h"
#include "db_status_events.h"
#include "libs.h"

int getChoice(int gap1, int gap2) {
    int num;
    while (1) {
        if (scanf("%d", &num) != 1)
            printf("n/a\n");
        else if ((num > gap2) || (num < gap1))
            printf("n/a\n");
        else
            break;
    }
    return num;
}

int showTables() {
    int is_error = 0;
    FILE *mptr = fopen(modules_fpath, "rb");
    FILE *lptr = fopen(levels_fpath, "rb");
    FILE *eptr = fopen(events_fpath, "rb");
    if ((mptr == NULL) || (lptr == NULL) || (eptr == NULL)) {
        is_error = 1;
    } else {
        printf("MODULES:\n");
        printModules(mptr);
        printf("=======================\nLEVELS:\n");
        printLevels(lptr);
        printf("=======================\nEVENTS:\n");
        printEvents(eptr);
        fclose(mptr);
        fclose(lptr);
        fclose(eptr);
    }

    return is_error;
}

//////////////////////////////////////////////
// Menu for selectin table action
void printMenu(char *module_name) {
    printf("            МЕНЮ %s\n", module_name);
    printf("╠══════════════════════════════╣\n");
    printf("║  0 - ПОКАЗАТЬ ТАБЛИЦУ        ║\n");
    printf("║  1 - ДОБАВИТЬ В ТАБЛИЦУ      ║\n");
    printf("║  2 - ВСТАВИТЬ                ║\n");
    printf("║  3 - ПОМЕНЯТЬ                ║\n");
    printf("║  4 - УДАЛИТЬ                 ║\n");
    printf("║ -1 - ВЫЙТИ                   ║\n");
    printf("╚══════════════════════════════╝\n");
}
//////////////////////////////////////////////

typedef enum TABLE_MODE {
    PRINT = 0,
    ADD = 1,
    INSERT = 2,
    CHANGE = 3,
    REMOVE = 4,
    BACK = -1,
} TABLE_MODE;

int modulesAddRoutine(FILE *ptr) {
    int id = getLastId(ptr);
    modules rec = getModulesRecord(id + 1);
    int is_error = addModulesRecord(ptr, rec);
    printModules(ptr);
    return is_error;
}

int modulesInsertRoutine(FILE *ptr) {
    int is_error = 0;
    int id = getChoice(-1000000, 1000000);
    if (checkModulesId(ptr, id)) {
        modules rec = getModulesRecord(id);
        is_error = insertModulesRecord(ptr, id, rec);
        printModules(ptr);
    } else {
        printf("Doesn't exist\n");
    }
    return is_error;
}

int modulesChangeRoutine(FILE *ptr) {
    printf("Which one?\n");
    int is_error = 0;
    int id = getChoice(-1000000, 1000000);
    if (checkModulesId(ptr, id)) {
        modules rec = getModulesRecord(id);
        is_error = changeModulesRecord(ptr, id, rec);
        printModules(ptr);
    } else {
        printf("Doesn't exist\n");
    }
    return is_error;
}

void modulesRemoveRoutine(FILE *ptr) {
    int id = getChoice(-1000000, 1000000);
    if (checkModulesId(ptr, id)) {
        deleteModulesRecord(ptr, id);
        printModules(ptr);
    } else {
        printf("Doesn't exist\n");
    }
}

int modulesControll() {
    int is_error = 0;
    int flag = 1;
    FILE *ptr = fopen(modules_fpath, "r+b");
    while (flag) {
        printMenu("Modules");
        TABLE_MODE choice = getChoice(-1, 4);
        switch (choice) {
            case PRINT:
                printModules(ptr);
                break;
            case ADD:
                is_error = modulesAddRoutine(ptr);
                break;
            case INSERT:
                printf("Which one?\n");
                is_error = modulesInsertRoutine(ptr);
                break;
            case CHANGE:
                printf("Which one?\n");
                is_error = modulesChangeRoutine(ptr);
                break;
            case REMOVE:
                printf("Which one?\n");
                modulesRemoveRoutine(ptr);
                break;
            case BACK:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}

int levelsAddRoutine(FILE *ptr) {
    levels rec = getLevelsRecord();
    int is_error = addLevelsRecord(ptr, rec);
    printLevels(ptr);
    return is_error;
}

int levelsInsertRoutine(FILE *ptr) {
    printf("Which one?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkLevelsId(ptr, id)) {
        levels rec = getLevelsRecord();
        is_error = insertLevelsRecord(ptr, id, rec);
        printLevels(ptr);
    } else {
        printf("Doesn't exist\n");
    }
    return is_error;
}

int levelsChangeRoutine(FILE *ptr) {
    printf("Which one?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkLevelsId(ptr, id)) {
        levels rec = getLevelsRecord();
        is_error = changeLevelsRecord(ptr, id, rec);
        printLevels(ptr);
    } else {
        printf("Doesn't exist\n");
    }
    return is_error;
}

int levelsRemoveRoutine(FILE *ptr) {
    printf("Which one?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkLevelsId(ptr, id)) {
        is_error = deleteLevelsRecord(ptr, id);
        printLevels(ptr);
    } else {
        printf("Doesn't exist\n");
    }
    return is_error;
}

int levelsControll() {
    int is_error = 0;
    int flag = 1;
    FILE *ptr = fopen(levels_fpath, "r+b");
    while (flag) {
        printMenu("Levels");
        TABLE_MODE choice = getChoice(-1, 4);
        switch (choice) {
            case PRINT:
                printLevels(ptr);
                break;
            case ADD:
                levelsAddRoutine(ptr);
                break;
            case INSERT:
                levelsInsertRoutine(ptr);
                break;
            case CHANGE:
                levelsChangeRoutine(ptr);
                break;
            case REMOVE:
                levelsRemoveRoutine(ptr);
                break;
            case BACK:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}

int eventsAddRoutine(FILE *ptr) {
    int id = getLastEventId(ptr);
    printf("Which event to create?\n");
    events rec = getEventsRecord(id + 1, 0, 0, "", "");
    int is_error = addEventsRecord(ptr, rec);
    printEvents(ptr);
    return is_error;
}

int eventsInsertRoutine(FILE *ptr) {
    printf("Which event ID would you like to insert at?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkEventsId(ptr, id)) {
        events buff = getEventsRecord(id, 0, 0, "", "");
        printf("Enter module ID: ");
        buff.module_id = getChoice(-1000000, 1000000);
        printf("Enter status: ");
        buff.status = getChoice(-1000000, 1000000);
        printf("Enter date (dd.mm.yyyy): ");
        scanf("%10s", buff.date);
        printf("Enter time (hh:mm:ss): ");
        scanf("%8s", buff.time);
        is_error = insertEventsRecord(ptr, id, buff);
        printEvents(ptr);
    } else {
        printf("Event ID doesn't exist\n");
    }
    return is_error;
}

int eventsChangeRoutine(FILE *ptr) {
    printf("Which event ID would you like to change?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkEventsId(ptr, id)) {
        events buff = getEventsRecord(id, 0, 0, "", "");
        printf("Enter new module ID: ");
        buff.module_id = getChoice(-1000000, 1000000);
        printf("Enter new status: ");
        buff.status = getChoice(-1000000, 1000000);
        printf("Enter new date (dd.mm.yyyy): ");
        scanf("%10s", buff.date);
        printf("Enter new time (hh:mm:ss): ");
        scanf("%8s", buff.time);
        is_error = changeEventsRecord(ptr, id, buff);
        printEvents(ptr);
    } else {
        printf("Event ID doesn't exist\n");
    }
    return is_error;
}

int eventsRemoveRoutine(FILE *ptr) {
    printf("Which event to delete?\n");
    int id = getChoice(-1000000, 1000000);
    int is_error = 0;
    if (checkEventsId(ptr, id)) {
        is_error = deleteEventsRecord(ptr, id);
        printEvents(ptr);
    } else {
        printf("Event doesn't exist\n");
    }
    return is_error;
}

int eventsControll() {
    int is_error = 0;
    int flag = 1;
    FILE *ptr = fopen(events_fpath, "r+b");
    while (flag) {
        printMenu("Events");
        TABLE_MODE choice = getChoice(-1, 4);
        switch (choice) {
            case PRINT:
                printEvents(ptr);
                break;
            case ADD:
                eventsAddRoutine(ptr);
                break;
            case REMOVE:
                eventsRemoveRoutine(ptr);
                break;
            case CHANGE:
                eventsChangeRoutine(ptr);
                break;
            case INSERT:
                eventsInsertRoutine(ptr);
                break;
            case BACK:
                flag = 0;
                break;
        }
        if (is_error) flag = 0;
    }
    return is_error;
}

int createIndexFileEVENT(const char *indexFileName) {
    FILE *ptr = fopen(events_fpath, "r+b");
    int is_error = 0;
    if (ptr == NULL) {
        printf("Failed to open data file.\n");
        is_error = 1;
    } else {
        FILE *indexFile = fopen(indexFileName, "wb");
        if (indexFile == NULL) {
            printf("Failed to create index file.\n");
            fclose(ptr);
            is_error = 1;
        } else {
            IndexEntry entry;
            int position = 0;
            modules rec;
            fread(&rec, sizeof(modules), 1, ptr);
            while (!feof(ptr)) {
                entry.position = position;
                entry.id = rec.id;
                fwrite(&entry, sizeof(IndexEntry), 1, indexFile);
                fread(&rec, sizeof(modules), 1, ptr);
                position++;
            }
            fclose(indexFile);
        }
    }
    return is_error;
}

int createIndexFileMODULE(const char *indexFileName) {
    FILE *ptr = fopen(modules_fpath, "r+b");
    int is_error = 0;
    if (ptr == NULL) {
        printf("Failed to open data file.\n");
        is_error = 1;
    } else {
        FILE *indexFile = fopen(indexFileName, "wb");
        if (indexFile == NULL) {
            printf("Failed to create index file.\n");
            fclose(ptr);
            is_error = 1;
        } else {
            IndexEntry entry;
            int position = 0;
            modules rec;
            fread(&rec, sizeof(modules), 1, ptr);
            while (!feof(ptr)) {
                entry.position = position;
                entry.id = rec.id;
                fwrite(&entry, sizeof(IndexEntry), 1, indexFile);
                fread(&rec, sizeof(modules), 1, ptr);
                position++;
            }
            fclose(indexFile);
        }
    }
    return is_error;
}

int createIndexFileLEVELS(const char *indexFileName) {
    FILE *ptr = fopen(levels_fpath, "r+b");
    int is_error = 0;
    if (ptr == NULL) {
        printf("Failed to open data file.\n");
        is_error = 1;
    } else {
        FILE *indexFile = fopen(indexFileName, "wb");
        if (indexFile == NULL) {
            printf("Failed to create index file.\n");
            fclose(ptr);
            is_error = 1;
        } else {
            IndexEntry entry;
            int position = 0;
            modules rec;
            fread(&rec, sizeof(modules), 1, ptr);
            while (!feof(ptr)) {
                entry.position = position;
                entry.id = rec.id;
                fwrite(&entry, sizeof(IndexEntry), 1, indexFile);
                fread(&rec, sizeof(modules), 1, ptr);
                position++;
            }

            fclose(indexFile);
        }
    }
    return is_error;
}