#ifndef COMLAR_CONSTRAINT_HPP
#define COMLAR_CONSTRAINT_HPP

#include "forward.hpp"
#include <array>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Constraint<A, B> Structure    )//
    template <typename A, class B>
    struct Constraint{
    
        //+    Static Member Function    +//
        template <typename C>
        inline static auto get_result_func (VirtualType<C>) noexcept -> bool(*)(const C&, const A&);

        //+    Member Varialbe    +//
        A value;

        //+    Member Function    +//
        //_ Constructor
        inline Constraint (A) noexcept;
    };




    //(    comlar::Constraint<A, B, As...> Structure    )//
    template <typename A, typename B, class... As>
    struct Constraints{

        //+    Constant Expression Member Value    +// 
        template <typename D, size_t N>
        inline static auto get_result_func (VirtualType<D>, Num<N>) noexcept -> bool(*)(const D&, const std::array<A, N>&, size_t);

       
        //+    Member Function    +//
        //_ Constructor
        inline auto _construct   (std::initializer_list<A>, size_t =0) noexcept -> void;
        inline       Constraints (void)                                noexcept;

        //_ Constant Function
        [[noreturn]] inline auto get_value (size_t ) const noexcept -> const A&;
    };



    template <typename A, typename B, class C, class... As>
    struct Constraints<A, B, C, As...>{
 
        //+    Static Member Function    +//
        template <typename D, size_t N>
        inline static auto get_result_func (VirtualType<D>, Num<N>) noexcept -> bool(*)(const D&, const std::array<A, N>&, size_t); 
 

        //+    Member Variable    +//
        A                        value;
        Constraints<A, B, As...> constraints;
       

        //+    Member Function    +//
        //_ Constructor
        inline auto _construct   (std::initializer_list<A>, size_t=0) noexcept -> void; 
        inline       Constraints (void)                               noexcept;
        inline       Constraints (std::initializer_list<A>)           noexcept;

        //_ Constant Function
        inline auto get_value (size_t) const noexcept -> const A&;
    };
}

#include "constraint.inl"

#endif

