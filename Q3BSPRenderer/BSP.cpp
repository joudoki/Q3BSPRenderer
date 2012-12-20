#include "BSP.h"

BSP* BSP::fromStream(std::istream& is) {
	// Read the magic string (4 byte string)
	char magic[5] = {0};
	is.read(magic, 4 * sizeof(char));
    if (strcmp(magic, BSP_MAGIC) != 0) {
        printf("Magic Mismatch! Got \"%s\", expecting \"%s\"!\n", magic, BSP_MAGIC);
        return NULL;
    }
        
	// Read the version (4 byte integer)
	int version = 0;
    is.read((char*) &version, sizeof(int));
	if (version != BSP_VERSION) {
		printf("Version mismatch! Got %d, expecting %d!\n", version, BSP_VERSION);
		return NULL;
	}

	// Read the lump table (17 entries @ 8 bytes each)
	BSPLumpEntry_t lumps[BSP_LUMP_COUNT];
    is.read((char*) &lumps, BSP_LUMP_COUNT * sizeof(BSPLumpEntry_t));
    for (size_t i=0; i<BSP_LUMP_COUNT; ++i) {
        printf(
            "Lump [%d] - [%d,%d)\n",
            i,
            lumps[i].offset,
            lumps[i].offset + lumps[i].length
        );
    }

	// Make bsp file
    BSP* bsp = new BSP();
    return bsp;
}