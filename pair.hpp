#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
    template <class T1, class T2>
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  _first;
        second_type _second;

        pair(void): _first(), _second() {};
        
        template <class U, class V>
        pair(const pair<U, V>& pr): _first(pr._first), _second(pr._second) {};

        pair(const first_type& a, const second_type& b): _first(a), _second(b) {};

        pair& operator=(const pair& other)
        {
            if (&other == this)
            {
                return (*this);
            }
            this->_first = other.getFirst();
            this->_second = other.getSecond();
            return (*this);
        }

        first_type getFirst(void) const
        {
            return (this->_first);
        }

        second_type getSecond(void) const
        {
            return (this->_second);
        }
    };
    
    template <class T1, class T2>
    bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (lhs._first == rhs._first && lhs._second == rhs._second);
    }

    template <class T1, class T2>
    bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (!(lhs == rhs));
    }

    template <class T1, class T2>
    bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (lhs._first < rhs._first && lhs._second < rhs._second);
    }

    template <class T1, class T2>
    bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (!(rhs < lhs));
    }

    template <class T1, class T2>
    bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (rhs < lhs);
    }

    template <class T1, class T2>
    bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs) 
    {
		return (!(lhs < rhs));
    }

    template <class T1, class T2>
    ft::pair<T1, T2> make_pair(T1 x, T2 y) 
    {
		return (ft::pair<T1, T2>(x, y));
    }
}

#endif