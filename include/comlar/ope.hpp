#ifndef COMLAR_OPE_HPP
#define COMLAR_OPE_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Ope<As...> Structure    )//
    template <typename... As>
    struct Ope{

        //+    Member Varialbe    +//
        void* operate =nullptr;


        //+    Member Function    +//
        //_ Variable Function
        inline auto  set_operate (void*) noexcept -> void; 
        
        //_ Constant Function
        template <class Com, typename... Bs> inline auto _operate2 (Com&, Bs&...) noexcept -> int;
    };


    template <typename A, typename... As>
    struct Ope<A, As...>{
        

        //+    Member Variable    +//
        A&         ope_val;
        Ope<As...> ope;
        

        //+    Member Function    +//
        //_ Variable Function
        inline auto set_operate (void*) noexcept -> void;

        //_ Constant Function
        template <class Com, typename... Bs> inline auto _operate2 (Com& com_, Bs&... bs_) noexcept -> int;
    };
}

#include "ope.inl"

#endif
