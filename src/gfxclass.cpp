// Name:    Captain Calc
// Date:    August 11, 2021
// File:    gfxclass.cpp
// Purpose: This file provides the definitions of the GraphX class member
//          functions declared in gfxclass.h and initializes the GraphX
//          singleton.


#include <stdint.h>

#include <graphx.h>
#include <fileioc.h>

#include "gfxclass.h"


// Initialize the GraphX singleton.
bool GraphX::m_Active(false);
GraphX* GraphX::instance(nullptr);


void GraphX::p_Begin()
{
    gfx_Begin();
    gfx_SetPalette(m_Palette, m_Size, m_Offset);
    gfx_SetTransparentColor(m_TransparentColor);
    gfx_SetDrawBuffer();
    m_Active = true;
    return;
}


GraphX::GraphX(
  const void* palette,
  size_t size,
  uint8_t offset,
  uint8_t transparent_color)
 :
 m_Palette(palette),
 m_Size(size),
 m_Offset(offset),
 m_TransparentColor(transparent_color)
{
    if (instance)
        return;
    instance = this;
    ti_SetGCBehavior(&End, &Begin);
    instance->p_Begin();
}


GraphX::~GraphX()
{
    if (instance)
        End();
    instance = nullptr;
}


void GraphX::Begin()
{
    if (!instance)
        return;
    instance->p_Begin();
    return;
}


void GraphX::End()
{
    if (!instance)
        return;
    gfx_End();
    m_Active = false;
}