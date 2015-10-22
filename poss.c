struct Possibility {
    int instructor;
    int class;
    int time;
    struct Possibility *next;
}

struct Possibility *last = NULL;
struct Possibility *first = NULL;

struct Possibility * NewPossibility(int i, int c, int t) {
    struct Possibility *result = malloc(sizeof(struct Possibility));
}


void ReleaseData() {
    Destroy(first);    
}

void Destroy(struct Possibility *pos) {
    if(pos == NULL) return;
    Destroy(pos->next);
    free(pos);
}
