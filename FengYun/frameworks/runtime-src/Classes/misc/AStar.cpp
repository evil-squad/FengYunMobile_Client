/**
 * @file  AStar.cpp
 * @project  FengYun
 * @author Bluce Nong <nongjinxia@mokylin.com>
 * @Created by BluceNong on 2017/2/2.
 * @  Copyright © 2017年 MokyLin  Bluce Nong <nongjinxia@mokylin.com>. All rights reserved.
*/

#include "AStar.h"
#include "MinHeap.h"
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

namespace
{
    struct Node
    {
        int id;
        int F, G, H;
        struct Node* parent;

        Node() : id(0), F(0), G(0), H(0), parent(nullptr) {}

        void reset()
        {
            id = 0;
            F = 0;
            G = 0;
            H = 0;
            parent = nullptr;
        }
    };

    class NodePool
    {
    public:
        NodePool() { addPage(); }
        NodePool(int capacity) { addPage(capacity); }
        ~NodePool()
        {
            for (auto p: _datas) delete[] p;
        }

        Node* alloc()
        {
            if (_frees.empty()) addPage();
            Node* n = _frees.front();
            _frees.pop();
            return n;
        }

        void release(Node* p)
        {
            p->reset();
            _frees.push(p);
        }

    private:
        std::vector<Node*> _datas;
        std::queue<Node*> _frees;

        void addPage(int size = 20)
        {
            Node* buf = new Node[size];
            _datas.push_back(buf);
            for (int i=0; i<size; ++i)
                _frees.push(buf + i);
        }
    };

    class NodePtr
    {
    public:
        NodePtr() : _node(nullptr) {}
        NodePtr(Node* n) : _node(n) {}

        int key() const { return _node->id; }

        bool valid() const { return _node != nullptr; }

        Node* ptr() { return _node; }

        Node* operator-> ()
        {
            return _node;
        }

        bool operator == (const NodePtr& other)
        {
            return _node == other._node;
        }

        bool operator < (const NodePtr& other)
        {
            return _node->F < other._node->F;
        }

    private:
        Node* _node;
    };
}

struct AStarData_t
{
    NodePool pool;
    std::unordered_map<int, Node*> nodes;
    MinHeap<NodePtr> opened;
    std::unordered_set<int> closed;
};

AStar::AStar()
{
    _data = new AStarData_t;
}
AStar::~AStar()
{
    delete _data;
}

using namespace std;

static Node* getNode(AStarData_t* data, int id)
{
    auto iter = data->nodes.find(id);
    if (iter != data->nodes.end()) return iter->second;
    Node* n = data->pool.alloc();
    n->id = id;
    data->nodes[id] = n;
    return n;
}

static void releaseData(AStarData_t* data)
{
    for (auto iter: data->nodes)
    {
        data->pool.release(iter.second);
    }
    data->nodes.clear();
    data->opened.clear();
    data->closed.clear();
}

bool AStar::searchPath(int start, int end, std::vector<int>& path, Calculator& calc)
{
    if (start == end) return false;

    MinHeap<NodePtr>& opened = _data->opened;
    unordered_set<int>& closed = _data->closed;

    opened.push(getNode(_data, start));

    NodePtr cur;
    int id, cost, idx, G;
    Node* n;
    bool found = false;
    while (!opened.empty())
    {
        cur = opened.pop();
        closed.insert(cur->id);

        const vector<pair<int, int> >& links = calc.getLinks(cur->id);
        for (auto& l: links)
        {
            id = l.first;
            cost = l.second;

            if (id == end)
            {
                n = getNode(_data, id);
                n->parent = cur.ptr();
                cur = n;
                found = true;
                break;
            }

            if (closed.count(id))
                continue;

            idx = opened.findByKey(id);
            if (idx == -1)
            {
                n = getNode(_data, id);
                n->G = cur->G + cost;
                n->H = calc.calculateH(id, end);
                n->F = n->G + n->H;
                n->parent = cur.ptr();
                opened.push(n);
            }
            else
            {
                n = opened.at(idx).ptr();
                G = cur->G + cost;
                if (n->G > G)
                {
                    n->G = G;
                    n->F = n->G + n->H;
                    n->parent = cur.ptr();
                    opened.resort(idx);
                }
            }
        }

        if (found) break;
    }

    bool ret = false;

    if (found)
    {
        n = cur.ptr();
        while (n)
        {
            path.push_back(n->id);
            n = n->parent;
        }
        
        reverse(path.begin(), path.end());
        ret = true;
    }
    
    releaseData(_data);
    return ret;
}

