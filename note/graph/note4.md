## 有向图

特点：每条边都是有方向的，从一个顶点到另一个顶点

术语：

- **指出**：⓪→① 顶点0指出顶点1
- **出度**：对于⓪→①→②  0和1 都各有一条出度
- **入度**：1 和 2 都各有一条入度
- **头**：一条有向边的第一个顶点
- **尾**：与头相反
- **有向路径**：由一系列顶点和有向边组成如⓪→①→②
- **简单有向环**：除起点和终点其它各不相同
- **长度**：包含的边数
- **达到**：当有⓪→① 则 1能由0达到
- **强连通**：对于⓪，①若存在⓪→① 的路径也存在①→⓪的路径，则称0，1强连通
- **强连通分量**：对于同一强连通分量的顶点，任一两点都强连通

### 有向图基本API

| 接口                  | 操作                          | 返回类型 |
| --------------------- | ----------------------------- | -------- |
| Digraph(int v)        | 创建一个含有V个点无边的无向图 | 构造函数 |
| V()                   | 查看顶点数                    | int      |
| E()                   | 查看边数                      | int      |
| addEdge(int v, int w) | 向图中添加一条v-w边           | int      |
| adj(int v)            | 查看v的出度                   | Bag<int> |
| reverse()             | 该图的反向图                  | Digraph  |

#### 概要

有向图的基本api和无向图的区别在于有向图有reverse()函数用于生成一张反向图，其实现也十分简单。还有一点就是adj函数变成用于查询出度。这都是由于有向图的实现方式，有向图我们依旧使用邻接表数组，但是原来的边会记录两次，分别为该边连接的两点，但有向图为了体现边的有向性，将一条有向边只记录一次，记录在指出这条边的点。既然如此，reverse函数的实现也变得简单，只需要创建一个新有向图，遍历邻接表中的每一个点的出度（也就是遍历所有有向边）并将原本的有向边的尾记录为新的头。

#### Digraph头文件

```c++
class Digraph
{
public:
    Digraph(int v);
    Digraph(const Digraph &G);
    ~Digraph() { delete[] _adj; }

    int V() { return vertex_num; };
    int E() { return edge_num; };

    void addEdge(int v, int w);
    Bag<int> adj(int v) { return _adj[v]; };

    Digraph reverse();

    Digraph &operator=(const Digraph &G);
    friend std::ostream &operator<<(std::ostream &os, const Digraph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<int> *_adj;
};
```

#### addEdge的改变

```c++
inline void Digraph::addEdge(int v, int w)
{
    for (int temp : adj(v))
        if (temp == w)
            return;
    if (v == w)
        return;
    _adj[v].add(w); // 有向图只加一边
    edge_num++;
}
```

#### reverse的实现

```c++
Digraph Digraph::reverse()
{
    Digraph reverse_digraph(vertex_num);
    for (int i = 0; i < vertex_num; i++)
        for (int v : _adj[i])
            reverse_digraph.addEdge(v, i);
    return reverse_digraph;
}
```

### 有向图算法

#### 有向图的可达性API

| 接口                          | 操作                      | 返回类型 |
| ----------------------------- | ------------------------- | -------- |
| DirectedDFS(Digraph G, int s) | 找到和起点s连通的所有顶点 | 构造函数 |
| DirectedDFS(Digraph G, Bag<int> b) | 找到和一组起点连通的所有顶点 | 构造函数 |
| marked(int v)                 | v和s(一组起点)是否连通        | bool     |


有向图的可达性也就是主要利用DFS和BFS的算法，会如同一下的有向图的寻路。

#### 有向图的寻路API
| 接口                 | 操作                               | 返回类型 |
| -------------------- | ---------------------------------- | -------- |
| Path(Digraph G, int s) | 创建一个含有V个点无边的无向图      | 构造函数 |
| hasPathTo(int v)     | 是否存在从s到v 的路径              | bool     |
| pathTo(int v)        | s到v的路径，如果不存在，返回空序列 | int      |

#### DFS

```c++
Path::Path(Digraph G, int s) : _marked(new bool[G.V()]{false}), edgeTo(new int[G.V()]), root_node(s)
{
    dfs(G, s);
}

void Path::dfs(Digraph G, int s)
{
    _marked[s] = true;
    for (int v : G.adj(s))
    {
        if (!_marked[v]){
            edgeTo[v] = s;
            _count++;
            dfs(G, v);
        }
    }
}
```

#### BFS

