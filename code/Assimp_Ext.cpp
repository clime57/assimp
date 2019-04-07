
/** @file  Assimp_Ext.cpp
 *  
 */

#include <assimp/Assimp_Ext.h>
#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>
#include <assimp/Importer.hpp>
#include <assimp/importerdesc.h>
#include <assimp/scene.h>
#include <assimp/GenericProperty.h>
#include <assimp/Exceptional.h>
#include <assimp/BaseImporter.h>

#include "CInterfaceIOWrapper.h"
#include "Importer.h"
#include "ScenePrivate.h"

#include <list>

// ------------------------------------------------------------------------------------------------
#ifndef ASSIMP_BUILD_SINGLETHREADED
#   include <thread>
#   include <mutex>
#endif
// ------------------------------------------------------------------------------------------------
using namespace Assimp;
#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------------------------------------------------------------------------

ASSIMP_API bool aiScene_HasMaterials(aiScene* ptrScene)
{
    return ptrScene->HasMaterials();
}
ASSIMP_API uint aiScene_GetNumMaterials(aiScene* ptrScene)
{
    return ptrScene->mNumMaterials;
}
ASSIMP_API uint aiScene_GetNumMeshes(aiScene* ptrScene)
{
    return ptrScene->mNumMeshes;
}
ASSIMP_API uint aiScene_GetNumAnimations(aiScene* ptrScene)
{
    return ptrScene->mNumAnimations;
}
ASSIMP_API uint aiScene_GetNumCameras(aiScene* ptrScene)
{
    return ptrScene->mNumCameras;
}
ASSIMP_API uint aiScene_GetNumLights(aiScene* ptrScene)
{
    return ptrScene->mNumLights;
}
ASSIMP_API bool aiScene_HasMeshes(aiScene* ptrScene)
{
    return ptrScene->HasMeshes();
}
ASSIMP_API bool aiScene_HasAnimation(aiScene* ptrScene)
{
    return ptrScene->HasAnimations();
}
ASSIMP_API bool aiScene_HasCameras(aiScene* ptrScene)
{
    return ptrScene->HasCameras();
}
ASSIMP_API bool aiScene_HasLights(aiScene* ptrScene)
{
    return ptrScene->HasLights();
}
ASSIMP_API aiNode* aiScene_GetRootNode(aiScene* ptrScene)
{
    return ptrScene->mRootNode;
}
ASSIMP_API aiMaterial* aiScene_GetMaterial(aiScene* ptrScene, uint uintIndex)
{
    return ptrScene->mMaterials[uintIndex];
}

ASSIMP_API aiMesh* aiScene_GetMesh(aiScene* ptrScene, uint uintIndex)
{
    return ptrScene->mMeshes[uintIndex];
}
ASSIMP_API aiAnimation* aiScene_GetAnimation(aiScene* ptrScene, uint uintIndex)
{
    return ptrScene->mAnimations[uintIndex];
}
ASSIMP_API aiCamera* aiScene_GetCamera(aiScene* ptrScene, uint uintIndex)
{
    return ptrScene->mCameras[uintIndex];
}
ASSIMP_API aiLight* aiScene_GetLight(aiScene* ptrScene, uint uintIndex)
{
    return ptrScene->mLights[uintIndex];
}
ASSIMP_API const char* aiNode_GetName(aiNode* ptrNode)
{
    return ptrNode->mName.C_Str();
}

ASSIMP_API uint aiNode_GetNumChildren(aiNode* ptrNode)
{
    return ptrNode->mNumChildren;
}
ASSIMP_API uint aiNode_GetNumMeshes(aiNode* ptrNode)
{
    return ptrNode->mNumMeshes;
}
ASSIMP_API aiNode* aiNode_GetChildren(aiNode* ptrNode, uint uintIndex)
{
    return ptrNode->mChildren[uintIndex];
}

ASSIMP_API uint aiNode_GetMeshIndex(aiNode* ptrNode, uint uintIndex)
{
    return ptrNode->mMeshes[uintIndex];
}
ASSIMP_API aiNode* aiNode_GetParent(aiNode* ptrNode)
{
    return ptrNode->mParent;
}
ASSIMP_API aiMatrix4x4* aiNode_GetTransformation(aiNode* ptrNode)
{
    return &ptrNode->mTransformation;
}

