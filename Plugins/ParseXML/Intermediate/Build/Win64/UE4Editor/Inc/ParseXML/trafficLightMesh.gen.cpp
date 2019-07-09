// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ParseXML/Public/trafficLightMesh.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodetrafficLightMesh() {}
// Cross Module References
	PARSEXML_API UClass* Z_Construct_UClass_AtrafficLightMesh_NoRegister();
	PARSEXML_API UClass* Z_Construct_UClass_AtrafficLightMesh();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ParseXML();
// End Cross Module References
	void AtrafficLightMesh::StaticRegisterNativesAtrafficLightMesh()
	{
	}
	UClass* Z_Construct_UClass_AtrafficLightMesh_NoRegister()
	{
		return AtrafficLightMesh::StaticClass();
	}
	struct Z_Construct_UClass_AtrafficLightMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AtrafficLightMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ParseXML,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "trafficLightMesh.h" },
		{ "ModuleRelativePath", "Public/trafficLightMesh.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_AtrafficLightMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AtrafficLightMesh>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AtrafficLightMesh_Statics::ClassParams = {
		&AtrafficLightMesh::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AtrafficLightMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AtrafficLightMesh()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AtrafficLightMesh_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(AtrafficLightMesh, 779534016);
	template<> PARSEXML_API UClass* StaticClass<AtrafficLightMesh>()
	{
		return AtrafficLightMesh::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AtrafficLightMesh(Z_Construct_UClass_AtrafficLightMesh, &AtrafficLightMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AtrafficLightMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AtrafficLightMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
