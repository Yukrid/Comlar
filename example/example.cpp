#include "../comlar.hpp"
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    // Make instance of comlar::Executor
    Executor exec(argc, argv);



    // Add field for option (optional)
    Field field=exec.add_field("For example, flag");



    // Add Command -f, --flmodify  (in: int, float --> out: float)
    float float_val=2.9;
    {
        Command<Arg<int, float>, Ope<float>> com{"f", "flmodify", REQUIRED, float_val};
        com.set_check(+[](const int& a_, const float& b_){
            
            std::cout<<"flmodify check called: "<<a_<<" "<<b_<<std::endl;
        
            if(a_<0){
                std::cerr<<"[-f, --flmodify] The first value should be plus."<<std::endl;
                return -1;
            }
            else     return 0;
        });
        com.set_operate(+[](const int& a_, const float& b_, float& float_val_){
        
            std::cout<<"flmodify operate called: "<<a_<<" "<<b_<<" "<<float_val_<<std::endl;
            float_val_=float_val_*a_+b_;
        
            return 0;
        });
        com.set_info("float modification", "[First should be plus]");
        exec.add_command(com);
    }


    // Add Command -if, --intflag  (in: [nothing] --> out: bool)
    bool int_flag=false;
    {
        Command<Arg<>, Ope<bool>> com{"if", "intflag", OPTIONAL, int_flag};
        com.set_operate(default_flag<true>());
        com.set_info("flag for user int");
        com.set_field(field);
        exec.add_command(com);
    }


    // Add Command -if, --intvalue  (in: int --> out: int)
    int int_val=0;
    {
        Command<Arg<int>, Ope<int>> com{"iv", "intvalue", OPTIONAL, int_val};
        com.set_operate(default_assign<int>());
        com.set_info("user int value");
        exec.add_command(com);
    }


    // Add default help command
    std::stringstream ss1;
    ss1<<"Hello World!"<<std::endl;
    exec.add_help(ss1.str());


    // Execute
    if(exec.execute()){
        std::cout<<"Execute Failure!"<<std::endl;
        std::exit(EXIT_FAILURE);
    }else{
        std::cout<<"Execute Success!"<<std::endl;
    }
        

    // Result
    std::cout<<"float value: "<<float_val<<std::endl;
    std::cout<<"int flag   : "<<int_flag<<std::endl;
    std::cout<<"int value  : "<<int_val<<std::endl;
}
;
