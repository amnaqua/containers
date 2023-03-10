#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include "pair.hpp"
# include "reverse_iterator.hpp"
# include "bidirectional_iterator.hpp"
# include "binary_search_tree.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map 
    {
    public:
        typedef Key						key_type;
		typedef T						mapped_type;
		typedef ft::pair<const Key, T>	value_type;
		typedef std::size_t				size_type;
		typedef std::ptrdiff_t			difference_type;
		typedef Compare					key_compare;
		typedef Alloc					allocator_type;

		typedef value_type&						reference;
		typedef const value_type&				const_reference;
		typedef typename Alloc::pointer			pointer;
		typedef typename Alloc::const_pointer	const_pointer;

		typedef typename ft::BST<Key, T, Compare>::iterator					iterator;
		typedef typename ft::BST<Key, T, Compare>::const_iterator			const_iterator;
		typedef typename ft::BST<Key, T, Compare>::reverse_iterator			reverse_iterator;
		typedef typename ft::BST<Key, T, Compare>::const_reverse_iterator   const_reverse_iterator;

        class value_compare: public std::binary_function<value_type, value_type, bool>
        {
        public:
            typedef bool		result_type;
			typedef value_type	first_argument_type;
			typedef value_type	second_argument_type;

			bool operator()(const value_type&x, const value_type& y) const
            {
				return (this->_comp(x.first, y.first));
			}

        protected:
			Compare		_comp;

			value_compare(Compare c) : _comp(c) {};
        };

    private:
        allocator_type          _alloc;
        key_compare             _compare;
        BST<Key, T, Compare>    _bst;

    public:
        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type());
		
        map(const map& x);
		
        ~map(void);
	    
        map& operator=(const map& x);

        iterator					begin(void);
		const_iterator				begin(void) const;
		iterator					end(void);
		const_iterator				end(void) const;
		reverse_iterator			rbegin(void);
		const_reverse_iterator		rbegin(void) const;
		reverse_iterator			rend(void);
		const_reverse_iterator		rend(void) const;

        bool	    empty(void) const;
		size_type	size(void) const;
		size_type	max_size(void) const;

        mapped_type&		operator [] (const key_type& k);
		mapped_type&		at(const key_type& k);
		const mapped_type&	at(const key_type& k) const;

        pair<iterator, bool>	insert(const value_type& val);
		iterator				insert(iterator position, const value_type& val);
		template <class InputIterator>
		void					insert(InputIterator first, InputIterator last);
		void		erase(iterator position);
		size_type	erase(const key_type& k);
		void		erase(iterator first, iterator last);
		void		swap(map& x);
		void		clear(void);

        key_compare		key_comp(void) const;
		value_compare	value_comp(void) const;

        iterator			find(const key_type& k);
		const_iterator		find(const key_type& k) const;
		size_type			count(const key_type& k) const;
		iterator			lower_bound(const key_type& k);
		const_iterator		lower_bound(const key_type& k) const;
		iterator			upper_bound(const key_type& k);
		const_iterator		upper_bound(const key_type& k) const;
		pair<const_iterator, const_iterator>	equal_range(const key_type& k) const;
		pair<iterator, iterator>				equal_range(const key_type& k);

        allocator_type get_allocator(void) const;

        explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
			_bst(comp, alloc),
            _alloc(alloc),
            _compare(comp) {}

        template <class InputIterator>
		map(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, 
			const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
             _bst(comp, alloc),
             _alloc(alloc),
             _compare(comp)
        {
	        while (first != last) 
            {
		    	this->_bst.insertNode(first->pair);
		    	first++;
		    }
		}

        map(const map& x): _bst(x._compare, x._alloc), _alloc(x._alloc), _compare(x._compare)
        {
			*this = x;
		}

		map& operator=(const map& x) 
        {
		    if (this == &x)
            {
		    	return (*this);
            }

		    for (iterator it = x.begin(); it != x.end(); it++)
            {
		    	this->_bst.insertNode(*it);
            }
		    return (*this);
		}

        ~map(void) {}

        iterator begin(void) 
        {
			return (iterator(this->_bst.minimum(this->_bst.getRoot())));
		}

		const_iterator begin(void) const 
        {
			return (const_iterator(this->_bst.minimum(this->_bst.getRoot())));
		}

		iterator end(void) 
        {
			return (iterator(this->_bst.maximum(this->_bst.getRoot())));
		}

		const_iterator end(void) const 
        {
			return (const_iterator(this->_bst.maximum(this->_bst.getRoot())));
		}

		reverse_iterator rbegin(void) 
        {
			return (reverse_iterator(this->_bst.maximum(this->_bst.getRoot())));
		}

		const_reverse_iterator	rbegin(void) const 
        {
			return (const_reverse_iterator(this->_bst.maximum(this->_bst.getRoot())));
		}

		reverse_iterator rend(void) 
        {
			return (reverse_iterator(this->_bst.minimum(this->_bst.getRoot())));
		}

		const_reverse_iterator	rend(void) const 
        {
			return (const_reverse_iterator(this->_bst.minimum(this->_bst.getRoot())));
		}

        bool empty(void) const 
        {
				if (this->_bst.getSize() == 0)
                {
						return (true);
                }
				return (false);
		}

		size_type size(void) const 
        {
			return (this->_bst.getSize());
		}

		size_type max_size(void) const
        {
			return (this->_alloc.max_size());
		}

        mapped_type& operator[](const key_type& k) 
        {
			iterator	it = this->_bst.find(k);

			return (it->pair._first);
		}

		mapped_type& at(const key_type& k)
        {
			iterator it = this->_bst.find(k);

			if (it->_ptr == this->_bst.getNull())
            {
				throw std::out_of_range("Out of Range");
            }
			return (it->pair._first);
		}

		const mapped_type& at(const key_type& k) const 
        {
			iterator	it = this->_bst.find(k);

			if (it->_ptr == this->_bst.getNull())
            {
				throw std::out_of_range("Out of Range");
            }
			return (it->pair._first);
		}

        ft::pair<iterator, bool> insert(const value_type& val) 
        {
			bool		isNew;
			iterator	it;

			isNew = this->_bst.insertNode(val);
			it = this->_bst.find(val->_first);
			return (ft::make_pair(it, isNew));
        }

        iterator insert(iterator position, const value_type& val) 
        {
			iterator	it;

			this->_bst.insertNode(val);
			it = this->_bst.find(val->_first);
			return (it);
		}

        template <class InputIterator>
		void insert (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last) 
        {
			while (first != last) 
            {
				this->_bst.insertNode(first->pair);
				first++;
			}
		}

        void erase(iterator position)
        {
			his->_bst.deleteNode(position->pair._first);
		}

        size_type erase(const key_type& k) 
        {
			if (this->_bst.deleteNode(k))
            {
				return (1);
            }
			return (0);
		}

        void erase(iterator first, iterator last) 
        {
			while (first != last) 
            {
				this->_bst.deleteNode(first->pair._first);
				first++;
		    }
		}

        void swap(map& x) 
        {
			BST<Key, T, Compare> tmp;

			tmp = this->_bst;
			this->_bst = x._bst;
			x._bst = tmp;
		}

        void clear(void) 
        {
			if (this->_bst.getRoot() != NULL)
            {
				this->_bst.clearTree();
            }
		}

        key_compare key_comp(void) const
        {
			return (this->_compare);
		}

		value_compare value_comp(void) const
        {
			return (value_compare());
		}


    };

    template <class Key, class T, class Compare, class Alloc>
	bool operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);
	template <class Key, class T, class Compare, class Alloc>
	bool operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);
	template <class Key, class T, class Compare, class Alloc>
	bool operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);
	template <class Key, class T, class Compare, class Alloc>
	bool operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);
	template <class Key, class T, class Compare, class Alloc>
	bool operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);
	template <class Key, class T, class Compare, class Alloc>
	bool operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs);

    template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs);
}

#endif