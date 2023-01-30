#ifndef COMLAR_OPTION_INL
#define COMLAR_OPTION_INL

#include "option.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    comlar::Core Structure    )//
    //+    Member Function    +//
    //_ Constructor
    inline Core::Core (const std::string& abrn_, const std::string& fomn_, Attribute atr_) noexcept
        : abr_name  {abrn_}
        , fom_name  {fomn_}
        , attribute {atr_}
        , message   { }
        , typestr   { }
        , supple    { }
        , field     {0}
        , choiced   {false}
    {
        return;
    }



    //_ Variable Function
    inline auto Core::set_info (const std::string& mes_, const std::string& sup_) noexcept
        -> void
    {
        message =mes_;
        supple  =sup_;

        return;
    }


    inline auto Core::set_field (Field field_) noexcept
        -> void
    {
        field =field_;

        return;
    }




    //(    comlar::Option<As...> Structure    )//
    //+    Member Constant Expression Function    +//
    template <typename... As>
    inline constexpr auto Option<As...>::default_assign (void) noexcept
        -> std::function<int(const std::tuple<As...>&, std::tuple<As&...>&)>
    {
        return [](const std::tuple<As...>& arg_, std::tuple<As&...>& ope_){
            
            ope_=arg_;

            return 0;
        };
    }


    //+    Member Function    +//
    //_ Constructor
    template <typename... As>
    inline Option<As...>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, As&... as_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  {as_...}
    {
        args.stream_type_str(Core::typestr);

        return;
    }
 

    template <typename... As>
    inline Option<As...>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, std::tuple<As...>& tp_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  (tp_)
    {
        args.stream_type_str(Core::typestr);

        return;
    }
   


    //_ Varialbe Function
    template <typename... As>
    inline auto Option<As...>::set_value (size_t num_, const char* str_) noexcept
        -> int
    {
        return args.set_value(num_, str_);
    }


    template <typename... As>
    inline auto Option<As...>::nof_args (void) noexcept
        -> size_t
    {
        return Arg<As...>::nof_args();
    }
    
    

    template <typename... As>
    inline auto Option<As...>::operate (void) noexcept
        -> int
    {
        return ope.operate(args);
    }


    template <typename... As>
    inline auto Option<As...>::function (void) noexcept
        -> int
    {
        return args.function();
    }


    template <typename... As>
    inline auto Option<As...>::set_function (const typename Arg<As...>::FuncType1& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }


    template <typename... As>
    inline auto Option<As...>::set_function (const typename Arg<As...>::FuncType2& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }
           
    
    template <typename... As>
    inline auto Option<As...>::set_operate (const typename Ope<Arg<As...>, As...>::FuncType1& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }
 

    template <typename... As>
    inline auto Option<As...>::set_operate (const typename Ope<Arg<As...>, As...>::FuncType2& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }



    //(    comlar::Option<Arg<>, bool> Structure    )//
    //+    Member Constant Expression Function    +//
    template <bool B> inline auto Option<Arg<>, bool>::default_flag (void) noexcept
        -> std::function<int(bool&)>
    {
        return [](bool& b_){
            b_=B;
            return 0;
        };
    }



    //+    Member Function    +//
    //_ Constructor
    inline Option<Arg<>, bool>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, bool& bs_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  {bs_}
    {
        args.stream_type_str(Core::typestr);

        return;
    }



    inline Option<Arg<>, bool>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, std::tuple<bool>& tp_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  (tp_)
    {
        args.stream_type_str(Core::typestr);

        return;
    }
        


    //_ Varialbe Function
    inline auto Option<Arg<>, bool>::set_value (size_t num_, const char* str_) noexcept
        -> int
    {
        return args.set_value(num_, str_);
    }


    inline auto Option<Arg<>, bool>::nof_args (void) noexcept
        -> size_t
    {
        return Arg<>::nof_args();
    }
    

    inline auto Option<Arg<>, bool>::operate (void) noexcept
        -> int
    {
        return ope.operate(args);
    }


    inline auto Option<Arg<>, bool>::function (void) noexcept
        -> int
    {
        return args.function();
    }


    inline auto Option<Arg<>, bool>::set_function (const typename Arg<>::FuncType1& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }


    inline auto Option<Arg<>, bool>::set_function (const typename Arg<>::FuncType2& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }
           
    
    inline auto Option<Arg<>, bool>::set_operate (const typename Ope<Arg<>, bool>::FuncType1& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }
 

    inline auto Option<Arg<>, bool>::set_operate (const typename Ope<Arg<>, bool>::FuncType2& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }



    //(    comlar::Option<Arg<As...>, Bs...> Structure    )//
    //_ Constructor
    template <typename... As, typename... Bs>
    inline Option<Arg<As...>, Bs...>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, Bs&... bs_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  {bs_...}
    {


        args.stream_type_str(Core::typestr);

        return;
    }


    template <typename... As, typename... Bs>
    inline Option<Arg<As...>, Bs...>::Option (const std::string& abrn_, const std::string& fomn_, Attribute atr_, std::tuple<Bs...>& tp_) noexcept
        : Core {abrn_, fomn_, atr_}
        , args { }
        , ope  (tp_)
    {
        args.stream_type_str(Core::typestr);

        return;
    }



    //_ Varialbe Function
    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::set_value (size_t num_, const char* str_) noexcept
        -> int
    {
        return args.set_value(num_, str_);
    }


    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::nof_args (void) noexcept
        -> size_t
    {
        return Arg<As...>::nof_args();
    }
    
    

    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::operate (void) noexcept
        -> int
    {
        return ope.operate(args);
    }


    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::function (void) noexcept
        -> int
    {
        return args.function();
    }


    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::set_function (const typename Arg<As...>::FuncType1& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }


    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::set_function (const typename Arg<As...>::FuncType2& f_) noexcept
        -> void
    {
        args.set_function(f_);

        return;
    }
           
    
    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::set_operate (const typename Ope<Arg<As...>, Bs...>::FuncType1& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }
 

    template <typename... As, typename... Bs>
    inline auto Option<Arg<As...>, Bs...>::set_operate (const typename Ope<Arg<As...>, Bs...>::FuncType2& f_) noexcept
        -> void
    {
        ope.set_operate(f_);

        return;
    }
}
#endif
