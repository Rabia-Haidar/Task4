#include <iostream>
#include <queue>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

TreeNode* add(TreeNode* root, int val) {
    if (root == nullptr) {
        return new TreeNode(val);
    }
    if (val < root->value) {
        root->left = add(root->left, val);
    } else {
        root->right = add(root->right, val);
    }
    return root;
}

void populate_tree(TreeNode*& root, int* data, int size) {
    for (int i = 0; i < size; i++) {
        root = add(root, data[i]);
        cout << data[i] << " Inserted into the BST" << endl;
    }
}

void postOrder(TreeNode* root, int* result, int& i) {
    if (root == nullptr){ 
        return; 
        } else{
    postOrder(root->left, result, i);
    postOrder(root->right, result, i);
    result[i++] = root->value;
    }
}

void preOrder(TreeNode* root, int* result, int& i) {
    if (root == nullptr) {
        return;
        } else{
    result[i++] = root->value;
    preOrder(root->left, result, i);
    preOrder(root->right, result, i);
    }
}

class MinHeap {
private:
    int* heap;
    int size;
    int capacity;
    public:

    MinHeap(int c) : capacity(c), size(0) {
        heap = new int[capacity];
    }

    void heapify_up(int i) {
        while (i > 0 && heap[i] < heap[(i - 1) / 2]) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void heapify_down(int i) {
        int smallest = i;
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;

        if (left_child < size && heap[left_child] < heap[smallest]) {
            smallest = left_child;
        }

        if (right_child < size && heap[right_child] < heap[smallest]) {
            smallest = right_child;
        }

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify_down(smallest);
        }
    }

    void insert(int val) {
        if (size == capacity) {
            return;
            } else{ 
        heap[size++] = val;
        heapify_up(size - 1);
        }
    }

    void buildHeap(int* val, int n) {
        for (int i = 0; i < n; i++) {
            heap[i] = val[i];
        }
        size = n;
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify_down(i);
        }
    }

    void display() {
        for (int i = 0; i < size; i++) {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int data[] = {55, 78, 87, 25, 28, 56, 2, 99, 41, 13, 9, 1, 70, 16, 79};
    int size = sizeof(data) / sizeof(data[0]);

    TreeNode* root = nullptr;
    populate_tree(root, data, size);

    int post_order_result[100];
    int post_index = 0;
    postOrder(root, post_order_result, post_index);
    cout << "Post-order traversal: ";
    for (int i = 0; i < post_index; i++) {
        cout << post_order_result[i] << " ";
    }
    cout << endl;

    MinHeap h1(100);
    for (int i = 0; i < post_index; i++) {
        h1.insert(post_order_result[i]);
    }
    cout << "Min Heap using Insert method: ";
    h1.display();

    int pre_order_result[100];
    int pre_index = 0;
    preOrder(root, pre_order_result, pre_index);
    cout << "Pre-order traversal: ";
    for (int i = 0; i < pre_index; i++) {
        cout << pre_order_result[i] << " ";
    }
    cout << endl;

    MinHeap h2(100);
    h2.buildHeap(pre_order_result, pre_index);
    cout << "Min Heap using BuildHeap method: ";
    h2.display();

    return 0;
}
