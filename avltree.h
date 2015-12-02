//zihang zhou
//861090400
//problem set 6
#ifndef AVLTREE_H
#define AVLTREE_H

#include "value_ptr.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>


template<typename T>
class avltree {
	private:
	struct node;
	
	struct node {
		node() {}
		node(const T &e) : element(e) { 
			h = 0; 
			size = 1; 
		}	
		T element;
		value_ptr<node> left,right;
		int h;
		int size;
	};
	value_ptr<node> root;
	
	private:
	static T kthsmallest(const value_ptr<node> &n, const int x) {
		if(n->left == nullptr && x==1) 
			return n->element;
		if(n->left == nullptr && x==2)
			 return n->right->element;
		if( x < sz(n->left))
			return kthsmallest(n->left,x);
		if(x == sz(n->left))
			return n->element;
		if(x > sz(n->left))
			return kthsmallest(n->right,x-sz(n->left)-1);
		return n->element;
	   }
   
	public:
		T kthsmallest(int k) const {
			// write this function
			if(k > root->size || k < 0)
				throw std::out_of_range("k_out_of_range");
			return kthsmallest(root,k);
		}
	private:
		void between(avltree<T> &temp, const T&x1, const T&x2, value_ptr<node> &n) {
			if (x1 <= x2) {
				if(n->element == x1) {
					temp.insert(n->element);
					std::cout<< n->element << std::endl;
					if (n->right)
						between(temp, x1, x2, n->right);
				}
				else if (n->element > x1 && n->element <= x2) {
					temp.insert(n->element);
					std::cout<< n->element << std::endl;
					if(n->right)
						between(temp,x1, x2, n->right);
					if(n->left)
						between(temp, x1, x2, n->left);
				}
				else if (n->element < x1 && n->right)
					between(temp, x1, x2, n->right);
				else if (n->element > x2 && n->left)
					between (temp, x1, x2, n->left);
			}
		}
		
	public:
		avltree<T> between(const T &x1, const T &x2) {
			// write this function
			avltree <T> temp;
			between(temp,x1,x2,root);
			return temp;
		}
   
		void insert(const T &x) {
			insert(root,x);
		}
   
   
		void remove(const T &x) {
			remove(root,x);
		}
   
		bool contains(const T &x) const {
			return contains(root,x);
		}
   
	private:
		static int ht(const value_ptr<node> &n) {
		return n ? n->h : -1;
		}
   
		static void setht(const value_ptr<node> &n) {
			if (!n) return;
			n->h = 1+std::max(ht(n->left),ht(n->right));
			if(!n->right && !n->left)
				n->size = 0;
			if(n->right)
				n->size = 1 + (n->left ? 1 + n->left->size : 0 ) + n->right->size;
			if(n->left)
				n->size = 1 + (n->right ? 1 + n->right->size : 0) + n->left->size;
		}
		static int sz(const value_ptr<node> &n) {
			if (!n)
				return n->size + 1; 
			return 0;
		}
   
		static void rotateleft(value_ptr<node> &n) {
			auto Y = std::move(n->left->right);
			auto a = std::move(n->left);
			auto b = std::move(n);
			n = std::move(a);
			n->right = std::move(b);
			n->right->left = std::move(Y);
			setht(n->right);
			setht(n);
		}
	
		static void rotateright(value_ptr<node> &n) {
			auto Y = std::move(n->right->left);
			auto b = std::move(n->right);
			auto a = std::move(n);
			n = std::move(b);
			n->left = std::move(a);
			n->left->right = std::move(Y);
			setht(n->left);
			setht(n);
		}
   
		static void doublerotateleft(value_ptr<node> &n) {
			rotateright(n->left);
			rotateleft(n);
		}
   
		static void doublerotateright(value_ptr<node> &n) {
			rotateleft(n->right);
			rotateright(n);
		}
   
		static void balance(value_ptr<node> &n) {
			if (!n) return;
			if (ht(n->left) > ht(n->right)+1) {
				if (ht(n->left->right)>ht(n->left->left))
					doublerotateleft(n);
				else rotateleft(n);
			} else if (ht(n->right) > ht(n->left)+1) {
				if (ht(n->right->left)>ht(n->right->right))
					doublerotateright(n);
				else rotateright(n);
			}
			setht(n);
		}
   
		static bool contains(const value_ptr<node> &n, const T &x) {
			if (n==nullptr) return false;
			if (n->element == x) return true;
			if (x < n->element) return contains(n->left,x);
			return contains(n->right,x);
		}
   
		static void insert(value_ptr<node> &n, const T &x) {
			if (n==nullptr) n = value_ptr<node>(new node(x));
			else if (n->element == x) return;
			else if (x < n->element) insert(n->left,x);
			else insert(n->right,x);
			balance(n);
		}
   
		static T removemin(value_ptr<node> &n) {
			if (n->left) {
			T ret = removemin(n->left);
			n->size = 0;
			balance(n);
			return ret;
			}
			else {
				T ret = std::move(n->element);
				n->size = 0;
				removenode(n);
				balance(n);
				return ret;
			}
		}
   
		static void removenode(value_ptr<node> &n) {
			if (!n->right) n=std::move(n->left);
			else if (!n->left) n=std::move(n->right);
			else n->element = removemin(n->right);
		}
   
		static void remove(value_ptr<node> &n, const T &x) {
			if (n==nullptr) return;
			if (n->element == x) removenode(n);
			else if (x < n->element) remove(n->left,x);
			else remove(n->right,x);
			balance(n);
		}
   
	public:
	
		void print(std::ostream &os) const {
		os << "start tree" << std::endl;
		print(os,root,std::string{},std::string{},std::string{});
		os << "end tree" << std::endl;
		}
	
	private:
	
		static void print(std::ostream &os, const value_ptr<node> &n,
					 std::string prefixl, std::string prefixc,
					 std::string prefixr) {
		if (n==nullptr) return;
		std::stringstream ss;
		ss << n->element;
		ss << " " << n->size;
		auto myout = std::string("[") + ss.str() + "]";
		auto newpre1 = std::string(2+myout.size(),' ')+std::string(1,'|');
		auto newpre2 = std::string(2+myout.size(),' ')+std::string(1,' ');
		auto newpre3 = std::string(2+myout.size(),' ')+std::string(1,'/');
		auto newpre4 = std::string(2+myout.size(),' ')+std::string(1,'\\');
		print(os,n->left,prefixl+newpre2,prefixl+newpre3,prefixl+newpre1);
		os << prefixc << '-' << myout;
		if (n->left && n->right) os << "-+";
		else if (n->left) os << "-/";
		else if (n->right) os << "-\\";
		os << std::endl;
		print(os,n->right,prefixr+newpre1,prefixr+newpre4,prefixr+newpre2);
		}
   
};
#endif
