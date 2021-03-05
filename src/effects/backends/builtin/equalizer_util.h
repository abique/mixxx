#pragma once

#include <QObject>

#include "effects/backends/effectmanifest.h"

class EqualizerUtil {
  public:
    // Creates common EQ parameters like low/mid/high gain and kill buttons.
    static void createCommonParameters(EffectManifest* pManifest, bool linear) {
        EffectManifestParameter::ValueScaler valueScaler =
                EffectManifestParameter::ValueScaler::LOGARITHMIC;
        double maximum = 4.0;
        if (linear) {
            valueScaler = EffectManifestParameter::ValueScaler::LINEAR;
            maximum = 2.0;
        }

        EffectManifestParameterPointer low = pManifest->addParameter();
        low->setId("low");
        low->setName(QObject::tr("Low"));
        low->setDescription(QObject::tr("Gain for Low Filter"));
        low->setValueScaler(valueScaler);
        low->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        low->setNeutralPointOnScale(0.5);
        low->setRange(0, 1.0, maximum);

        EffectManifestParameterPointer killLow = pManifest->addParameter();
        killLow->setId("killLow");
        killLow->setName(QObject::tr("Kill Low"));
        killLow->setDescription(QObject::tr("Kill the Low Filter"));
        killLow->setValueScaler(EffectManifestParameter::ValueScaler::TOGGLE);
        killLow->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        killLow->setRange(0, 0, 1);

        EffectManifestParameterPointer mid = pManifest->addParameter();
        mid->setId("mid");
        mid->setName(QObject::tr("Mid"));
        mid->setDescription(QObject::tr("Gain for Mid Filter"));
        mid->setValueScaler(valueScaler);
        mid->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        mid->setNeutralPointOnScale(0.5);
        mid->setRange(0, 1.0, maximum);

        EffectManifestParameterPointer killMid = pManifest->addParameter();
        killMid->setId("killMid");
        killMid->setName(QObject::tr("Kill Mid"));
        killMid->setDescription(QObject::tr("Kill the Mid Filter"));
        killMid->setValueScaler(EffectManifestParameter::ValueScaler::TOGGLE);
        killMid->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        killMid->setRange(0, 0, 1);

        EffectManifestParameterPointer high = pManifest->addParameter();
        high->setId("high");
        high->setName(QObject::tr("High"));
        high->setDescription(QObject::tr("Gain for High Filter"));
        high->setValueScaler(valueScaler);
        high->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        high->setNeutralPointOnScale(0.5);
        high->setRange(0, 1.0, maximum);

        EffectManifestParameterPointer killHigh = pManifest->addParameter();
        killHigh->setId("killHigh");
        killHigh->setName(QObject::tr("Kill High"));
        killHigh->setDescription(QObject::tr("Kill the High Filter"));
        killHigh->setValueScaler(EffectManifestParameter::ValueScaler::TOGGLE);
        killHigh->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
        killHigh->setRange(0, 0, 1);
    }

    static QString adjustFrequencyShelvesTip() {
        return QObject::tr(
                "To adjust frequency shelves, go to Preferences -> Equalizers.");
    }
};
