//#include "command.hpp"

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




    //(    comlar::Command<Arg, Ope> Structure    )//
    //_ Constructor
    template <class Arg, class Ope> template <typename... As>
    inline Command<Arg, Ope>::Command (const std::string& abrn_, const std::string& fomn_, Attribute atr_, As&... as_) noexcept
        : Core {abrn_, fomn_, atr_}
        , Arg  { }
        , Ope  {as_...}
    {
        Arg::stream_type_str(Core::typestr);

        return;
    }
    


    //_ Varialbe Function
    template <class Arg, class Ope> template <typename Func>
    inline auto Command<Arg, Ope>::set_check (Func* f_) noexcept
        -> void
    {
        Arg::set_check(reinterpret_cast<void*>(f_));

        return;
    }

    
    template <class Arg, class Ope> template <typename Func>
    inline auto Command<Arg, Ope>::set_operate (Func* f_) noexcept
        -> void
    {
        Ope::set_operate(reinterpret_cast<void*>(f_));

        return;
    }
    

    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_nof_args (void) noexcept
        -> size_t
    {
        return Arg::nof_args();
    }
 

    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::set_value (size_t num_, const char* str_) noexcept
        -> int
    {
        return Arg::set_value(num_, str_);
    }


    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_operate (void) noexcept
        -> int
    {
        return Arg::_operate1(*this);
    }


    template <class Arg, class Ope>
    inline auto Command<Arg, Ope>::_check (void) noexcept
        -> int
    {
        return Arg::_check1(*this);
    }
}
