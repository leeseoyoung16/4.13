//������ �ۼ��� "�̷� Ż�� �� ���ƿ� �� Ƚ�� ��� ���α׷�"�� �����Ͽ�
//�̷�Ż�� ��η� ����ϰ��Ѵ�.
//�ݵ�� Stack���� ����ؾ� �ϸ� �Ա����� �ⱸ���� ������� ��µǾ�� �Ѵ�.
//(�߰�����)���� �ǵ��� ���� ��ΰ� ���� ��θ� ����ϴ� ��� �߰� ������ �־�����


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
        fprintf(stderr, "���� ��ȭ ����\n");
        return;
    }
    else {
        s->data[++(s->top)] = item;
    }
}

element pop(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
        exit(1);
    }
    else {

        return s->data[(s->top)--];
    }
}

element peek(StackType* s) {
    if (is_empty(s)) {
        fprintf(stderr, "���� ���� ����\n");
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

//��ġ�� ���ÿ� ����
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

//�̷θ� ȭ�鿡 ����Ѵ�
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
            printf("����\n");
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

    printf("\n\n�̵� ���:\n");
    // �̵� ��� ���
    while (!is_empty(&pa_re)) {
        element re_el = pop(&pa_re);
        printf("(%d, %d)  ",re_el.r,re_el.c );
    }

    printf("����\n");
    printf("count : %d", count);
    return 0;
}