#include "ResourcesLoaderOpenGL.h"
#include <glm\vec3.hpp>
#include <glm\vec4.hpp>
#include <SOIL\SOIL.h>
#include "ImageResourceOpenGL.h"
#include "MeshResourceOpenGL.h"
#define GLEW_STATIC //use static binding. All the code used from the library is put into the executable and no needed to attach a dll
#include <GL/glew.h>//for abstracting cumbersome OpenGL procedures
#include <iostream>
#include <fstream>

//for loading resources using OpenGL specific techniques
ResourcesLoaderOpenGL::ResourcesLoaderOpenGL()
{
}

ResourcesLoaderOpenGL::~ResourcesLoaderOpenGL()
{
}

IResource* ResourcesLoaderOpenGL::LoadImage(std::string p_file)
{
	int t_width, t_height;
	unsigned char* t_imageData = SOIL_load_image(p_file.c_str(), &t_width, &t_height, 0, SOIL_LOAD_RGB);
	if (t_imageData == 0)
		return nullptr;

	glActiveTexture(GL_TEXTURE0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	GLuint t_texture;
	glGenTextures(1, &t_texture);
	glBindTexture(GL_TEXTURE_2D, t_texture);
	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, t_width, t_height, 0, GL_RGB, GL_UNSIGNED_BYTE, t_imageData);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(t_imageData);
	ImageResourceOpenGL* r_newResource = new ImageResourceOpenGL(t_width, t_height, t_texture);
	glBindTexture(GL_TEXTURE_2D, 0);
	return r_newResource;
}

void  SplitString(std::string t_line, std::string t_delimiter, std::string* t_parts, int t_elements)
{
	std::string t_token;
	size_t t_position;
	//take the three values
	for (size_t t_element = 0; t_element < t_elements; t_element++)
	{
		t_position = t_line.find(t_delimiter);
		t_token = t_line.substr(0, t_position);//get the first value
		t_line.erase(0, t_position + t_delimiter.size());//delete the first value from the read line
		t_parts[t_element] = t_token;
	}
}

