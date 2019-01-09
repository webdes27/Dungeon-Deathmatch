// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equippable.h"
#include "EquipmentEnums.h"
#include "Weapon.generated.h"

class UCapsuleComponent;

/**
 * The base class for all weapons in the game. Stores damaging effects and generates hit events for melee weapons when they are set in an attacking state.
 */
UCLASS()
class DUNGEONDEATHMATCH_API AWeapon : public AEquippable
{
	GENERATED_BODY()
	
public:
	/* The volume that generates overlap events, allowing a weapon to damage a target. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UCapsuleComponent* DamagingVolume;

protected:

	/** What hand(s) the weapon requires to use. Determines where the weapon is stored on the character and loadout validity. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	EWeaponHand WeaponHand;

	/** The weapon's type. Determines base animations and loadout validity. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	EWeaponType WeaponType;

	EWeaponState WeaponState;

	/** The socket on the equipping character's mesh to attach the weapon to when sheathed */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attachment")
	FName SheathedAttachSocketName;

	/** The socket on the equipping character's mesh to attach the weapon to unsheathed */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Attachment")
	FName UnsheathedSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 BaseDamageMin;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	int32 BaseDamageMax;

public:
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);

	virtual ~AWeapon() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	/**
	 * Gets the hand(s) required to use this weapon
	 *
	 * @return The required hand(s) enum
	 */
	EWeaponHand GetWeaponHand();

	/**
	 * Gets the type of the weapon
	 *
	 * @return The weapon type enum
	 */
	EWeaponType GetWeaponType();

	EWeaponState GetWeaponState();

	/**
	 * Calls character equipment logic. Can be overridden in BP.
	 */
	virtual void OnEquip_Implementation(ADungeonCharacter* NewEquippingCharacter) override;

	/**
	 * Calls character unequip logic. Can be overridden in BP.
	 */
	virtual void OnUnequip_Implementation() override;
};
