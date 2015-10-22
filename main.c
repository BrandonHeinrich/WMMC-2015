#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "data.h"

struct Triple {
    int i;
    int c;
    int t;
};

bool CanTeach(int i, int c) {
    return !(instructorClassPreferences[i][c] == 0);
}

bool IsAvailible(int i, int t) {
    switch(t) {
        case 0:
            return !(instructorTimePreferences[i][0] == 0);
        case 1:
        case 2:
        case 3:
            return !(instructorTimePreferences[i][1] == 0);
        case 4:
        case 5:
        case 6:
            return !(instructorTimePreferences[i][2] == 0);
        case 7:
            return !(instructorTimePreferences[i][3] == 0);
    }
}

bool TryClass(int *schedule, struct Triple *validClasses, 
              int scheduleLength,
              int numValidClasses,
              int classToAdd) {         
    struct Triple newClass = validClasses[classToAdd];
    //printf("<TRYING> Instructor: %d\tClass: %d\tTime: %d\n", newClass.i, newClass.c, newClass.t);
    //printf("<FAILED> Autofail\n");
    //return false;
    
    int classIndex = 0;
    while(schedule[classIndex] != -1) {
        classIndex += 1;
        if(classIndex == scheduleLength) return true;
    }
    
    //printf("THINGS %d   %d   %d   %d\n", scheduleLength, classIndex, numValidClasses, classToAdd);
    
    if(scheduleLength-classIndex > numValidClasses-classToAdd) {
        //printf("<FAILED> Not enough possibilities\n");
    }
    
    int roomsOccupied = 1;
    int classesTaught = 0;
    int sections=1;
    
    bool prevPrevClass = false;
    bool prevClass = false;
    bool nextClass = false;
    bool nextNextClass = false;
    
    
    
    int i;
    for(i=0; i<classIndex; i+=1) {
        struct Triple cur = validClasses[schedule[i]];
        
        if(cur.t == newClass.t) {
            roomsOccupied += 1;
        }
        
        if(cur.c == newClass.c) {
            sections += 1;
        }
        
        if(cur.i == newClass.i) {
            classesTaught += 1;
            if(cur.t == newClass.t) {
                //printf("<FAILED> Cannot teach 2 classes at same time.\n");
                return false; // Teacher in Other Class
            }
            if(IN_GROUP_2(cur.c) && IN_GROUP_2(newClass.c)) {
                //printf("<FAILED> Teacher already teaches group 2 class.\n");
                return false; // Already teaches a group 2 class.
            }
            
            if(newClass.t == cur.t+2) prevPrevClass = true;
            if(newClass.t == cur.t+1) prevClass = true;
            if(newClass.t == cur.t-1) nextClass = true;
            if(newClass.t == cur.t-2) nextNextClass = true;
        }
    }
    
    // All Rooms Occupied
    if(roomsOccupied > NUM_ROOMS) {
        //printf("<FAILED> No availible rooms.\n");
        return false;
    }
    
    // All Rooms Occupied
    if(sections > courseChart[newClass.c][0]) {
        //printf("<FAILED> Too many sections of class.\n");
        return false;
    }
    
    // Teacher already worked 3 classes in a row
    if(prevClass && prevPrevClass) {
        //printf("<FAILIED> Cannot teach more than 2 Classes in a row.\n");
        return false;
    }
    
    if(prevClass && nextClass) {
        //printf("<FAILIED> Cannot teach more than 2 Classes in a row.\n");
        return false;
    }
    
    if(nextClass && nextNextClass) {
        //printf("<FAILIED> Cannot teach more than 2 Classes in a row.\n");
        return false;
    }
    
    // Senior already teaches 3 classes
    if(IS_SENIOR(newClass.i)) {
        if (classesTaught > 3) {
            return false;
            //printf("<FAILED> Senior instructor cannot teach more than 3 classes.\n");
        }
    }
    // Junior already teaches 4 classes
    if(IS_JUNIOR(newClass.i)) {
        if (classesTaught > 4) {
            return false;
            //printf("<FAILED> Junior instructor cannot teach more than 4 classes.\n");
        }
    }
    // Manager already teaches a class
    if(IS_MANAGER(newClass.i)) {
        if (classesTaught > 1) {
            return false;
            //printf("<FAILED> Manager cannot teach more than 1 class.\n");
        }
    }
    
    
    schedule[classIndex] = classToAdd;
    //printf("<ADDING> Instructor: %d\tClass: %d\tTime: %d\n", newClass.i, newClass.c, newClass.t);
    if(scheduleLength == classIndex+1) {
        printf("<FINAL> Instructor: %d\tClass: %d\tTime: %d\n", newClass.i, newClass.c, newClass.t);
        return true;
    }
    for(i=classToAdd+1; i < numValidClasses; i+=1) {
        //printf("I: %d\n", i);
        if(TryClass(schedule, validClasses, scheduleLength, numValidClasses, i)) {
            printf("<FINAL> Instructor: %d\tClass: %d\tTime: %d\n", newClass.i, newClass.c, newClass.t);
            return true;
        }
    }
    schedule[classIndex] = -1;
    //printf("<REMOVING> Instructor: %d\tClass: %d\tTime: %d\n", newClass.i, newClass.c, newClass.t);
    return false;    
}

struct Triple MakeTriple(int instructor, int class, int time) {
    struct Triple result = {.i=instructor, .c=class, .t=time};
    return result;
}

int main(int argc, char **argv) {
    // Create Empty Schedule
    int x;
    for(x=0; x<SCHEDULE_LENGTH; x+=1) schedule[x] = -1;



    printf("Counting Possibilities\n");
    
    int count = 0;
    
    // Create Possibilities
    int i, c, t;
    for(i=0; i < JUNIORS+SENIORS+MANAGER; i+=1) {
        for(c=0; c < GROUP_1+GROUP_2; c += 1) {
            if(CanTeach(i,c)) {
                for(t=FIRST_CLASS; t < LAST_CLASS; t += 1) {
                    if(IsAvailible(i, t)) {
                        count += 1;
                        printf("(%d, %d, %d)\n", i, c, t);
                    }
                }
            }
        }
    }
    
    printf("There are %d possible combinations\n", count);
   
    struct Triple validClasses[count];
    
    int index = 0;
    for(i=0; i < JUNIORS+SENIORS+MANAGER; i+=1) {
        for(c=0; c < GROUP_1+GROUP_2; c += 1) {
            if(CanTeach(i,c)) {
                for(t=FIRST_CLASS; t < LAST_CLASS; t += 1) {
                    if(IsAvailible(i, t)) {
                        validClasses[index] = MakeTriple(i, c, t);
                        index += 1;
                    }
                }
            }
        }
    }
    
    //return 0;
    
    for(i=0; i<count; i+=1) {
        printf("i=%d\n", i);
        if(TryClass(schedule, validClasses, SCHEDULE_LENGTH, count, i)) {
            printf("SCHEDULE EXISTS!!!\n");
            return 0;
        }
    }
    
    
    
    return 0;
}
