#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 10

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

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Stack {
    Point data[MAZE_SIZE * MAZE_SIZE];
    int top;
} Stack;

void push(Stack* s, Point p) {
    s->data[++(s->top)] = p;
}

Point pop(Stack* s) {
    return s->data[(s->top)--];
}

Point get_top(Stack* s) {
    return s->data[s->top];
}

int is_empty(Stack* s) {
    return s->top == -1;
}

int is_valid(Point p) {
    return p.x >= 0 && p.x < MAZE_SIZE && p.y >= 0 && p.y < MAZE_SIZE;
}

int is_wall(Point p) {
    return maze[p.x][p.y] == '1';
}

int is_visited(Point p) {
    return maze[p.x][p.y] == '.';
}

void print_maze() {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}
void print_path(Stack* s) {
    Point path[MAZE_SIZE * MAZE_SIZE];
    int i = 0;
    while (!is_empty(s)) {
        path[i++] = pop(s);
    }
    printf("미로 탈출 경로:\n ");
    for (int j = i - 1; j >= 0; j--) {
        printf("(%d,%d)\n ", path[j].x, path[j].y);
    }
    printf("\n");
}

int main() {
    Stack s;
    s.top = -1;
    Point p = { 1, 0 };
    push(&s, p);
    while (!is_empty(&s)) {
        p = get_top(&s);
        if (maze[p.x][p.y] == 'x') { // 출구 도착
            print_path(&s);
            int count = 0;
            while (!is_empty(&s)) {
                pop(&s);
                count++;
            }
            printf("되돌아간 총 횟수: %d\n", count - 1); // 시작점은 제외
            return 0;
        }

        if (is_visited(p)) {
            pop(&s);
        }
        else if (is_valid(p) && !is_wall(p)) {
            maze[p.x][p.y] = '.'; // 방문한 점 표시
            push(&s, (Point) { p.x - 1, p.y }); // 위로 이동
            push(&s, (Point) { p.x + 1, p.y }); // 아래로 이동
            push(&s, (Point) { p.x, p.y - 1 }); // 왼쪽으로 이동
            push(&s, (Point) { p.x, p.y + 1 }); // 오른쪽으로 이동
        }
        else {
            pop(&s);
        }
    }
    printf("미로를 탈출할 수 없습니다.\n");
    return 0;
}

