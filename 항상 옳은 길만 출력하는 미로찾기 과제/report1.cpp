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

bool isValidLoc(int r, int c) { //�� �� �ִ� �������� true or false�� üũ
    if (r < 0 || c < 0 || r >= MAZE_SIZE || c >= MAZE_SIZE) return false;
    else return map[r][c] == '0' || map[r][c] == 'x';
}

int main() {
    Location2D pre[MAZE_SIZE][MAZE_SIZE]; //������ ���� ��ǥ�� ���� ��ǥ�� ������ 2���� �迭
    stack<Location2D> locStack, line; // stack �� ���� �����.
    Location2D entry(1, 0); // �ʱ���ġ�� �������ش�.
    locStack.push(entry); //locstack�� ó�� ��ġ push.

    while (locStack.empty() == false) { //locstack�� ������� ���� ������ ���
        Location2D here = locStack.top(); // locstack�� �ֻ�ܿ�Ҹ� ���� ��ġ�� �����Ѵ�.
        locStack.pop(); // �����ϰ� �����Ѵ�.

        int r = here.row, c = here.col; //r�� ������ x��ǥ, c�� ������ y��ǥ�̴�.
        // printf("(%d,%d) ", r, c);
        if (map[r][c] == 'x') { //������ ��ǥ�� x�� ����Ǿ� ���� ��, if�� ����

            Location2D now = here; //now�� ������ ��ǥ�� �����Ѵ�.
            while (!(now == entry)) { // ������ ��ǥ�� ���� ������ �ƴ� �� ó��.
                line.push(now); //��Ʈ ������ ���� ��ǥ���� push���ش�.
                now = pre[now.row][now.col]; //pre ��ġ�� �������ش�.
            }
            line.push(entry); // ��Ʈ ���ÿ� �ʱ���ǥ�� push �Ѵ�.

            while (!line.empty()) { // ��Ʈ ���ÿ� ������� ���� �� ó��
                cout << '(' << line.top().row << ',' << line.top().col << ')' << "->";
                line.pop();  // �������� ��Ʈ�� ����ϰ� pop�ϴ� ���� �ݺ��Ѵ�.
            }
            printf("�̷� Ž�� ����\n"); //����� ��ġ�� �̷� Ž���� ����.
            return 0;
        }
        else { //������ ��ǥ�� x�� ����Ǿ� ���� ���� ��, else�� ����
            map[r][c] = '.'; // �迭�� '.' ����
            if (isValidLoc(r - 1, c))
                locStack.push(Location2D(r - 1, c)), pre[r - 1][c] = here;
            //�̵� �� ��ǥ�� �����Ѵ�.
            if (isValidLoc(r + 1, c))
                locStack.push(Location2D(r + 1, c)), pre[r + 1][c] = here;
            //�̵� �� ��ǥ�� �����Ѵ�.
            if (isValidLoc(r, c - 1))
                locStack.push(Location2D(r, c - 1)), pre[r][c - 1] = here;
            //�̵� �� ��ǥ�� �����Ѵ�.
            if (isValidLoc(r, c + 1))
                locStack.push(Location2D(r, c + 1)), pre[r][c + 1] = here;
            //�̵� �� ��ǥ�� �����Ѵ�.
        }
    }

    printf("�̷� Ž�� ����\n");

    return 0;

}