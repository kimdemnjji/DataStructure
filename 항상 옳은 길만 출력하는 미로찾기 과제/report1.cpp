#include "Location2D.h"
#include <iostream>
#include <stack>
#include <windows.h>
using namespace std;

const int MAZE_SIZE = 6;
char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', '1'},
    {'1', 'x', '1', '1', '1', '1'},
};

bool isValidLoc(int r, int c) { //갈 수 있는 방향인지 true or false로 체크
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
    else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
    Location2D pre[MAZE_SIZE][MAZE_SIZE]; //지나온 현재 좌표에 직전 좌표를 저장할 2차원 배열
    stack<Location2D> locStack, line; // stack 두 개를 만든다.
    Location2D entry(1, 0); // 초기위치를 지정해준다.
    locStack.push(entry); //locstack에 처음 위치 push.

    while (locStack.empty() == false) { //locstack이 비어있지 않을 때까지 계속
        Location2D here = locStack.top(); // locstack의 최상단요소를 현재 위치에 저장한다.
        locStack.pop(); // 저장하고 삭제한다.

        int r = here.row, c = here.col; //r는 현재의 x좌표, c는 현재의 y좌표이다.
        // printf("(%d,%d) ", r, c);
        if (map[r][c] == 'x') { //현재의 좌표에 x가 저장되어 있을 때, if문 실행

            Location2D now = here; //now에 현재의 좌표를 저장한다.
            while (!(now == entry)) { // 현재의 좌표가 시작 지점이 아닐 때 처리.
                line.push(now); //루트 스택의 현재 좌표값을 push해준다.
                now = pre[now.row][now.col]; //pre 위치를 저장해준다.
            }
            line.push(entry); // 루트 스택에 초기좌표를 push 한다.

            while (!line.empty()) { // 루트 스택에 비어있지 않을 때 처리
                cout << '(' << line.top().row << ',' << line.top().col << ')' << "->";
                line.pop();  // 역순으로 루트를 출력하고 pop하는 것을 반복한다.
            }
            printf("미로 탐색 성공\n"); //출력을 마치고 미로 탐색을 성공.
            return 0;
        }
        else { //현재의 좌표에 x가 저장되어 있지 않을 때, else문 실행
            map[r][c] = '.'; // 배열에 '.' 저장
            if (isValidLoc(r - 1, c))
                locStack.push(Location2D(r - 1, c)), pre[r - 1][c] = here;
            //이동 전 좌표를 저장한다.
            if (isValidLoc(r + 1, c))
                locStack.push(Location2D(r + 1, c)), pre[r + 1][c] = here;
            //이동 전 좌표를 저장한다.
            if (isValidLoc(r, c - 1))
                locStack.push(Location2D(r, c - 1)), pre[r][c - 1] = here;
            //이동 전 좌표를 저장한다.
            if (isValidLoc(r, c + 1))
                locStack.push(Location2D(r, c + 1)), pre[r][c + 1] = here;
            //이동 전 좌표를 저장한다.
        }
    }

    printf("미로 탐색 실패\n");

    return 0;

}