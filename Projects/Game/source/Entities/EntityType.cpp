#include "Entities\StaticEntity.h"
#include "Entities\EntityType.h"
#include "DllAPIs\Renderer.h"
#include "DllAPIs\FileIO.h"



#define LoadStaticEntityValue(_Type, _FakeType, _Name)	m_##_Name = (_Type) FileIO::BpGet##_FakeType(#_Name);

Entities::EntityType::EntityType(const char* _StaticEntityFolder)
{
	char bpPath[1024];
	sprintf_s(bpPath, "%s\\Blueprint.bp", _StaticEntityFolder);

	FileIO::LoadBp(bpPath);

	unitTypeID = FileIO::BpGetInt("ID");

	std::string imagePath = FileIO::BpGetString("Image");
	image = Renderer::LoadImageFromFile(imagePath.c_str(), FileIO::BpGetInt("ImageNumFrames"));
	size = FileIO::BpGetInt2("Size");
	printf("%i, %i.\n", size.x, size.y);


	char scriptPath[1024];
	sprintf_s(scriptPath, "..\\%s\\%04i.dll", _StaticEntityFolder, unitTypeID);
	HINSTANCE hInst;
	if(!(hInst = LoadLibrary(scriptPath)))
	{
		printf("Could not load unit script at %s.\n", scriptPath);
		return;
	}

	this->OnCreate = (pEnt_OnCreate)GetProcAddress(hInst, "OnCreate");
}

Entities::StaticEntity* Entities::EntityType::Create( float2 _Pos )
{
	Entities::StaticEntity* staticEntity = new Entities::StaticEntity();
	staticEntity->m_Rotation = 0;
	staticEntity->m_EntityType = this;

	return staticEntity;
}

////////////////////////////////////////////////////////////////
//      ///      ///  /  //////  ///    ///          /        //
//  ////  /  ////  /  /  //////  /  ////  /////  /////  ////////
//      ///      ///  ///  //  ///        /////  /////      ////
//  ///////  ///  //  ///  //  ///  ////  /////  /////  ////////
//  ///////  ////  /  /////  /////  ////  /////  /////        //
////////////////////////////////////////////////////////////////

Entities::EntityType::EntityType()
{

}