#pragma once
#include "Node.hpp"
#include "Chunk.hpp"
#include "Y-sort.hpp"

class WorldView : public Node
{
private:
    std::vector<Chunk> loadedChunks;

    
    void deallocateChunks();
    void allocateChunks();
public:
    WorldView();
};