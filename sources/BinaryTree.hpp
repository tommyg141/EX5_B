#pragma once
/*
# some of algoritems ideas taken from geaksforgeaks site
#the idea of itrator was learn and was improve to this suolstion from leacter 8 "skt"
#smart pointers was in lectecer 12 
$$ the add left and right was build before itrators so i use the inorder algoritem to move on the tree
**Tommy mordehay goroh
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
using namespace std;
namespace ariel
{

    template <typename T>
    class BinaryTree
    {
        struct Node
        {
            T m_value;
            Node *left;
            Node *right;
            Node *parent;
            Node(const T &v, Node *left = nullptr, Node *right = nullptr, Node *parent = nullptr)
                : m_value(v), left(left), right(right), parent(parent)
            {
            }
        };
        Node *root;

    public:
        BinaryTree()
        {
            this->root = nullptr;
        }
        BinaryTree(const BinaryTree &other)
        {
            if (other.root != nullptr)
            {
                root = new Node(other.root->m_value);
                deep_cp(other.root, root);
            }
        }
        void deep_cp(const Node *n1, Node *n2)
        {
            if (n1->left != nullptr)
            {
                n2->left = new Node(n1->left->m_value);
                deep_cp(n1->left, n2->left);
            }
            if (n1->right != nullptr)
            {
                n2->right = new Node(n1->right->m_value);
                deep_cp(n1->right, n2->right);
            }
        }
        BinaryTree(BinaryTree &&other) noexcept
        {
            root = other.root;
            other.root = nullptr;
        }
        BinaryTree &operator=(BinaryTree &&n1) noexcept
        {
            if (this != &n1)
            {
                del(this->root);
                this->root = n1.root;
                n1.root = nullptr;
            }
            return *this;
        }
        BinaryTree &operator=(const BinaryTree n)
        {
            if (this != &n)
            {
                del(this->root);
                this->root = new Node(n.root->m_value);
                deep_cp(n.root, root);
            }
            return *this;
        }

        //move build
        //"=" for move
        //"=" deep copy

        ~BinaryTree()
        {
            del(root);
        };
        void del(Node *root)
        {
            if (root != nullptr)
            {
                del(root->right);
                del(root->left);
            }
            delete root;
        }
        BinaryTree &add_root(const T &root_value)
        {
            if (this->root == nullptr)
            {
                this->root = new Node(root_value);
            }
            else
            {

                this->root->m_value = root_value;
            }
            return *this;
        }
        BinaryTree &add_left(const T &parent, const T &left)
        {
            if (this->root == nullptr)
            {
                throw("no tree");
            }
            stack<Node *> s;
            Node *curr = root;

            while (curr != NULL || s.empty() == false)
            {
                while (curr != NULL)
                {
                    s.push(curr);
                    curr = curr->left;
                }
                curr = s.top();
                if (curr->m_value == parent)
                {
                    if (curr->left == nullptr)
                    {
                        curr->left = new Node(left);
                    }
                    else
                    {
                        curr->left->m_value = left;
                    }
                    return *this;
                }
                s.pop();
                curr = curr->right;
            }

            throw("not have the corrent node");
        }
        BinaryTree &add_right(const T &parent, const T &right)
        {
            if (this->root == nullptr)
            {
                throw("no tree");
            }
            stack<Node *> s;
            Node *curr = root;

            while (curr != NULL || s.empty() == false)
            {
                while (curr != NULL)
                {
                    s.push(curr);
                    curr = curr->left;
                }
                curr = s.top();
                if (curr->m_value == parent)
                {
                    if (curr->right == nullptr)
                    {
                        curr->right = new Node(right);
                    }
                    else
                    {
                        curr->right->m_value = right;
                    }
                    return *this;
                }
                s.pop();
                curr = curr->right;
            }

            throw("not have the corrent node");
        }
        friend std::ostream &operator<<(std::ostream &os, const BinaryTree<T> &binaryTree) { return os; }

        class preorder
        {

        private:
            Node *point_pre;
            stack<Node *> s;

        public:
            preorder(Node *ptr = nullptr)
                : point_pre(ptr)
            {
                if (ptr != nullptr)
                {
                    s.push(ptr);
                    point_pre = ptr;
                }
                else
                {
                    point_pre = nullptr;
                }
            }

            T &operator*() const
            {
                return point_pre->m_value;
            }

            T *operator->() const
            {
                return &(point_pre->m_value);
            }

            preorder &operator++()
            {
                if (!s.empty())
                {

                    s.pop();
                    if (point_pre->right)
                    {
                        s.push(point_pre->right);
                    }
                    if (point_pre->left)
                    {
                        s.push(point_pre->left);
                    }
                }
                if (s.empty())
                {
                    point_pre = nullptr;
                }
                else
                {
                    point_pre = s.top();
                }
              
                return *this;
            }

            preorder operator++(int)
            {
                preorder tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const preorder &rhs) const
            {
                return point_pre == rhs.point_pre;
            }

            bool operator!=(const preorder &rhs) const
            {
                return point_pre != rhs.point_pre;
            }
        }; // END OF CLASS ITERATOR
        preorder begin_preorder()
        {
            return preorder{root};
        }

        preorder end_preorder()
        {
            return preorder{};
        }
        class inorder
        {

        private:
            Node *point;
            stack<Node *> s;

        public:
            inorder(Node *ptr = nullptr) : point(ptr)
            {

                Node *temp = point;
                while (temp != nullptr)
                {
                    s.push(temp);
                    temp = temp->left;
                }
                if (s.empty())
                {
                    point = nullptr;
                }
                else
                {
                    point = s.top();
                }
            }

            T &operator*() const
            {

                return point->m_value;
            }

            T *operator->() const
            {
                return &(point->m_value);
            }

            inorder &operator++()
            {
                if (!s.empty())
                {

                    Node *curr = s.top(); //2
                    s.pop();              //3
                    if (curr->right != nullptr)
                    {
                        s.push(curr->right);
                        curr = curr->right;
                        while (curr->left != nullptr)
                        {

                            curr = curr->left;
                            s.push(curr);
                        }
                    }
                    if (s.empty())
                    {
                        this->point = nullptr;
                    }
                    else
                    {
                        this->point = s.top();
                    }
                }
                else
                {
                    this->point = nullptr;
                }
                return *this;
            }

            inorder operator++(int)
            {

                inorder temp = *this;
                ++*this;
                return temp;
            }

            bool operator==(const inorder &rhs) const
            {
                return point == rhs.point;
            }

            bool operator!=(const inorder &rhs) const
            {
                return point != rhs.point;
            }
        };
        inorder begin_inorder()
        {
            return inorder{root};
        }
        inorder end_inorder()
        {
            // return nullptr;
            return inorder{nullptr};
        }
        class postorder
        {

        private:
            Node *point;
            // stack<Node *> s;
            stack<Node *> stk1;

        public:
            postorder(Node *ptr = nullptr)
            {
                point = ptr;
                if (point != nullptr)
                {
                    stack<Node *> only_for_start;
                    only_for_start.push(point);
                    while (!only_for_start.empty())
                    {
                        Node *temp = only_for_start.top();
                        only_for_start.pop();
                        stk1.push(temp);
                        if (temp->left != nullptr)
                        {
                            only_for_start.push(temp->left);
                        }
                        if (temp->right != nullptr)
                        {
                            only_for_start.push(temp->right);
                        }
                    }
                    this->point = stk1.top();
                    //            stk1.pop();
                }
                else
                {
                    this->point = nullptr;
                }
                // while (!stk1.empty()){
                //      cout<<stk1.top()->m_value<<endl;
                //      stk1.pop();
            }

            T &operator*() const
            {

                return point->m_value;
            }

            T *operator->() const
            {
                return &(point->m_value);
            }

            postorder &operator++()
            {

                if (point != nullptr)
                {
                    if (!stk1.empty())
                    {
                        stk1.pop();
                        if (!stk1.empty())
                        {
                            point = stk1.top();
                        }
                        else
                        {
                            point = nullptr;
                        }
                    }
                    else
                    {
                        point = nullptr;
                    }
                }
                return *this;
            }

            postorder operator++(int)
            {
                postorder tmp = *this;
                ++*this;
                return tmp;
            }

            bool operator==(const postorder &rhs) const
            {
                return point == rhs.point;
            }

            bool operator!=(const postorder &rhs) const
            {
                return point != rhs.point;
            }
        };
        postorder begin_postorder()
        {
            return postorder{root};
        }
        postorder end_postorder()
        {
            // return nullptr;
            return postorder{};
        }
        inorder begin()
        {
            return begin_inorder();
        };
        inorder end()
        {
            return end_inorder();
        };

    }; // end of binarytee
};
