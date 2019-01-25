// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.
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
	const UE4CodeGen_Private::FArrayPropertyParams Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices = { UE4CodeGen_Private::EPropertyClass::Array, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0010800000000000, 1, nullptr, STRUCT_OFFSET(AEdgeMesh, vertices), METADATA_PARAMS(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_MetaData, ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_MetaData)) };
	const UE4CodeGen_Private::FStructPropertyParams Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_Inner = { UE4CodeGen_Private::EPropertyClass::Struct, "vertices", RF_Public|RF_Transient|RF_MarkAsNative, (EPropertyFlags)0x0000000000000000, 1, nullptr, 0, Z_Construct_UScriptStruct_FVector, METADATA_PARAMS(nullptr, 0) };
	const UE4CodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AEdgeMesh_Statics::PropPointers[] = {
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices,
		(const UE4CodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AEdgeMesh_Statics::NewProp_vertices_Inner,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_AEdgeMesh_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AEdgeMesh>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_AEdgeMesh_Statics::ClassParams = {
		&AEdgeMesh::StaticClass,
		DependentSingletons, ARRAY_COUNT(DependentSingletons),
		0x009000A0u,
		nullptr, 0,
		Z_Construct_UClass_AEdgeMesh_Statics::PropPointers, ARRAY_COUNT(Z_Construct_UClass_AEdgeMesh_Statics::PropPointers),
		nullptr,
		&StaticCppClassTypeInfo,
		nullptr, 0,
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
	IMPLEMENT_CLASS(AEdgeMesh, 3172074384);
	static FCompiledInDefer Z_CompiledInDefer_UClass_AEdgeMesh(Z_Construct_UClass_AEdgeMesh, &AEdgeMesh::StaticClass, TEXT("/Script/ParseXML"), TEXT("AEdgeMesh"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(AEdgeMesh);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
