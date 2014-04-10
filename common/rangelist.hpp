/** @file rangelist.hpp
    @brief Range List
    @author Luis Cabellos
    @date 2014-04-08
*/
//------------------------------------------------------------------------------
#ifndef RANGELIST_HPP_
#define RANGELIST_HPP_

//------------------------------------------------------------------------------
#include <list>
#include <algorithm>

//------------------------------------------------------------------------------
template<typename T>
class RangeListIterator{
public:
    static_assert( std::is_integral<T>::value,
                   "RangeList works only with integral types" );
    using value_type = T;
    using RangeItem = std::pair< value_type, value_type >;
    using RangeItemList = std::list<RangeItem>;
    using RangeItem_iterator = typename RangeItemList::iterator;

    RangeListIterator( RangeItem_iterator it, value_type val,
                       RangeItem_iterator itEnd );

    bool operator!=( const RangeListIterator<T> & b ) const;

    RangeListIterator& operator++();
    RangeListIterator operator++( int );

    const value_type& operator*() const;

private:
    RangeItem_iterator m_listIt;
    RangeItem_iterator m_listEnd;
    value_type m_val;
};

//------------------------------------------------------------------------------
template<typename T>
RangeListIterator<T>::RangeListIterator( RangeItem_iterator it,
                                         value_type val,
                                         RangeItem_iterator itEnd)
    : m_listIt{ it }, m_listEnd{ itEnd }, m_val{ val }
{
    // empty
}

//------------------------------------------------------------------------------
template<typename T>
bool RangeListIterator<T>::operator!=( const RangeListIterator<T> & b ) const{
    return (m_listIt != b.m_listIt) or (m_val != b.m_val);
}

//------------------------------------------------------------------------------
template<typename T>
RangeListIterator<T>& RangeListIterator<T>::operator++() {
    if( m_val == std::numeric_limits<T>::max() ){
        ++m_listIt;
        m_val = 0;
    }else{
        ++m_val;
        if( m_val > m_listIt->second ){
            ++m_listIt;
            if( m_listIt == m_listEnd ){
                m_val = 0;
            }else{
                m_val = m_listIt->first;
            }
        }
    }

    return *this;
}

//------------------------------------------------------------------------------
template<typename T>
RangeListIterator<T> RangeListIterator<T>::operator++( int ) {
    auto temp = *this;
    ++*this;
    return temp;
}

//------------------------------------------------------------------------------
template<typename T>
const typename RangeListIterator<T>::value_type&
RangeListIterator<T>::operator*() const{
    return m_val;
}

//------------------------------------------------------------------------------
template<typename T>
class RangeList{
public:
    static_assert( std::is_integral<T>::value,
                   "RangeList works only with integral types" );
    using value_type = T;
    using RangeItem = std::pair< value_type, value_type >;
    using RangeItemList = std::list<RangeItem>;
    using RangeItem_iterator = typename RangeItemList::iterator;
    using RangeItem_const_iterator = typename RangeItemList::const_iterator;
    using iterator = RangeListIterator<T>;

    void insert( const T val );
    void remove( const T val );
    bool contains( const T val ) const;

    RangeItem_iterator beginItem();
    RangeItem_const_iterator beginItem() const;

    RangeItem_iterator endItem();
    RangeItem_const_iterator endItem() const;

    iterator begin();
    iterator end();

private:
    std::list<RangeItem> m_items;
};

//------------------------------------------------------------------------------
template<typename T>
void RangeList<T>::insert( const T val ){
    for( auto it = std::begin(m_items) ; it != std::end(m_items) ; ++it ){
        if( val < it->first ){
            if( val == (it->first - 1) ){
                it->first = val;
            }else{
                m_items.emplace( it, std::make_pair( val, val ) );
            }
            return;
        }else if( val <= it->second ){
            return;
        }else if( val == (it->second + 1) ){
            auto next = std::next(it);
            if( next != std::end(m_items) ){
                if( (val >= next->first - 1) and (val <= next->second) ){
                    it->second = next->second;
                    m_items.erase( next );
                    return;
                }
            }
            it->second = val;
            return;
        }
    }

    m_items.emplace_back( std::make_pair( val, val ) );
}

//------------------------------------------------------------------------------
template<typename T>
void RangeList<T>::remove( const T val ){
    for( auto it = std::begin(m_items) ; it != std::end(m_items) ; ++it ){
        if( val >= it->first and val <= it->second ){
            std::cout << "remove it " << std::endl;
            if( it->first == it->second ){
                m_items.erase( it );
                return;
            }
            if( val == it->first ){
                it->first = it->first + 1;
                return;
            }
            if( val == it->second ){
                it->second = it->second - 1;
                return;
            }
            m_items.emplace( it, std::make_pair( it->first, val - 1 ) );
            it->first = val + 1;
            return;
        }
        if( val < it->first ){
            return;
        }
    }
}

//------------------------------------------------------------------------------
template<typename T>
bool RangeList<T>::contains( const T val ) const{
    for( const auto & it: m_items ){
        auto rmin = it.first <= val;
        if( rmin and (it.second >= val) ){
            return true;
        }
        if( not rmin ){
            return false;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
template<typename T>
inline
typename RangeList<T>::RangeItem_iterator
RangeList<T>::beginItem(){
    return m_items.begin();
}

//------------------------------------------------------------------------------
template<typename T>
inline
typename RangeList<T>::RangeItem_const_iterator
RangeList<T>::beginItem() const{
    return m_items.begin();
}

//------------------------------------------------------------------------------
template<typename T>
inline
typename RangeList<T>::RangeItem_iterator
RangeList<T>::endItem(){
    return m_items.end();
}

//------------------------------------------------------------------------------
template<typename T>
inline
typename RangeList<T>::RangeItem_const_iterator
RangeList<T>::endItem() const{
    return m_items.end();
}

//------------------------------------------------------------------------------
template<typename T>
typename RangeList<T>::iterator
RangeList<T>::begin(){
    auto listIt = std::begin(m_items);
    return RangeListIterator<T>( listIt, listIt->first, std::end(m_items) );
}

//------------------------------------------------------------------------------
template<typename T>
inline
typename RangeList<T>::iterator
RangeList<T>::end(){
    return RangeListIterator<T>( std::end(m_items), 0, std::end(m_items) );
}

//------------------------------------------------------------------------------
#endif//RANGELIST_HPP_

//------------------------------------------------------------------------------
