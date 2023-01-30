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

    //(    comlar::Option<As...> Structure Template    )//
    template <typename... As>
    struct Option;

    //(    comlar::Executor Structure Template    )//
    struct Executor;



    //-------------//
    //    Alias    //
    //-------------//
    using Field  =size_t;


    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Attribute Enumeration    )//
    enum Attribute : uint8_t{
        REQUIRED, OPTIONAL
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
}

#include "forward.inl"

#endif