ASSIMP_API const char* aiMaterial_GetEmbeddedTextureName(aiTexture* ptrTexture)
{
    return ptrTexture->mFilename.C_Str();
}
ASSIMP_API void aiMaterial_ReleaseEmbeddedTexture(aiTexture* ptrTexture)
{
    delete ptrTexture;
}
ASSIMP_API bool aiMaterial_IsEmbeddedTextureCompressed(aiTexture* ptrTexture)
{
    return ptrTexture->mHeight == 0;
}
ASSIMP_API uint aiMaterial_GetEmbeddedTextureDataSize(aiTexture* ptrTexture)
{
    return ptrTexture->mHeight * ptrTexture->mHeight;
}
ASSIMP_API aiTexel* aiMaterial_GetEmbeddedTextureDataPointer(aiTexture* ptrTexture)
{
    return ptrTexture->pcData;
}
ASSIMP_API int aiMaterial_GetEmbeddedTextureWidth(aiTexture* ptrTexture)
{
    return ptrTexture->mWidth;
}
ASSIMP_API int aiMaterial_GetEmbeddedTextureHeight(aiTexture* ptrTexture)
{
    return ptrTexture->mHeight;
}

ASSIMP_API const aiTexture* aiScene_GetEmbeddedTexture(aiScene* ptrScene, const char* strFilename)
{
    return ptrScene->GetEmbeddedTexture(strFilename);
}

ASSIMP_API uint aiMaterial_GetTextureCount(aiMaterial* ptrMat,uint uintType)
{
    return ptrMat->GetTextureCount((aiTextureType)uintType);
}

ASSIMP_API bool aiMaterial_GetTextureDiffuse(aiMaterial* ptrMat, uint uintType,
    char* strPath, aiTextureMapping* uintMapping, uint* uintUvIndex, ai_real* floatBlend, aiTextureOp* uintOp,
    aiTextureMapMode* uintMapMode)
{
    aiString aiStrPath;
    aiReturn r = ptrMat->GetTexture(aiTextureType_DIFFUSE, uintType,
        &aiStrPath, uintMapping, uintUvIndex, floatBlend, uintOp,
        uintMapMode);
    memcpy(strPath, aiStrPath.C_Str(), aiStrPath.length);
    return  r  == aiReturn_SUCCESS;
}
ASSIMP_API uint aiMaterial_GetNumTextureDiffuse(aiMaterial* ptrMat)
{
    return ptrMat->GetTextureCount(aiTextureType_DIFFUSE);
}
ASSIMP_API bool aiMaterial_HasTextureEmissive(aiMaterial* ptrMat, uint uintIndex)
{
    return ptrMat->GetTextureCount(aiTextureType_EMISSIVE) > 0;
}
ASSIMP_API bool aiMaterial_GetTextureEmissive(aiMaterial* ptrMat, uint uintType,
    char* strPath, aiTextureMapping* uintMapping, uint* uintUvIndex, ai_real* floatBlend, aiTextureOp* uintOp,
    aiTextureMapMode* uintMapMode)
{
    aiString aiStrPath;
    aiReturn r = ptrMat->GetTexture(aiTextureType_EMISSIVE, uintType,
        &aiStrPath, uintMapping, uintUvIndex, floatBlend, uintOp,
        uintMapMode);
    memcpy(strPath, aiStrPath.C_Str(), aiStrPath.length);
    return  r == aiReturn_SUCCESS;
}
ASSIMP_API uint aiMaterial_GetNumTextureEmissive(aiMaterial* ptrMat)
{
    return ptrMat->GetTextureCount(aiTextureType_EMISSIVE);
}
ASSIMP_API bool aiMaterial_HasTextureSpecular(aiMaterial* ptrMat, uint uintIndex)
{
    return ptrMat->GetTextureCount(aiTextureType_SPECULAR) > 0;
}
ASSIMP_API bool aiMaterial_GetTextureSpecular(aiMaterial* ptrMat, uint uintType,
    char* strPath, aiTextureMapping* uintMapping, uint* uintUvIndex, ai_real* floatBlend, aiTextureOp* uintOp,
    aiTextureMapMode* uintMapMode)
{
    aiString aiStrPath;
    aiReturn r = ptrMat->GetTexture(aiTextureType_SPECULAR, uintType,
        &aiStrPath, uintMapping, uintUvIndex, floatBlend, uintOp,
        uintMapMode);
    memcpy(strPath, aiStrPath.C_Str(), aiStrPath.length);
    return  r == aiReturn_SUCCESS;
}

