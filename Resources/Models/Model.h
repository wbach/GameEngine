#pragma once
#include "Mesh.h"
#include <list>
#include "../OpenGLObject.h"

class CModel : public COpenGLObject
{
public:
	CModel();

	virtual void InitModel(std::string file_name);
    CModel(const CModel& ) = delete;
	virtual ~CModel() {}
	virtual void Update(float dt) {};
	virtual const std::vector<glm::mat4>& GetBonesTransforms(unsigned int mesh_id) { return  std::vector<glm::mat4>(); }
	virtual void AddCurrentFramePtr(unsigned int* ptr) { m_CurrentFrames.push_back(ptr); }
	virtual void SetCurrentFrame(unsigned int& current_frame) {}
	virtual void SetTime(const float& time) {}
	void OpenGLLoadingPass();
	CMesh* AddMesh(std::vector<float>& positions, std::vector<float>& text_coords, std::vector<float>& normals, std::vector<float>& tangents,
		std::vector<unsigned short>& indices, SMaterial& material, std::vector<SVertexBoneData>& bones);
	const std::list<CMesh>& GetMeshes() const {return m_Meshes;	}
protected:
	std::list<CMesh> m_Meshes;

	//For all model
	BoundingBox m_BoundingBox;

	//One model in memory for all entities, so we need have time from outside to update (each entity can have diffrent animation progress)
	std::list<unsigned int*> m_CurrentFrames;

    unsigned int m_Id = 0;
    static unsigned int s_Id;
};
