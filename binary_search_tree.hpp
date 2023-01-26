#ifndef BINARY_SEARCH_TREE
# define BINARY_SEARCH_TREE

# include "pair.hpp"
# include "bidirectional_iterator.hpp"
# include "reverse_iterator.hpp"

# include <functional>
# include <iostream>

namespace ft 
{

    template <class Key, class T>
    struct Node 
    {
		bool			    color;
		ft::pair<Key, T>	pair;
		Node*				lChild;
		Node*				rChild;
		Node*				parent;

		Node(ft::pair<Key, T> newPair): color(true), pair(newPair), lChild(NULL), rChild(NULL), parent(NULL) {}
		Node(void): color(false), pair(), lChild(NULL), rChild(NULL), parent(NULL) {}
};

    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::Node<Key, T> > >
    class BST
    {
    public:
		typedef Node<Key, T>	Node;
		typedef Node*			NodePtr;
		typedef Alloc			allocator_type;
		typedef Compare			comp_operation;

		template <class U>
		class BSTIterator : public ft::bidirectional_iterator<U>
		{
		private :
			friend class BST;
			BST _bst;
				
        public:
			ft::pair<Key, T>&	operator * (void) const 
            {
				return (*this->_ptr->pair);
			}

			ft::pair<Key, T>*	operator -> (void) const 
            {
				return  (&(*this->_ptr->pair));
			}

			BSTIterator& operator++(void) 
            {
				NodePtr y;

				if (this->_ptr == this->_bst.maximum(this->_bst.getRoot()))
                {
					throw std::exception();
                }
                
                y = this->_bst.minimum(this->_ptr->rChild);
				if (y != this->_bst._null && y != NULL)
                {
					this->_ptr = y;
                }
				else if (this->_ptr->parent->rChild != this->_ptr)
                {
					this->_ptr = this->_ptr->parent;
                }
				else
                {
					this->_ptr = this->_ptr->parent->parent;
                }
				return (*this);
			}

			BSTIterator			operator++(int) 
            {
				BSTIterator	tmp(*this);

				++(*this);
				return (tmp);
			}

			BSTIterator&    operator--(void) 
            {
				NodePtr		y;

				if (this->_ptr == this->_bst.minimum(this->_bst.getRoot()))
                {
					throw std::exception();
                }

				y = this->_bst.maximum(this->_ptr->lChild);
				if (y != this->_bst._null && y != NULL)
                {
					this->_ptr = y;
                }
				else if (this->_ptr->parent->lChild != this->_ptr)
                {
					this->_ptr = this->_ptr->parent;
                }
				else
                {
					this->_ptr = this->_parent->parent;
                }
				return (*this);
			}

			BSTIterator	operator--(int) 
            {
			    BSTIterator	tmp(*this);

				--(*this);
				return (tmp);
			}

		};

		typedef BSTIterator<NodePtr>					iterator;
		typedef BSTIterator<const NodePtr>				const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

	private:		
		NodePtr		_root;
		NodePtr		_null;
		Compare		_comp;
		Alloc		_alloc;
		std::size_t	_size;

	public:
		BST(const comp_operation& comp = comp_operation(), const allocator_type& alloc = allocator_type());

		BST&		operator = (const BST& x);		

		~BST(void);		

		void	clearTree(void);
		bool	insertNode(ft::pair<const Key, T> newPair);
		bool	deleteNode(const Key& key);
		void	insertFix(NodePtr x);
		void	deleteFix(NodePtr x);
		void	recolor(NodePtr node);
		void	leftRotate(NodePtr node);
		void	rightRotate(NodePtr node);

		NodePtr			minimum(NodePtr x);
		NodePtr 		maximum(NodePtr x);
		std::size_t		getSize(void) const;
		NodePtr			getNull(void) const;
		NodePtr			getRoot(void) const;
		iterator		find(const Key& key);

		BST(const comp_operation& comp = comp_operation(), const allocator_type& alloc = allocator_type()): _root(NULL), _comp(comp), _alloc(alloc), _size(0) 
        {
			_null = _alloc.allocate(1);
			_alloc.construct(_null, Node());
			_null->color = false;
			_null->lChild = NULL;
			_null->rChild = NULL;
			_null->parent = NULL;
			_root = _null;
		}

		BST& operator=(const BST& x) 
        {
			if (this == &x)
            {
				return (*this);
            }
			this->_root = x._root;
			this->_null = x._null;
			this->_size = x._size;
			return (*this);
		}

		~BST(void) 
        {
			if (this->_root != NULL)
            {
				this->clearTree();
            }
		}

		void clearTree(void) 
        {
			while (this->_root != this->_null)
            {
				deleteNode(this->_root->pair._first);
            }
			this->_root = NULL;
			_alloc.destroy(this->_null);
		    _alloc.deallocate(this->_null, 1);
			this->_null = NULL;
			this->_size = 0;
		}

		std::size_t getSize(void) const 
        {
			return (this->_size);
		}

