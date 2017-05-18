#include "workingrangemanager.h"

WorkingRangeManager::WorkingRangeManager()
{

}

WorkingRangeManager::~WorkingRangeManager() {

}

void WorkingRangeManager::setValveWorkingRate() {
    auto finded = workingRangeMap.find(Function::route);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::route, std::make_shared<EmptyWorkingRange>()));
    }
}

void WorkingRangeManager::setPumpWorkingRange(units::Volumetric_Flow rateValue) {
    auto finded = workingRangeMap.find(Function::route);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::route, std::make_shared<PumpWorkingRange>(rateValue, rateValue)));
    } else {
        std::shared_ptr<PumpWorkingRange> range = std::dynamic_pointer_cast<PumpWorkingRange>(finded->second);
        if (rateValue < range->getMinRate()) {
            range->setMinRate(rateValue);
        } else if (rateValue > range->getMaxRate()) {
            range->setMaxRate(rateValue);
        }
    }
}

void WorkingRangeManager::setHeaterWorkingRange(units::Temperature temperatreValue) {
    auto finded = workingRangeMap.find(Function::heat);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::heat, std::make_shared<HeaterWorkingRange>(temperatreValue, temperatreValue)));
    } else {
        std::shared_ptr<HeaterWorkingRange> range = std::dynamic_pointer_cast<HeaterWorkingRange>(finded->second);
        if (temperatreValue < range->getMinTemperature()) {
            range->setMinTemperature(temperatreValue);
        } else if (temperatreValue > range->getMaxTemperature()) {
            range->setMaxTemperature(temperatreValue);
        }
    }
}

void WorkingRangeManager::setLigthWorkingRange(units::LuminousIntensity intensity, units::Length wavelength) {
    auto finded = workingRangeMap.find(Function::apply_light);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::apply_light,
                                              std::make_shared<LigthWorkingRange>(wavelength, wavelength, intensity, intensity)));
    } else {
        std::shared_ptr<LigthWorkingRange> range = std::dynamic_pointer_cast<LigthWorkingRange>(finded->second);
        if (intensity < range->getMinIntensity()) {
            range->setMinIntensity(intensity);
        } else if (intensity > range->getMaxIntensity()) {
            range->setMaxIntensity(intensity);
        }

        if (wavelength < range->getMinWaveLength()) {
            range->setMinWaveLength(wavelength);
        } else if (wavelength > range->getMaxWaveLength()) {
            range->setMaxWaveLength(wavelength);
        }
    }
}

void WorkingRangeManager::setOdSensorWorkingRange(units::Length wavelength) {
    auto finded = workingRangeMap.find(Function::measure_od);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::measure_od,
                                              std::make_shared<MeasureOdWorkingRange>(wavelength, wavelength)));
    } else {
        std::shared_ptr<MeasureOdWorkingRange> range = std::dynamic_pointer_cast<MeasureOdWorkingRange>(finded->second);
        if (wavelength < range->getMinWaveLength()) {
            range->setMinWaveLength(wavelength);
        } else if (wavelength > range->getMaxWaveLength()) {
            range->setMaxWaveLength(wavelength);
        }
    }
}

void WorkingRangeManager::setStirerWorkingRange(units::Frequency intensity) {
    auto finded = workingRangeMap.find(Function::stir);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::stir, std::make_shared<StirWorkingRange>(intensity, intensity)));
    } else {
        std::shared_ptr<StirWorkingRange> range = std::dynamic_pointer_cast<StirWorkingRange>(finded->second);
        if (intensity < range->getMinIntensity()) {
            range->setMinIntensity(intensity);
        } else if (intensity > range->getMaxIntensity()) {
            range->setMaxIntensity(intensity);
        }
    }
}

void WorkingRangeManager::setShakerWorkingRange(units::Frequency intensity) {
    auto finded = workingRangeMap.find(Function::shake);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::shake, std::make_shared<ShakeWorkingRange>(intensity, intensity)));
    } else {
        std::shared_ptr<ShakeWorkingRange> range = std::dynamic_pointer_cast<ShakeWorkingRange>(finded->second);
        if (intensity < range->getMinIntensity()) {
            range->setMinIntensity(intensity);
        } else if (intensity > range->getMaxIntensity()) {
            range->setMaxIntensity(intensity);
        }
    }
}

void WorkingRangeManager::setCentrifugerWorkingRange(units::Frequency intensity) {
    auto finded = workingRangeMap.find(Function::centrifugate);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::centrifugate, std::make_shared<CentrifugationWorkingRange>(intensity, intensity)));
    } else {
        std::shared_ptr<CentrifugationWorkingRange> range = std::dynamic_pointer_cast<CentrifugationWorkingRange>(finded->second);
        if (intensity < range->getMinIntensity()) {
            range->setMinIntensity(intensity);
        } else if (intensity > range->getMaxIntensity()) {
            range->setMaxIntensity(intensity);
        }
    }
}

void WorkingRangeManager::setElectrophorerWorkingRange(units::ElectricField intensity) {
    auto finded = workingRangeMap.find(Function::electrophoresis);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::electrophoresis,
                                              std::make_shared<ElectrophoresisWorkingRange>(intensity, intensity)));
    } else {
        std::shared_ptr<ElectrophoresisWorkingRange> range = std::dynamic_pointer_cast<ElectrophoresisWorkingRange>(finded->second);
        if (intensity < range->getMinEField()) {
            range->setMinEField(intensity);
        } else if (intensity > range->getMaxEField()) {
            range->setMaxEField(intensity);
        }
    }
}

void WorkingRangeManager::setTemperatureSensorWorkingRange() {
    auto finded = workingRangeMap.find(Function::measure_temperature);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::measure_temperature, std::make_shared<EmptyWorkingRange>()));
    }
}

void WorkingRangeManager::setLuminiscenceSensorWorkingRange() {
    auto finded = workingRangeMap.find(Function::measure_luminiscence);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::measure_luminiscence, std::make_shared<EmptyWorkingRange>()));
    }
}

void WorkingRangeManager::setFluorescenceSensorWorkingRange(units::Length emission, units::Length excitation) {
    auto finded = workingRangeMap.find(Function::measure_fluorescence);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::measure_fluorescence,
                                              std::make_shared<MeasureFluorescenceWorkingRange>(emission, emission, excitation, excitation)));
    } else {
        std::shared_ptr<MeasureFluorescenceWorkingRange> range = std::dynamic_pointer_cast<MeasureFluorescenceWorkingRange>(finded->second);
        if (emission < range->getMinEmission()) {
            range->setMinEmission(emission);
        } else if (emission > range->getMaxEmission()) {
            range->setMaxEmission(emission);
        }

        if (excitation < range->getMinExcitation()) {
            range->setMinExcitation(excitation);
        } else if (excitation > range->getMaxExcitation()) {
            range->setMaxExcitation(excitation);
        }
    }
}

void WorkingRangeManager::setVolumeSensorWorkingRange() {
    auto finded = workingRangeMap.find(Function::measure_volume);
    if (finded == workingRangeMap.end()) {
        workingRangeMap.insert(std::make_pair(Function::measure_volume, std::make_shared<EmptyWorkingRange>()));
    }
}
