#include "D3DModel.h"
#include <sstream>

#include "TextureManager.h"

static unsigned int nextID = 0;

D3DModel::D3DModel()
{
	texture = 0;
	staticMesh = true;
	ID = nextID++;
}

D3DModel::D3DModel(unsigned int id)
{
	texture = 0;
	staticMesh = true;
	ID = id;
}

D3DModel::~D3DModel()
{
}

bool D3DModel::LoadModel(ID3D11Device* device, std::wstring fileName)
{
	bool result;

	std::wifstream fileIn(fileName.c_str());

	std::wstring checkString;

	if(fileIn)
	{
		while(fileIn)
		{
			fileIn >> checkString;

			if(checkString == L"MD5Version")
			{
				//this ensures proper parsing
				fileIn >> checkString;
				if(checkString != L"10")
				{
					return false;
				}
			}
			else if(checkString == L"commandline")
			{
				//ignore commandline. not needed
				std::getline(fileIn, checkString);
			}
			else if(checkString == L"numJoints")
			{
				//determine the number of joints in the file
				fileIn >> numJoints;
			}
			else if(checkString == L"numMeshes")
			{
				//determine the number of subsets in the file
				fileIn >> numSubsets;
			}
			else if(checkString == L"joints")
			{
				Joint tempJoint;

				fileIn >> checkString;

				for(int i = 0; i < numJoints; i++)
				{
					fileIn >> tempJoint.name;
					//ensure the full name is returned
					if(tempJoint.name[tempJoint.name.size()-1] != '"')
					{
						wchar_t checkChar;
						bool jointNameFound = false;
						while(!jointNameFound)
						{
							checkChar = fileIn.get();

							if(checkChar == '"')
							{
								jointNameFound = true;
							}

							tempJoint.name += checkChar;
						}
					}

					//store the paretn joint's ID
					fileIn >> tempJoint.parentID;

					//skip the "("
					fileIn >> checkString;

					//store position of this joint (swap y and z axis if model was made in RH Coord Sys)
					fileIn >> tempJoint.position.x >> tempJoint.position.z >> tempJoint.position.y;

					//skip the ")" and "("
					fileIn >> checkString >> checkString;

					//store orientation of the joint
					fileIn >> tempJoint.orientation.x >> tempJoint.orientation.z >> tempJoint.orientation.y;

					//erase the quotation marks stored in the name
					tempJoint.name.erase(0, 1);
					tempJoint.name.erase(tempJoint.name.size()-1, 1);

					//compute the w for the orientation quaternion
					float t = 1.0f - (tempJoint.orientation.x * tempJoint.orientation.x)
						- (tempJoint.orientation.y * tempJoint.orientation.y)
						- (tempJoint.orientation.z * tempJoint.orientation.z);
					if(t < 0.0f)
					{
						tempJoint.orientation.w = 0.0f;
					}
					else
					{
						tempJoint.orientation.w = -sqrtf(t);
					}

					//skip the rest of this line
					std::getline(fileIn, checkString);

					//store the joint into the model's joints
					joints.push_back(tempJoint);
				}

				fileIn >> checkString;
			}
			else if(checkString == L"mesh")
			{
				ModelSubset subset;
				int numVerts, numTris, numWeights;

				fileIn >> checkString;

				fileIn >> checkString;
				while(checkString != L"}")
				{
					if(checkString == L"shader")
					{
						std::wstring fileNamePath;
						fileIn >> fileNamePath;

						//ensure the entire name is stored
						if(fileNamePath[fileNamePath.size()-1] != '"')
						{
							wchar_t checkChar;
							bool fileNameFound = false;
							while(!fileNameFound)
							{
								checkChar = fileIn.get();

								if(checkChar == '"')
								{
									fileNameFound = true;
								}

								fileNamePath += checkChar;
							}
						}

						//remove the quotation marks from the texture path
						fileNamePath.erase(0, 1);
						fileNamePath.erase(fileNamePath.size()-1, 1);

						//load the texture this will be changed later for memory optimization
						if(texture == 0)// && textureNames[fileNamePath])
						{
							std::string reference(fileNamePath.begin(), fileNamePath.end());
							texture = textureManager->GetTexture(reference);
						}

						//skip the rest of the line
						std::getline(fileIn, checkString);
					}
					else if(checkString == L"numverts")
					{
						//store the number of vertices in this subset
						fileIn >> numVerts;

						//skip the rest of the line
						std::getline(fileIn, checkString);

						for(int i = 0; i < numVerts; i++)
						{
							Vertex tempVert;

							//remove the "vert" the vert number and the "("
							fileIn >> checkString >> checkString >> checkString;

							//store the texture UV
							fileIn >> tempVert.texture.x >> tempVert.texture.y;

							//remove the ")"
							fileIn >> checkString;

							//store the start weight
							fileIn >> tempVert.StartWeight;

							//store the number of weights
							fileIn >> tempVert.WeightCount;

							//skip the rest of the line
							std::getline(fileIn, checkString);

							subset.vertices.push_back(tempVert);
						}
					}
					else if(checkString == L"numtris")
					{
						//store the number of tris for the subset
						fileIn >> numTris;
						subset.numTriangles = numTris;

						//skip the rest of the line
						std::getline(fileIn, checkString);

						for(int i = 0; i < numTris; i++)
						{
							DWORD tempIndex;
							//skip the "tri" and the tri number
							fileIn >> checkString >> checkString;

							//push back each index of the tri
							for(int j = 0; j < 3; j++)
							{
								fileIn >> tempIndex;
								subset.indices.push_back(tempIndex);
							}

							//skip the rest of the line
							std::getline(fileIn, checkString);
						}
					}
					else if(checkString == L"numweights")
					{
						//store the number of weights
						fileIn >> numWeights;

						//skip the rest of the line
						std::getline(fileIn, checkString);

						for(int i = 0; i < numWeights; i++)
						{
							Weight tempWeight;
							//skip the "weight" and the weight number
							fileIn >> checkString >> checkString;

							//store the joint id
							fileIn >> tempWeight.jointID;

							//store the weight bias
							fileIn >> tempWeight.bias;

							//skip the "("
							fileIn >> checkString;

							//store the weight position
							fileIn >> tempWeight.position.x;
							fileIn >> tempWeight.position.z;
							fileIn >> tempWeight.position.y;

							//skip the rest of the line
							std::getline(fileIn, checkString);

							subset.weights.push_back(tempWeight);
						}
					}
					else
					{
						//skip the rest of the line
						std::getline(fileIn, checkString);
					}
					
					fileIn >> checkString;
				}

				//find each vertex's position using the joints and weights
				for(unsigned int i = 0; i < subset.vertices.size(); ++i)
				{
					Vertex tempVert = subset.vertices[i];
					//set the initial vert position to [0,0,0]
					tempVert.position = D3DXVECTOR3(0, 0, 0);

					for(int j = 0; j < tempVert.WeightCount; ++j)
					{
						Weight tempWeight = subset.weights[tempVert.StartWeight + j];
						Joint tempJoint = joints[tempWeight.jointID];

						//store the orientation and weight position as quaternions
						D3DXQUATERNION tempJointOrientation = D3DXQUATERNION(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
						D3DXQUATERNION tempWeightPos = D3DXQUATERNION(tempWeight.position.x, tempWeight.position.y, tempWeight.position.z, 0.0f);

						//store the orientation conjugate (-x,-y,-z,w)
						D3DXQUATERNION tempJointOrientationConjugate = D3DXQUATERNION(-tempJoint.orientation.x, -tempJoint.orientation.y, -tempJoint.orientation.z, tempJoint.orientation.w);

						//calculate vertex position
						D3DXQUATERNION tempQuaternion;
						D3DXQuaternionMultiply(&tempQuaternion, &tempJointOrientation, &tempWeightPos);
						D3DXQuaternionMultiply(&tempQuaternion, &tempQuaternion, &tempJointOrientationConjugate);
						D3DXVECTOR3 rotatedPoint = D3DXVECTOR3(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z);

						tempVert.position.x += (tempJoint.position.x + rotatedPoint.x) * tempWeight.bias;
						tempVert.position.y += (tempJoint.position.y + rotatedPoint.y) * tempWeight.bias;
						tempVert.position.z += (tempJoint.position.z + rotatedPoint.z) * tempWeight.bias;
					}

					subset.positions.push_back(tempVert.position);
				}

				for(unsigned int i = 0; i < subset.vertices.size(); i++)
				{
					subset.vertices[i].position = subset.positions[i];
				}

				std::vector<D3DXVECTOR3> tempNormal;

				D3DXVECTOR3 unnormalized = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				float vecX, vecY, vecZ;

				D3DXVECTOR3 edge1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				D3DXVECTOR3 edge2 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

				for(int i = 0; i < subset.numTriangles; ++i)
				{
					vecX = subset.vertices[subset.indices[(i*3)]].position.x - subset.vertices[subset.indices[(i*3)+2]].position.x;
					vecY = subset.vertices[subset.indices[(i*3)]].position.y - subset.vertices[subset.indices[(i*3)+2]].position.y;
					vecZ = subset.vertices[subset.indices[(i*3)]].position.z - subset.vertices[subset.indices[(i*3)+2]].position.z;
					edge1 = D3DXVECTOR3(vecX, vecY, vecZ);

					vecX = subset.vertices[subset.indices[(i*3)+2]].position.x - subset.vertices[subset.indices[(i*3)+1]].position.x;
					vecY = subset.vertices[subset.indices[(i*3)+2]].position.y - subset.vertices[subset.indices[(i*3)+1]].position.y;
					vecZ = subset.vertices[subset.indices[(i*3)+2]].position.z - subset.vertices[subset.indices[(i*3)+1]].position.z;
					edge2 = D3DXVECTOR3(vecX, vecY, vecZ);

					D3DXVec3Cross(&unnormalized, &edge1, &edge2);

					tempNormal.push_back(unnormalized);
				}

				D3DXVECTOR3 normalSum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				int facesUsing = 0;
				float tX, tY, tZ;

				for(unsigned int i = 0; i < subset.vertices.size(); ++i)
				{
					for(int j = 0; j < subset.numTriangles; ++j)
					{
						if(subset.indices[j*3] == i ||
							subset.indices[(j*3)+1] == i ||
							subset.indices[(j*3)+2] == i)
						{
							tX = normalSum.x + tempNormal[j].x;
							tY = normalSum.y + tempNormal[j].y;
							tZ = normalSum.z + tempNormal[j].z;

							normalSum = D3DXVECTOR3(tX, tY, tZ);

							facesUsing++;
						}
					}

					normalSum = normalSum / (float)facesUsing;

					D3DXVec3Normalize(&normalSum, &normalSum);

					subset.vertices[i].normal.x = -normalSum.x;
					subset.vertices[i].normal.y = -normalSum.y;
					subset.vertices[i].normal.z = -normalSum.z;

					//create the joint space normal for animations
					Vertex tempVert = subset.vertices[i];
					subset.jointSpaceNormals.push_back(D3DXVECTOR3(0, 0, 0));
					D3DXQUATERNION normal = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 0.0f);
					
					for(int j = 0; j < tempVert.WeightCount; j++)
					{
						//get the joint's orientation
						Joint tempJoint = joints[subset.weights[tempVert.StartWeight + j].jointID];
						D3DXQUATERNION jointOrientation = D3DXQUATERNION(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);

						//calculate the normal based on the joint's orientation
						D3DXQUATERNION tempConjugate, normalSumQ;
						D3DXQuaternionInverse(&tempConjugate, &jointOrientation);
						normalSumQ = D3DXQUATERNION(normalSum.x, normalSum.y, normalSum.z, 0.0f);
						D3DXQuaternionMultiply(&normal, &tempConjugate, &normalSumQ);
						D3DXQuaternionMultiply(&normal, &normal, &jointOrientation);

						//normalize the normal
						D3DXQuaternionNormalize(&normal, &normal);
						subset.weights[tempVert.StartWeight + j].normal = D3DXVECTOR3(normal.x, normal.y, normal.z);
					}

					normalSum = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					facesUsing = 0;
				}

				result = InitializeBuffers(device, subset);
				if(!result)
				{
					return false;
				}

				subsets.push_back(subset);
			}
		}
	}
	else
	{
		return false;
	}

	return true;
};

