#pragma once

#include <vector>

class AVLTree
{
    struct Node
    {
        int value;
        unsigned int height = 0;

        Node * right = nullptr;
        Node * left = nullptr;

        explicit Node(int val)
            : value(val)
        {
        }

        ~Node()
        {
            delete left;
            delete right;
        }
    };

    using NodePtr = Node *;

    NodePtr root = nullptr;

    std::size_t tree_size = 0;

    static unsigned int height_by_side(NodePtr node);
    static int sides_diff(NodePtr node);
    static void update_height(NodePtr node);

    static NodePtr rotate_left(NodePtr a);
    static NodePtr rotate_right(NodePtr a);
    static NodePtr big_rotate_left(NodePtr a);
    static NodePtr big_rotate_right(NodePtr a);

    static void balance(NodePtr & node);

    static NodePtr & find_min(NodePtr & node);
    static NodePtr & find_side_of(int value, NodePtr node);

    static void insert(int value, NodePtr & current);
    static void remove(int value, NodePtr & current);

    static void fill_values(std::vector<int> & result, NodePtr current);

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();
};