ASSIMP_API uint aiMaterial_GetNumTextureSpecular(aiMaterial* ptrMat)
{
    return ptrMat->GetTextureCount(aiTextureType_SPECULAR);
}
ASSIMP_API bool aiMaterial_HasTextureNormals(aiMaterial* ptrMat, uint uintIndex)
{
    return ptrMat->GetTextureCount(aiTextureType_NORMALS) > 0;
} 
ASSIMP_API bool aiMaterial_GetTextureNormals(aiMaterial* ptrMat, uint uintType,
    char* strPath, aiTextureMapping* uintMapping, uint* uintUvIndex, ai_real* floatBlend, aiTextureOp* uintOp,
    aiTextureMapMode* uintMapMode)
{
    aiString aiStrPath;
    aiReturn r = ptrMat->GetTexture(aiTextureType_NORMALS, uintType,
        &aiStrPath, uintMapping, uintUvIndex, floatBlend, uintOp,
        uintMapMode);
    memcpy(strPath, aiStrPath.C_Str(), aiStrPath.length);
    return  r == aiReturn_SUCCESS;
}

ASSIMP_API uint aiMaterial_GetNumTextureNormals(aiMaterial* ptrMat)
{
    return ptrMat->GetTextureCount(aiTextureType_NORMALS);
}

ASSIMP_API bool aiMaterial_HasTextureHeight(aiMaterial* ptrMat, uint uintIndex)
{
    return ptrMat->GetTextureCount(aiTextureType_HEIGHT) > 0;
}

ASSIMP_API bool aiMaterial_GetTextureHeight(aiMaterial* ptrMat, uint uintType,
    char* strPath, aiTextureMapping* uintMapping, uint* uintUvIndex, ai_real* floatBlend, aiTextureOp* uintOp,
    aiTextureMapMode* uintMapMode)
{
    aiString aiStrPath;
    aiReturn r = ptrMat->GetTexture(aiTextureType_HEIGHT, uintType,
        &aiStrPath, uintMapping, uintUvIndex, floatBlend, uintOp,
        uintMapMode);
    memcpy(strPath, aiStrPath.C_Str(), aiStrPath.length);
    return  r == aiReturn_SUCCESS;
}
ASSIMP_API uint aiMaterial_GetNumTextureHeight(aiMaterial* ptrMat)
{
    return ptrMat->GetTextureCount(aiTextureType_HEIGHT);
}

