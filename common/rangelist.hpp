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
template<typename T,
         typename = typename std::enable_if<std::is_integral<T>::value>::type>
class RangeList; // undefined

//------------------------------------------------------------------------------
template<typename T>
class RangeList<T>{
public:
    using value_type = T;
    using RangeItem = std::pair< value_type, value_type >;
    using RangeItemList = std::list<RangeItem>;
    using RangeItem_iterator = typename RangeItemList::iterator;
    using RangeItem_const_iterator = typename RangeItemList::const_iterator;

    void insert( const value_type val );
    bool contains( const value_type val ) const;

    RangeItem_iterator beginItem();
    RangeItem_const_iterator beginItem() const;

    RangeItem_iterator endItem();
    RangeItem_const_iterator endItem() const;

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
            it->second = val;
            return;
        }
    }

    m_items.emplace_back( std::make_pair( val, val ) );
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
#endif//RANGELIST_HPP_

//------------------------------------------------------------------------------