		NodePtr	getRoot(void) const 
        {
			return (this->_root);
		}

		NodePtr	getNull(void) const 
        {
			return (this->_null);
		}

		bool	insertNode(ft::pair<Key, T> newPair) 
        {
			bool isNewNode = false;

			if (this->_root == this->_null) 
            {
				NodePtr	newNode = NULL;

				newNode = _alloc.allocate(1);
				_alloc.construct(newNode, Node(newPair));
				newNode->lChild = this->_null;
				newNode->rChild = this->_null;
				this->_root = newNode;
				recolor(this->_root);
				this->_size++;
				isNewNode = true;
			}
			else 
            {
				NodePtr	cur = this->_root;
				NodePtr		ptrParent = NULL;
				int	dir;

				while (cur != this->_null) 
                {
                    if (cur->pair._first == newPair._first)
                    {
						return (false);
                    }
                    else if (this->_comp(newPair._first, cur->pair._first)) 
                    {
						ptrParent = cur;
						cur = cur->lChild;
						dir = 0;
					}
                    else 
                    {
						ptrParent = cur;
						cur = cur->rChild;
						dir = 1;
					}
				}
                NodePtr		newNode = NULL;

			    newNode = _alloc.allocate(1);
			    _alloc.construct(newNode, Node(newPair));
				newNode->rChild = this->_null;
				newNode->lChild = this->_null;
				newNode->parent = ptrParent;
				if (dir == 0)
                {
					ptrParent->lChild = newNode;
                }
				else
                {
					ptrParent->rChild = newNode;
                }
				cur = newNode;
				this->_size++;
				isNewNode = true;
				insertFix(cur);
				return (isNewNode);
			}
		}

		void	insertFix(NodePtr x)
        {
			NodePtr	gp = NULL;
			bool	r;
			bool	uncle = true;

			if (x->parent->parent != NULL) 
            {
				gp = x->parent->parent;
				if (gp->lChild == x->parent)
                {
					r = false;
                }
				else
                {
					r = true;
                }
				if ((r && gp->lChild == this->_null) || (!r && gp->rChild == this->_null))
                {
					uncle = false;
                }
			}

			if (x->parent->color)
            {
				if ((r && (gp->lChild != this->_null && gp->lChild->color)) || (!r && (gp->rChild != this->_null && gp->rChild->color))) 
                {
					if (gp != this->_root)
                    {
						recolor(gp);
                    }
					recolor(gp->lChild);
					recolor(gp->rChild);
				}
				else if (!uncle || ((r && !gp->lChild->color) || (!r && !gp->rChild->color))) 
                {
					if (r && x->parent->rChild == x) 
                    {
						leftRotate(gp);
						recolor(gp);
						recolor(x->parent);
					}
					else if (r && x->parent->lChild == x) 
                    {
						rightRotate(x->parent);
						leftRotate(gp);
						recolor(gp);
						recolor(x);
					}
					else if (!r && x->parent->lChild == x) 
                    {
						rightRotate(gp);
						recolor(gp);
						recolor(x->parent);
					}
					else if (!r && x->parent->rChild == x)
                    {
						leftRotate(x->parent);
						rightRotate(gp);
						recolor(gp);
						recolor(x);
					}
				}
			}
	    }

		bool deleteNode(const Key& key) 
        {
			NodePtr	cur;
			NodePtr	y;
			NodePtr	x;
			bool	oldColor = true;

			cur = this->_root;
			if (cur == this->_null || cur == NULL)
            {
				return (false);
            }

			while (cur != this->_null && cur->pair._first != key) 
            {
				if (this->_comp(key, cur->pair._first))
                {
					cur = cur->lChild;
                }
				else
                {
					cur = cur->rChild;
                }
			}
			if (cur == this->_null) 
            {
			    std::cout << "No occurence found" << std::endl;
				return (false);
			}

			if (cur->lChild != this->_null && cur->rChild != this->_null) 
            {
				y = minimum(cur->rChild);
				oldColor = !y->color;
				if (y->parent == cur) 
                {
					cur->rChild = this->_null;
                }
				else
                {
					y->parent->lChild = y->rChild;
                }
				x = y->rChild;
				if (x == this->_null)
                {
					x->parent = y->parent;
                }
				cur->pair = y->pair;
				_alloc.destroy(y);
				_alloc.deallocate(y, 1);
			}
			else if (cur->lChild == this->_null && cur->rChild == this->_null) 
            {
				oldColor = !cur->color;
				if (cur->parent == NULL)
                {
					this->_root = this->_null;
                }
				else if (cur->parent->lChild == cur) 
                {
					cur->parent->lChild = this->_null;
					x = cur->parent->lChild;
					x->parent = cur->parent;
				}
			    else 
                {
					cur->parent->rChild = this->_null;
					x = cur->parent->rChild;
					x->parent = cur->parent;
				}
				_alloc.destroy(cur);
				_alloc.deallocate(cur, 1);
			}
			else if (cur->lChild != this->_null)
            {
				y = cur->lChild;
				cur->pair = y->pair;
				cur->lChild = this->_null;
				x = cur->lChild;
				x->parent = cur;
				oldColor = !y->color;
				_alloc.destroy(y);
				_alloc.deallocate(y, 1);
			}
			else 
            {
				y = cur->rChild;
				cur->pair = y->pair;
				cur->rChild = this->_null;
				x = cur->rChild;
				x->parent = cur;
				oldColor = !y->color;
				_alloc.destroy(y);
				_alloc.deallocate(y, 1);
			}
			this->_size--;
			if (oldColor)
            {
				deleteFix(x);
            }
			return (true);
		}

