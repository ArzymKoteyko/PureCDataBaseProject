#ifndef SRC_EVENTS_H_
#define SRC_EVENTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "libs.h"

#define levels_fpath "../materials/master_levels.db"
#define modules_fpath "../materials/master_modules.db"
#define events_fpath "../materials/master_status_events.db"

typedef struct events events;
int printEvents(FILE* ptr);
int addEventsRecord(FILE* ptr, events rec);
int deleteEventsRecord(FILE* ptr, int event_id);
int getLastEventId(FILE* ptr);
events getEventsRecord(int event_id, int module_id, int status, const char* date, const char* time);
int checkEventsId(FILE* ptr, int event_id);
int changeEventsRecord(FILE* ptr, int event_id, events rec);
int insertEventsRecord(FILE* ptr, int event_id, events rec);

#endif  // SRC_EVENTS_H_