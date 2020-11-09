// AvlTree.hpp
#include <vector>

template<typename T>
class AvlTree
{
public:

    AvlTree() : root_(nullptr) {}
    AvlTree(const T& data);
    ~AvlTree() { Delete(root_);}

    void Delete();
    bool Find(const T& data);
    void Insert(const T& data);
    void Remove(const T& data);

private:
    class Node
    {
    private:
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

    void LLRotation(Node *node, const T& k);
	void RRRotation(Node *node, const T& k);
	void LRRotation(Node *node, const T& k);
	void RLRotation(Node *node, const T& k);

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