```c++
Path::Path(Digraph G, int s) : _marked(new bool[G.V()]{false}), edgeTo(new int[G.V()]), root_node(s)
{
    bfs(G, s);
}

void Path::bfs(Digraph G, int s)
{
    using namespace std;
    queue<int> b_que;
    _marked[s] = true;
    b_que.push(s);
    while (!b_que.empty())
    {
        int v = b_que.front();
        b_que.pop();
        for (int w : G.adj(v))
        {
            if (!_marked[w])
            {
                _marked[w] = true;
                edgeTo[w] = v;
                b_que.push(w);
                _count++;
            }
        }
    }
}

```

分析：BFS和DFS在有向图中依旧可以使用，甚至代码几乎没有什么变化，此处作为复习。同理只有BFS的实现才是最短路径。

#### 拓扑排序

情景：此时你需要为一些任务进行排序，而且，这些任务中的部分包含先后顺序的要求，例如存在任务ABCD其中D需要在A之后完成，C要在A之前完成，B要在A之后完成。此时如何排序就成为一种实际问题。

对这种问题进行抽象化，将任务抽象化为一个顶点，之间的先后要求抽象成有向边此时我们可以得到

```mermaid
graph LR
A((A))
B((B))
C((C))
D((D))

A --> D
C --> A
A --> B
```

对于以上的描述，我们得到一张十分简单的有向图，虽然此时我们能一下分辨先后，但是如果有多个顶点，任务就复杂起来。我们需要一种算法，来解决这种问题。

思考：为了确保任务的顺利完成，我们先要排除**不可处理的情况**。此时，对于可进行这种排序的有向图，它一定是无环的，若有环，例如对于任务ABC，如下图所示，根本无法进行排序。所以在解决问题之前，我们应该先排除有向环的存在。

```mermaid
graph LR
A((A))
B((B))
C((C))
A --> B
B --> C
C --> A
```

#### 寻找有向环API

#### 有向图的寻路API
| 接口                     | 操作                           | 返回类型 |
| ------------------------ | ------------------------------ | -------- |
| DirectedCycle(Digraph G) | 寻找有向环构造函数             | 构造函数 |
| hasCycle()               | G是否存在有向环                | bool     |
| cycle()                  | 有向环中的所有顶点（如果存在） | Bag<int> |

#### 头文件

```c++
class DirectedCycle
{
public:
    DirectedCycle(Digraph G);
    ~DirectedCycle(){ delete [] onStack, edgeTo;}
    bool hasCycle() { return !_cycle.isEmpty(); };
    Bag<int> cycle() { return _cycle; };

private:
    void dfs(Digraph G, int s);

    Bag<int> _cycle;
    bool *marked;
    bool *onStack;
    int *edgeTo;
};
```

思路：和无向图的搜索环类似，利用深度优先搜索，记录当前的路径，若出现重复顶点又不是根节点，即为环。此时要获取环，只需要利用edgeTo数组的链接即可。

实现：

```c++
DirectedCycle::DirectedCycle(Digraph G) : marked(new bool[G.V()]), onStack(new bool[G.V()]), edgeTo(new int[G.V()])
{
    for (int i = 0; i < G.V(); i++)
    {
        if (!marked[i])
        {
            dfs(G, i);
        }
    }
}

void DirectedCycle::dfs(Digraph G, int s)
{
    onStack[s] = true;
    marked[s] = true;
    for (int v : G.adj(s))
    {
        if (hasCycle())
            return;
        else if (!marked[v])
        {
            edgeTo[v] = s;
            dfs(G, v);
        }
        else if (onStack[v])
        {
            Bag<int> cc;
            for (int x = s; x != v; x = edgeTo[x])
                cc.add(x);
            cc.add(v);
            cc.add(s);
            _cycle = cc;
        }
    }
    onStack[s] = false;
}
```

#### 拓扑排序

解决了环的判定，此时我们就可以进入正题了，这种排序的名称为**拓扑排序**

要求：给定一有向图，将所有的顶点排序，使所有顶点只能指向排在后面的点。

示例：

```mermaid
graph TB
0((0))
1((1));2((2));3((3));4((4));5((5));6((6));7((7));8((8));9((9));10((10))
11((11));12((12))

0 --> 1; 0-->6; 0-->5;
2 --> 0; 2-->3;
3 --> 5;
5 --> 4; 6-->4;
7 --> 6; 6-->9;
9 --> 10; 9-->12; 11-->12;
9 --> 11;
8 -->7 ; 7-->6;
```

以上图的排序结果：

```mermaid
graph LR
0((8))
1((7));2((2));3((3));4((0));5((6));6((9));7((10));8((11));9((12));10((1))
11((5));12((4))
0 --> 1;1 --> 2;2 --> 3;3 --> 4;4 --> 5;5 --> 6;6 --> 7;7 --> 8;8 --> 9;9 --> 10;10 --> 11;11 --> 12;
```