void D3DModel::LoadTexture(D3DTexture* temp)
{
	texture = temp;
}

bool D3DModel::LoadAnimation(std::wstring fileName)
{
	ModelAnimation tempAnim;

	std::wifstream fileIn(fileName.c_str());

	std::wstring checkString;

	if(fileIn)
	{
		while(fileIn)
		{
			fileIn >> checkString;

			//check to ensure the proper version is used
			if(checkString == L"MD5Version")
			{
				fileIn >> checkString;
				if(checkString != L"10")
				{
					return false;
				}
			}
			else if(checkString == L"commandline")
			{
				//ignore this line
				std::getline(fileIn, checkString);
			}
			else if(checkString == L"numFrames")
			{
				//store the number of frame in the animation
				fileIn >> tempAnim.numFrames;
			}
			else if(checkString == L"numJoints")
			{
				//store the number of joints in the animation
				fileIn >> tempAnim.numJoints;
			}
			else if(checkString == L"frameRate")
			{
				//store the intended framerate
				fileIn >> tempAnim.frameRate;
			}
			else if(checkString == L"numAnimatedComponents")
			{
				//store the number of components in each frame section
				fileIn >> tempAnim.numAnimatedComponents;
			}
			else if(checkString == L"hierarchy")
			{
				//skip the "{"
				fileIn >> checkString;
				
				//load in each joint
				for(int i = 0; i < tempAnim.numJoints; i++)
				{
					AnimJointInfo tempJoint;

					//store the joint name
					fileIn >> tempJoint.name;

					//ensure the full name is stored
					if(tempJoint.name[tempJoint.name.size()-1] != '"')
					{
						wchar_t checkChar;
						bool jointNameFound = false;
						while(!jointNameFound)
						{
							checkChar = fileIn.get();

							if(checkChar == '"')
							{
								jointNameFound = true;
							}

							tempJoint.name += checkChar;
						}
					}

					//erase the quotations in the name
					tempJoint.name.erase(0, 1);
					tempJoint.name.erase(tempJoint.name.size()-1, 1);

					//store the joint's parent id, flags, and start index
					fileIn >> tempJoint.parentID;
					fileIn >> tempJoint.flags;
					fileIn >> tempJoint.startIndex;

					//check to ensure the joint was found for the model
					bool jointMatchFound = false;
					for(int j = 0; j < numJoints; j++)
					{
						if(joints[j].name == tempJoint.name)
						{
							if(joints[j].parentID == tempJoint.parentID)
							{
								jointMatchFound = true;
								tempAnim.jointInfo.push_back(tempJoint);
								break;
							}
						}
					}
					if(!jointMatchFound)
					{
						return false;
					}
					//skip the rest of the line
					std::getline(fileIn, checkString);
				}
			}
			else if(checkString == L"bounds")
			{
				//skip the "{"
				fileIn >> checkString;

				for(int i = 0; i < tempAnim.numFrames; i++)
				{
					BoundingBox tempBB;

					//skip the "("
					fileIn >> checkString;
					//store the min position
					fileIn >> tempBB.min.x >> tempBB.min.z >> tempBB.min.y;
					//skip the ")" and "("
					fileIn >> checkString >> checkString;
					//store the max position
					fileIn >> tempBB.max.x >> tempBB.max.z >> tempBB.max.y;
					//skip the ")"
					fileIn >> checkString;

					tempAnim.frameBounds.push_back(tempBB);
				}
			}
			else if(checkString == L"baseframe")
			{
				//skip the "{"
				fileIn >> checkString;

				for(int i = 0; i < tempAnim.numJoints; i++)
				{
					Joint tempBFJ;

					//skip the "("
					fileIn >> checkString;
					//store the position
					fileIn >> tempBFJ.position.x >> tempBFJ.position.z >> tempBFJ.position.y;
					//skip the ")" and "("
					fileIn >> checkString >> checkString;
					//store the orientation
					fileIn >> tempBFJ.orientation.x >> tempBFJ.orientation.z >> tempBFJ.orientation.y;
					//skip the ")"
					fileIn >> checkString;

					tempAnim.baseFrameJoints.push_back(tempBFJ);
				}
			}
			else if(checkString == L"frame")
			{
				FrameData tempFrame;

				//store the frame id
				fileIn >> tempFrame.frameID;

				//skip the "{"
				fileIn >> checkString;

				for(int i = 0; i < tempAnim.numAnimatedComponents; i++)
				{
					float tempData;
					//get the data
					fileIn >> tempData;

					tempFrame.frameData.push_back(tempData);
				}

				tempAnim.frameData.push_back(tempFrame);

				std::vector<Joint> tempSkeleton;

				for(unsigned int i = 0; i < tempAnim.jointInfo.size(); i++)
				{
					int j = 0;

					//start the frame's joint with the base frame's joint
					Joint tempFrameJoint = tempAnim.baseFrameJoints[i];
					//store the parent id
					tempFrameJoint.parentID = tempAnim.jointInfo[i].parentID;

					//handle joint info flags
					
					//position.x flag (000001)
					if(tempAnim.jointInfo[i].flags & 1)
					{
						tempFrameJoint.position.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}
					//position.y flag (000010)
					if(tempAnim.jointInfo[i].flags & 2)
					{
						tempFrameJoint.position.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}
					//position.z flag (000100)
					if(tempAnim.jointInfo[i].flags & 4)
					{
						tempFrameJoint.position.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}
					//orientation.x flag (001000)
					if(tempAnim.jointInfo[i].flags & 8)
					{
						tempFrameJoint.orientation.x = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}
					//orientation.y flag (010000)
					if(tempAnim.jointInfo[i].flags & 16)
					{
						tempFrameJoint.orientation.z = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}
					//orientation.z flag (100000)
					if(tempAnim.jointInfo[i].flags & 32)
					{
						tempFrameJoint.orientation.y = tempFrame.frameData[tempAnim.jointInfo[i].startIndex + j++];
					}

					//compute the quaternion w for the orientation
					float t = 1.0f - (tempFrameJoint.orientation.x * tempFrameJoint.orientation.x)
						- (tempFrameJoint.orientation.y * tempFrameJoint.orientation.y)
						- (tempFrameJoint.orientation.z * tempFrameJoint.orientation.z);
					if(t < 0.0f)
					{
						tempFrameJoint.orientation.w = 0.0f;
					}
					else
					{
						tempFrameJoint.orientation.w = -sqrtf(t);
					}

					if(tempFrameJoint.parentID >= 0)
					{
						Joint parentJoint = tempSkeleton[tempFrameJoint.parentID];

						//store orientation and position quaternions for the parent joint
						D3DXQUATERNION parentJointOrientation = D3DXQUATERNION(parentJoint.orientation.x, parentJoint.orientation.y, parentJoint.orientation.z, parentJoint.orientation.w);
						D3DXQUATERNION tempJointPos = D3DXQUATERNION(tempFrameJoint.position.x, tempFrameJoint.position.y, tempFrameJoint.position.z, 0.0f);
						D3DXQUATERNION parentOrientationConjugate = D3DXQUATERNION(-parentJointOrientation.x, -parentJointOrientation.y, -parentJointOrientation.z, parentJointOrientation.w);

						//get the rotated position
						D3DXQUATERNION tempQuaternion;
						D3DXQuaternionMultiply(&tempQuaternion, &parentJointOrientation, &tempJointPos);
						D3DXQuaternionMultiply(&tempQuaternion, &tempQuaternion, &parentOrientationConjugate);
						D3DXVECTOR3 rotatedPos = D3DXVECTOR3(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z);

						//translate the joint position to model space
						tempFrameJoint.position.x = rotatedPos.x + parentJoint.position.x;
						tempFrameJoint.position.y = rotatedPos.y + parentJoint.position.y;
						tempFrameJoint.position.z = rotatedPos.z + parentJoint.position.z;

						//translate the joint orientation to model space
						tempQuaternion = D3DXQUATERNION(tempFrameJoint.orientation.x, tempFrameJoint.orientation.y, tempFrameJoint.orientation.z, tempFrameJoint.orientation.w);
						D3DXQuaternionMultiply(&tempQuaternion, &parentJointOrientation, &tempQuaternion);

						//normalize the orientation
						D3DXQuaternionNormalize(&tempQuaternion, &tempQuaternion);
						tempFrameJoint.orientation = D3DXVECTOR4(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z, tempQuaternion.w);
					}
					//store the joint into the temporary frame skeleton
					tempSkeleton.push_back(tempFrameJoint);
				}
				//store the frame skeleton into the animation skeleton
				tempAnim.frameSkeleton.push_back(tempSkeleton);

				//skip the "}"
				fileIn >> checkString;
			}
		}

		//calculate and store some animation data
		tempAnim.frameTime = 1.0f / tempAnim.frameRate;
		tempAnim.totalAnimTime = tempAnim.numFrames * tempAnim.frameTime;
		tempAnim.currAnimTime = 0.0f;

		animations.push_back(tempAnim);
	}
	else
	{
		return false;
	}

	staticMesh = false;
	return true;
}

