#include <stdio.h>

int bfs(int lines, int columns, int xrebeka, int yrebeka, char matriz[lines][columns]){
    int visited[lines][columns];
    for (int i = 0; i < lines; i++)
        for (int j = 0; j < columns; j++)
            visited[i][j] = 0;

    int tamanho = lines * columns;
    int qx[tamanho];
    int qy[tamanho];
    int qdist[tamanho];
    int front = 0, back = 0;

    qx[back] = xrebeka;
    qy[back] = yrebeka;
    qdist[back] = 0;
    back++;
    visited[yrebeka][xrebeka] = 1;

    while (front < back){
        int cx = qx[front];
        int cy = qy[front];
        int cd = qdist[front];
        front++;

        if (matriz[cy][cx] == 'd') return cd;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= columns || ny < 0 || ny >= lines) continue;
            if (visited[ny][nx]) continue;
            if (matriz[ny][nx] == '#') continue;

            visited[ny][nx] = 1;
            qx[back] = nx;
            qy[back] = ny;
            qdist[back] = cd + 1;
            back++;
        }
    }
    return 999999;
}

int main(void){
    int lines, columns;
    scanf("%dx%d\n", &lines, &columns);
    char matriz[lines][columns];
    int xrebeka = 0, yrebeka = 0;
    for (int i = 0; i < lines; i++){
        for (int j = 0; j < columns; j++){
            char temp;
            scanf("%c", &temp);
            matriz[i][j] = temp;
            if (temp == 'o'){
                xrebeka = j;
                yrebeka = i;
            }
        }
        char temp2; scanf("%c", &temp2);
    }
    int meters = bfs(lines, columns, xrebeka, yrebeka, matriz);
    if (meters < 999999){
        printf("Apos correr %d metros e quase desistir por causa da dist�ncia, Rebeka conseguiu escapar!\n", meters);
    } else {
        printf("Poxa... Parece que nao foi dessa vez que Rebeka conseguiu fugir\n");
    }
}
