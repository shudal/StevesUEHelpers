#pragma once

#include "CoreMinimal.h"

#include "UiTheme.h"
#include "Components/Image.h"
#include "StevesHelperCommon.h"
#include "InputImage.generated.h"

UENUM(BlueprintType)
enum class EInputBindingType : uint8
{
    /// A button action, will be looked up based on input mappings
    Action = 0,
    /// An axis action, will be looked up based on input mappings
    Axis = 1,
    /// A manually specified FKey (which can be key, button, axis)
    Key = 2
};


/// A special widget containing an image which populates itself based on an input action / axis and can dynamically
/// change based on the active input method.
UCLASS()
class STEVESUEHELPERS_API UInputImage : public UImage
{
    GENERATED_BODY()

protected:
    /// What type of an input binding this image should look up
    UPROPERTY(EditAnywhere)
    EInputBindingType BindingType;

    /// If BindingType is Action/Axis, the name of it 
    UPROPERTY(EditAnywhere)
    FName ActionOrAxisName;
    
    /// If BindingType is Key, the key 
    UPROPERTY(EditAnywhere)
    FKey Key;

    /// Custom theme to use for this input image set; if not supplied will use UStevesGameSubsystem::DefaultUiTheme
    UPROPERTY(EditAnywhere)   
    UUiTheme* CustomTheme;
    
    EInputMode CurrentInputMode;

public:

    /// Tell this image to display the bound action for the current input method
    UFUNCTION(BlueprintCallable)
    virtual void SetFromAction(FName Name);

    /// Tell this image to display the bound axis for the current input method
    UFUNCTION(BlueprintCallable)
    virtual void SetFromAxis(FName Name);

    /// Tell this image to display a specific key image
    UFUNCTION(BlueprintCallable)
    virtual void SetFromKey(FKey K);

    /// Get the binding type that we'll use to populate the image
    UFUNCTION(BlueprintCallable)
    virtual EInputBindingType GetBindingType() const { return BindingType; }

    /// If BindingType is Action/Axis, get the name of the action or axis to look up the image for
    UFUNCTION(BlueprintCallable)
    virtual FName GetActionOrAxisName() const { return ActionOrAxisName; };

    /// If BindingType is Key, get the key 
    UFUNCTION(BlueprintCallable)
    virtual FKey GetKey() const { return Key; }

    /// Get the custom theme, if any
    virtual UUiTheme* GetCustomTheme() const { return CustomTheme; }
    /// Change the custom theme for this image
    virtual void SetCustomTheme(UUiTheme* Theme);
    
    virtual void BeginDestroy() override;
protected:

    virtual TSharedRef<SWidget> RebuildWidget() override;
    void UpdateImageFromAction(const FName& Name);
    void UpdateImageFromAxis(const FName& Name);
    void UpdateImageFromTable(const FKey& Key, const TSoftObjectPtr<UDataTable>& Asset);
    void UpdateImageFromKey(const FKey& Key);
    virtual void UpdateImage();
    virtual UUiTheme* GetTheme();
        
    UFUNCTION()
    void OnInputModeChanged(int PlayerIndex, EInputMode InputMode);
    
};
