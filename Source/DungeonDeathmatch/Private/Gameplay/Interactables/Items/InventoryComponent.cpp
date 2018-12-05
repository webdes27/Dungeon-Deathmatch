// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Item.h"
#include "DungeonCharacter.h"
#include "UnrealNetwork.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	bReplicates = true;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryComponent, Inventory);
}

TArray<AItem*> UInventoryComponent::GetInventory()
{
	return Inventory;
}

void UInventoryComponent::Server_AddItem_Implementation(AItem* Item)
{
	if (Item)
	{
		Multicast_OnItemAdd(Item);

		// Add instance to the Array
		int32 AddedIndex = Inventory.Add(Item);
	}
}

bool UInventoryComponent::Server_AddItem_Validate(AItem* Item)
{
	return true;
}

void UInventoryComponent::Server_RemoveItem_Implementation(AItem* Item)
{
	for (int32 i = 0; i < Inventory.Num(); i++)
	{
		if (Inventory[i] == Item)
		{
			Multicast_OnItemRemove(Item);
			Inventory.RemoveAtSwap(i);
		}
	}
}

bool UInventoryComponent::Server_RemoveItem_Validate(AItem* Item)
{
	return true;
}

void UInventoryComponent::Multicast_OnItemAdd_Implementation(AItem* Item)
{
	ADungeonCharacter* Character = Cast<ADungeonCharacter>(GetOwner());
	if (Character && Character->IsLocallyControlled())
	{
		OnItemAdded.Broadcast(Item);
	}
	// Hide item in world
	Item->SetActorEnableCollision(false);
	Item->GetMeshComponent()->SetSimulatePhysics(false);
	Item->GetMeshComponent()->SetVisibility(false);
	Item->SetActorLocation(FVector(0, 0, 0));
}

void UInventoryComponent::Multicast_OnItemRemove_Implementation(AItem* Item)
{
	ADungeonCharacter* Character = Cast<ADungeonCharacter>(GetOwner());
	if (Character && Character->IsLocallyControlled())
	{
		OnItemRemoved.Broadcast(Item);
	}
	Item->SetActorEnableCollision(true);
	Item->GetMeshComponent()->SetSimulatePhysics(true);
	Item->GetMeshComponent()->SetVisibility(true);
	Item->SetActorLocation(GetOwner()->GetActorLocation());
}