IResource* ResourcesLoaderOpenGL::LoadMesh(std::string p_file)
{
	std::vector<Rol::Vertex> t_vertices;
	std::vector<unsigned int> t_facesIndex;
	MeshResourceOpenGL* t_newMeshResource = new MeshResourceOpenGL();

	if (p_file == "fakeMesh.obj")
	{
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(0.5f, 0.5f, 0.0f),
				glm::vec4(1.f, 0.f, 0.f, 1.f),
				glm::vec2(1.f, 1.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(0.5f, -0.5f, 0.0f),
				glm::vec4(0.f, 1.f, 0.f, 1.f),
				glm::vec2(1.f, 0.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(-0.5f, -0.5f, 0.0f),
				glm::vec4(0.f, 0.f, 1.f, 1.f),
				glm::vec2(0.f, 0.f)));
		t_vertices.push_back(
			Rol::Vertex(
				glm::vec3(-0.5f, 0.5f, 0.0f),
				glm::vec4(1.f, 1.f, 0.f, 1.f),
				glm::vec2(0.f, 1.f)));
		t_facesIndex.push_back(0);
		t_facesIndex.push_back(1);
		t_facesIndex.push_back(3);
		t_facesIndex.push_back(1);
		t_facesIndex.push_back(2);
		t_facesIndex.push_back(3);

		t_newMeshResource->CreateMesh(t_vertices, t_facesIndex);
		return t_newMeshResource;
	}
	
	//read the .mtl file 
	glm::vec4 t_color = glm::vec4(1,1,1,1);
	std::string t_mtlFile = p_file;
	t_mtlFile[t_mtlFile.size() - 3] = 'm'; 
	t_mtlFile[t_mtlFile.size() - 2] = 't'; 
	t_mtlFile[t_mtlFile.size() - 1] = 'l';
	std::ifstream t_fileReader(t_mtlFile, std::ifstream::in);
	std::string t_line;
	if (t_fileReader)
	{
		while (std::getline(t_fileReader, t_line))
		{
			//diffuse color
			if (t_line[0] == 'K' && t_line[1] == 'd')
			{
				//delete first three characters "Kd "
				t_line.erase(0, 3);
				//get the color values
				std::string t_values[3];
				SplitString(t_line, " ", t_values, 3);
				t_color = glm::vec4(std::stof(t_values[0]), std::stof(t_values[1]), std::stof(t_values[2]), 1);
			}
			if (t_line[0] == 'd')
			{
				//get the alpha value
				//delete first two characters "d "
				t_line.erase(0, 2);
				t_color.a = std::stof(t_line);
			}
		}
	}
	else
		std::cout << "No .mtl file found. Is it in the same directory as the .obj file?" << std::endl;
	t_fileReader.close();

	//read the .obj file 
	t_fileReader.open(p_file, std::ifstream::in);
	if (!t_fileReader)
		return nullptr;

	std::vector<glm::vec3> t_verticesPositions;
	std::vector<glm::vec2> t_verticesTextureCoords;
	while (std::getline(t_fileReader, t_line))
	{
		//vertex
		if		(t_line[0] == 'v' && t_line[1] == ' ')
		{
			//delete first two characters "v "
			t_line.erase(0, 2);
			//split the line into the three vertex positions and store it
			std::string t_parts[3];
			SplitString(t_line, " ", t_parts, 3);
			t_verticesPositions.push_back(glm::vec3(std::stof(t_parts[0]), std::stof(t_parts[1]), std::stof(t_parts[2])));
		}
		//vertex texture coordinate
		else if (t_line[0] == 'v' && t_line[1] == 't')
		{
			//delete first three characters "vt "
			t_line.erase(0, 3);
			//split the line into the two vertex texture coordinates and store it
			std::string t_parts[2];
			SplitString(t_line, " ", t_parts, 2);
			t_verticesTextureCoords.push_back(glm::vec2(std::stof(t_parts[0]), std::stof(t_parts[1])));
		}
		//vertex normal
		else if (t_line[0] == 'v' && t_line[1] == 'n')
		{
			//pa que?
		}
		//face
		else if (t_line[0] == 'f')
		{
			/*check the type of face this object has
			f v1 v2 v3							--> only vertex positions
			f v1/vt1 v2/vt2 v3/vt3				--> vertex positions and texture coordinates
			f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3	--> vertex positions, texture coordinates and vertex normals
			f v1//vn1 v2//vn2 v3//vn3			--> vertex positions and vertex normals*/
			//count the number of slashes in the line
			int t_count = 0;
			for (size_t t_char = 0; t_char < t_line.size(); ++t_char)
			{
				if (t_line[t_char] == '/')
					++t_count;
			}
			//now is possible to know the type of face 

			//f v1 v2 v3			 --> only vertex positions
			if (t_count == 0)
			{
				std::string t_parts[3];
				//read the rest of the file from here so checking the type of face is not needed again
				do 
				{
					//delete first two characters "f "
					t_line.erase(0, 2);
					//split the line into the two vertex texture coordinates and store it
					SplitString(t_line, " ", t_parts, 3);
					t_facesIndex.push_back(std::atoi(t_parts[0].c_str()) - 1);
					t_facesIndex.push_back(std::atoi(t_parts[1].c_str()) - 1);
					t_facesIndex.push_back(std::atoi(t_parts[2].c_str()) - 1);
				} while (std::getline(t_fileReader, t_line));
				for (glm::vec3 t_position : t_verticesPositions)
					t_vertices.push_back(Rol::Vertex(t_position, t_color));
				break;
			}
			//f v1/vt1 v2/vt2 v3/vt3 --> vertex positions and texture coordinates 
			else if (t_count == 3)
			{
				std::string t_parts[3];
				std::string t_partsAux[2];
				//read the rest of the file from here so checking the type of face is not needed again
				do
				{
					//delete first two characters "f "
					t_line.erase(0, 2);
					//get the face three vertex info
					SplitString(t_line, " ", t_parts, 3);
					for (std::string t_part : t_parts)
					{
						//parse each vertex info
						SplitString(t_part, "/", t_partsAux, 2);
						for (std::string t_part : t_partsAux)
						{
							Rol::Vertex t_newVertex(
								t_verticesPositions[std::atoi(t_parts[0].c_str())],
								t_color,
								t_verticesTextureCoords[std::atoi(t_parts[1].c_str())]
							);
							//search for the vertex in the vertex list
							int t_index = 0;
							for (Rol::Vertex t_vertex : t_vertices)
							{
								//the vertex is already in the list
								if (t_vertex == t_newVertex)
								{
									t_facesIndex.push_back(t_index);
									break;
								}
								++t_index;
							}
							if (t_index == t_vertices.size())
							{
								//the vertex was not in the list
								t_vertices.push_back(t_newVertex);
								t_facesIndex.push_back(t_index);
							}
						}
					}
				} while (std::getline(t_fileReader, t_line));
				break;
			}
			//could be (vertex positions, texture coordinates and vertex normals) or (vertex positions and vertex normals)
			else if (t_count == 6)
			{
				if (t_line[t_line.find('/') + 1] == '/')
				{
					//the face is --> f v1//vn1 v2//vn2 v3//vn3 vertex positions and vertex normals
					//read the rest of the file from here so checking the type of face is not needed again

					//TODO que hago con las normales?
					std::string t_parts[3];
					std::string t_partsAux[2];
					//read the rest of the file from here so checking the type of face is not needed again
					do
					{
						//delete first two characters "f "
						t_line.erase(0, 2);
						//split the line into the three vertex
						SplitString(t_line, " ", t_parts, 3);
						for (std::string t_vertex : t_parts)
						{
							//split each vertex into vertex position and vertex normal
							SplitString(t_vertex, "//", t_partsAux, 2);
							t_facesIndex.push_back(std::atoi(t_partsAux[0].c_str()) - 1);
						}
					} while (std::getline(t_fileReader, t_line));
					for (glm::vec3 t_position : t_verticesPositions)
						t_vertices.push_back(Rol::Vertex(t_position, t_color));
					break;
				}
				else
				{
					//the face is --> f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 vertex positions, texture coordinates and vertex normals
					//read the rest of the file from here so checking the type of face is not needed again
					std::string t_parts[3];
					std::string t_partsAux[3];
					//read the rest of the file from here so checking the type of face is not needed again
					do
					{
						//delete first two characters "f "
						t_line.erase(0, 2);
						//get the face three vertex info
						SplitString(t_line, " ", t_parts, 3);
						//parse each vertex info
						for (std::string t_part : t_parts)
						{
							SplitString(t_part, "/", t_partsAux, 3);//TODO el tercer elemento son las normales. que hago?
							Rol::Vertex t_newVertex(
								t_verticesPositions[std::atoi(t_partsAux[0].c_str()) - 1],
								t_color,
								t_verticesTextureCoords[std::atoi(t_partsAux[1].c_str()) - 1]
							);
							//search for the vertex in the vertex list
							int t_index = 0;
							for (Rol::Vertex t_vertex : t_vertices)
							{
								//the vertex is already in the list
								if (t_vertex == t_newVertex)
								{
									t_facesIndex.push_back(t_index);
									break;
								}
								++t_index;
							}
							if (t_index == t_vertices.size())
							{
								//the vertex was not in the list
								t_vertices.push_back(t_newVertex);
								t_facesIndex.push_back(t_index);
							}
						}
					} while (std::getline(t_fileReader, t_line));
					break;
				}
			}
			else
				std::cout << "Unsupported mesh format. Please assure that mesh has been triangulated" << std::endl;
		}
	}
	t_fileReader.close();
	t_newMeshResource->CreateMesh(t_vertices, t_facesIndex);
	return t_newMeshResource;
}
