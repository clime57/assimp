/** @file  cimport_ext.h
 *  
 */
#pragma once
#include "defs.h"
#ifndef AI_ASSIMP_EXT_H_INC
#define AI_ASSIMP_EXT_H_INC

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int uint;

struct aiScene;  // aiScene.h
struct aiFileIO; // aiFileIO.h
struct aiNode;
struct aiMaterial;
struct aiMesh;
struct aiAnimation;
struct aiCamera;
struct aiLight;
struct aiAnimMesh;
struct aiFace;
struct aiBone;
struct aiVertexWeight;
struct aiMeshMorphKey;

#ifdef __cplusplus
}
#endif

#endif // AI_ASSIMP_EXT_H_INC
