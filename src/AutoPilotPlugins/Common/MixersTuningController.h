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
///     @author

#ifndef MixersTuningController_H
#define MixersTuningController_H

#include <QTimer>

#include "FactPanelController.h"
#include "UASInterface.h"
#include "QGCLoggingCategory.h"
#include "AutoPilotPlugin.h"
#include <FactMetaData.h>

Q_DECLARE_LOGGING_CATEGORY(MixersTuningControllerLog)
Q_DECLARE_LOGGING_CATEGORY(MixersTuningControllerVerboseLog)

namespace Ui {
    class MixersTuningController;
}

class MixersTuningController : public FactPanelController
{
    Q_OBJECT

public:
    MixersTuningController(void);
    ~MixersTuningController();

    Q_PROPERTY(QQuickItem* getMixersCountButton MEMBER _getMixersCountButton    NOTIFY getMixersCountButtonChanged)
    Q_PROPERTY(QQuickItem* requestAllButton MEMBER _requestAllButton    NOTIFY requestAllButtonChanged)
    Q_PROPERTY(QQuickItem* requestMissingButton MEMBER _requestMissingButton    NOTIFY requestMissingButtonChanged)
    Q_PROPERTY(QQuickItem* requestSubmixerCountButton MEMBER _requestSubmixerCountButton   NOTIFY requestSubmixerCountButtonChanged)
    Q_PROPERTY(QQuickItem* refreshGUIButton MEMBER _refreshGUIButton   NOTIFY refreshGUIButtonChanged)

    Q_PROPERTY(QmlObjectListModel*  mixersList          MEMBER _mixers          CONSTANT)

    Q_INVOKABLE void getMixersCountButtonClicked(void);
    Q_INVOKABLE void requestAllButtonClicked(void);
    Q_INVOKABLE void requestMissingButtonClicked(void);
    Q_INVOKABLE void requestSubmixerCountButtonClicked(void);
    Q_INVOKABLE void refreshGUIButtonClicked(void);

    unsigned int groupValue(void);
    unsigned int mixerIndexValue(void);
    unsigned int submixerIndexValue(void);
    float parameterValue(void);
        
    
signals:
    void getMixersCountButtonChanged(void);
    void requestAllButtonChanged(void);
    void requestMissingButtonChanged(void);
    void requestSubmixerCountButtonChanged(void);
    void refreshGUIButtonChanged(void);

//    void statusTextChanged(void);
//    void nextButtonChanged(void);
//    void skipButtonChanged(void);
        
    void groupValueChanged(unsigned int groupValue);
    void parameterValueChanged(float paramValue);
        
//    /// Signalled to QML to indicate reboot is required
//    void functionMappingChangedAPMReboot(void);

private slots:
//    void _rcChannelsChanged(int channelCount, int pwmValues[Vehicle::cMaxRcChannels]);
    void _updateMixers(void);

private:

    
    static const int _updateInterval;   ///< Interval for ui update timer

    QQuickItem* _getMixersCountButton;
    QQuickItem* _requestAllButton;
    QQuickItem* _requestMissingButton;
    QQuickItem* _requestSubmixerCountButton;
    QQuickItem* _refreshGUIButton;
    QmlObjectListModel* _mixers;

    FactMetaData _mockMetaData;
    QList<Fact*> _mockFactList;

//    QQuickItem* _statusText;
//    QQuickItem* _nextButton;
//    QQuickItem* _skipButton;
    
//    QString _imageHelp;
    
//#ifdef UNITTEST_BUILD
//    // Nasty hack to expose controller to unit test code
//    static RadioComponentController*    _unitTestController;
//#endif
};

#endif // MixersTuningController_H
