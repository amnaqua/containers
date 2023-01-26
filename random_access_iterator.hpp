#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

# include "./iterator.hpp"

namespace ft
{
    template <class T>
    class random_access_iterator: public ft::Iterator<ft::random_access_iterator_tag, T>
    {
    public:
        typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::value_type        value_type;
        typedef typename ft::Iterator<ft::random_access_iterator_tag, t>::difference_type   difference_type;
        typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::pointer           pointer;
        typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::reference         reference;
        typedef typename ft::Iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;

    private:
        pointer _ptr;
        
        random_access_iterator(void);
        random_access_iterator(const random_access_iterator& x);
        random_access_iterator(pointer _newPtr);

        random_access_iterator& operator=(const random_access_iterator& x);

        ~random_access_iterator(void);

        bool operator==(const random_access_iterator& rhs) const;
        bool operator!=(const random_access_iterator& rhs) const;

        reference operator*(void) const;
        reference operator->(void) const;

        random_access_iterator &operator++(void);
        random_access_iterator operator++(int);

        random_access_iterator &operator--(void);
        random_access_iterator operator--(int);

        random_access_iterator operator+(difference_type n) const;
        random_access_iterator operator-(difference_type n) const;

        difference_type operator-(const random_access_iterator& rhs);

        bool operator<(const random_access_iterator& rhs) const;
        bool operator>(const random_access_iterator& rhs) const;
        bool operator<=(const random_access_iterator& rhs) const;
        bool operator>=(const random_access_iterator& rhs) const;

        random_access_iterator operator+=(difference_type n) const;
        random_access_iterator operator-=(difference_type n) const;

        reference operator[](difference_type n);
        
        pointer getPointer(void) const;

    public:
        random_access_iterator(void): _ptr(NULL) {}
        random_access_iterator(const random_access_iterator& x): _ptr(x._ptr) {}
        random_access_iterator(pointer _newPtr): _ptr(_newPtr) {}
        
        random_access_iterator& operator=(const random_access_iterator& x)
        {
            if (&x == this)
                return (*this);
            this->_ptr = x._ptr;
            return (*this);
        }

        ~random_access_iterator(void)
        {
            this->_ptr = NULL;
        }

        bool operator==(const random_access_iterator& rhs) const
        {
            return (this->_ptr == rhs._ptr);
        }

        bool operator!=(const random_access_iterator& rhs) const
        {
            return (this->_ptr == rhs._ptr);
        }

        reference operator*(void) const
        {
            return (*this->_ptr);
        }

        pointer operator->(void) const
        {
            return (&(*this->_ptr));
        }

        random_access_iterator& operator++(void)
        {
            this->_ptr++;
            return (*this);
        }

        random_access_iterator operator++(int)
        {
            random_access_iterator tmp(*this);

            this->_ptr++;
            return (tmp);
        }

        random_access_iterator& operator--(void)
        {
            this->_ptr--;
            return (*this);
        }

        random_access_iterator operator--(int)
        {
            random_access_iterator tmp(*this);

            this->_ptr--;
            return (tmp);
        }

        random_access_iterator operator+(difference_type n) const
        {
            return (this->_ptr + n);
        }

        random_access_iterator operator-(difference_type n) const
        {
            return (this->_ptr - n);
        }

        difference_type operator-(const random_access_iterator& rhs)
        {
            random_access_iterator tmp(*this);
            difference_type res = 0;

            if (tmp < rhs)
            {
                while (tmp != rhs)
                {
                    tmp++;
                    res--;
                }
            }
            else if (tmp > rhs)
            {
                while (tmp != rhs)
                {
                    tmp--;
                    res++;
                }
            }
            return (res);
        }

        bool operator<(const random_access_iterator& rhs) const
        {
            return (this->_ptr < rhs._ptr);
        }

        bool operator>(const random_access_iterator& rhs) const
        {
            return (this->_ptr > rhs._ptr);
        }

        bool operator<=(const random_access_iterator& rhs) const
        {
            return (this->_ptr <= rhs._ptr);
        }

        bool operator>=(const random_access_iterator& rhs) const
        {
            return (this->_ptr >= rhs._ptr);
        }

        random_access_iterator operator+=(difference_type n)
        {
            this->_ptr += n;
            return (*this);
        }

        random_access_iterator operator-=(difference_type n)
        {
            this->_ptr -= n;
            return (*this);
        }

        reference operato[](difference_type n) const
        {
            return (*(this->_ptr + n));
        }

        operator random_access_iterator<const value_type> (void) const
        {
            return (random_access_iterator<const value_type>(this->_ptr));
        }

        pointer getPointer(void) const
        {
            return (this->_ptr);
        }
    };

    template <typename T>
    typename ft::random_access_iterator<T> operator+(typename ft::random_access_iterator<T>::difference_type n,
        ft::random_access_iterator<T>& cur)
    {
        return (&(*cur) + n);
    }

    template <typename T1, typename T2>
    typename ft::random_access_iterator<T1>::difference_type operator-(const ft::random_access_iterator<T1> lhs,
        const ft::random_access_iterator<T2> rhs)
    {
        ft::random_access_iterator<T1>  tmp(lhs);
        typename ft::random_access_iterator<T1>::difference_type    res = 0;

        if (lhs < rhs)
        {
            while (tmp != rhs)
            {
                tmp++;
                res--;
            }
        }
        else if (lhs > rhs)
        {
            while (tmp != rhs)
            {
                tmp--;
                res++;
            }
        }
        return (res);
    }

    template <typename T1, typename T2>
    bool operator!=(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() != rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator==(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() == rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator>(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() > rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator<(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() < rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator>=(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() >= rhs.getPointer());
    }

    template <typename T1, typename T2>
    bool operator<=(const ft::random_access_iterator<T1>& lhs, const ft::random_access_iterator<T2>& rhs)
    {
        return (lhs.getPointer() <= rhs.getPointer());
    }
}

#endif