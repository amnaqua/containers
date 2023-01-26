#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

# include "./iterator.hpp"

namespace ft
{
    template <class T>
    class bidirectional_iterator: public ft::Iterator<ft::bidirectional_iterator_tag, T>
    {
    public:
        typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::value_type        value_type;
        typedef typaname ft::Iterator<ft::bidirectional_iterator_tag, T>::difference_type   difference_type;
        typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::pointer           pointer;
        typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::reference         reference;
        typedef typename ft::Iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;

    protected:
        pointer _ptr;

    public:
        bidirectional_iterator(void);
        bidirectional_iterator(const bidirectional_iterator& x);
        bidirectional_iterator(pointer _newPtr);

        bidirectional_iterator& operator=(const bidirectional_iterator& x);

        ~bidirectional_iterator(void);

        bool operator==(const bidirectional_iterator& rhs) const;
        bool operator!=(const bidirectional_iterator& rhs) const;

        reference operator*(void) const;
        pointer operator->(void) const;

        bidirectional_iterator& operator++(void);
        bidirectional_iterator  operator++(int);
        bidirectional_iterator& operator--(void);
        bidirectional_iterator  operator--(int);

        pointer getPointer(void) const;

        /*--------------------------------------------------------------------------------*/

        bidirectional_iterator(void): _ptr(NULL) {}

        bidirectional_iterator(const bidirectional_iterator& x): _ptr(x._ptr) {}

        bidirectional_iterator(pointer newPtr) : _ptr(newPtr) {}

		bidirectional_iterator&		operator = (const bidirectional_iterator& x) 
        {
			if (&x == *this)
            {
				return (*this);
            }
			this->_ptr = x._ptr;
		    return (*this);
		}

		~bidirectional_iterator(void) 
        {
			this->_ptr = NULL;
        }

		bool	operator==(const bidirectional_iterator& rhs) const 
        {
			return (this->_ptr == rhs._ptr);
	    }

		bool operator!=(const bidirectional_iterator& rhs) const 
        {
			return (this->_ptr != rhs._ptr);
		}

		reference operator*(void) const 
        {
			return (*this->_ptr);
		}

		pointer	operator->(void) const 
        {
			return (&(*this->_ptr));
		}

		bidirectional_iterator&	operator++(void) 
        {
			this->_ptr++;
			return (*this);
	    }

		bidirectional_iterator operator++(int) 
        {
			bidirectional_iterator	tmp(*this);

			this->_ptr++;
			return (tmp);
		}

		bidirectional_iterator&	operator--(void) 
        {
			this->_ptr--;
			return (*this);
		}

		bidirectional_iterator operator--(int) 
        {
			bidirectional_iterator	tmp(*this);

			this->_ptr--;
			return (tmp);
		}

		pointer getPointer(void) const 
        {
			return (this->_ptr);
		}
    };

    template <typename T1, typename T2>
    bool operator==(const ft::bidirectional_iterator<T1>& lhs, const ft::bidirectional_iterator<T2>& rhs) 
    {
		return (lhs.getPointer() == rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator!=(const ft::bidirectional_iterator<T1>& lhs, const ft::bidirectional_iterator<T2>& rhs) 
    {
		return (lhs.getPointer() != rhs.getPointer());
    }
}

#endif