#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include "header/DynamicBinaryTree.hpp"
#include <iostream>

namespace BinaryTree {
	
	template <typename T>
	class BinarySearchTree : protected DynamicBinaryTree<T> {

		using value_type = T;
		using node = DynamicNode<T>;

	public:
		BinarySearchTree() : DynamicBinaryTree<T>() {};

		bool empty() const {
			return DynamicBinaryTree<T>::empty();
		}

		const node* search(value_type val) {
			return __search(val, DynamicBinaryTree<T>::root());
		}

		int search_len(value_type val) {
			return __search_len(val, DynamicBinaryTree<T>::root(), 0);
		}

		bool contain(value_type val) {
			return nullptr != search(val);
		}

		void insert(value_type val) {
			__insert(val, DynamicBinaryTree<T>::root());
		}

		void remove(value_type val) {
			__remove(val, DynamicBinaryTree<T>::root());
		}

		void clear() {
			this->delete_tree(DynamicBinaryTree<T>::root());
		}

		void sort(::std::ostream& out_dest = ::std::cout) {
			this->for_each(IN_ORDER, [&](value_type val) {out_dest << val << ' '; });
		}

		// ensure the container that iterator bind to have enough space 
		template <typename ForwardIter>
		void sort(ForwardIter iter) {
			this->for_each(IN_ORDER, [&](value_type val) {*iter = val; ++iter; });
		}

		void show(::std::ostream& out = ::std::cout) {
			DynamicBinaryTree<T>::show(out);
		}

	private:
		node* __search(value_type val, node* root) {
			if (root == nullptr)
				return nullptr;

			value_type root_val = root->data;
			if (val == root_val)
				return root;
			else if (val < root_val)
				return __search(val, root->lchild);
			else
				return __search(val, root->rchild);
		}

		int __search_len(value_type val, node* root, int len) {
			if (root == nullptr)
				return len;

			value_type root_val = root->data;
			if (++len, val == root_val)
				return len;
			else if (val < root_val)
				return __search_len(val, root->lchild, len);
			else
				return __search_len(val, root->rchild, len);
		}

		void __insert(value_type val, node*& root) {
			if (root == nullptr)
				root = new node(val, nullptr, nullptr);
			else if (val < root->data)
				__insert(val, root->lchild);
			else if (val > root->data)
				__insert(val, root->rchild);
			else
				;
		}

		void __remove(value_type val, node*& root) {
			if (root == nullptr)
				return;
			else if (val < root->data)
				__remove(val, root->lchild);
			else if (val > root->data)
				__remove(val, root->rchild);
			else
				if (root->lchild == nullptr) {
					node* temp = root;
					root = root->rchild;
					delete temp;
				}
				else if (root->rchild == nullptr) {
					node* temp = root;
					root = root->lchild;
					delete temp;
				}
				else
					root->data = __remove_min(root->rchild);
		}

		value_type __remove_min(node*& root) {
			if (root->lchild == nullptr) {
				value_type ret = root->data;
				node* temp = root;
				root = root->rchild;
				delete temp;
				return ret;
			}
			else
				return __remove_min(root->lchild);
		}

	}; // class BinarySearchTree

	template <typename T>
	using BST = BinarySearchTree<T>; // alias of BinarySearchTree

} // namespace BinaryTree

#endif // _BINARY_SEARCH_TREE_HPP_