#pragma once
#include "ft_containers.hpp"
#include "vector.hpp"

 // --> https://cplusplus.com/reference/stack/stack/
namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
    {
    	public:
        //====================================================================//
        //                    M E M B E R          T Y P E S                  //
        //====================================================================//
		// typedef -> give new name to existing data type
		typedef T           value_type;
		typedef Container   container_type;
        //====================================================================//
        //                        C O N S T R U C T O R                       //
        //====================================================================//
        // --> https://cplusplus.com/reference/stack/stack/stack/
        explicit stack (const container_type& ctnr = container_type()) { c = ctnr;}
        //====================================================================//
        //                  M E M B E R    F U N C T I O N S                  //
        //====================================================================//
		// --> https://en.cppreference.com/w/cpp/container/stack
		// --> https://legacy.cplusplus.com/reference/stack/stack/
			bool empty() const                  {return (c.empty());}
			size_t size() const                 {return (c.size());}
			value_type& top()                   {return (c.back());}
			const value_type& top() const       {return (c.back());}
			void push (const value_type& val)   {c.push_back(val);}
			void pop()							{c.pop_back();}
        //====================================================================//
        //           R E L A T I O N A L          O P E R A T O R S           //
        //====================================================================//
        // --> https://cplusplus.com/reference/stack/stack/operators/
		template <class TT, class CContainer>
		friend bool operator== (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);
		
		template <class TT, class CContainer>
		friend bool operator!= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);

		template <class TT, class CContainer>
		friend bool operator<  (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);

		template <class TT, class CContainer> 
		friend bool operator<= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);

		template <class TT, class CContainer> 
		friend bool operator>  (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);

		template <class TT, class CContainer> 
		friend bool operator>= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs);
    //--------------------------------------------------------------------------
    	protected:
        	container_type      c;
	};
		template <class TT, class CContainer>
		 bool operator== (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs) // TO DO : without friend
		{return lhs.c == rhs.c;}
		
		template <class TT, class CContainer>
		 bool operator!= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs)
		{return (lhs.c != rhs.c);}

		template <class TT, class CContainer>
		 bool operator<  (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs)
		{return (lhs.c < rhs.c);}

		template <class TT, class CContainer> 
		 bool operator<= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs)
		{return (lhs.c <= rhs.c);}

		template <class TT, class CContainer> 
		 bool operator>  (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs)
		{return (lhs.c > rhs.c);}

		template <class TT, class CContainer> 
		 bool operator>= (const stack<TT,CContainer>& lhs, const stack<TT,CContainer>& rhs)
		{return (lhs.c >= rhs.c);}
}
// explicit -> only direct initialisation (no implicit conversion or copy initialisation)
// friend -> can acess private & protected stuff from class 