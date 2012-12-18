#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <iostream>
#include <fstream>

#include <GL/glfw.h>

using namespace std;

int defaultWidth    = 800; // px
int defaultHeight   = 600; // px

template <typename T, size_t bufferSize>
class FPSCounter {
private:
    size_t currentIndex;
    T buffer[bufferSize];
    
public:
    FPSCounter() : currentIndex(0) {
        for (size_t i=0; i<bufferSize; ++i)
            buffer[i] = 0;
    }
    
    // Adds the specified data point to the top of the stack
    void add(T dataPoint) {
        buffer[currentIndex] = dataPoint;
        currentIndex = (currentIndex + 1) % bufferSize;
    }
    
    T getAverageFPS() {
        double inverseSize = 1.0 / (double) bufferSize;
        
        // Sum up the inter-arrival times and take an average
        T average = 0;
        for (size_t i=0; i<bufferSize; ++i) {
            average += buffer[i] * inverseSize;
        }
        
        // Return average inter-arrival time reciprocal (i.e. fps)
        return 1.0 / average;
    }
};

#define BSP_MAGIC "IBSP"
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

class BSPHeader {
public:
    char magic[5];
    int version;
    
    BSPLumpEntry_t lumps[BSP_LUMP_COUNT];
};

class BSP {
private:
    BSPHeader header;

    BSP() {}
    BSP(const BSP& other);
    
public:
    static BSP* fromStream(istream& is) {
        BSP* bsp = new BSP();
        BSPHeader* header = new BSPHeader();
        
        is.read(header->magic, 4 * sizeof(char));
        if (strcmp(header->magic, BSP_MAGIC) != 0) {
            printf("Magic Mismatch! Got \"%s\", expecting \"%s\"!\n", header->magic, BSP_MAGIC);
            return NULL;
        }
        
        is >> header->version;
        printf("%s v%d\n", header->magic, header->version);
        
        is.read((char*) header->lumps, BSP_LUMP_COUNT * sizeof(BSPLumpEntry_t));
        for (size_t i=0; i<BSP_LUMP_COUNT; ++i) {
            printf(
                "Lump [%d] - [%d,%d)\n",
                i,
                header->lumps[i].offset,
                header->lumps[i].offset + header->lumps[i].length
            );
        }
        
        return bsp;
    }
};

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    ifstream inputFile(argv[1], ios::binary);
    if (!inputFile) {
        printf("Unable to open BSP file \"%s\" for reading!\n", argv[1]);
        return EXIT_FAILURE;
    }
    
    BSP* bsp = BSP::fromStream(inputFile);
    
    inputFile.close();
    
    /*
    if (!glfwInit()) {
        printf("Unable to initialize glfw!\n");
        return EXIT_FAILURE;
    }
    
    if (!glfwOpenWindow(
        defaultWidth, defaultHeight,
        8, 8, 8, 8, // RGBA all each 8 bits for 32-bit coloring
        8, 0, // 8 bit depth, 0 bit stencil
        GLFW_WINDOW
    )) {
        printf("Unable to open glfw window!\n");
        
        glfwTerminate();
        return EXIT_FAILURE;
    }
    
    char windowTitle[25] = {};
    glfwSetWindowTitle("Q3BSPRenderer");
    
    // Keep 10 samples of inter-framerate time
    FPSCounter<double, 10> fpsCounter;
    
    // Time of current frame and time since last frame, respectively
    double t(0.0), dt(0.0);
    while(true) {
        {
            double now = glfwGetTime();
            dt = now - t;
            t = now;
        }
        
        // Calculate & display average FPS
        fpsCounter.add(dt);
        sprintf(windowTitle, "Q3BSPRenderer - %d FPS", (int) fpsCounter.getAverageFPS());
        glfwSetWindowTitle(windowTitle);
    
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Render here
        
        glfwSwapBuffers();
        
        // Check for stopping conditions
        if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED))
            break;
    }
    
    glfwTerminate();
    */
    
    return EXIT_SUCCESS;
}