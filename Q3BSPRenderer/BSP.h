#ifndef BSP_H
#define BSP_H

#include <cstdlib>
#include <cstdio>

#include <iostream>

#define BSP_MAGIC "IBSP"
#define BSP_VERSION 0x2E
#define BSP_LUMP_COUNT 17

enum BSPLumpIndex {
    LUMP_ENTITIES    = 0,
    LUMP_TEXTURES    = 1,
    LUMP_PLANES      = 2,
    LUMP_NODES       = 3,
    LUMP_LEAFS       = 4,
    LUMP_LEAFFACES   = 5,
    LUMP_LEAFBRUSHES = 6,
    LUMP_MODELS      = 7,
    LUMP_BRUSHES     = 8,
    LUMP_BRUSHSIDES  = 9,
    LUMP_VERTS       = 10,
    LUMP_MESHES      = 11,
    LUMP_EFFECTS     = 12,
    LUMP_FACES       = 13,
    LUMP_LIGHTMAPS   = 14,
    LUMP_LIGHTVOLS   = 15,
    LUMP_VSIDATA     = 16
};

typedef struct {
    int offset;
    int length;
} BSPLumpEntry_t;

class BSP {
private:
    BSP() {}
	~BSP() {}

	// Hide/disable copy constructor to prevent accidental copies
    BSP(const BSP& other);
    
public:
    static BSP* fromStream(std::istream& is);
};

#endif