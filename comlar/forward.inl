//#include "forward.hpp"

//+++++++++++++++++//
//    Namespace    //
//+++++++++++++++++//
namespace comlar{

    //---------------------------//
    //    Variable Definition    //
    //---------------------------//
    std::ostream& error_os =std::cerr;



    //---------------------------//
    //    Function Definition    //
    //---------------------------//
    //(    com Namespace    )//
    template <typename A>
    [[noreturn]] inline auto str_conv (const char*) noexcept
        -> A
    {
        error_os<<"Unknown conversion from string to value."<<std::endl;
        std::exit(EXIT_FAILURE);
    }


    template <>
    inline auto str_conv<short> (const char* str_) noexcept -> short
    {
        return static_cast<short>(std::stoi(str_));
    }


    template <>
    inline auto str_conv<int> (const char* str_) noexcept -> int
    {
        return std::stoi(str_);
    }


    template <>
    inline auto str_conv<long> (const char* str_) noexcept -> long
    {
        return std::stol(str_);
    }


    template <>
    inline auto str_conv<long long> (const char* str_) noexcept -> long long
    {
        return std::stol(str_);
    }


    template <>
    inline auto str_conv<bool> (const char* str_) noexcept -> bool
    {
        return static_cast<bool>(std::stoul(str_));
    }


    template <>
    inline auto str_conv<unsigned char> (const char* str_) noexcept -> unsigned char
    {
        return static_cast<unsigned char>(std::stoul(str_));
    }


    template <>
    inline auto str_conv<unsigned short> (const char* str_) noexcept -> unsigned short
    {
        return static_cast<unsigned short>(std::stoul(str_));
    }


    template <>
    inline auto str_conv<unsigned int> (const char* str_) noexcept -> unsigned int
    {
        return static_cast<unsigned int>(std::stoul(str_));
    }


    template <>
    inline auto str_conv<unsigned long> (const char* str_) noexcept -> unsigned long
    {
        return std::stoul(str_);
    }


    template <>
    inline auto str_conv<unsigned long long> (const char* str_) noexcept -> unsigned long long
    {
        return std::stoull(str_);
    }


    template <>
    inline auto str_conv<float> (const char* str_) noexcept -> float
    {
        return static_cast<float>(std::stod(str_));
    }


    template <>
    inline auto str_conv<double> (const char* str_) noexcept -> double
    {
        return std::stod(str_);
    }


    template <>
    inline auto str_conv<long double> (const char* str_) noexcept -> long double
    {
        return std::stold(str_);
    }


    template <>
    inline auto str_conv<char> (const char* str_) noexcept -> char
    {
        return str_[0];
    }


    template <>
    inline auto str_conv<std::string> (const char* str_) noexcept -> std::string
    {
        return std::string{str_};
    }


    template <>
    inline auto str_conv<const char*> (const char* str_) noexcept -> const char*
    {
        return str_;
    }
    
    template <typename A>
    inline auto default_assign (void) noexcept -> int(*)(const A&, A&)
    {
        return +[](const A& i_, A& o_){
            
            o_=i_;

            return 0;
        };
    }


    template <bool B>
    inline auto default_flag (void) noexcept -> int(*)(bool&)
    {
        return +[](bool& o_){
            
            o_=B;

            return 0;
        };
    }

/*

    template <typename A>
    [[noreturn]] inline auto str_check (const char* str_)
        -> A
    {
        error_os<<"Unknown type conversion from string."<<std::endl;
        
        return -4;
    }


    template <>
    inline auto str_check<short> (const char* str_)
        -> short
    {
        return static_cast<short>(std::stoi(str_));
    }


    template <>
    inline auto str_check<int> (const char* str_) noexcept -> int
    {
        return std::stoi(str_);
    }


    template <>
    inline auto str_check<long> (const char* str_) noexcept -> long
    {
        return std::stol(str_);
    }


    template <>
    inline auto str_check<long long> (const char* str_) noexcept -> long long
    {
        return std::stol(str_);
    }


    template <>
    inline auto str_check<bool> (const char* str_) noexcept -> bool
    {
        return static_cast<bool>(std::stoul(str_));
    }


    template <>
    inline auto str_check<unsigned char> (const char* str_) noexcept -> unsigned char
    {
        return static_cast<unsigned char>(std::stoul(str_));
    }


    template <>
    inline auto str_check<unsigned short> (const char* str_) noexcept -> unsigned short
    {
        return static_cast<unsigned short>(std::stoul(str_));
    }


    template <>
    inline auto str_check<unsigned int> (const char* str_) noexcept -> unsigned int
    {
        return static_cast<unsigned int>(std::stoul(str_));
    }


    template <>
    inline auto str_check<unsigned long> (const char* str_) noexcept -> unsigned long
    {
        return std::stoul(str_);
    }


    template <>
    inline auto str_check<unsigned long long> (const char* str_) noexcept -> unsigned long long
    {
        return std::stoull(str_);
    }


    template <>
    inline auto str_check<float> (const char* str_) noexcept -> float
    {
        return static_cast<float>(std::stod(str_));
    }


    template <>
    inline auto str_check<double> (const char* str_) noexcept -> double
    {
        return std::stod(str_);
    }


    template <>
    inline auto str_check<long double> (const char* str_) noexcept -> long double
    {
        return std::stold(str_);
    }


    template <>
    inline auto str_check<char> (const char* str_) noexcept -> char
    {
        return str_[0];
    }


    template <>
    inline auto str_check<std::string> (const char* str_) noexcept -> std::string
    {
        return std::string{str_};
    }


    template <>
    inline auto str_check<const char*> (const char* str_) noexcept -> const char*
    {
        return str_;
    }
*/
}
