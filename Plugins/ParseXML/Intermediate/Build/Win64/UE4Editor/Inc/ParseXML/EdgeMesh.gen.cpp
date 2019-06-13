// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ParseXML/Public/EdgeMesh.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeEdgeMesh() {}
// Cross Module References
	PARSEXML_API UClass* Z_Construct_UClass_AEdgeMesh_NoRegister();
	PARSEXML_API UClass* Z_Construct_UClass_AEdgeMesh();
	ENGINE_API UClass* Z_Construct_UClass_AActor();
	UPackage* Z_Construct_UPackage__Script_ParseXML();
	COREUOBJECT_API UScriptStruct* Z_Construct_UScriptStruct_FVector();
// End Cross Module References
	void AEdgeMesh::StaticRegisterNativesAEdgeMesh()
	{
	}
	UClass* Z_Construct_UClass_AEdgeMesh_NoRegister()
	{
		return AEdgeMesh::StaticClass();
	}
	struct Z_Construct_UClass_AEdgeMesh_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam NewProp_vertices_MetaData[];
#endif
		static const UE4CodeGen_Private::FArrayPropertyParams NewProp_vertices;
		static const UE4CodeGen_Private::FStructPropertyParams NewProp_vertices_Inner;
		static const UE4CodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_AEdgeMesh_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AActor,
		(UObject* (*)())Z_Construct_UPackage__Script_ParseXML,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEdgeMesh_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "EdgeMesh.h" },
		{ "ModuleRelativePath", "Public/EdgeMesh.h" },
	};
#endif
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_MetaData[] = {
		{ "ModuleRelativePath", "Public/EdgeMesh.h" },
		{ "ToolTip", "To make sure that the vertices also get copied for every PIE instance (No loss of actor data)" },
	};
#endif
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices = { "vertices", nullptr, (EPropertyFlags)0x0010800000000000, UE4CodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEdgeMesh, vertices), METADATA_PARAMS(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_MetaData, ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_Inner = { "vertices", nullptr, (EPropertyFlags)0x0000000000000000, UE4CodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, 1, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
<<<<<<< Updated upstream
=======
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_AEdgeMesh_Statics::NewProp_Material_MetaData[] = {
		{ "Category", "ProcMesh" },
		{ "ModuleRelativePath", "Public/EdgeMesh.h" },
	};
#endif
	const UE4CodeGen_Private::FObjectPropertyParams Z_Construct_UClass_AEdgeMesh_Statics::NewProp_Material = { "Material", nullptr, (EPropertyFlags)0x0010000000020001, UE4CodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, STRUCT_OFFSET(AEdgeMesh, Material), Z_Construct_UClass_UMaterial_NoRegister, METADATA_PARAMS(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_Material_MetaData, ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_Material_MetaData)) };
>>>>>>> Stashed changes
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEdgeMesh_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEdgeMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEdgeMesh>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEdgeMesh_Statics::ClassParams = {
		&AEdgeMesh::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_AEdgeMesh_Statics::PropPointers,
		nullptr,
		ARRAY_COUNT(DependentSingletons),
		0,
		ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::PropPointers),
		0,
		0x009000A0u,
		METADATA_PARAMS(Z_Construct_UClass_AEdgeMesh_Statics::Class_MetaDataParams, ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_AEdgeMesh()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_AEdgeMesh_Statics::ClassParams);
		}
		return OuterClass;
	}
<<<<<<< Updated upstream
	IMPLEMENT_CLASS(AEdgeMesh, 1691831995);
=======
	IMPLEMENT_CLASS(AEdgeMesh, 1194285728);
>>>>>>> Stashed changes
	template<> PARSEXML_API UClass* StaticClass<AEdgeMesh>()
	{
		return AEdgeMesh::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEdgeMesh(Z_Construct_UClass_AEdgeMesh, &AEdgeMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AEdgeMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEdgeMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
