#include <Windows.h>

#include <cstring>
#include <fstream>
#include <iostream>

int n, m, row, column, table[10][10];
bool set[10][10];

void read() {
    std::ifstream f("data.txt");
    f >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            f >> table[i][j];
            if (table[i][j])
                set[i][j] = true;
        }
    f.close();
}

void init() {
    table[row][column] = 0;
}

int successor() {
    if (table[row][column] < 9) {
        table[row][column]++;
        return table[row][column];
    }
    return 0;
}

bool solution() {
    for (int j = column + 1; j < m; j++)
        if (set[row][j] == 0)
            return 0;

    for (int i = row + 1; i < n; i++)
        for (int j = 0; j < m; j++)
            if (set[i][j] == 0)
                return 0;
    
    return 1;
}

void output() {
    std::ofstream g("output.txt");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            g << table[i][j] << ' ';
        g << '\n';
    }
    g.close();
}

bool valid() {
    if (row > 0 || column > 0) {
        for (int i = 0; i < row; i++)
            if (table[i][column] == table[row][column])
                return 0;

        for (int i = n - 1; i > row; i--)
            if (table[i][column] == table[row][column])
                return 0;

        for (int j = 0; j < column; j++)
            if (table[row][j] == table[row][column])
                return 0;

        for (int j = m - 1; j > column; j--)
            if (table[row][j] == table[row][column])
                return 0;

        for (int i = row - row % 3; i < row - row % 3 + 3; i++)
            for (int j = column - column % 3; j < column - column % 3 + 3; j++)
                if (i != row || j != column)
                    if (table[i][j] == table[row][column])
                        return 0;
    }
    return 1;
}
void bk() {
    row = 0;
    column = 0;
    int AS;
    while (set[row][column]) {
        if (column < m)
            column++;
        else {
            row++;
            column = 0;
        }
    }
    while (row > -1) {
        do  // successor is searched on the k level as long there still are successors and a valid one wasn't found
        {
            AS = successor();
        } while (AS && !valid());
        if (AS)  // successor exists and is valid
            if (solution()) {
                output();  // writes the solution
                return;
            } else {  // stack incomplete
                do {
                    if (column < m - 1)
                        column++;
                    else {
                        row++;
                        column = 0;
                    }
                } while (set[row][column] && row < n);
                if (row == n) {
                    std::cout << "Eee\n";
                }
                init();
            }
        else {
            init();
            do {
                if (column > 0)
                    column--;
                else {
                    row--;
                    column = m - 1;
                }
            } while (set[row][column] && row > -1);
        }
    }
}

int main(int argc, char *argv[]) {
    read();
    bk();
    return 0;
}