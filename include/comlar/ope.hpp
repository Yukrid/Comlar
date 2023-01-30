#ifndef COMLAR_OPE_HPP
#define COMLAR_OPE_HPP

#include "forward.hpp"
#include "arg.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //-----------------------//
    //    Type Definition    //
    //-----------------------//
    //(    comlar::Ope<As...> Structure Template    )//
    template <typename... As>
    struct Ope{
    
    };


    //(    comlar::Ope<Arg<As...>, Bs...> Specialized Structure Template    )//
    template <typename... As, typename... Bs>
    struct Ope<Arg<As...>, Bs...>{


        //+    Alias    +//
        using FuncType1 = std::function<int(const As&..., Bs&...)>;
        using FuncType2 = std::function<int(const std::tuple<As...>&, std::tuple<Bs&...>&)>;
        
        //+    Member Varialbe    +//
        FuncType1          func1;
        FuncType2          func2;
        uint8_t            func_id;
        std::tuple<Bs&...> tuple;

        //+    Member Function    +//
        //_ Constructor
        inline Ope (Bs&...)              noexcept; 
        inline Ope (std::tuple<Bs...>&) noexcept; 

        //_ Variable Function
        inline auto set_operate (const FuncType1&) noexcept -> void; 
        inline auto set_operate (const FuncType2&) noexcept -> void; 
        
        //_ Constant Function
        inline auto operate (const Arg<As...>&) noexcept -> int;
    };


    //(    comlar::Ope<std::array<A, S>, Bs...> Specialized Structure Template    )//
    template <typename A, size_t S, typename... Bs>
    struct Ope<Arg<std::array<A, S>>, Bs...>{


        //+    Alias    +//
        using FuncType1 = std::function<int(const std::array<A, S>&, Bs&...)>;
        using FuncType2 = std::function<int(const std::array<A, S>&, std::tuple<Bs&...>&)>;
        
        //+    Member Varialbe    +//
        FuncType1          func1;
        FuncType2          func2;
        uint8_t            func_id;
        std::tuple<Bs&...> tuple;

        //+    Member Function    +//
        //_ Constructor
        inline Ope (Bs&...)              noexcept; 
        inline Ope (std::tuple<Bs...>&) noexcept; 

        //_ Variable Function
        inline auto set_operate (const FuncType1&) noexcept -> void; 
        inline auto set_operate (const FuncType2&) noexcept -> void; 
        
        //_ Constant Function
        inline auto operate (const Arg<std::array<A, S>>&) noexcept -> int;
    };



    //(    comlar::Ope<std::vector<A>, Bs...> Specialized Structure Template    )//
    template <typename A, typename... Bs>
    struct Ope<Arg<std::vector<A>>, Bs...>{


        //+    Alias    +//
        using FuncType1 = std::function<int(const std::vector<A>&, Bs&...)>;
        using FuncType2 = std::function<int(const std::vector<A>&, std::tuple<Bs&...>&)>;
        
        //+    Member Varialbe    +//
        FuncType1          func1;
        FuncType2          func2;
        uint8_t            func_id;
        std::tuple<Bs&...> tuple;

        //+    Member Function    +//
        //_ Constructor
        inline Ope (Bs&...)              noexcept; 
        inline Ope (std::tuple<Bs...>&) noexcept; 

        //_ Variable Function
        inline auto set_operate (const FuncType1&) noexcept -> void; 
        inline auto set_operate (const FuncType2&) noexcept -> void; 
        
        //_ Constant Function
        inline auto operate (const Arg<std::vector<A>>&) noexcept -> int;
    };

}

#include "ope.inl"

#endif
