#ifndef SRC_SHARED_H_
#define SRC_SHARED_H_

typedef struct {
    int id;
    int position;
} IndexEntry;

int modulesControll();
int showTables();
int getChoice(int gap1, int gap2);
int levelsControll();
int eventsControll();
int createIndexFileEVENT(const char* indexFileName);
int createIndexFileMODULE(const char* indexFileName);
int createIndexFileLEVELS(const char* indexFileName);

#endif  // SRC_SHARED_H_