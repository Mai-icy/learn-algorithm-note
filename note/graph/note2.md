### 探究：union-find算法

连通分量：处于同一连通分量的点相互连通。

### 算法API


|  接口  | 操作  | 返回类型 |
|  ----  | ----  | ----  |
| connect(int w, int v) | 连接 w，v点       |void|
| find(int v) | 查看v点的连通分量 | int |
| connected(int w, int v) | 查看w和v是否连通 | bool |
| count() | 查看连通分量的数量 | int      |

#### UF头文件

```c++
class UF
{
public:
    UF(int n);
    UF(const UF &uf);
    ~UF() { delete[] id; }

    virtual void connect(int w, int v);
    virtual int find(int v) const;
    bool connected(int w, int v) const { return find(w) == find(v); };
    int count() const { return _count; };

    UF &operator=(const UF &uf);
    friend std::ostream &operator<<(std::ostream &os, const UF &uf);

protected:
    int size;
    int _count;
    int *id = nullptr;
};
```

#### quick-find算法：

目的：实现find的高效

实现：维护数组id，点在id对应的值即为改点的连通分量。

```c++
inline int UF::find(int v) const { return id[v]; }

void UF::connect(int w, int v)
{
    int w_id = id[w];
    int v_id = id[v];
    if (w_id == v_id)
        return;
    for (int i = 0; i < size; i++)
    {
        if (id[i] == w_id)
            id[i] = v;
        _count--;
    }
}
```

connect操作为找到两点的连通分量，遍历数组，将两个连通分量的元素值统一。

分析：实现find的高效会导致connect函数的连接操作变的复杂。find操作的时间复杂度成功降到O(1)，但connect的操作由于要遍历一遍数组，时间复杂度也达到O(N)。

#### quick-union算法

目的：实现connect的高效

实现：维护数组id，整个数据结构成为树状，每个连通分量为一颗树，每颗树的根节点即为该树的连通分量值。此时若要connect，只需要把连接的一点连向另一点即可（连接之前确保两点不在同一连通分量）

```c++
int UF::find(int v) const
{
    while (v != id[v])
        v = id[v];
    return v;
}

void UF::connect(int w, int v)
{
    int w_id = find(w);
    int v_id = find(v);
    if (w_id == v_id)
        return;
    id[w] = v;
    _count--;
}
```

分析：同样，为了实现connect的高效，find操作的效率也有所牺牲。在一些最坏情况下，一棵树可能深度很大，就会导致效率很低。为了优化，提出了加权quick-union算法，在两个连通分量连接的时候，为了避免造出一颗深度很大的树，加权quick-union算法确保小树添加在大树上。

#### 加权quick-union算法

目的：quick-union算法在坏情况下的低效率

实现：额外维护数组size，size存放了每个连通分量对应的树的深度，并以此为依据，保证两树连接的时候，深度小的树连接在深度大的树上。

```c++
int WUF::find(int v) const
{
    int ori_p = v;
    while (v != id[v])
        v = id[v];
    return v;
}

void WUF::connect(int w, int v)
{
    int w_id = find(w);
    int v_id = find(v);
    if (w_id == v_id)
        return;
    if (sz[w] < sz[v])
    {
        id[w] = v;
        sz[v] += sz[w];
    }
    else
    {
        id[v] = w;
        sz[w] += sz[v];
    }
    _count--;
}
```

分析：维护了数组sz，用额外的空间复杂度换取了时间复杂度的降低。但加权quick-union算法仍然有进步空间。

#### 路径压缩的加权quick-union算法

目的：更加优化加权quick-union算法

实现：实现及其简单，在确保connect高效的情况下，提高find的效率，只需要在每次find的时候，将被搜索的点直接连接到其树的根节点，在多次find之后便可以减小树的深度。

```c++
int WUF::find(int v) const
{
    int ori_p = v;
    while (v != id[v])
        v = id[v];
    id[ori_p] = v; // 路径压缩
    return v;
}
```

分析：虽然看起来十分简单粗暴，但是在实际测试使用中，确实会达到更加高效的效果。



