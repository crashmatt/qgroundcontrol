/****************************************************************************
 *
 *   (c) 2009-2016 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>
 *
 * QGroundControl is licensed according to the terms in the file
 * COPYING.md in the root of the source code directory.
 *
 ****************************************************************************/


/// @file
///     @brief Mixers Config Qml Controller
///     @author Matthew Coleman <uavflightdirector@gmail.com>

#include "MixersTuningController.h"
#include "MixersManager.h"
#include "QGCApplication.h"

#include <QSettings>

QGC_LOGGING_CATEGORY(MixersTuningControllerLog, "MixersTuningControllerLog")
QGC_LOGGING_CATEGORY(MixersTuningControllerVerboseLog, "MixersTuningControllerVerboseLog")

//#ifdef UNITTEST_BUILD
//// Nasty hack to expose controller to unit test code
//MixersComponentController* MixersComponentController::_unitTestController = NULL;
//#endif

const int MixersTuningController::_updateInterval = 150;              ///< Interval for timer which updates stuff

MixersTuningController::MixersTuningController(void)
    : _mixers(new QmlObjectListModel(this))
    , _mockMetaData(FactMetaData::valueTypeString, this)
    , _mockFactList()
{
//    _getMixersCountButton = NULL;
//#ifdef UNITTEST_BUILD
//    // Nasty hack to expose controller to unit test code
//    _unitTestController = this;
//#endif

    _mockMetaData.setName("MOCK_METADATA");
    _mockMetaData.setGroup("MIXER_COMP_CONTROLLER");
    _mockMetaData.setRawDefaultValue("MOCK_STRING");

    Fact *fact;

    fact = new Fact(-1, "Mock Fact 1", FactMetaData::valueTypeString, this);
    fact->setMetaData(&_mockMetaData);
    fact->setRawValue("1");
    _mockFactList.append(fact);

    fact = new Fact(-1, "Mock Fact 2", FactMetaData::valueTypeString, this);
    fact->setMetaData(&_mockMetaData);
    fact->setRawValue("2");
    _mockFactList.append(fact);

    fact = new Fact(-1, "Mock Fact 3", FactMetaData::valueTypeString, this);
    fact->setMetaData(&_mockMetaData);
    fact->setRawValue("3");
    _mockFactList.append(fact);

    connect(_vehicle->mixersManager(), &MixersManager::mixerDataReadyChanged, this, &MixersTuningController::_updateMixers);
}



MixersTuningController::~MixersTuningController()
{
//    _storeSettings();
}


void MixersTuningController::getMixersCountButtonClicked(void)
{
    _vehicle->mixersManager()->requestMixerCount(0);
}


void MixersTuningController::requestAllButtonClicked(void)
{
    _vehicle->mixersManager()->requestMixerAll(0);
}

void MixersTuningController::requestMissingButtonClicked(void)
{
    _vehicle->mixersManager()->requestMissingData(0);
}

void MixersTuningController::requestSubmixerCountButtonClicked(void)
{
    _vehicle->mixersManager()->requestSubmixerCount(0, 0);
}

void MixersTuningController::refreshGUIButtonClicked(void){
    QObjectList newMixerList;
    Fact* fact;

    foreach(fact, _mockFactList){
        newMixerList.append(fact);
    }

    _mixers->swapObjectList(newMixerList);
}


//void RadioComponentController::_loadSettings(void)
//{
//    QSettings settings;
    
//    settings.beginGroup(_settingsGroup);
//    _transmitterMode = settings.value(_settingsKeyTransmitterMode, 2).toInt();
//    settings.endGroup();
    
//    if (_transmitterMode != 1 || _transmitterMode != 2) {
//        _transmitterMode = 2;
//    }
//}

//void RadioComponentController::_storeSettings(void)
//{
//    QSettings settings;
    
//    settings.beginGroup(_settingsGroup);
//    settings.setValue(_settingsKeyTransmitterMode, _transmitterMode);
//    settings.endGroup();
//}


unsigned int MixersTuningController::groupValue(void)
{    
    return 0;
}

float MixersTuningController::parameterValue(void)
{
    return 0.0;
}

void MixersTuningController::_updateMixers(void){
    QObjectList newMixerList;

    Fact* fact;
    unsigned typeID;
    QMap<int, Mixer*> *subMixers;

    MixerMetaData *mixerMetaData = _vehicle->mixersManager()->getMixerMetaData();

    MixerGroup *mixerGroup = _vehicle->mixersManager()->getMixerGroup(0);
    if(mixerGroup == nullptr) return;

    QMap<int, Mixer*> *mixers = mixerGroup->getMixers();
    Mixer *mixer;
    Mixer *submixer;

    //Add each mixer type and submixer type to the list
    foreach(int mixer_index, mixers->keys()) {
        mixer = mixers->value(mixer_index);
        typeID = mixer->getMixerTypeID();
        fact = mixerMetaData->GetMixerType(typeID);
        if(fact != nullptr)
            newMixerList.append(fact);

        subMixers = mixer->getSubmixers();
        foreach(int submixer_index, subMixers->keys()) {
            submixer = subMixers->value(submixer_index);
            typeID = submixer->getMixerTypeID();
            fact = mixerMetaData->GetMixerType(typeID);
            if(fact != nullptr)
                newMixerList.append(fact);
        }
    }
    _mixers->swapObjectList(newMixerList);
}

