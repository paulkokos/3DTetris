//
// Created by paulkokos on 8/20/17.
//

#ifndef INC_3DTETRIS_GENERATOR_H
#define INC_3DTETRIS_GENERATOR_H

/*=============================================================================
Generate random numbers from x to y
 Created by paulkokos on 8/20/17.
Class name

 Description

 Brief description of method
/**
 * @pre
 *    Any preconditions that this method requires
 * @post
 *    Any post conditions that result because of this method
 * @param [0, n-1] paramName
 *    Brief description of parameter
 * @return
 *    Brief description of return value
 * @throw
 *    An EXPLICIT throw specification - including which guarantee it offers (basic, strong, nothrow)
 *    and WHY the various exceptions may be thrown.
 =============================================================================*/
class Generator {
public:
    static int generateNum();
    static int randPosX();
    static int randPosY();

};


#endif //INC_3DTETRIS_GENERATOR_H
