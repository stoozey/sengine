//#include "utils/model_util.hpp"
//#include "classes/mesh.hpp"
//
//namespace utils {
//    void SceneToMeshVector(const aiScene *scene, std::vector<classes::Mesh> *outMeshes) {
//        for (int i = 0; i < node->mNumChildren; i++) {
//            ProcessNode(directory, node->mChildren[i]);
//        }
//        for (int i = 0; i < node->mNumMeshes; i++) {
//            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//            // vertices
//            core::Log::Info("ProcessMesh1");
//            std::vector<structs::Vertex> vertices;
//            for (int j = 0; j < mesh->mNumVertices; j++)
//            {
//                glm::vec3 position;
//                position.x = mesh->mVertices[j].x;
//                position.y = mesh->mVertices[j].y;
//                position.z = mesh->mVertices[j].z;
//
//                glm::vec3 normal;
//                if (mesh->mNormals != nullptr) {
//                    normal.x = mesh->mNormals[j].x;
//                    normal.y = mesh->mNormals[j].y;
//                    normal.z = mesh->mNormals[j].z;
//                }
//
//                glm::vec2 texCoords;
//                if (mesh->mTextureCoords[0]) {
//                    texCoords.x = mesh->mTextureCoords[0][j].x;
//                    texCoords.y = mesh->mTextureCoords[0][j].y;
//                }
//
//                vertices.push_back({ position, normal, texCoords });
//            }
//
//            // indices
//            core::Log::Info("ProcessMesh2");
//            std::vector<GLuint> indices;
//            for (int j = 0; j < mesh->mNumFaces; j++)
//            {
//                aiFace face = mesh->mFaces[j];
//                for (int p = 0; p < face.mNumIndices; p++)
//                    indices.push_back(face.mIndices[p]);
//            }
//
//            // textures
//            core::Log::Info("ProcessMesh3");
//            std::vector<std::weak_ptr<assets::Texture>> textures;
////        if (mesh->mMaterialIndex >= 0)
////        {
////            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
////            vector<Texture> diffuseMaps = loadMaterialTextures(material,
////                                                               aiTextureType_DIFFUSE, "texture_diffuse");
////            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
////            vector<Texture> specularMaps = loadMaterialTextures(material,
////                                                                aiTextureType_SPECULAR, "texture_specular");
////            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
////        }
//
//            core::Log::Info("ProcessMesh4");
//            outMeshes->emplace_back(classes::Mesh{ vertices, indices, textures });
//        }
//
//    }
//}