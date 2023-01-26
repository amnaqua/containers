#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "./iterator_traits.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator                                                iterator_type;
        typedef typename iterator_traits<Iterator>::value_type          value_type;
        typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
        typedef typename ft::iterator_traits<Iterator>::pointer         pointer;
        typedef typename ft::iterator_traits<Iterator>::reference       reference;

        reverse_iterator(void);

        explicit reverse_iterator(iterator_type it);
        template <class Iter> reverse_iterator(const reverse_iterator<Iter>& rev_it);
        iterator_type base(void) const;

        reference operator*(void) const;
        reverse_iterator operator+(difference_type n) const;
        reverse_iterator &operator++(void);
        reverse_iterator operator++(int);
        reverse_iterator &operator+=(difference_type n);
        reverse_iterator operator-(difference_type n) const;
        reverse_iterator &operator--(void);
        reverse_iterator operator--(int);
        reverse_iterator &operator-=(difference_type n);

        pointer operator->(void) const;
        reference operator[](difference_type n) const;

    private:
        iterator_type _base;

    public:
        reverse_iterator(void): _base(NULL) {}

        explicit reverse_iterator(iterator_type it): _base(it) {}

        template <class Iter>
        reverse_iterator(const reverse_iterator<Iter>& rev_it): _base(rev_it.base()) {}

        iterator_type base(void) const
        {
            return (iterator_type(this->_base));
        }

        reference operator*(void) const
        {
            iterator_type tmp(this->_base);

            tmp--;
            return(*tmp);
        }

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(this->_base - n));
        }

        reverse_iterator &operator++(void)
        {
            this->_base++;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator tmp(*this);

            this->_base--;
            return (tmp);
        }

        reverse_iterator &opertaor+=(difference_type n)
        {
            this->_base -= n;
            return (*this);
        }

        reverse_iterator opertaor-(difference_type n) const
        {
            return (reverse_iterator(this->_base + n));
        }

        reverse_iterator &operator--(void)
        {
            this->_base++;
            return (*this);
        }

        reverse_iterator opertaor--(int)
        {
            reverse_iterator tmp(*this);

            this->_base++;
            return (tmp);
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->_base += n;
            return (*this);
        }

        pointer operator->(void) const
        {
            return (&(operator*()));
        }

        reference operator[](difference_type n) const
        {
            return (this->_base()[-n - 1]);
        }
    };

    template <class Iterator> bool	operator==(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);
	template <class Iterator> bool	operator!=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);
	template <class Iterator> bool	operator<(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);
	template <class Iterator> bool	operator<=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);
	template <class Iterator> bool	operator>(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);
	template <class Iterator> bool	operator>=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);

    template <class Iterator>
    ft::reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it);

    template <class Iterator>
    ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs);

    template <class Iterator>
    bool operator==(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator==(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator>
	bool operator!=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (lhs.base() != rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (lhs.base() != rhs.base());
	}

    template <class Iterator>
	bool operator<(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (lhs.base() > rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (lhs.base() > rhs.base());
	}

    template <class Iterator>
	bool operator<=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (lhs.base() >= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (lhs.base() >= rhs.base());
	}

    template <class Iterator>
	bool operator>(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (lhs.base() < rhs.base());
	}

	template <class Iterator>
	bool operator>=(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (lhs.base() <= rhs.base());
	}

	template <class Iterator1, class Iterator2>
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (lhs.base() <= rhs.base());
	}

    template <class Iterator>
	ft::reverse_iterator<Iterator>operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const ft::reverse_iterator<Iterator>& rev_it) 
    {
		return (rev_it + n);
	}

    template <class Iterator>
	typename ft::reverse_iterator<Iterator>::difference_type operator-(const ft::reverse_iterator<Iterator>& lhs, const ft::reverse_iterator<Iterator>& rhs) 
    {
		return (rhs.base() - lhs.base());
	}

	template <class Iterator1, class Iterator2>
	typename ft::reverse_iterator<Iterator1>::difference_type operator-(const ft::reverse_iterator<Iterator1>& lhs, const ft::reverse_iterator<Iterator2>& rhs) 
    {
		return (rhs.base() - lhs.base());
	}
}

#endif