void D3DModel::Shutdown()
{
	ReleaseTexture();

	ShutdownBuffers();
}

void D3DModel::Update(ID3D11DeviceContext* deviceContext, float dt, int animation)
{
	if(!staticMesh)
	{
		animations[animation].currAnimTime += dt;

		if(animations[animation].currAnimTime > animations[animation].totalAnimTime)
		{
			animations[animation].currAnimTime = 0.0f;
		}

		//determine the current frame
		float currentFrame = animations[animation].currAnimTime * animations[animation].frameRate;
		int frame0 = (int)floorf(currentFrame);
		int frame1 = frame0 + 1;

		//make sure not to go over the total frames
		if(frame0 == animations[animation].numFrames-1)
		{
			frame1 = 0;
		}

		//get the remainder in time between the current and next frame
		float interpolation = currentFrame - frame0;

		//create a frame skeleton
		std::vector<Joint> interpolatedSkeleton;

		for(int i = 0; i < animations[animation].numJoints; i++)
		{
			Joint tempJoint;
			Joint joint0 = animations[animation].frameSkeleton[frame0][i];
			Joint joint1 = animations[animation].frameSkeleton[frame1][i];

			//turn get the orientations of the joints as quaternions
			D3DXQUATERNION joint0Orientation = D3DXQUATERNION(joint0.orientation.x, joint0.orientation.y, joint0.orientation.z, joint0.orientation.w);
			D3DXQUATERNION joint1Orientation = D3DXQUATERNION(joint1.orientation.x, joint1.orientation.y, joint1.orientation.z, joint1.orientation.w);

			//interpolate positions
			tempJoint.position.x = joint0.position.x + (interpolation * (joint1.position.x - joint0.position.x));
			tempJoint.position.y = joint0.position.y + (interpolation * (joint1.position.y - joint0.position.y));
			tempJoint.position.z = joint0.position.z + (interpolation * (joint1.position.z - joint0.position.z));

			//slerp
			D3DXQUATERNION tempQuaternion;
			D3DXQuaternionSlerp(&tempQuaternion, &joint0Orientation, &joint1Orientation, interpolation);
			//store the interpolated orientation
			tempJoint.orientation = D3DXVECTOR4(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z, tempQuaternion.w);

			//store the joint in the interpolated skeleton
			interpolatedSkeleton.push_back(tempJoint);
		}

		for(int i = 0; i < numSubsets; i++)
		{
			for(unsigned int j = 0; j < subsets[i].vertices.size(); ++j)
			{
				Vertex tempVert = subsets[i].vertices[j];
				//clear out the position and normal before use
				tempVert.position = D3DXVECTOR3(0, 0, 0);
				tempVert.normal = D3DXVECTOR3(0, 0, 0);

				for(int k = 0; k < tempVert.WeightCount; ++k)
				{
					Weight tempWeight = subsets[i].weights[tempVert.StartWeight + k];
					Joint tempJoint = interpolatedSkeleton[tempWeight.jointID];

					//store joint orientation and weight position
					D3DXQUATERNION tempJointOrientation = D3DXQUATERNION(tempJoint.orientation.x, tempJoint.orientation.y, tempJoint.orientation.z, tempJoint.orientation.w);
					D3DXQUATERNION tempWeightPos = D3DXQUATERNION(tempWeight.position.x, tempWeight.position.y, tempWeight.position.z, 0.0f);
					D3DXQUATERNION tempOrientationConjugate;
					D3DXQuaternionInverse(&tempOrientationConjugate, &tempJointOrientation);

					//calculate the rotated point
					D3DXQUATERNION tempQuaternion;
					D3DXQuaternionMultiply(&tempQuaternion, &tempJointOrientation, &tempWeightPos);
					D3DXQuaternionMultiply(&tempQuaternion, &tempQuaternion, &tempOrientationConjugate);
					D3DXVECTOR3 rotatedPoint = D3DXVECTOR3(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z);

					//move the vertex's position from joint space to world space, taking the bias into account
					tempVert.position.x += (tempJoint.position.x + rotatedPoint.x) * tempWeight.bias;
					tempVert.position.y += (tempJoint.position.y + rotatedPoint.y) * tempWeight.bias;
					tempVert.position.z += (tempJoint.position.z + rotatedPoint.z) * tempWeight.bias;

					//store the weight normal
					D3DXQUATERNION tempWeightNormal = D3DXQUATERNION(tempWeight.normal.x, tempWeight.normal.y, tempWeight.normal.z, 0.0f);
				
					//calculate the rotated point for the normal
					D3DXQuaternionMultiply(&tempQuaternion, &tempJointOrientation, &tempWeightNormal);
					D3DXQuaternionMultiply(&tempQuaternion, &tempQuaternion, &tempOrientationConjugate);
					rotatedPoint = D3DXVECTOR3(tempQuaternion.x, tempQuaternion.y, tempQuaternion.z);

					//add the rotated normal to the vertex's normal with the weight bias
					tempVert.normal.x -= rotatedPoint.x * tempWeight.bias;
					tempVert.normal.y -= rotatedPoint.y * tempWeight.bias;
					tempVert.normal.z -= rotatedPoint.z * tempWeight.bias;
					//normalize the normal vector
					D3DXVec3Normalize(&tempVert.normal, &tempVert.normal);
				}

				subsets[i].positions[j] = tempVert.position;
				subsets[i].vertices[j].normal = tempVert.normal;
			}
			//store the positions into the vertices for the subset
			for(unsigned int j = 0; j < subsets[i].vertices.size(); j++)
			{
				subsets[i].vertices[j].position = subsets[i].positions[j];
			}

			D3D11_MAPPED_SUBRESOURCE mappedVertBuff;
			HRESULT hr = deviceContext->Map(subsets[i].vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedVertBuff);

			memcpy(mappedVertBuff.pData, &subsets[i].vertices[0], (sizeof(Vertex) * subsets[i].vertices.size()));

			deviceContext->Unmap(subsets[i].vertexBuffer, 0);

			deviceContext->UpdateSubresource(subsets[i].vertexBuffer, 0, NULL, &subsets[i].vertices[0], 0, 0);
		}
	}
}

