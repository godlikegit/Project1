#include "inc.h"


template<class ID>
class Rank
{
    struct Node
    {
        int score = 0;
        ID id = 0;
        Node* pre = nullptr;
        Node* next = nullptr;
    };
    unordered_map<ID, Node*> m;
    Node* head = nullptr;
    Node* tail = nullptr;
    vector<Node> nodes;
    int used_size = 0;

public:
    // ?
    Rank(int n) {
        head = new Node;
        tail = new Node;
        nodes.resize(n);
    }

    Node* createNode(int score, ID id) {
        if (nodes.size() == used_size) {
            return tail;
        }
        Node* node = &nodes[used_size++];
        node->score = score;
        node->id = id;
        return node;
    }
public:
    //get score
    int getScoreById(ID id);
    int getScoreByRank(int rank);

    //get id
    ID getIdByRank(int rank);
    vector<ID> getIdByScore(int score1, int score2);
    ID getFirstIDByScore(int score);
    //get rank
    int getRankById(ID id);

    void swapNode(Node* l, Node* r) {
        if (l == r) {
            return;
        }
        //相邻节点
        if (l == r->pre) {
            r->next->pre = l;
            l->next = r->next;
            l->pre->next = r;
            r->pre = l->pre;
            r->next = l;
            l->pre = r;
        }
        else {
            Node* r_pre = r->pre;
            Node* l_pre = l->pre;
            Node* r_next = r->next;
            Node* l_next = l->next;

            l_pre->next = r;
            l_next->pre = r;
            r->pre = l_pre;
            r->next = l_next;

            r_pre->next = l; 
            r_next->pre = l;
            l->pre = r_pre;
            l->next = r_next;
        }
    }

    void insertNode(Node* s, Node* t, bool preNotNext) {
        if (s == t) return;
        //将s插到t前面
        if (preNotNext) {
            //相邻节点
            if (t->next == s) { // t<->s
                t->pre->next = s;
                s->pre = t->pre;
                t->next = s->next;
                s->next->pre = t;
                s->next = t;
                t->pre = s;
            }
            else {

            }
        }
        //将s插到t后面
        else {
            //相邻节点
            if (t->pre == s) { //s<->t

            }
            else {

            }
        }
    }
    void judgePre(Node* s) {
        //向前挪
        Node* t = s;
        while (t->pre != head && s->score > t->pre->score) {
            t = t->pre;
        }
        //插入到t的前面
        insertNode(s, t, true);
    }
    void judgeNext(Node* s) {
        //向后挪
        Node* t = s;
        while (t->next != tail && s->score < t->next->score) {
            t = t->next;
        }
        //插入到t的后面
        insertNode(s, t, false);
    }

    void insert(int score, ID id)
    {
        if (nullptr == head->next) {
            Node* c = createNode(score, id);
            if (nullptr == c) return;

            head->next = c;
            c->pre = head;
            tail->pre = c;
            c->next = tail;

            m.insert({ id, head->next });
            return;
        }

        //不在榜里
        if (m.find(id) == m.end()) {
            Node* p = createNode(score, id);
            //榜满员了
            if (tail == p) {
                //与最后一名作比较
                p = tail->pre;
                if (score < p->score) {
                    //积分不够入榜
                    return;
                }
                //替换掉最后一名
                p->score = score;
                p->id = id;

                judgePre(p);
            }
            else {
                //加入到最后一名
                tail->pre->next = p;
                p->pre = tail->pre;
                p->next = tail;
                tail->pre = p;

                judgePre(p);
            }

            m.insert({ id, p });
            return;
        }

        Node* p = m[id];
        if (score < p->score) {
            p->score = score;
            judgeNext(p);
        }
        else if (score > p->score) {
            p->score = score;
            judgePre(p);
        }
        else {
            //积分无变化不做调整
        }

        //Node* p = m[id];
        //if (score < p->score) {
        //    Node* c = p;
        //    while (nullptr != c->next && score < c->next->score) {
        //        c = c->next;
        //    }
        //    if (c == p) {
        //        p->score = score;
        //    }
        //    else {
        //        p->pre->next = p->next;
        //        if (nullptr != p->next) p->next->pre = p->pre;
        //        c->pre->next = p;
        //        p->pre = c->pre;
        //        c->pre = p;
        //        p->next = c;
        //    }
        //}
        //else if (score > p->score) {
        //    Node* c = p;
        //    while (head != c->pre && score > c->score) {
        //        c = c->pre;
        //    }
        //    if (c == p) {
        //        p->score = score;
        //    }
        //    else {
        //        p->pre->next = p->next;
        //        if (nullptr != p->next) p->next->pre = p->pre;
        //
        //        if (nullptr != c->next) c->next->pre = p;
        //        p->next = c->next;
        //        c->pre->next = p;
        //        p->pre = c->pre;
        //    }
        //}
    }

    void erase(int id)
    {

    }

    void print()
    {
        Node* p = head->next;
        while (nullptr != p)
        {
            printf("%d, %d\n", p->score, p->id);
            p = p->next;
        }
        printf("\n");
    }

};


void mysort()
{
    int arr[4] = { 1334,1173,1158,1571 };
    for (int i = 1; i < 4; ++i)
    {
        for (int j = i - 1; j >= 0 && arr[j] < arr[j + 1]; --j)
        {
            int t = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = t;
        }
    }

    int a = 1;
}

int main() {
    mysort();

    Rank<int> r(10);
    r.insert(8, 1);
    r.insert(2, 2);
    r.insert(5, 3);
    r.insert(9, 4);
    r.insert(3, 5);
    r.print();

    r.insert(6, 5);
    r.print();

    return 0;
}


//if (c == p) {
       //    return;
       //}
       //if (c == p->pre) { //相邻节点
       //    p->next->pre = c;
       //    c->next = p->next;
       //    c->pre->next = p;
       //    p->pre = c->pre;
       //    p->next = c;
       //    c->pre = p;
       //}
       //else {
       //    Node* p_pre = p->pre;
       //    Node* c_pre = c->pre;
       //    Node* p_next = p->next;
       //    Node* c_next = c->next;
       //
       //    c_pre->next = p;
       //    c_next->pre = p;
       //    p->pre = c_pre;
       //    p->next = c_next;
       //
       //    p_pre->next = c;
       //    p_next->pre = c;
       //    c->pre = p_pre;
       //    c->next = p_next;
       //}