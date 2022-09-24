#include "../include/comlar.hpp"
#include <sstream>

using namespace comlar;

int main(int argc, char** argv){

    // 1. Instantiation of Executor class
    Executor exec(argc, argv);


    // 2. Prepare variables for use in option operation
    float scalar;
    bool  flag;
    float plus=1.0, minus=1.0;


    // 3. Definition of options
    // Example1 (-s --scalar)
    {
        Option<Arg<float>, Ope<float>> opt{"s", "scalar", REQUIRED, scalar};
        opt.set_operate(default_assign<float>());
        exec.add_option(opt);
    }
  
    // Example2 (-f --flag)
    {
        Option<Arg<>, Ope<bool>> opt{"f", "flag", OPTIONAL, flag};
        opt.set_operate(default_flag<true>());
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
        exec.add_option(opt);
    }


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
