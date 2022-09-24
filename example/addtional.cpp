#include "../include/comlar.hpp"
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    // 1. Instantiation of Executor class
    Executor exec(argc, argv);
    
    //*** Add field1
    Field f1=exec.add_field("Field1");


    // 2. Prepare variables for use in option operation
    float scalar;
    bool  flag;
    float plus=1.0, minus=1.0;


    // 3. Definition of options
    // Example1 (-s --scalar)
    {
        Option<Arg<float>, Ope<float>> opt{"s", "scalar", REQUIRED, scalar};
        //*** Set check function
        opt.set_check(default_and_cstrs<float, Geq, Les>({-1., 1.}));
        opt.set_operate(default_assign<float>());
        //*** Set information for help
        opt.set_info("set scalar value", "<=-1 and <1");
        exec.add_option(opt);
    }
  
    // Example2 (-f --flag)
    {
        Option<Arg<>, Ope<bool>> opt{"f", "flag", OPTIONAL, flag};
        opt.set_operate(default_flag<true>());
        //*** Set information for help
        opt.set_info("turn on flag");
        exec.add_option(opt);
    }

    // Example3 (-pm --pmave)
    {
        Option<Arg<int, int>, Ope<float, float>> opt{"pm", "pmave", OPTIONAL, plus, minus};
        opt.set_operate(+[](const int& in1_, const int& in2_, float& plus_, float& minus_){
            
            float ave=static_cast<float>(in1_+in2_)*0.5;
            plus_ +=ave;
            minus_-=ave;

            return 0;
        });
        //*** Set field
        opt.set_field(f1);
        //*** Set information for help
        opt.set_info("add and subtract average");
        exec.add_option(opt);
    }

    //*** Add help
    exec.add_help("Header String");


    // 4. Call the execute function of Exectutor class
    int result=exec.execute();
    if(result){
        std::cout<<"result: "<<result<<std::endl;
        std::exit(EXIT_FAILURE);
    }



    // Result
    std::cout<<"scalar: "<<scalar<<std::endl;
    std::cout<<"flag  : "<<flag<<std::endl;
    std::cout<<"plus  : "<<plus<<std::endl;
    std::cout<<"minus : "<<minus<<std::endl;
    std::cout<<"result: "<<result<<std::endl;
}
