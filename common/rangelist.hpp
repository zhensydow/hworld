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
    using RangeItem = std::pair< value_type, unsigned int>;

    void insert( const value_type val );
    bool contains( const value_type val ) const;
    
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
                it->second = it->second + 1;
                std::cout <<  " increase begin " << val << std::endl;
                return;
            }else{
                m_items.emplace( it, std::make_pair( val, 1 ) );
                std::cout <<  " emplace before " << val << std::endl;
                return;
            }
        }else if( val < (it->first + it->second) ){
            std::cout <<  " already " << val << std::endl;
            return;
        }else if( val == (it->first + it->second) ){
            it->second = it->second + 1;
            std::cout <<  " increase end " << val << std::endl;
            return;
        }
    }
    
    std::cout <<  " emplace back " << val << std::endl;
    m_items.emplace_back( std::make_pair( val, 1 ) );
}

//------------------------------------------------------------------------------
template<typename T>
bool RangeList<T>::contains( const T val ) const{
    for( const auto & it: m_items ){
        std::cout << " ck " << it.first << "," << it.second << " = " << val;
        std::cout << std::endl;
        auto rmin = it.first <= val;
        auto rmax = (it.first + it.second) > val;
        if( rmin and rmax ){
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------
#endif//RANGELIST_HPP_

//------------------------------------------------------------------------------
