//#include "constraint.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Constraint<A, B> Structure    )//
    //+    Static Member Function    +//
    template <typename A, class B> template <typename C>
    inline auto Constraint<A, B>::get_result_func (VirtualType<C>) noexcept
        -> bool(*)(const C&, const A&)
    {    
        return +[](const C& c_, const A& a_){

            B compare;
                
            return compare(c_, a_);
        };
    }


    //+    Member Function    +//
    //_ Constructor
    template <typename A, class B> 
    inline Constraint<A, B>::Constraint (A value_) noexcept
        : value {value_}
    {
        return;
    }



    
    //(    comlar::Constraint<A, B, As...> Structure    )//
    //+    Static Member Function    +//
    template <typename A, typename B, class... As> template <typename D, size_t N>
    inline auto Constraints<A, B, As...>::get_result_func (VirtualType<D>, Num<N>) noexcept
        -> bool(*)(const D&, const std::array<A, N>&, size_t)
    {    
        return +[](const D&, const std::array<A, N>&, size_t){
                
            return true;
        };
    }


    template <typename A, typename B, class C, class... As> template <typename D, size_t N>
    inline auto Constraints<A, B, C, As...>::get_result_func (VirtualType<D>, Num<N>) noexcept
        -> bool(*)(const D&, const std::array<A, N>&, size_t)
    {    
        return +[](const D& d_, const std::array<A, N>& ar_, size_t n_){

            B logical;
            C compare;
                
            return logical(compare(d_, ar_[n_]), Constraints<A, B, As...>::get_result_func(VirtualType<D>{ }, Num<N>{ })(d_, ar_, n_+1));
        };
    }
    

       
    //+    Member Function    +//
    //_ Constructor
    template <typename A, typename B, class... As>
    inline auto Constraints<A, B, As...>::_construct (std::initializer_list<A> lst_, size_t n_) noexcept
        -> void
    {
        return;
    }


    template <typename A, typename B, class C, class... As> 
    inline auto Constraints<A, B, C, As...>::_construct (std::initializer_list<A> lst_, size_t n_) noexcept -> void
    {
        value=lst_.begin()[n_];
        constraints._construct(lst_, n_+1);

        return;
    }

       
    template <typename A, typename B, class... As>
    inline Constraints<A, B, As...>::Constraints (void) noexcept
    {
        return;
    }


    template <typename A, typename B, class C, class... As> 
    inline Constraints<A, B, C, As...>::Constraints (void) noexcept
    {
        return;
    }


    template <typename A, typename B, class C, class... As>
    inline Constraints<A, B, C, As...>::Constraints (std::initializer_list<A> lst_) noexcept
    {
        _construct(lst_);

        return;
    }


    
    //_ Constant Function
    template <typename A, typename B, class... As>
    inline auto Constraints<A, B, As...>::get_value (size_t n_) const noexcept
        -> const A&
    {
        std::cerr<<"[comlar::Constraints<A, B, As...>::get_value] Operation reached invalid function."<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    

    template <typename A, typename B, class C, class... As>
    inline auto Constraints<A, B, C, As...>::get_value (size_t n_) const noexcept -> const A&
    {
        if(n_==0) return value;
        else      return constraints.get_value(n_-1);
    }
}
