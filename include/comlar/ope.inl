#ifndef COMLAR_OPE_INL
#define COMLAR_OPE_INL

#include "ope.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Ope<As...> Structure    )//
    //+    Member Function    +//
    //_ Constructor
    template <typename... As, typename... Bs>
    inline Ope<Arg<As...>, Bs...>::Ope(Bs&... bs_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   {bs_...}
    {
        return;
    }
 

    template <typename... As, typename... Bs>
    inline Ope<Arg<As...>, Bs...>::Ope(std::tuple<Bs...>& bt_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   (std::apply(std::tie<Bs...>, bt_))
    {
        return;
    }

    

    //_ Variable Function
    template <typename... As, typename... Bs>
    inline auto Ope<Arg<As...>, Bs...>::set_operate (const FuncType1& f1_) noexcept
        -> void
    {
        func1   =f1_;
        func_id =1;

        return;
    }


    template <typename... As, typename... Bs>
    inline auto Ope<Arg<As...>, Bs...>::set_operate (const FuncType2& f2_) noexcept
        -> void
    {
        func2   =f2_;
        func_id =2;

        return;
    }


    
    //_ Constant Function
    template <typename... As, typename... Bs>
    inline auto Ope<Arg<As...>, Bs...>::operate (const Arg<As...>& args_) noexcept
        -> int
    {
        switch(func_id){
            case 1:{
                std::tuple<const As..., Bs&...> all=std::tuple_cat(args_.tuple, tuple);
                return std::apply(func1, all);
            }
            case 2:{
                return func2(args_.tuple, tuple);
            }
            default:{
                return 0;
            }
        }
    }



    //(    comlar::Ope<std::array<A, S>, Bs..> Structure    )//
    //+    Member Function    +//
    //_ Constructor
    template <typename A, size_t S, typename... Bs>
    inline Ope<Arg<std::array<A, S>>, Bs...>::Ope(Bs&... bs_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   {bs_...}
    {
        return;
    }
 

    template <typename A, size_t S, typename... Bs>
    inline Ope<Arg<std::array<A, S>>, Bs...>::Ope(std::tuple<Bs...>& bt_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   (std::apply(std::tie<Bs...>, bt_))
    {
        return;
    }

    

    //_ Variable Function
    template <typename A, size_t S, typename... Bs>
    inline auto Ope<Arg<std::array<A, S>>, Bs...>::set_operate (const FuncType1& f1_) noexcept
        -> void
    {
        func1   =f1_;
        func_id =1;

        return;
    }


    template <typename A, size_t S, typename... Bs>
    inline auto Ope<Arg<std::array<A, S>>, Bs...>::set_operate (const FuncType2& f2_) noexcept
        -> void
    {
        func2   =f2_;
        func_id =2;

        return;
    }


    
    //_ Constant Function
    template <typename A, size_t S, typename... Bs>
    inline auto Ope<Arg<std::array<A, S>>, Bs...>::operate (const Arg<std::array<A, S>>& args_) noexcept
        -> int
    {
        switch(func_id){
            case 1:{
                std::tuple<const std::array<A, S>&> a(args_.array);
                std::tuple<const std::array<A, S>, Bs&...> all=std::tuple_cat(a, tuple);
                return std::apply(func1, all);
            }
            case 2:{
                return func2(args_.array, tuple);
            }
            default:{
                return 0;
            }
        }
    }



    //(    comlar::Ope<std::vector<A>, Bs..> Structure    )//
    //+    Member Function    +//
    //_ Constructor
    template <typename A, typename... Bs>
    inline Ope<Arg<std::vector<A>>, Bs...>::Ope(Bs&... bs_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   {bs_...}
    {
        return;
    }
 

    template <typename A, typename... Bs>
    inline Ope<Arg<std::vector<A>>, Bs...>::Ope(std::tuple<Bs...>& bt_) noexcept
        : func1   { }
        , func2   { }
        , func_id {0}
        , tuple   (std::apply(std::tie<Bs...>, bt_))
    {
        return;
    }

    

    //_ Variable Function
    template <typename A, typename... Bs>
    inline auto Ope<Arg<std::vector<A>>, Bs...>::set_operate (const FuncType1& f1_) noexcept
        -> void
    {
        func1   =f1_;
        func_id =1;

        return;
    }


    template <typename A, typename... Bs>
    inline auto Ope<Arg<std::vector<A>>, Bs...>::set_operate (const FuncType2& f2_) noexcept
        -> void
    {
        func2   =f2_;
        func_id =2;

        return;
    }


    
    //_ Constant Function
    template <typename A, typename... Bs>
    inline auto Ope<Arg<std::vector<A>>, Bs...>::operate (const Arg<std::vector<A>>& args_) noexcept
        -> int
    {
        switch(func_id){
            case 1:{
                std::tuple<const std::vector<A>&> a(args_.vector);
                std::tuple<const std::vector<A>, Bs&...> all=std::tuple_cat(a, tuple);
                return std::apply(func1, all);
            }
            case 2:{
                return func2(args_.vector, tuple);
            }
            default:{
                return 0;
            }
        }
    }
}
#endif