		void deleteFix(NodePtr x)
        {
			NodePtr	w;

			while (x != this->_root && !x->color) 
            {
				if (x->parent->lChild == x) 
                {
					w = x->parent->rChild;
					if (w->rChild == NULL)
                    {
						w->rChild = this->_null;
                    }
					if (w->lChild == NULL)
                    {
						w->lChild = this->_null;
                    }
					if (w->color) 
                    {
						recolor(w);
						x->parent->color = true;
						leftRotate(x->parent);
						w = x->parent->rChild;
                    }
					else if ((w->rChild != this->_null && !w->rChild->color) && (w->lChild != this->_null && !w->lChild->color)) 
                    {
						w->color = true;
						x = x->parent;
					}
				    else if (!w->rChild->color)
                    {
						w->lChild->color = false;
						w->color = true;
						rightRotate(w);
						w = x->parent->rChild;
					}
					else 
                    {
						w->color = x->parent->color;
						if (x->parent != this->_root)
                        {
							x->parent->parent->color = false;
                        }
						w->rChild->color = false;
					    leftRotate(x->parent);
						x = this->_root;
					}
				}
				else 
                {
					w = x->parent->lChild;
					if (w->color)
                    {
						recolor(w);
						x->parent->color = true;
						rightRotate(x->parent);
					    w = x->parent->lChild;
					}
					else if (!w->rChild->color && !w->lChild->color) 
                    {
					    w->color = true;
						x = x->parent;
					}
					else if (!w->lChild->color) 
                    {
						w->rChild->color = false;
						w->color = true;
						leftRotate(w);
						w = x->parent->lChild;
					}
					else 
                    {
						w->color = x->parent->color;
						if (x->parent != this->_root)
                        {
							x->parent->parent->color = false;
                        }
						w->lChild->color = false;
						rightRotate(x->parent);
						x = this->_root;
					}
				}
			}
		    x->color = false;
		}

		NodePtr	minimum(NodePtr x) 
        {
			while (x->lChild != this->_null && x->lChild != NULL) 
            {
				x = x->lChild;
			}
			return (x);
		}

		NodePtr	maximum(NodePtr x) 
        {
			while (x->rChild != this->_null && x->rChild != NULL)
            {
				x = x->rChild;
            }
			return (x);
		}

		void leftRotate(NodePtr x) 
        {
		    if (x->rChild == this->_null)
            {
				return;
            }

			NodePtr	y = x->rChild;
			x->rChild = y->lChild;

			if (x->rChild != this->_null)
            {
				x->rChild->parent = x;
            }

			y->lChild = x;
			y->parent = x->parent;
		    if (y->parent == this->_null || y->parent == NULL)
            {
				this->_root = y;
            }
			else if (y->parent->lChild == x)
            {
				y->parent->lChild = y;
            }
			else
            {
				y->parent->rChild = y;
            }
			x->parent = y;
		}

		void	rightRotate(NodePtr x) 
        {
		    if (x->lChild == this->_null)
            {
				return;
            }

			NodePtr	y = x->lChild;
			x->lChild = y->rChild;

			if (x->lChild != this->_null)
            {
				x->lChild->parent = x;
            }

			y->rChild = x;
			y->parent = x->parent;

			if (y->parent == this->_null || y->parent == NULL)
            {
				this->_root = y;
            }
			else if (y->parent->lChild == x)
            {
				y->parent->lChild = y;
            }
			else
            {
				y->parent->rChild = y;
            }
            x->parent = y;
		}

		void recolor(NodePtr node) 
        { 
            node->color = !node->color; 
        }

		iterator find(const Key& key) 
        {
			iterator	it = this->minimum(this->getRoot());

			while (it->_ptr != this->_null && it->first != key)
            {
								it++;
            }
			return (it);
		}

		void printTree(NodePtr root, int space) const 
        {
			if (root == this->_null || root == NULL)
            {
				return ;
            }
			space += 5;
			printTree(root->rChild, space);
			std::cout << std::endl;
			for (int i = 5; i < space; i++)
            {
				std::cout << " ";
            }

			std::string		strCol;

			if (root->color)
            {
				strCol = "\033[1;31m";
            }
			else
            {
				strCol = "\033[0m";
            }
			std::cout << strCol << root->pair._second << "\033[0m" << std::endl;
		    printTree(root->lChild, space);
		}
    };
}

#endif