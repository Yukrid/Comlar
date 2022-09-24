#ifndef COMLAR_ARG_HPP
#define COMLAR_ARG_HPP

#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Arg<As...> Structure    )//
    template <typename... As>
    struct Arg{
        
        //+    Member Constant Expression Function    +//
                            static constexpr inline auto  nof_args (void) noexcept -> int32_t;
        template <size_t N> static constexpr        auto _type     (Num<N> =Num<N>{ }) noexcept -> void;

        //+    Member Varialbe    +//
        void* check =nullptr;


        //+    Member Function    +//
        //_ Variable Function
        inline auto set_check (void*)               noexcept -> void; 
        inline auto set_value (size_t, const char*) noexcept -> int;

        //_ Constant Function
        template <typename Com, typename... Bs> inline auto _check1   (Com& com_, const Bs&... bs_) const noexcept -> int;
        template <typename Com, typename... Bs> inline auto _operate1 (Com& com_, const Bs&... bs_) const noexcept -> int;
        
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };


    template <typename A, typename... As>
    struct Arg<A, As...>{
        
        //+    Member Constant Expression Function    +//
                            static constexpr inline auto  nof_args (void) noexcept -> int32_t;
        template <size_t N> static constexpr        auto _type     (Num<N> =Num<N>{ }) noexcept -> decltype(Arg<As...>::template _type<N-1>());
                            static constexpr        auto _type     (Num<0> =Num<0>{ }) noexcept -> A;


        //+    Alias    +//
        template <size_t N> using type = decltype(_type(std::declval<Num<N>>()));
    

        //+    Member Variable    +//
        A          arg_val;
        Arg<As...> arg;
        

        //+    Member Function    +//
        //_ Variable Function
        inline auto set_check (void*)               noexcept -> void;
        inline auto set_value (size_t, const char*) noexcept -> int;

        //_ Constant Function
        template <typename Com, typename... Bs> inline auto _check1   (Com& com_, const Bs&... bs_) const noexcept -> int;
        template <typename Com, typename... Bs> inline auto _operate1 (Com& com_, const Bs&... bs_) const noexcept -> int;
    
        inline auto stream_type_str (std::string& str_) const noexcept -> std::string&;
    };
}

#include "arg.inl"

#endif
