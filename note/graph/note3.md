### 无向图基本API

| 接口                  | 操作                          | 返回类型 |
| --------------------- | ----------------------------- | -------- |
| Graph(int v)          | 创建一个含有V个点无边的无向图 | 构造函数 |
| V()                   | 查看顶点数                    | int      |
| E()                   | 查看边数                      | int      |
| addEdge(int v, int w) | 向图中添加一条v-w边           | int      |
| adj(int v)            | 查看v相邻的点                 | Bag<int> |

#### 数据类型

对于无向图的数据类型，我们选用邻接表数组。邻接表数组即一个数组内的每个元素维护一个bag对象，由于c++没有Bag对象，我们将进行定义。Bag对象的特点类似于链表，可以不断添加，但Bag不能删除元素，因为基本api并不要求删除，若要求，可以换个类型例如链表。

#### Undigraph头文件

```c++
// 代码中Undigraph显示为Graph
class Graph
{
public:
    Graph(int v);
    Graph(const Graph &G);
    ~Graph() { delete[] _adj; }

    int V() { return vertex_num; };
    int E() { return edge_num; };

    void addEdge(int v, int w);
    Bag<int> adj(int v) {return _adj[v];} ;
 
    Graph &operator=(const Graph &G);
    friend std::ostream &operator<<(std::ostream &os, const Graph &G);

private:
    int vertex_num;
    int edge_num;
    Bag<int> *_adj;
};
```

分析：对于邻接表数组，添加边的操作，时间复杂度为O(1)。adj()函数实现也只需要查看对应数组内的Bag内容即可。优点：性能好 缺点：内存占用大。



