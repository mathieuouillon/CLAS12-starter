#pragma once

// <fmt> headers
#include <fmt/core.h>
#include <fmt/ranges.h>

// C++ headers
#include <limits>
#include <map>
#include <unordered_map>
#include <vector>

// Project headers
#include <hipo4/bank.h>

namespace Core {
inline static auto load_bank_by_index(const hipo::bank& from_bank, const std::string& idx) -> std::map<int, std::vector<int>> {
    std::map<int, std::vector<int>> map;
    if (from_bank.getRows() > 0) {
        for (int i_from = 0; i_from < from_bank.getRows(); i_from++) {
            int iTo = from_bank.get<float>(idx.data(), i_from);
            if (!map.contains(iTo)) map.try_emplace(iTo);
            map.at(iTo).emplace_back(i_from);
        }
    }
    return map;
}

struct CherenkovBank {
    int sector = std::numeric_limits<int>::quiet_NaN();
    float nphe = std::numeric_limits<float>::quiet_NaN();
    float time = std::numeric_limits<float>::quiet_NaN();
    float path = std::numeric_limits<float>::quiet_NaN();
    float chi2 = std::numeric_limits<float>::quiet_NaN();
    float x = std::numeric_limits<float>::quiet_NaN();
    float y = std::numeric_limits<float>::quiet_NaN();
    float z = std::numeric_limits<float>::quiet_NaN();
    float dtheta = std::numeric_limits<float>::quiet_NaN();
    float dphi = std::numeric_limits<float>::quiet_NaN();
    int status = std::numeric_limits<int>::quiet_NaN();
};

inline auto read_Cherenkov_bank(const hipo::bank& REC_Cherenkov, const int pindex) -> CherenkovBank {
    auto map = load_bank_by_index(REC_Cherenkov, "pindex");
    CherenkovBank output;

    if (!map.contains(pindex)) return output;

    for (int i : map.at(pindex)) {
        if (REC_Cherenkov.get<int>("detector", i) != 15) continue;
        output.sector = REC_Cherenkov.get<int>("sector", i);
        output.nphe = REC_Cherenkov.get<float>("nphe", i);
        output.time = REC_Cherenkov.get<float>("time", i);
        output.path = REC_Cherenkov.get<float>("path", i);
        output.chi2 = REC_Cherenkov.get<float>("chi2", i);
        output.x = REC_Cherenkov.get<float>("x", i);
        output.y = REC_Cherenkov.get<float>("y", i);
        output.z = REC_Cherenkov.get<float>("z", i);
        output.dtheta = REC_Cherenkov.get<float>("dtheta", i);
        output.dphi = REC_Cherenkov.get<float>("dphi", i);
        output.status = REC_Cherenkov.get<int>("status", i);
    }

    return output;
}

struct CalorimeterStruct {
    int sector = std::numeric_limits<int>::quiet_NaN();
    int layer = std::numeric_limits<int>::quiet_NaN();
    float energy = std::numeric_limits<float>::quiet_NaN();
    float time = std::numeric_limits<float>::quiet_NaN();
    float path = std::numeric_limits<float>::quiet_NaN();
    float chi2 = std::numeric_limits<float>::quiet_NaN();
    float x = std::numeric_limits<float>::quiet_NaN();
    float y = std::numeric_limits<float>::quiet_NaN();
    float z = std::numeric_limits<float>::quiet_NaN();
    float lu = std::numeric_limits<float>::quiet_NaN();
    float lv = std::numeric_limits<float>::quiet_NaN();
    float lw = std::numeric_limits<float>::quiet_NaN();
};

struct CalorimeterBank {
    CalorimeterStruct pcal;
    CalorimeterStruct inner;
    CalorimeterStruct outer;
};

inline auto read_Calorimeter_bank(const hipo::bank& REC_Calorimeter, const int pindex) -> CalorimeterBank {
    auto map = load_bank_by_index(REC_Calorimeter, "pindex");
    CalorimeterBank output;

    if (!map.contains(pindex)) return output;

    // layer:
    // 1 mean preshower calorimeter
    // 4 mean inner calorimeter
    // 7 mean outer calorimeter

    for (int i : map.at(pindex)) {
        if (REC_Calorimeter.get<int>("detector", i) != 7) continue;
        if (REC_Calorimeter.get<int>("layer", i) == 1) {
            output.pcal.sector = REC_Calorimeter.get<int>("sector", i);
            output.pcal.layer = REC_Calorimeter.get<int>("layer", i);
            output.pcal.energy = REC_Calorimeter.get<float>("energy", i);
            output.pcal.time = REC_Calorimeter.get<float>("time", i);
            output.pcal.path = REC_Calorimeter.get<float>("path", i);
            output.pcal.chi2 = REC_Calorimeter.get<float>("chi2", i);
            output.pcal.x = REC_Calorimeter.get<float>("x", i);
            output.pcal.y = REC_Calorimeter.get<float>("y", i);
            output.pcal.z = REC_Calorimeter.get<float>("z", i);
            output.pcal.lu = REC_Calorimeter.get<float>("lu", i);
            output.pcal.lv = REC_Calorimeter.get<float>("lv", i);
            output.pcal.lw = REC_Calorimeter.get<int>("lw", i);
        }
        if (REC_Calorimeter.get<int>("layer", i) == 4) {
            output.inner.sector = REC_Calorimeter.get<int>("sector", i);
            output.inner.layer = REC_Calorimeter.get<int>("layer", i);
            output.inner.energy = REC_Calorimeter.get<float>("energy", i);
            output.inner.time = REC_Calorimeter.get<float>("time", i);
            output.inner.path = REC_Calorimeter.get<float>("path", i);
            output.inner.chi2 = REC_Calorimeter.get<float>("chi2", i);
            output.inner.x = REC_Calorimeter.get<float>("x", i);
            output.inner.y = REC_Calorimeter.get<float>("y", i);
            output.inner.z = REC_Calorimeter.get<float>("z", i);
            output.inner.lu = REC_Calorimeter.get<float>("lu", i);
            output.inner.lv = REC_Calorimeter.get<float>("lv", i);
            output.inner.lw = REC_Calorimeter.get<int>("lw", i);
        }
        if (REC_Calorimeter.get<int>("layer", i) == 7) {
            output.outer.sector = REC_Calorimeter.get<int>("sector", i);
            output.outer.layer = REC_Calorimeter.get<int>("layer", i);
            output.outer.energy = REC_Calorimeter.get<float>("energy", i);
            output.outer.time = REC_Calorimeter.get<float>("time", i);
            output.outer.path = REC_Calorimeter.get<float>("path", i);
            output.outer.chi2 = REC_Calorimeter.get<float>("chi2", i);
            output.outer.x = REC_Calorimeter.get<float>("x", i);
            output.outer.y = REC_Calorimeter.get<float>("y", i);
            output.outer.z = REC_Calorimeter.get<float>("z", i);
            output.outer.lu = REC_Calorimeter.get<float>("lu", i);
            output.outer.lv = REC_Calorimeter.get<float>("lv", i);
            output.outer.lw = REC_Calorimeter.get<int>("lw", i);
        }
    }

    return output;
}

}  // namespace Core
