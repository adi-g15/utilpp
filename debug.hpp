#pragma once

#include <iostream>

using std::clog;
using std::endl;

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#define DEBUG_START std::clog << "[DEBUG] START :" << std::endl;
#define DEBUG_END std::clog << "\n: [DEBUG] PASSED" << std::endl;
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
/*HELPFUL FOR GETTING TO THE SEG_FAULT SITE*/
#define DEBUG_BLOCK(code) \
    DEBUG_START           \
    code                  \
        DEBUG_END
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

  /*
   @purpose-> Debug the String
  @brief -> This function is used to know string content at debugging, 

    @benefit -> Instead of two print statements -> print i, print s;
                we can directly call print dbgStr(s,i) 
                
    @example -> dbgStr("hi there i am a long string, loogink for the 24th position",   24)
    
        Output -> hi there i am a long string, looking for the 24th position
                                          |

                            (the line signifies the ith element)
    @note-> `loc` is based on 0-based indexing, so 24th index is actually thr 25th char    
        */
void dbgStr(const std::string& s, int loc){
    std::cout<<s<<std::endl;
    for (unsigned i = 0; i < loc; i++)
    {
        std::cout<<' ';
    }
    std::cout<<'|'<<std::endl;   
}
