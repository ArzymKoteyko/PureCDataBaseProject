#include "db_status_events.h"

int printEvents(FILE* ptr) {
    int is_error = 0;
    events rec;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        printf("EVENTS\n");
        fread(&rec, sizeof(events), 1, ptr);
        while (!feof(ptr)) {
            printf("%d %d %d %s %s\n", rec.event_id, rec.module_id, rec.status, rec.date, rec.time);
            fread(&rec, sizeof(events), 1, ptr);
        }
    }
    return is_error;
}

int addEventsRecord(FILE* ptr, events rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, 0, SEEK_END);
        fwrite(&rec, sizeof(events), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

int deleteEventsRecord(FILE* ptr, int event_id) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        events rec;
        int i = event_id;
        fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
        while (!feof(ptr)) {
            fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
            if (fread(&rec, sizeof(events), 1, ptr) != 1) break;
            fseek(ptr, i * sizeof(events), SEEK_SET);
            fwrite(&rec, sizeof(events), 1, ptr);
            i++;
        }
        fseek(ptr, 0, SEEK_SET);
        truncate(events_fpath, i * sizeof(events));
    }
    return is_error;
}

int changeEventsRecord(FILE* ptr, int event_id, events rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        fseek(ptr, event_id * sizeof(events), SEEK_SET);
        fwrite(&rec, sizeof(events), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

int insertEventsRecord(FILE* ptr, int event_id, events rec) {
    int is_error = 0;
    if (ptr == NULL) {
        is_error = 1;
    } else {
        events temp_rec;
        int i = getLastEventId(ptr);
        fseek(ptr, i * sizeof(events), SEEK_SET);
        while (i >= event_id) {
            fread(&temp_rec, sizeof(events), 1, ptr);
            fseek(ptr, (i + 1) * sizeof(events), SEEK_SET);
            fwrite(&temp_rec, sizeof(events), 1, ptr);
            fseek(ptr, i * sizeof(events), SEEK_SET);
            i--;
        }
        fseek(ptr, event_id * sizeof(events), SEEK_SET);
        fwrite(&rec, sizeof(events), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return is_error;
}

int getLastEventId(FILE* ptr) {
    int event_id = -1;
    if (ptr != NULL) {
        fseek(ptr, -sizeof(events), SEEK_END);
        fread(&event_id, sizeof(int), 1, ptr);
        fseek(ptr, 0, SEEK_SET);
    }
    return event_id;
}

events getEventsRecord(int event_id, int module_id, int status, const char* date, const char* time) {
    events rec;
    rec.event_id = event_id;
    rec.module_id = module_id;
    rec.status = status;
    strncpy(rec.date, date, sizeof(rec.date));
    strncpy(rec.time, time, sizeof(rec.time));
    rec.date[sizeof(rec.date) - 1] = '\0';
    rec.time[sizeof(rec.time) - 1] = '\0';
    return rec;
}

int checkEventsId(FILE* ptr, int event_id) {
    int res = 0;
    fseek(ptr, 0, SEEK_END);
    int size = ftell(ptr) / sizeof(events);
    if ((event_id >= 0) && (event_id < size)) res = 1;
    return res;
}