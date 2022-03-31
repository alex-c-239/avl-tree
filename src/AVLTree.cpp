#include "AVLTree.h"

unsigned int AVLTree::height_by_side(NodePtr node)
{
    return (node == nullptr) ? (0) : (node->height + 1);
}

int AVLTree::sides_diff(NodePtr node)
{
    return (node == nullptr) ? (0) : (height_by_side(node->left) - height_by_side(node->right));
}

void AVLTree::update_height(NodePtr node)
{
    if (node != nullptr) {
        node->height = std::max(height_by_side(node->left), height_by_side(node->right));
    }
}

AVLTree::NodePtr AVLTree::rotate_left(NodePtr a)
{
    NodePtr b = a->right;
    a->right = b->left;
    update_height(a);
    b->left = a;
    update_height(b);
    return b;
}

AVLTree::NodePtr AVLTree::rotate_right(NodePtr a)
{
    NodePtr b = a->left;
    a->left = b->right;
    update_height(a);
    b->right = a;
    update_height(b);
    return b;
}

AVLTree::NodePtr AVLTree::big_rotate_left(NodePtr a)
{
    a->right = rotate_right(a->right);
    return rotate_left(a);
}

AVLTree::NodePtr AVLTree::big_rotate_right(NodePtr a)
{
    a->left = rotate_left(a->left);
    return rotate_right(a);
}

void AVLTree::balance(NodePtr & node)
{
    if (sides_diff(node) == 2 && sides_diff(node->left) >= 0) {
        node = rotate_right(node);
    }
    else if (sides_diff(node) == 2) {
        node = big_rotate_right(node);
    }
    else if (sides_diff(node) == -2 && sides_diff(node->right) <= 0) {
        node = rotate_left(node);
    }
    else if (sides_diff(node) == -2) {
        node = big_rotate_left(node);
    }
}

AVLTree::NodePtr & AVLTree::find_side_of(int value, NodePtr node)
{
    return (node->value > value) ? (node->left) : (node->right);
}

AVLTree::NodePtr & AVLTree::find_min(NodePtr & node)
{
    if (node == nullptr || node->left == nullptr) {
        return node;
    }
    return find_min(node->left);
}

bool AVLTree::contains(int value) const
{
    NodePtr current = root;
    while (current != nullptr && current->value != value) {
        current = find_side_of(value, current);
    }
    return current != nullptr;
}

void AVLTree::insert(int value, NodePtr & current)
{
    if (current == nullptr) {
        current = new Node(value);
        return;
    }
    insert(value, find_side_of(value, current));
    update_height(current);
    balance(current);
}

bool AVLTree::insert(int value)
{
    if (contains(value)) {
        return false;
    }
    insert(value, root);
    tree_size++;
    return true;
}

void AVLTree::remove(int value, NodePtr & current)
{
    if (current->value != value) {
        remove(value, find_side_of(value, current));
    }
    else {
        if (current->left != nullptr && current->right != nullptr) {
            current->value = find_min(current->right)->value;
            remove(current->value, current->right);
        }
        else {
            NodePtr current_old = current;
            current = (current->left == nullptr) ? (current->right) : (current->left);
            current_old->right = current_old->left = nullptr;
            delete current_old;
        }
    }
    update_height(current);
    balance(current);
}

bool AVLTree::remove(int value)
{
    if (!contains(value)) {
        return false;
    }
    remove(value, root);
    tree_size--;
    return true;
}

std::size_t AVLTree::size() const
{
    return tree_size;
}

bool AVLTree::empty() const
{
    return tree_size == 0;
}

void AVLTree::fill_values(std::vector<int> & result, NodePtr current)
{
    if (current == nullptr) {
        return;
    }
    fill_values(result, current->left);
    result.push_back(current->value);
    fill_values(result, current->right);
}

std::vector<int> AVLTree::values() const
{
    std::vector<int> result;
    result.reserve(tree_size);
    fill_values(result, root);
    return result;
}

AVLTree::~AVLTree()
{
    delete root;
}
