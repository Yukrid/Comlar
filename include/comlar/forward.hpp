#ifndef COMLAR_FORWARD_HPP
#define COMLAR_FORWARD_HPP

#include <iostream>

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Declaraion    //
    //-----------------------//
    //(    comlar::Arg<As...> Structure   )//
    template <typename... As>
    struct Arg;
    
    //(    comlar::Ope<As...> Structure   )//
    template <typename... As>
    struct Ope;

    //(    comlar::Command<Arg, Ope> Structure Template    )//
    template <class Arg, class Ope>
    struct Command;

    //(    comlar::Executor Structure Template    )//
    struct Executor;

    //(    comlar::Constraint<A, B> Structure Template    )//
    template <typename A, class B>
    struct Constraint;

    //(    comlar::Constraint<A, B, As...> Structure Template    )//
    template <typename A, class B, class... As>
    struct Constraints;


    //-------------//
    //    Alias    //
    //-------------//
    using Field  =size_t;
    using Les =std::less<>;
    using Leq =std::less_equal<>;
    using Grt =std::greater<>;
    using Geq =std::greater_equal<>;
    using Eq  =std::equal_to<>;
    using Neq =std::not_equal_to<>;

    template <typename A, class... As> using AndConstraints =Constraints<A, std::logical_and<>, As...>;
    template <typename A, class... As> using OrConstraints  =Constraints<A, std::logical_or<>, As...>;


    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Attribute Enumeration    )//
    enum Attribute : uint8_t{
        REQUIRED, OPTIONAL
    };


    //(    comlar::Num Structure    )//
    template <size_t N>
    struct Num{

    };


    //(    comlar::VirtualType Structure    )//
    template <typename T>
    struct VirtualType{
    
    };


    //----------------------------//
    //    Function Declaration    //
    //----------------------------//
    //(    comlar Namespace    )//
    template <typename A> [[noreturn]] inline auto str_conv                     (const char*) noexcept -> A;
    template <>                        inline auto str_conv<short>              (const char*) noexcept -> short;
    template <>                        inline auto str_conv<int>                (const char*) noexcept -> int;
    template <>                        inline auto str_conv<long>               (const char*) noexcept -> long;
    template <>                        inline auto str_conv<long long>          (const char*) noexcept -> long long;
    template <>                        inline auto str_conv<bool>               (const char*) noexcept -> bool;
    template <>                        inline auto str_conv<unsigned char>      (const char*) noexcept -> unsigned char;
    template <>                        inline auto str_conv<unsigned short>     (const char*) noexcept -> unsigned short;
    template <>                        inline auto str_conv<unsigned int>       (const char*) noexcept -> unsigned int;
    template <>                        inline auto str_conv<unsigned long>      (const char*) noexcept -> unsigned long;
    template <>                        inline auto str_conv<unsigned long long> (const char*) noexcept -> unsigned long long;
    template <>                        inline auto str_conv<float>              (const char*) noexcept -> float;
    template <>                        inline auto str_conv<double>             (const char*) noexcept -> double;
    template <>                        inline auto str_conv<long double>        (const char*) noexcept -> long double;
    template <>                        inline auto str_conv<char>               (const char*) noexcept -> char;
    template <>                        inline auto str_conv<std::string>        (const char*) noexcept -> std::string;
    template <>                        inline auto str_conv<const char*>        (const char*) noexcept -> const char*;
    
    template <typename A>           inline auto default_assign    (void)                     noexcept -> int(*)(const A&, A&);
    template <bool B>               inline auto default_bool      (void)                     noexcept -> int(*)(bool&);
    template <typename A, class B>  inline auto default_cstr      (const A&)                 noexcept -> Constraint<A, B>;
    template <class A, class... As> inline auto default_and_cstrs (std::initializer_list<A>) noexcept -> AndConstraints<A, As...>;
    template <class A, class... As> inline auto default_or_cstrs  (std::initializer_list<A>) noexcept -> OrConstraints<A, As...>;
}

#include "forward.inl"

#endif

