#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int MAX_N = 110;

int N;
bool A[MAX_N][MAX_N];
vector<int> B[MAX_N];  // A^-
int tag[MAX_N];
int count[2 * MAX_N];
bool choice[MAX_N][MAX_N];
bool tagMap[2 * MAX_N];
vector<int> output[2];

bool dfs(int start, int tree_id, bool color) {
    if (tag[start] > 0) {
        return tag[start] == 2 * tree_id + int(color) - 1;
    }

    tag[start] = 2 * tree_id + int(color) - 1;
    count[tag[start]]++;
    for (int i = 0; i < B[start].size(); i++) {
        if (!dfs(B[start][i], tree_id, !color))
            return false;
    }

    return true;
}


int main() {
    scanf("%d", &N);
    memset(A, 0, N * MAX_N * sizeof(bool));

    int i = 0;
    int a;
    while (i < N) {
        scanf("%d", &a);
        if (a == 0)
            i++;
        else
            A[i][a - 1] = true;
    }

    for (i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (!A[i][j] || !A[j][i]) {
                B[i].push_back(j);
                B[j].push_back(i);
            }
        }
    }

    memset(tag, 0, N * sizeof(int));
    memset(count, 0, (N + 1) * 2 * sizeof(int));

    int ans = 0;
    int tree_id = 1;
    for (i = 0; i < N; i++) {
        if (tag[i] == 0) {
            if (!dfs(i, tree_id, false)) {
                ans = -1;
                break;
            }
            tree_id++;
        }
    }

    if (ans < 0)
        printf("No solution");
    else {
        int num_set = tree_id - 1;
        memset(A, 0, (num_set + 1) * MAX_N * sizeof(bool));
        memset(choice, 0, (num_set + 1) * MAX_N * sizeof(bool));
        A[0][0] = true;
        for (i = 1; i <= num_set; i++) {
            for (int j = 0; j <= N; j++) {
                if (j - count[2 * i - 1] >= 0 && A[i - 1][j - count[2 * i - 1]]) {
                    A[i][j] = true;
                    choice[i][j] = false;
                }
                else if (j - count[2 * i] >= 0 && A[i - 1][j - count[2 * i]]) {
                    A[i][j] = true;
                    choice[i][j] = true;
                }
            }
        }

        for (i = (N + 1) / 2; i >= 0; i--) {
            if (A[num_set][i]) {
                break;
            }
        }
        
        for (int j = num_set; j > 0; j--) {
            tagMap[2 * j - 1 + int(choice[j][i])] = true;
            tagMap[2 * j - 1 + int(!choice[j][i])] = false;
            i -= count[2 * j - 1 + int(choice[j][i])];
        }

        for (i = 1; i <= N; i++) {
            output[int(tagMap[tag[i - 1]])].push_back(i);
        }
        
        if (output[0].size() == 0 || output[1].size() == 0)
            printf("No solution");
        else {
            for (int i = 0; i < 2; i++) {
                printf("%d", int(output[i].size()));
                for (int j = 0; j < output[i].size(); j++) {
                    printf(" %d", output[i][j]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}