ASSIMP_API bool aiMaterial_HasAmbient(aiMaterial* ptrMat)
{
    aiColor4D colorOut;
    return ptrMat->Get(AI_MATKEY_COLOR_AMBIENT, colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_GetAmbient(aiMaterial* ptrMat, aiColor4D* colorOut)
{
    return ptrMat->Get(AI_MATKEY_COLOR_AMBIENT, *colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_HasDiffuse(aiMaterial* ptrMat)
{
    aiColor4D colorOut;
    return ptrMat->Get(AI_MATKEY_COLOR_DIFFUSE, colorOut) == aiReturn_SUCCESS;
}

ASSIMP_API bool aiMaterial_GetDiffuse(aiMaterial* ptrMat, aiColor4D* colorOut)
{
    return ptrMat->Get(AI_MATKEY_COLOR_DIFFUSE, *colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_HasSpecular(aiMaterial* ptrMat)
{
    aiColor4D colorOut;
    return ptrMat->Get(AI_MATKEY_COLOR_SPECULAR, colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_GetSpecular(aiMaterial* ptrMat, aiColor4D* colorOut)
{
    return ptrMat->Get(AI_MATKEY_COLOR_SPECULAR, *colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_HasEmissive(aiMaterial* ptrMat)
{
    aiColor4D colorOut;
    return ptrMat->Get(AI_MATKEY_COLOR_EMISSIVE, colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_GetEmissive(aiMaterial* ptrMat, aiColor4D* colorOut)
{
    return ptrMat->Get(AI_MATKEY_COLOR_EMISSIVE, *colorOut) == aiReturn_SUCCESS;
}
ASSIMP_API bool aiMaterial_HasName(aiMaterial* ptrMat)
{
    aiString name;
    return ptrMat->Get(AI_MATKEY_NAME, name);
}
ASSIMP_API bool aiMaterial_GetName(aiMaterial* ptrMat, char* nameOut)
{
    aiString name;
    aiReturn r = ptrMat->Get(AI_MATKEY_NAME, name);
    if (r == aiReturn_SUCCESS)
    {
        memcpy(nameOut, name.C_Str(), name.length);
    }
    return r;
}
ASSIMP_API bool aiMaterial_HasBumpScaling(aiMaterial* ptrMat)
{
    float bumpScaling = 0;
    return ptrMat->Get(AI_MATKEY_BUMPSCALING, bumpScaling);
}
ASSIMP_API bool aiMaterial_GetBumpScaling(aiMaterial* ptrMat, float* floatOut)
{
    aiReturn r = ptrMat->Get(AI_MATKEY_BUMPSCALING, floatOut);
    return r;
}
ASSIMP_API bool aiMaterial_HasShininess(aiMaterial* ptrMat)
{
    float floatOut = 0;
    return ptrMat->Get(AI_MATKEY_SHININESS, floatOut);
}
ASSIMP_API bool aiMaterial_GetShininess(aiMaterial* ptrMat, float* floatOut)
{
    return ptrMat->Get(AI_MATKEY_SHININESS, floatOut);
}

ASSIMP_API bool aiMaterial_HasShininessStrength(aiMaterial* ptrMat)
{
    float floatOut = 0;
    return ptrMat->Get(AI_MATKEY_SHININESS_STRENGTH, floatOut);
}
ASSIMP_API bool aiMaterial_GetShininessStrength(aiMaterial* ptrMat, float* floatOut)
{
    return ptrMat->Get(AI_MATKEY_SHININESS_STRENGTH, floatOut);
}
ASSIMP_API bool aiMaterial_HasOpacity(aiMaterial* ptrMat)
{
    float floatOut = 0;
    return ptrMat->Get(AI_MATKEY_OPACITY, floatOut);
}
ASSIMP_API bool aiMaterial_GetOpacity(aiMaterial* ptrMat, float* floatOut)
{
    return ptrMat->Get(AI_MATKEY_OPACITY, floatOut);
}

ASSIMP_API aiAnimMesh* aiMesh_GetAnimMesh(aiMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->mAnimMeshes[uintIndex];
}
ASSIMP_API const char* aiAnimMesh_GetName(aiAnimMesh* ptrMesh)
{
    return ptrMesh->mName.C_Str();
}
ASSIMP_API uint aiMesh_GetAnimMeshCount(aiMesh* ptrMesh)
{
    return ptrMesh->mNumAnimMeshes;
}
ASSIMP_API uint aiAnimMesh_GetVerticesCount(aiAnimMesh* ptrMesh)
{
    return ptrMesh->mNumVertices;
}
ASSIMP_API bool aiAnimMesh_HasPositions(aiAnimMesh* ptrMesh)
{
    return ptrMesh->HasPositions();
}

ASSIMP_API bool aiAnimMesh_HasNormals(aiAnimMesh* ptrMesh)
{
    return ptrMesh->HasNormals();
}
ASSIMP_API bool aiAnimMesh_HasTangentsAndBitangents(aiAnimMesh* ptrMesh)
{
    return ptrMesh->HasTangentsAndBitangents();
}
ASSIMP_API bool aiAnimMesh_HasTextureCoords(aiAnimMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->HasTextureCoords(uintIndex);
}
ASSIMP_API bool aiAnimMesh_HasVertexColors(aiAnimMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->HasVertexColors(uintIndex);
}
ASSIMP_API aiVector3D * aiAnimMesh_GetVertex(aiAnimMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mVertices[uintIndex];
}
ASSIMP_API aiVector3D* aiAnimMesh_GetNormal(aiAnimMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mNormals[uintIndex];
}
ASSIMP_API aiVector3D* aiAnimMesh_GetBitangent(aiAnimMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mBitangents[uintIndex];
}

ASSIMP_API aiVector3D* aiAnimMesh_GetTextureCoord(aiAnimMesh* ptrMesh, uint uintChannel, uint uintIndex)
{
    return &ptrMesh->mTextureCoords[uintChannel][uintIndex];
}

ASSIMP_API aiColor4D* aiAnimMesh_GetVertexColor(aiAnimMesh* ptrMesh, uint uintChannel, uint uintIndex)
{
    return &ptrMesh->mColors[uintChannel][uintIndex];
}

ASSIMP_API float aiAnimMesh_GetWeight(aiAnimMesh* ptrMesh)
{
    return ptrMesh->mWeight;
}
ASSIMP_API uint aiMesh_VertexCount(aiMesh* ptrMesh)
{
    return ptrMesh->mNumVertices;
}
ASSIMP_API bool aiMesh_HasNormals(aiMesh* ptrMesh)
{
    return ptrMesh->HasNormals();
}
ASSIMP_API bool aiMesh_HasTangentsAndBitangents(aiMesh* ptrMesh)
{
    return ptrMesh->HasTangentsAndBitangents();
}
ASSIMP_API bool aiMesh_HasTextureCoords(aiMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->HasTextureCoords(uintIndex);
}

ASSIMP_API bool aiMesh_HasVertexColors(aiMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->HasVertexColors(uintIndex);
}

ASSIMP_API aiVector3D* aiMesh_GetVertex(aiMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mVertices[uintIndex];
}
ASSIMP_API aiVector3D* aiMesh_GetNormal(aiMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mNormals[uintIndex];
}
ASSIMP_API aiVector3D* aiMesh_GetTangent(aiMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mTangents[uintIndex];
}
ASSIMP_API aiVector3D* aiMesh_GetBitangent(aiMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mBitangents[uintIndex];
}
ASSIMP_API aiVector3D* aiMesh_GetTextureCoord(aiMesh* ptrMesh, uint uintChannel, uint uintIndex)
{
    return &ptrMesh->mTextureCoords[uintChannel][uintIndex];
}
ASSIMP_API aiColor4D* aiMesh_GetVertexColor(aiMesh* ptrMesh, uint uintChannel, uint uintIndex)
{
    return &ptrMesh->mColors[uintChannel][uintIndex];
}

ASSIMP_API uint aiMesh_GetMatrialIndex(aiMesh* ptrMesh)
{
    return ptrMesh->mMaterialIndex;
}
ASSIMP_API const char* aiMesh_GetName(aiMesh* ptrMesh)
{
    return ptrMesh->mName.C_Str();
}
ASSIMP_API bool aiMesh_HasFaces(aiMesh* ptrMesh)
{
    return ptrMesh->HasFaces();
}

ASSIMP_API uint aiMesh_GetNumFaces(aiMesh* ptrMesh)
{
    return ptrMesh->mNumFaces;
}
ASSIMP_API void* aiMesh_GetFace(aiMesh* ptrMesh, uint uintIndex)
{
    return &ptrMesh->mFaces[uintIndex];
}
ASSIMP_API bool aiMesh_HasBones(aiMesh* ptrMesh)
{
    return ptrMesh->HasBones();
}
ASSIMP_API uint aiMesh_GetNumBones(aiMesh* ptrMesh)
{
    return ptrMesh->mNumBones;
}
ASSIMP_API void* aiMesh_GetBone(aiMesh* ptrMesh, uint uintIndex)
{
    return ptrMesh->mBones[uintIndex];
}
ASSIMP_API uint aiFace_GetNumIndices(aiFace* ptrFace)
{
    return ptrFace->mNumIndices;
}
ASSIMP_API uint aiFace_GetIndex(aiFace* ptrFace, uint uintIndex)
{
    return ptrFace->mIndices[uintIndex];
}

ASSIMP_API const char* aiBone_GetName(aiBone* ptrBone)
{
    return ptrBone->mName.C_Str();
}
ASSIMP_API uint aiBone_GetNumWeights(aiBone* ptrBone)
{
    return ptrBone->mNumWeights;
}
ASSIMP_API void* aiBone_GetWeights(aiBone* ptrBone, uint uintIndex)
{
    return &ptrBone->mWeights[uintIndex];
}

ASSIMP_API void* aiBone_GetOffsetMatrix(aiBone* ptrBone)
{
    return &ptrBone->mOffsetMatrix;
}

ASSIMP_API float aiVertexWeight_GetWeight(aiVertexWeight* ptrVweight)
{
    return ptrVweight->mWeight;
}

ASSIMP_API uint aiVertexWeight_GetVertexId(aiVertexWeight* ptrVweight)
{
    return ptrVweight->mVertexId;
}

ASSIMP_API const char* aiAnimation_GetName(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mName.C_Str();
}

ASSIMP_API float aiAnimation_GetDuraction(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mDuration;
}
ASSIMP_API float aiAnimation_GetTicksPerSecond(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mTicksPerSecond;
}
ASSIMP_API uint aiAnimation_GetNumChannels(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mNumChannels;
}
ASSIMP_API uint aiAnimation_GetNumMorphChannels(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mNumMorphMeshChannels;
}
ASSIMP_API void* aiAnimation_GetMeshMorphAnim(aiAnimation* ptrAnimation, uint uintIndex)
{
    return ptrAnimation->mMorphMeshChannels[uintIndex];
}
ASSIMP_API uint aiAnimation_GetNumMeshChannels(aiAnimation* ptrAnimation)
{
    return ptrAnimation->mNumMeshChannels;
}
ASSIMP_API void* aiAnimation_GetAnimationChannel(aiAnimation* ptrAnimation, uint uintIndex)
{
    return ptrAnimation->mChannels[uintIndex];
}
ASSIMP_API const char* aiNodeAnim_GetNodeName(aiNodeAnim* ptrNodeAnim)
{
    return ptrNodeAnim->mNodeName.C_Str();
}
ASSIMP_API const char* aiMeshMorphAnim_GetName(aiMeshMorphAnim* ptrAnimation)
{
    return ptrAnimation->mName.C_Str();
}
ASSIMP_API uint aiMeshMorphAnim_GetNumKeys(aiMeshMorphAnim* ptrAnimation)
{
    return ptrAnimation->mNumKeys;
}
ASSIMP_API uint aiNodeAnim_GetNumPositionKeys(aiNodeAnim* ptrAnimation)
{
    return ptrAnimation->mNumPositionKeys;
}
ASSIMP_API uint aiNodeAnim_GetNumRotationKeys(aiNodeAnim* ptrAnimation)
{
    return ptrAnimation->mNumRotationKeys;
}
ASSIMP_API uint aiNodeAnim_GetNumScalingKeys(aiNodeAnim* ptrAnimation)
{
    return ptrAnimation->mNumScalingKeys;
}
ASSIMP_API uint aiNodeAnim_GetPostState(aiNodeAnim* ptrAnimation)
{
    return ptrAnimation->mPostState;
}
ASSIMP_API uint aiNodeAnim_GetPreState(aiNodeAnim* ptrAnimation)
{
    return ptrAnimation->mPreState;
}
ASSIMP_API void* aiNodeAnim_GetPositionKey(aiNodeAnim* ptrAnimation, uint uintIndex)
{
    return &ptrAnimation->mPositionKeys[uintIndex];
}
ASSIMP_API void* aiMeshMorphAnim_GetMeshMorphKey(aiMeshMorphAnim* ptrAnimation, uint uintIndex)
{
    return &ptrAnimation->mKeys[uintIndex];
}
ASSIMP_API void* aiNodeAnim_GetRotationKey(aiNodeAnim* ptrAnimation, uint uintIndex)
{
    return &ptrAnimation->mRotationKeys[uintIndex];
}
ASSIMP_API void* aiNodeAnim_GetScalingKey(aiNodeAnim* ptrAnimation, uint uintIndex)
{
    return &ptrAnimation->mScalingKeys[uintIndex];
}

ASSIMP_API float aiMeshMorphKey_GetTime(aiMeshMorphKey* ptrVectorKey)
{
    return ptrVectorKey->mTime;
}
ASSIMP_API uint aiMeshMorphKey_GetNumValues(aiMeshMorphKey* ptrVectorKey)
{
    return ptrVectorKey->mNumValuesAndWeights;
}
ASSIMP_API uint aiMeshMorphKey_GetValue(aiMeshMorphKey* ptrVectorKey, uint uintIndex)
{
    return ptrVectorKey->mValues[uintIndex];
}
ASSIMP_API float aiMeshMorphKey_GetWeight(aiMeshMorphKey* ptrVectorKey, uint uintIndex)
{
    return ptrVectorKey->mWeights[uintIndex];
}
ASSIMP_API float aiVectorKey_GetTime(aiVectorKey* ptrVectorKey)
{
    return ptrVectorKey->mTime;
}
ASSIMP_API void* aiVectorKey_GetValue(aiVectorKey* ptrVectorKey)
{
    return &ptrVectorKey->mValue;
}


ASSIMP_API float aiQuatKey_GetTime(aiQuatKey* ptrQuatKey)
{
    return ptrQuatKey->mTime;
}
ASSIMP_API void* aiQuatKey_GetValue(aiQuatKey* ptrQuatKey)
{
    return &ptrQuatKey->mValue;
}

ASSIMP_API float aiCamera_GetAspect(aiCamera* ptrCamera)
{
    return ptrCamera->mAspect;
}
ASSIMP_API float aiCamera_GetClipPlaneFar(aiCamera* ptrCamera)
{
    return ptrCamera->mClipPlaneFar;
}
ASSIMP_API float aiCamera_GetClipPlaneNear(aiCamera* ptrCamera)
{
    return ptrCamera->mClipPlaneNear;
}
ASSIMP_API float aiCamera_GetHorizontalFOV(aiCamera* ptrCamera)
{
    return ptrCamera->mHorizontalFOV;
}

ASSIMP_API void* aiCamera_GetLookAt(aiCamera* ptrCamera)
{
    return &ptrCamera->mLookAt;
}
ASSIMP_API const char* aiCamera_GetName(aiCamera* ptrCamera)
{
    return ptrCamera->mName.C_Str();
}
ASSIMP_API void* aiCamera_GetPosition(aiCamera* ptrCamera)
{
    return &ptrCamera->mPosition;
}
ASSIMP_API void* aiCamera_GetUp(aiCamera* ptrCamera)
{
    return &ptrCamera->mUp;
}

ASSIMP_API float aiLight_GetAngleInnerCone(aiLight* ptrLight)
{
    return ptrLight->mAngleInnerCone;
}
ASSIMP_API float aiLight_GetAngleOuterCone(aiLight* ptrLight)
{
    return ptrLight->mAngleOuterCone;
}
ASSIMP_API float aiLight_GetAttenuationConstant(aiLight* ptrLight)
{
    return ptrLight->mAttenuationConstant;
}
ASSIMP_API float aiLight_GetAttenuationQuadratic(aiLight* ptrLight)
{
    return ptrLight->mAttenuationQuadratic;
}
ASSIMP_API void* aiLight_GetColorAmbient(aiLight* ptrLight)
{
    return &ptrLight->mColorAmbient;
}
ASSIMP_API void* aiLight_GetColorDiffuse(aiLight* ptrLight)
{
    return &ptrLight->mColorDiffuse;
}
ASSIMP_API void* aiLight_GetColorSpecular(aiLight* ptrLight)
{
    return &ptrLight->mColorSpecular;
}
ASSIMP_API void* aiLight_GetDirection(aiLight* ptrLight)
{
    return &ptrLight->mDirection;
}
ASSIMP_API const char* aiLight_GetName(aiLight* ptrLight)
{
    return ptrLight->mName.C_Str();
}
ASSIMP_API uint aiScene_GetMetadataCount(aiScene* ptrScene)
{
    if (ptrScene->mMetaData)
    {
        return ptrScene->mMetaData->mNumProperties;
    }
    return 0;
}
ASSIMP_API const char* aiScene_GetMetadataKey(aiScene* ptrScene, uint uintIndex)
{
    if (ptrScene->mMetaData)
    {
        return ptrScene->mMetaData->mKeys[uintIndex].C_Str();
    }
    return nullptr;
}
ASSIMP_API aiMetadataType aiScene_GetMetadataType(aiScene* ptrScene, uint uintIndex)
{
    if (ptrScene->mMetaData)
    {
        return ptrScene->mMetaData->mValues[uintIndex].mType;
    }
    return aiMetadataType::AI_BOOL;
}
ASSIMP_API void* aiScene_GetMetadataValue(aiScene* ptrScene, uint uintIndex)
{
    if (ptrScene->mMetaData)
    {
        return ptrScene->mMetaData->mValues[uintIndex].mData;
    }
    return nullptr;
}

#ifdef __cplusplus
}
#endif
