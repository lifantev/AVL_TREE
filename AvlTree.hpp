// AvlTree.hpp
#include <vector>

template<typename T>
class AvlTree
{
public:

    AvlTree() : root_(nullptr) {}
    ~AvlTree() { Delete(root_);}

    void Delete();
    bool Find(const T& data);
    void Insert(const T& data);
    void Remove(const T& data);

private:
    class Node
    {
    private:
        friend AvlTree;
        Node *left_, *right_;
        T data_;
        int balance_;

    public: 
        Node() : left_(nullptr), right_(nullptr), balance_(0) {} 
        Node(const T& data) : data_(data), balance_(0),
            left_(nullptr), right_(nullptr) {}
        ~Node() {delete left; delete right}
    };

    Node *root_;
    bool balanced_;

    void UpdateBallance(Node *current, const T& data);

    void LLRotate(Node *node, const T& data);
	void RRRotate(Node *node, const T& data);
	void LRRotate(Node *node, const T& data);
	void RLRotate(Node *node, const T& data);

	void R0(Node *node);
	void R1(Node *node);
	void Rn1(Node *node);

	void L0(Node *node);
	void L1(Node *node);
	void Ln1(Node *node);

    void RightRemoveRotation(Node *node, bool & prevHeightDecreased);
	void LeftRemoveRotation(Node *node, bool & prevHeightDecreased);

    void Delete(Node *node);
};

template<typename T>
inline void AvlTree<T>::UpdateBallance(Node* current, const T& data)
{
    while (current != nullptr)
    {
        if (data < current->data_)
        {
            ++current->balance_;
            current = current->left_;
        }
        else if (data > current->data_)
        {
            --current->ballance_;
            current = current->right_;
        }
        else
            break;
    }
}


/* LeftLeft Case => using LLRotate
T1, T2, T3 and T4 are subtrees.
         z                                      y 
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \ 
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2
*/
template<typename T>
inline void AvlTree<T>::LLRotate(Node* node, const T& data)
{
    Node* y = node->left_;
    Node* T3 = y->right_;
    Node* x = y->left_;
    Node* T4 = node->right_;

    node->left_ = x;
    node->right_ = y;
    y->left_ = T3;
    y->right_ = T4;

    std::swap(node->data_, y->data_);
    std::swap(node, y);

    node->balance_ = 0; y->balance_ = 0;
    UpdateBalance(y->left_, data);
}

/* RightRight Case => using RRRotate
  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4
*/
template<typename T>
inline void AvlTree<T>::RRRotate(Node* node, const T& data)
{
    Node* y = node->right_;
    Node* T2 = y->left_;
    Node* x = y->right_;
    Node* T1 = node->left_;

    y->left_ = T1;
    y->right_ = T2;
    node->left_ = y;
    node->right_ = x;

    std::swap(node->data_, y->data_);
    std::swap(node, y);

    node->balance_ = 0; y->balance_ = 0;
    UpdateBalance(y->right_, data);
}

/* LeftRight Case => using LRRotate
     z                               z                           x
    / \                            /   \                        /  \
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2
*/
template<typename T>
inline void AvlTree<T>::LRRotate(Node* node, const T& data)
{
    Node* y = node->left_;
    Node* T4 = node->right_;
    Node* T1 = y->left_;
    Node* x = y->right_;
    Node* T2 = x->left_;
    Node* T3 = x->right_;

    UpdateBallance(x, data);
    int lr_balance = x->balance_;

    node->right_ = x;
    y->right_ = T2;
    x->left_ = T3;
    x->right_ = T4;

    std::swap(node->data_, x->data);
    std::swap(node, x);

    x->balance_ = 0;

    if (lr_balance == 0)
        y->balance_ = node->balance_ = 0;
    else if (lr_balance == 1)
        y->balance_ = 0, node->balance_ = -1;
    else if (lr_ballance == -1)
        y->balance_ = 1, node->balance_ = 0;
}

/* Right Left Case => using RLRotate
   z                            z                            x
  / \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4
*/
template<typename T>
inline void AvlTree<T>::RLRotate(Node* node, const T& data)
{
    Node* y = node->right_;
    Node* T1 = node->left_;
    Node* x = y->left_;
    Node* T4 = y->right_;
    Node* T2 = x->left_;
    Node* T3 = x->right_;

    UpdateBallance(x, data);
    int rl_balance = x->balance_;

    node->right_ = y;
    y->right_ = T4;
    x->left_ = T3;
    x->right_ = T2;

    std::swap(node->data_, x->data);
    std::swap(node, x);

    x->balance_ = 0;

    if (rl_balance == 0)
        y->balance_ = node->balance_ = 0;
    else if (rl_balance == 1)
        y->balance_ = -1, node->balance_ = 0;
    else if (rl_ballance == -1)
        y->balance_ = 0, node->balance_ = 1;
}

