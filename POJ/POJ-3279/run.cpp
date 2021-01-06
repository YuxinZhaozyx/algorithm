#include <cstdio>
#include <cstring>

const int MAX_N = 17;

int M, N;

int tile[MAX_N];
int buf[MAX_N];


int trySolution(int firstLine) {
    buf[0] = firstLine;
    int mask = (1 << N) - 1;
    for (int i = 0; i < M; i++) {
        buf[i + 1] ^= ((buf[i] << 1) ^ buf[i] ^ (buf[i] >> 1)) & mask;
        buf[i + 2] ^= buf[i];
    }

    int times = 0;

    if (buf[M] == 0) {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                times += (buf[i] >> j) & 1;
            }
        }
    }
    else
        times = -1;

    return times;
}


int main() {
    int a;

    scanf("%d%d", &M, &N);

    memset(tile, 0, (M + 2) * sizeof(int));
    for (int i = 1; i <= M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &a);
            tile[i] = tile[i] << 1 | a;
        }
    }

    int minTimes = M * N + 1;
    int bestFirstLine = -1;
    int times;
    for (int i = 0; i < (1 << N); i++) {
        memcpy(buf, tile, (M + 2) * sizeof(int));
        times = trySolution(i);
        if (times >= 0 && times < minTimes) {
            bestFirstLine = i;
            minTimes = times;
        }
    }

    if (bestFirstLine < 0)
        printf("IMPOSSIBLE");
    else {
        memcpy(buf, tile, (M + 2) * sizeof(int));
        trySolution(bestFirstLine);
        for (int i = 0; i < M; i++) {
            for (int j = N - 1; j >= 0; j--) {
                if (j == 0)
                    printf("%d\n", (buf[i] >> j) & 1);
                else
                    printf("%d ", (buf[i] >> j) & 1);
            }
        }
    }

    return 0;
}
