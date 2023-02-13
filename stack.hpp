#pragma once
#include "ft_containers.hpp"
#include "vector.hpp"

 // --> https://cplusplus.com/reference/stack/stack/
namespace ft
{
	template<class T, class container = ft::vector<T> >
	class stack
    {
    	public:
        //====================================================================//
        //                    M E M B E R          T Y P E S                  //
        //====================================================================//
        	typedef T           value_type;
        	typedef container   container_type;
        //====================================================================//
        //                        C O N S T R U C T O R                       //
        //====================================================================//
        // --> https://cplusplus.com/reference/stack/stack/stack/
        explicit stack (const container_type& ctnr = container_type()) { _ctnr = ctnr;}
        //====================================================================//
        //                  M E M B E R    F U N C T I O N S                  //
        //====================================================================//
		// --> https://en.cppreference.com/w/cpp/container/stack
		// --> https://legacy.cplusplus.com/reference/stack/stack/
			bool empty() const                  {return (_ctnr.empty());}
			size_t size() const                 {return (_ctnr.size());}
			value_type& top()                   {return (_ctnr.back());}
			const value_type& top() const       {return (_ctnr.back());}
			void push (const value_type& val)   {_ctnr.push_back(val);}
			void pop()							{_ctnr.pop_back();}
        //====================================================================//
        //           R E L A T I O N A L          O P E R A T O R S           //
        //====================================================================//
        // --> https://cplusplus.com/reference/stack/stack/operators/
		template <class TT, class Container>
		friend bool operator== (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return lhs._ctnr == rhs._ctnr;}
		
		template <class TT, class Container>
		friend bool operator!= (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return (lhs._ctnr != rhs._ctnr);}

		template <class TT, class Container>
		friend bool operator<  (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return (lhs._ctnr < rhs._ctnr);}

		template <class TT, class Container> 
		friend bool operator<= (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return (lhs._ctnr <= rhs._ctnr);}

		template <class TT, class Container> 
		friend bool operator>  (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return (lhs._ctnr > rhs._ctnr);}

		template <class TT, class Container> 
		friend bool operator>= (const stack<TT,Container>& lhs, const stack<TT,Container>& rhs)
		{return (lhs._ctnr >= rhs._ctnr);}
    //--------------------------------------------------------------------------
    	protected:
        	container_type      _ctnr;
	};
}
// typedef -> give new name to existing data type
// explicit -> only direct initialisation (no implicit conversion or copy initialisation)
// friend -> can acess private & protected stuff from class 