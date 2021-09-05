/*
   A dot animation that travels along rails
   (C) Voidstar Lab LLC 2021
*/

#ifndef RIPPLE_H_
#define RIPPLE_H_

// WARNING: These slow things down enough to affect performance. Don't turn on unless you need them!
//#define DEBUG_ADVANCEMENT  // Print debug messages about ripples' movement
//#define DEBUG_RENDERING  // Print debug messages about translating logical to actual position

#include <Adafruit_NeoPixel.h>
#include "mapping.h"


const byte mxDebug[3] = {117,160,253}; // RGB -> GRB
const byte mxGreen[3] = {0,240,0}; // RGB -> GRB
const byte mxWhite[3] = {255,255,255};
const byte mxRed[3] = {255,0,0};
const byte mxBrown[3] = {160,117,35};

byte mxFlag[40][14][3] = {
   
    {// 0
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 1
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 2
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 3
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 4
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 5
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 6
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 7
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 8
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 9
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 10
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 11
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 12
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 13
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 14
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 15
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 16
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 17
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 18
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 19
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 20
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 21
      
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 22
      
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 23
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 24
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 25
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 26

      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
     
    },
    {// 27
      
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
    },
    {// 28
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 29
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 30
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 31
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
      mxBrown[0],mxBrown[1],mxBrown[2],
    },
    {// 32
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 33
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 34
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
      mxRed[0],mxRed[1],mxRed[2],
    },
    {// 35
       mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 36
     mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 37
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
      mxGreen[0],mxGreen[1],mxGreen[2],
    },
    {// 38
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
    {// 39
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
      mxWhite[0],mxWhite[1],mxWhite[2],
    },
};


const byte pokeWhite[3] = {255,255,255};
const byte pokeRed[3] = {255,0,0};
const byte pokeYellow[3] = {255,255,255};
const byte pokeBlue[3] = {255,255,255};
const byte pokePurple[3] = {255,255,255};
const byte pokeBlack[3] = {0,0,0};
const byte pokeGray[3] = {62,62,62};


byte pokeFlag[40][14][3] = {
   
    {// 0
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 1
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 2
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 3
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 4
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 5
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 6
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 7
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 8
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 9
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 10
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 11
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 12
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 13
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
    },
    {// 14
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 15
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 16
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 17
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
    },
    {// 18
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
    },
    {// 19
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
    },
    {// 20
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 21
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
    },
    {// 22
      
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
    },
    {// 23
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      
    },
    {// 24
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
      pokeRed[0],pokeRed[1],pokeRed[2],
    },
    {// 25
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 26
      
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 27
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
    },
    {// 28
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
    },
    {// 29
      
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 30
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 31
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
      pokeGray[0],pokeGray[1],pokeGray[2],
    },
    {// 32
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 33
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeBlack[0],pokeBlack[1],pokeBlack[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 34
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 35
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 36
     pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 37
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 38
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
    {// 39
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
      pokeWhite[0],pokeWhite[1],pokeWhite[2],
    },
};



enum rippleState {
  dead,
  withinNode,  // Ripple isn't drawn as it passes through a node to keep the speed consistent
  travelingUpwards,
  travelingDownwards
};

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

class Ripple {
  public:
    Ripple(int id) : rippleId(id) {
      Serial.print("Instanced ripple #");
      Serial.println(rippleId);
    }

    rippleState state = dead;
    unsigned long color;

    /*
       If within a node: 0 is node, 1 is direction
       If traveling, 0 is segment, 1 is LED position from bottom
    */
    int position[2];

    // Place the Ripple in a node
    void start(byte n, byte d, unsigned long c, float s, unsigned long l, byte a, int f, int r, int g, int b) {
      color = c;
      speed = s;
      lifespan = l;
      aggressiveness = a;
      flagMode = f;
      customRed = r;
      customGreen = g;
      customBlue = b;

      birthday = millis();
      pressure = 0;
      state = withinNode;

      position[0] = n;
      position[1] = d;

      justStarted = true;

      Serial.print("Ripple ");
      Serial.print(rippleId);
      Serial.print(" starting at node ");
      Serial.print(position[0]);
      Serial.print(" direction ");
      Serial.println(position[1]);
    }

    void advance(byte ledColors[40][14][3]) {
      unsigned long age = millis() - birthday;

      if (state == dead)
        return;

      pressure += fmap(float(age), 0.0, float(lifespan), speed, 0.0);  // Ripple slows down as it ages
      // TODO: Motion of ripple is severely affected by loop speed. Make it time invariant

      if (pressure < 1 && (state == travelingUpwards || state == travelingDownwards)) {
        // Ripple is visible but hasn't moved - render it to avoid flickering
        renderLed(ledColors, age, flagMode);
      }

      while (pressure >= 1) {
#ifdef DEBUG_ADVANCEMENT
        Serial.print("Ripple ");
        Serial.print(rippleId);
        Serial.println(" advancing:");
#endif

        switch (state) {
          case withinNode: {
              if (justStarted) {
                justStarted = false;
              }
              else {
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Picking direction out of node ");
                Serial.print(position[0]);
                Serial.print(" with agr. ");
                Serial.println(aggressiveness);
#endif

                int newDirection = -1;

                // The more aggressive a ripple, the tighter turns it wants to make.
                // If there aren't any segments it can turn to, we need to adjust its aggressiveness.
                byte anger = aggressiveness;

                int sharpLeft = (position[1] + 1) % 6;
                int wideLeft = (position[1] + 2) % 6;
                int forward = (position[1] + 3) % 6;
                int wideRight = (position[1] + 4) % 6;
                int sharpRight = (position[1] + 5) % 6;

                while (newDirection < 0) {
                  if (anger == 0) {
                    int forwardConnection = nodeConnections[position[0]][forward];

                    if (forwardConnection < 0) {
                      // We can't go straight ahead - we need to take a more aggressive angle
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can't go straight - picking more agr. path");
#endif
                      anger++;
                    }
                    else {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Going forward");
#endif
                      newDirection = forward;
                    }
                  }

                  if (anger == 1) {
                    int leftConnection = nodeConnections[position[0]][wideLeft];
                    int rightConnection = nodeConnections[position[0]][wideRight];

                    if (leftConnection >= 0 && rightConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Turning left or right at random");
#endif
                      newDirection = random(2) ? wideLeft : wideRight;
                    }
                    else if (leftConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can only turn left");
#endif
                      newDirection = wideLeft;
                    }
                    else if (rightConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can only turn right");
#endif
                      newDirection = wideRight;
                    }
                    else {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can't make wide turn - picking more agr. path");
#endif
                      anger++;  // Can't take shallow turn - must become more aggressive
                    }
                  }

                  if (anger == 2) {
                    int leftConnection = nodeConnections[position[0]][sharpLeft];
                    int rightConnection = nodeConnections[position[0]][sharpRight];

                    if (leftConnection >= 0 && rightConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Turning left or right at random");
#endif
                      newDirection = random(2) ? sharpLeft : sharpRight;
                    }
                    else if (leftConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can only turn left");
#endif
                      newDirection = sharpLeft;
                    }
                    else if (rightConnection >= 0) {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can only turn right");
#endif
                      newDirection = sharpRight;
                    }
                    else {
#ifdef DEBUG_ADVANCEMENT
                      Serial.println("  Can't make tight turn - picking less agr. path");
#endif
                      anger--;  // Can't take tight turn - must become less aggressive
                    }
                  }

                  // Note that this can't handle some circumstances,
                  // like a node with segments in nothing but the 0 and 3 positions.
                  // Good thing we don't have any of those!
                }

#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Leaving node ");
                Serial.print(position[0]);
                Serial.print(" in direction ");
                Serial.println(newDirection);
#endif

                position[1] = newDirection;
              }

              position[0] = nodeConnections[position[0]][position[1]];  // Look up which segment we're on

#ifdef DEBUG_ADVANCEMENT
              Serial.print("  and entering segment ");
              Serial.println(position[0]);
#endif

              if (position[1] == 5 || position[1] == 0 || position[1] == 1) {  // Top half of the node
#ifdef DEBUG_ADVANCEMENT
                Serial.println("  (starting at bottom)");
#endif
                state = travelingUpwards;
                position[1] = 0;  // Starting at bottom of segment
              }
              else {
#ifdef DEBUG_ADVANCEMENT
                Serial.println("  (starting at top)");
#endif
                state = travelingDownwards;
                position[1] = 13; // Starting at top of 14-LED-long strip
              }
              break;
            }

          case travelingUpwards: {
              position[1]++;

              if (position[1] >= 14) {
                // We've reached the top!
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Reached top of seg. ");
                Serial.println(position[0]);
#endif
                // Enter the new node.
                int segment = position[0];
                position[0] = segmentConnections[position[0]][0];
                for (int i = 0; i < 6; i++) {
                  // Figure out from which direction the ripple is entering the node.
                  // Allows us to exit in an appropriately aggressive direction.
                  int incomingConnection = nodeConnections[position[0]][i];
                  if (incomingConnection == segment)
                    position[1] = i;
                }
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Entering node ");
                Serial.print(position[0]);
                Serial.print(" from direction ");
                Serial.println(position[1]);
#endif
                state = withinNode;
              }
              else {
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Moved up to seg. ");
                Serial.print(position[0]);
                Serial.print(" LED ");
                Serial.println(position[1]);
#endif
              }
              break;
            }

          case travelingDownwards: {
              position[1]--;
              if (position[1] < 0) {
                // We've reached the bottom!
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Reached bottom of seg. ");
                Serial.println(position[0]);
#endif
                // Enter the new node.
                int segment = position[0];
                position[0] = segmentConnections[position[0]][1];
                for (int i = 0; i < 6; i++) {
                  // Figure out from which direction the ripple is entering the node.
                  // Allows us to exit in an appropriately aggressive direction.
                  int incomingConnection = nodeConnections[position[0]][i];
                  if (incomingConnection == segment)
                    position[1] = i;
                }
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Entering node ");
                Serial.print(position[0]);
                Serial.print(" from direction ");
                Serial.println(position[1]);
#endif
                state = withinNode;
              }
              else {
#ifdef DEBUG_ADVANCEMENT
                Serial.print("  Moved down to seg. ");
                Serial.print(position[0]);
                Serial.print(" LED ");
                Serial.println(position[1]);
#endif
              }
              break;
            }

          default:
            break;
        }

        pressure -= 1;

        if (state == travelingUpwards || state == travelingDownwards) {
          // Ripple is visible - render it
          renderLed(ledColors, age, flagMode);
        }
      }

#ifdef DEBUG_ADVANCEMENT
      Serial.print("  Age is now ");
      Serial.print(age);
      Serial.print('/');
      Serial.println(lifespan);
#endif

      if (lifespan && age >= lifespan) {
        // We dead
#ifdef DEBUG_ADVANCEMENT
        Serial.println("  Lifespan is up! Ripple is dead.");
#endif
        state = dead;
        position[0] = position[1] = pressure = age = 0;
      }
    }

  private:
    float speed;  // Each loop, ripples move this many LED's.
    unsigned long lifespan;  // The ripple stops after this many milliseconds

    /*
       0: Always goes straight ahead if possible
       1: Can take 60-degree turns
       2: Can take 120-degree turns
    */
    byte aggressiveness;

    bool justStarted = false;

    float pressure;  // When Pressure reaches 1, ripple will move
    unsigned long birthday;  // Used to track age of ripple

    int flagMode;

    int customRed = 0;
    int customGreen = 0;
    int customBlue = 0;

    static byte rippleCount;  // Used to give them unique ID's
    byte rippleId;  // Used to identify this ripple in debug output

    void renderLed(byte ledColors[40][14][3], unsigned long age, int flag) {
      int strip = ledAssignments[position[0]][0];
      int led = ledAssignments[position[0]][2] + position[1];

      flagMode = flag;

      int red = ledColors[position[0]][position[1]][0];
      int green = ledColors[position[0]][position[1]][1];
      int blue = ledColors[position[0]][position[1]][2];

      switch(flagMode) {
        case "mexico": {
          red = mxFlag[position[0]][position[1]][0];
          green = mxFlag[position[0]][position[1]][1];
          blue = mxFlag[position[0]][position[1]][2];
          
//          ledColors[position[0]][position[1]][0] = red;
//          ledColors[position[0]][position[1]][1] = green;
//          ledColors[position[0]][position[1]][2] = blue;
          ledColors[position[0]][position[1]][0] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (red >> 8) & 0xFF, 0.0)) + red)));
          ledColors[position[0]][position[1]][1] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (green >> 16) & 0xFF, 0.0)) + green)));
          ledColors[position[0]][position[1]][2] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), blue & 0xFF, 0.0)) + blue)));
          break;
        }
        case "rgb":{
          red = customRed;
          green = customGreen;
          blue = customBlue;
          ledColors[position[0]][position[1]][0] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (red >> 8) & 0xFF, 0.0)) + red)));
          ledColors[position[0]][position[1]][1] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (green >> 16) & 0xFF, 0.0)) + green)));
          ledColors[position[0]][position[1]][2] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), blue & 0xFF, 0.0)) + blue)));
          
          break;
        }
        case "pokeball": {
          red = pokeFlag[position[0]][position[1]][0];
          green = pokeFlag[position[0]][position[1]][1];
          blue = pokeFlag[position[0]][position[1]][2];
          
//          ledColors[position[0]][position[1]][0] = red;
//          ledColors[position[0]][position[1]][1] = green;
//          ledColors[position[0]][position[1]][2] = blue;
          ledColors[position[0]][position[1]][0] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (red >> 8) & 0xFF, 0.0)) + red)));
          ledColors[position[0]][position[1]][1] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (green >> 16) & 0xFF, 0.0)) + green)));
          ledColors[position[0]][position[1]][2] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), blue & 0xFF, 0.0)) + blue)));
          break;
        }
        default: {
          ledColors[position[0]][position[1]][0] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (color >> 8) & 0xFF, 0.0)) + red)));
          ledColors[position[0]][position[1]][1] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), (color >> 16) & 0xFF, 0.0)) + green)));
          ledColors[position[0]][position[1]][2] = byte(min(255, max(0, int(fmap(float(age), 0.0, float(lifespan), color & 0xFF, 0.0)) + blue)));
          break;
        }
      }

#ifdef DEBUG_RENDERING
      Serial.print("Rendering ripple position (");
      Serial.print(position[0]);
      Serial.print(',');
      Serial.print(position[1]);
      Serial.print(") at Strip ");
      Serial.print(strip);
      Serial.print(", LED ");
      Serial.print(led);
      Serial.print(", color 0x");
      for (int i = 0; i < 3; i++) {
        if (ledColors[position[0]][position[1]][i] <= 0x0F)
          Serial.print('0');
        Serial.print(ledColors[position[0]][position[1]][i], HEX);
      }
      Serial.println();
#endif
    }
};

#endif