unsigned int D3DModel::GetID()
{
	return ID;
}

int D3DModel::GetNumSubsets()
{
	return numSubsets;
}

std::vector<ModelSubset> D3DModel::GetSubsets()
{
	return subsets;
}

ID3D11ShaderResourceView* D3DModel::GetTexture()
{
	return texture->GetTexture();
}

bool D3DModel::InitializeBuffers(ID3D11Device* device, ModelSubset& subset)
{
	HRESULT result;

	D3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(DWORD) * subset.numTriangles * 3;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA dataPtr;

	dataPtr.pSysMem = &subset.indices[0];
	result = device->CreateBuffer(&indexBufferDesc, &dataPtr, &subset.indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	D3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(vertexBufferDesc));

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(Vertex) * subset.vertices.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA dataPtr2;

	dataPtr2.pSysMem = &subset.vertices[0];
	result = device->CreateBuffer(&vertexBufferDesc, &dataPtr2, &subset.vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void D3DModel::ShutdownBuffers()
{
	for(int i = 0; i < numSubsets; i++)
	{
		subsets[i].indexBuffer->Release();
		subsets[i].indexBuffer = 0;
		subsets[i].vertexBuffer->Release();
		subsets[i].vertexBuffer = 0;
	}
}

void D3DModel::ReleaseTexture()
{
	if(texture)
	{
		//dont delete the texture as there is a texture manager
		texture = 0;
	}
}