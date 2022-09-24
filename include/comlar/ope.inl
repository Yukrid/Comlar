//#include "ope.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Ope<As...> Structure    )//
    //+    Member Function    +//
    //_ Variable Function
    template <typename... As>
    inline auto Ope<As...>::set_operate (void* f_) noexcept
        -> void
    {
        operate=f_;

        return;
    }


    template <typename A, typename... As>
    inline auto Ope<A, As...>::set_operate (void* f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }
    


    //_ Constant Function
    template <typename... As> template <class Com, typename... Bs>
    inline auto Ope<As...>::_operate2 (Com& com_, Bs&... bs_) noexcept
        -> int
    {
        if(operate) return reinterpret_cast<int(*)(Bs&...)>(operate)(bs_...);
        else        return 0;
    }


    template <typename A, typename... As> template <class Com, typename... Bs>
    inline auto Ope<A, As...>::_operate2 (Com& com_, Bs&... bs_) noexcept
        -> int
    {
        return ope._operate2(com_, bs_..., ope_val);
    }
}
