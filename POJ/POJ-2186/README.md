# [POJ-2186](https://vjudge.net/problem/POJ-2186)

## 解法

本题要求的是有向图中所有结点都能到达的点。

本体的解法是先将强连通量缩点，然后再得到无环分量图上计算出度为0的点（只算缩点后的点即强连通量）的个数，如果有多个点出度都为0则说明图不连通，不存在所有点都能到达的点。如果点的出度和入度都为0，除只有一个强连接通量的情况，都是图不连通的情况，也不存在所有点都能到达的点。最终结果为出度为0的强连通量里的结点数。
