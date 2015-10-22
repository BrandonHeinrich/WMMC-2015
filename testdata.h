#include <stdbool.h>

#define SENIORS 1
#define JUNIORS 1
#define MANAGER 1

#define GROUP_1 3
#define GROUP_2 1



#define IS_JUNIOR(x) x>=0 && x<JUNIORS
#define IS_SENIOR(x) x>=JUNIORS && x<SENIORS
#define IS_MANAGER(x) x==JUNIORS+SENIORS

#define IN_GROUP_1(x) x>=0 && x<GROUP_1
#define IN_GROUP_2(x) x>=GROUP_1 && x<GROUP_1+GROUP_2

#define NUM_ROOMS 25

#define FIRST_CLASS 0
#define MORNING 3
#define AFTERNOON 4
#define LAST_CLASS 8 

#define SCHEDULE_LENGTH 8











int instructorClassPreferences[JUNIORS+SENIORS+MANAGER][GROUP_1+GROUP_2] = {
    {1, 2, 1, 0},
    {1, 0, 0, 2},
    {0, 0, 0, 1}
};

int instructorTimePreferences[JUNIORS+SENIORS+MANAGER][4] = {
    {1, 1, 0, 1},
    {1, 1, 0, 1},
    {1, 1, 0, 1}
};

int courseChart[GROUP_1+GROUP_2][2] = {
    {3, 3},
    {2, 2},
    {1, 4},
    {2, 4}
};

int schedule[SCHEDULE_LENGTH];

