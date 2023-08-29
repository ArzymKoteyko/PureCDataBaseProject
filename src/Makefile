FLAGS = -Wall -Werror -Wextra

all: Quest_1 build_db

Quest_1: modules_db.c db_modules.c db_levels.c db_status_events.c shared.c
	gcc $(FLAGS) -c modules_db.c db_modules.c db_levels.c db_status_events.c shared.c
	gcc db_modules.o db_levels.o db_status_events.o shared.o modules_db.o -o ../build/Quest_1


build_db: modules_db.c db_modules.c db_levels.c db_status_events.c shared.c
	gcc $(FLAGS) -c modules_db.c db_modules.c db_levels.c db_status_events.c shared.c
	gcc db_modules.o db_levels.o db_status_events.o shared.o modules_db.o -o ../build/build_db

clean:
	rm -f *.o

clean_all: clean
	rm -f ../build/*

all: build_db

rebuild: clean_all all