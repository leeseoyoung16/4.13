//이전에 작성한 "미로 탈출 중 돌아온 총 횟수 출력 프로그램"을 수정하여
//미로탈출 경로룰 출력하게한다.
//반드시 Stack만을 사용해야 하며 입구부터 출구까지 순서대로 출력되어야 한다.
//(추가점수)만약 되돌아 오는 경로가 없게 경로를 출력하는 경우 추가 점수가 주어진다


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAZE_SIZE 10
#define MAX 100
int count = 0;
int cnt = 0;
typedef struct {
    short r;
    short c;
    
} element;

typedef struct {
    element data[MAX];
    int top;
} StackType;


void init_stack(StackType* s) {
    s->top = -1;
}

int is_empty(StackType* s) {
    return (s->top == -1);
}

int is_full(StackType* s) {
    return (s->top == (MAX - 1));
}

void push(StackType* s, element item) {
    if (is_full(s)) {
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {

        return s->data[(s->top)--];
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else {
        return s->data[s->top];
    }
}
element here = { 1, 0 }, entry = { 1,0 };


char maze[MAZE_SIZE][MAZE_SIZE] = {

        {'1','1','1','1','1','1','1','1','1','1'},
        {'e','1','0','1','0','0','0','1','0','1'},
        {'0','0','0','1','0','0','0','1','0','1'},
        {'0','1','0','0','0','1','1','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','1','0','0','0','0','1'},
        {'1','0','0','0','0','0','1','0','1','1'},
        {'1','0','1','1','1','0','1','1','0','1'},
        {'1','1','0','0','0','0','0','0','0','x'},
        {'1','1','1','1','1','1','1','1','1','1'}

};

//위치를 스택에 삽입
void push_loc(StackType* s, int r, int c ) {

    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) {
        
        return;
    }
    
    if (maze[r][c] != '1' && maze[r][c] != '.') {
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
        cnt += 1;
        
    }
    
}

//미로를 화면에 출력한다
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]) {
    printf("\n");
    for (int r = 0; r < MAZE_SIZE; r++) {
        for (int c = 0; c < MAZE_SIZE; c++) {
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

int main(void) {
    int r, c;
    StackType s;
    StackType pa;
    StackType pa_re;

    init_stack(&pa);
    init_stack(&s);
    init_stack(&pa_re);

    here = entry;
    while (maze[here.r][here.c] != 'x') {
        r = here.r;
        c = here.c;
        maze[r][c] = '.';
        maze_print(maze);
       
        element tmp;
        tmp.r = r;
        tmp.c = c;

        push(&pa, tmp);

        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);

        if (cnt == 0) {
            count += 1;
        }

        cnt = 0;

        if (is_empty(&s)) {
            printf("실패\n");
            return;
        }
        else {
            here = pop(&s);
        }

        
    }

    while (!is_empty(&pa)) {
        element re_el;
        re_el = pop(&pa);
        push(&pa_re, re_el);
    
    }

    printf("\n\n이동 경로:\n");
    // 이동 경로 출력
    while (!is_empty(&pa_re)) {
        element re_el = pop(&pa_re);
        printf("(%d, %d)  ",re_el.r,re_el.c );
    }

    printf("성공\n");
    printf("count : %d", count);
    return 0;
}