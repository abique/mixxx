#include "effects/backends/builtin/whitenoiseeffect.h"

#include "util/rampingvalue.h"

namespace {
const QString dryWetParameterId = QStringLiteral("dry_wet");
} // anonymous namespace

// static
QString WhiteNoiseEffect::getId() {
    return QStringLiteral("org.mixxx.effects.whitenoise");
}

// static
EffectManifestPointer WhiteNoiseEffect::getManifest() {
    EffectManifestPointer pManifest(new EffectManifest());
    pManifest->setId(getId());
    pManifest->setName(QObject::tr("White Noise"));
    pManifest->setAuthor("The Mixxx Team");
    pManifest->setVersion("1.0");
    pManifest->setDescription(QObject::tr("Mix white noise with the input signal"));
    pManifest->setEffectRampsFromDry(true);

    // This is dry/wet parameter
    EffectManifestParameterPointer drywet = pManifest->addParameter();
    drywet->setId(dryWetParameterId);
    drywet->setName(QObject::tr("Dry/Wet"));
    drywet->setDescription(QObject::tr("Crossfade the noise with the dry signal"));
    drywet->setValueScaler(EffectManifestParameter::ValueScaler::LOGARITHMIC);
    drywet->setUnitsHint(EffectManifestParameter::UnitsHint::UNKNOWN);
    drywet->setDefaultLinkType(EffectManifestParameter::LinkType::LINKED);
    drywet->setRange(0, 1, 1);

    return pManifest;
}

void WhiteNoiseEffect::loadEngineEffectParameters(
        const QMap<QString, EngineEffectParameterPointer>& parameters) {
    m_pDryWetParameter = parameters.value(dryWetParameterId);
}

void WhiteNoiseEffect::processChannel(
        WhiteNoiseGroupState* pState,
        const CSAMPLE* pInput,
        CSAMPLE* pOutput,
        const mixxx::EngineParameters& bufferParameters,
        const EffectEnableState enableState,
        const GroupFeatureState& groupFeatures) {
    Q_UNUSED(groupFeatures);

    WhiteNoiseGroupState& gs = *pState;

    CSAMPLE drywet = static_cast<CSAMPLE>(m_pDryWetParameter->value());
    RampingValue<CSAMPLE_GAIN> drywet_ramping_value(
            drywet, gs.previous_drywet, bufferParameters.framesPerBuffer());

    std::uniform_real_distribution<> r_distributor(0.0, 1.0);

    for (unsigned int i = 0; i < bufferParameters.samplesPerBuffer(); i++) {
        CSAMPLE_GAIN drywet_ramped = drywet_ramping_value.getNext();

        float noise = static_cast<float>(
                r_distributor(gs.gen));

        pOutput[i] = pInput[i] * (1 - drywet_ramped) + noise * drywet_ramped;
    }

    if (enableState == EffectEnableState::Disabling) {
        gs.previous_drywet = 0;
    } else {
        gs.previous_drywet = drywet;
    }
}
